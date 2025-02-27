/***************************************************************************
 * ROM Properties Page shell extension. (libromdata)                       *
 * Wim.cpp: Microsoft WIM header reader                                    *
 *                                                                         *
 * Copyright (c) 2023 by ecumber.                                          *
 * Copyright (c) 2019-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#include "stdafx.h"
#include "librpbase/config.librpbase.h"

#include "Wim.hpp"
#include "wim_structs.h"

#ifdef ENABLE_XML
// TinyXML2
#  include "tinyxml2.h"
using namespace tinyxml2;
// Character set conversion, needed for TinyXML2
// because WIM uses UTF-16LE manifests.
#  include "librptext/conversion.hpp"
#endif /* ENABLE_XML */

// librpbase, librpfile
#include "librpbase/timeconv.h"
using namespace LibRpText;
using namespace LibRpBase;
using LibRpFile::IRpFile;

// C includes
#include <cuchar>
#include <ctime>

// C++ STL classes
using std::string;

// for convenience
#define rowloop_current_image images[i]
#define rowloop_current_windowsinfo images[i].windowsinfo
#define rowloop_current_windowsver images[i].windowsinfo.version

namespace LibRomData {

class WimPrivate final : public RomDataPrivate
{
	public:
		WimPrivate(LibRpFile::IRpFile* file);  
	private:
		typedef RomDataPrivate super;
		RP_DISABLE_COPY(WimPrivate)

	public:
		/** RomDataInfo **/
		static const char *const exts[];
		static const char *const mimeTypes[];
		static const RomDataInfo romDataInfo;

	public:
		// ROM header
		WIM_Header wimHeader;

		// WIM version
		// NOTE: WIMs pre-1.13 are being detected but won't
		// be read due to the format being different.
		WIM_Version_Type versionType;

	public:
#ifdef ENABLE_XML
		/**
		 * Add fields from the WIM image's XML manifest.
		 * @return 0 on success; non-zero on error.
		 */
		int addFields_XML();
#endif /* ENABLE_XML */
};

ROMDATA_IMPL(Wim)

const char *const WimPrivate::exts[] = {
	".wim",
	".esd",
	".swm",
	// TODO: More?
    nullptr
};

const char *const WimPrivate::mimeTypes[] = {
	// Unofficial MIME types.
	"application/x-ms-wim",
	nullptr
};

const RomDataInfo WimPrivate::romDataInfo = {
	"WIM", exts, mimeTypes
};

struct WimWindowsLanguages {
	std::string language;
	//std::string default_language;	//not used right now
};

struct WimWindowsVersion {
	unsigned int majorversion = 0;
	unsigned int minorversion = 0;
	unsigned int buildnumber = 0;
	unsigned int spbuildnumber = 0;
	unsigned int splevel = 0; // only in windows 7+, added some time around build 6608-6730
};

struct WimWindowsInfo {
	WimWindowsArchitecture arch = Wim_Arch_x86;
	std::string productname, editionid, installationtype, hal, producttype, productsuite;
	WimWindowsLanguages languages;
	WimWindowsVersion version;
	std::string systemroot;
};

struct WimIndex {
	// if you have more than 2^32 indices in a wim
	// you probably have bigger issues
	uint32_t index = 0;
	uint64_t dircount = 0;
	uint64_t filecount = 0;
	uint64_t totalbytes = 0;
	//time_t creationtime = 0;	// not used right now
	time_t lastmodificationtime = 0;
	WimWindowsInfo windowsinfo;
	std::string name, description, flags, dispname, dispdescription;
	bool containswindowsimage = false;
};

#ifdef ENABLE_XML
/**
 * Add fields from the WIM image's XML manifest.
 * @return 0 on success; non-zero on error.
 */
int WimPrivate::addFields_XML() 
{
	if (!file || !file->isOpen()) {
		return -EIO;
	}

	// the eighth byte of the "size" is used for flags so we have to AND it
	const uint64_t size = (wimHeader.xml_resource.size & 0x00FFFFFFFFFFFFFF);
	if (size > 16U*1024*1024) {
		// XML is larger than 16 MB, which doesn't make any sense.
		return -ENOMEM;
	}

	// Read the WIM XML data.
	char *xml_data = new char[size+2];
	memset(xml_data, 0, size+2);
	file->rewind();
	file->seek(wimHeader.xml_resource.offset_of_xml); 
	// if seek is invalid
	if (file->tell() != (off64_t)wimHeader.xml_resource.offset_of_xml) {
		return -EIO;
	}

	size_t bytes_read = file->read(xml_data, size);
	if (bytes_read != size) {
		return -EIO;
	}

	// the xml inside wims are utf-16 but tinyxml only supports utf-8
	// this means we have to do some conversion
	std::string utf8_xml = LibRpText::utf16le_to_utf8(reinterpret_cast<char16_t*>(xml_data), (int)((size / 2) + 1));
	delete[] xml_data;

	XMLDocument document;
	int xerr = document.Parse(utf8_xml.c_str(), utf8_xml.size());
	if (xerr != XML_SUCCESS) {
		return 3;
	}

	const XMLElement *const wim_element = document.FirstChildElement("WIM");
	if (!wim_element) {
		// No wim element.
		// TODO: Better error code.
		return -EIO;
	}

	std::vector<WimIndex> images(0);
	images.reserve(wimHeader.number_of_images);
	const XMLElement *currentimage = wim_element->FirstChildElement("IMAGE");

	const char *const s_unknown = C_("Wim", "(unknown)");
	for (uint32_t i = 0; i <= wimHeader.number_of_images-1; i++) {
		WimIndex currentindex;
		currentindex.index = i + 1;

		assert(currentimage != nullptr);
		if (!currentimage)
			break;

		// the last modification time is split into a high part and a
		// low part so we shift and add them together
		const XMLElement *const creationTime = currentimage->FirstChildElement("CREATIONTIME");
		if (creationTime) {
			const XMLElement *const highPart = creationTime->FirstChildElement("HIGHPART");
			const XMLElement *const lowPart = creationTime->FirstChildElement("LOWPART");
			if (highPart && lowPart) {
				const char *const s_highPart = highPart->GetText();
				const char *const s_lowPart = lowPart->GetText();
				if (s_highPart && s_lowPart) {
					// Parse HIGHPART and LOWPART, then combine them like FILETIME.
					const uint32_t lastmodtime_high = strtoul(s_highPart, nullptr, 16);
					const uint32_t lastmodtime_low = strtoul(s_highPart, nullptr, 16);
					currentindex.lastmodificationtime = WindowsSplitTimeToUnixTime(lastmodtime_high, lastmodtime_low);
				}
			}
		}

		const XMLElement *const windowsinfo = currentimage->FirstChildElement("WINDOWS");
		if (windowsinfo) {
			currentindex.containswindowsimage = true;
			const XMLElement *const arch = windowsinfo->FirstChildElement("ARCH");
			if (arch) {
				currentindex.windowsinfo.arch = static_cast<WimWindowsArchitecture>(arch->IntText(0));
			}

			const XMLElement *const editionId = windowsinfo->FirstChildElement("EDITIONID");
			if (editionId) {
				const char *s_editionId = windowsinfo->FirstChildElement("EDITIONID")->GetText();
				currentindex.windowsinfo.editionid = (s_editionId ? s_editionId : s_unknown);
			} else {
				currentindex.windowsinfo.editionid = s_unknown;
			}

			const XMLElement *const languages = windowsinfo->FirstChildElement("LANGUAGES");
			if (languages) {
				// NOTE: Only retrieving the first language.
				const XMLElement *const language = languages->FirstChildElement("LANGUAGE");
				if (language) {
					const char *s_language = language->GetText();
					if (s_language) {
						currentindex.windowsinfo.languages.language = s_language;
					}
				}
			}
			if (currentindex.windowsinfo.languages.language.empty()) {
				currentindex.windowsinfo.languages.language = s_unknown;
			}

			const XMLElement *const version = windowsinfo->FirstChildElement("VERSION");
			if (version) {
				const XMLElement *const ver_major = version->FirstChildElement("MAJOR");
				if (ver_major) {
					currentindex.windowsinfo.version.majorversion = ver_major->IntText(0);
				}
				const XMLElement *const ver_minor = version->FirstChildElement("MINOR");
				if (ver_minor) {
					currentindex.windowsinfo.version.minorversion = ver_minor->IntText(0);
				}
				const XMLElement *const ver_build = version->FirstChildElement("BUILD");
				if (ver_build) {
					currentindex.windowsinfo.version.buildnumber = ver_build->IntText(0);
				}
				const XMLElement *const ver_spbuild = version->FirstChildElement("SPBUILD");
				if (ver_spbuild) {
					currentindex.windowsinfo.version.spbuildnumber = ver_spbuild->IntText(0);
				}
			}
		} else {
			currentindex.containswindowsimage = false;
		}

		// some wims don't have these fields, so we
		// need to set up fallbacks - the hierarchy goes
		// display name -> name -> "(None)"
		const char *const s_none = C_("Wim", "(none)");
		const XMLElement *const elem_name = currentimage->FirstChildElement("NAME");
		if (elem_name) {
			const char *const s_name = elem_name->GetText();
			currentindex.name = (s_name ? s_name : s_none);
		}
		const XMLElement *const elem_desc = currentimage->FirstChildElement("DESCRIPTION");
		if (elem_desc) {
			const char *const s_desc = elem_desc->GetText();
			currentindex.description = (s_desc ? s_desc : s_none);
		}
		const XMLElement *const elem_dispName = currentimage->FirstChildElement("DISPLAYNAME");
		if (elem_dispName) {
			const char *const s_dispName = elem_dispName->GetText();
			currentindex.dispname = (s_dispName ? s_dispName : s_none);
		}
		const XMLElement *const elem_dispDesc = currentimage->FirstChildElement("DISPLAYDESCRIPTION");
		if (elem_dispDesc) {
			const char *const s_dispDesc = elem_dispDesc->GetText();
			currentindex.dispdescription = (s_dispDesc ? s_dispDesc : s_none);
		}

		images.emplace_back(std::move(currentindex));
		currentimage = currentimage->NextSiblingElement();
	}

	auto vv_data = new RomFields::ListData_t();
	vv_data->reserve(10);

	char timestamp[20];
	tm* tm_struct;
	// loop for the rows
	for (uint32_t i = 0; i <= wimHeader.number_of_images-1; i++) {
		vv_data->resize(vv_data->size()+1);
		auto &data_row = vv_data->at(vv_data->size()-1);
		data_row.emplace_back(rp_sprintf("%u", i + 1));
		data_row.emplace_back(rowloop_current_image.name);
		data_row.emplace_back(rowloop_current_image.description);
		data_row.emplace_back(rowloop_current_image.dispname);
		data_row.emplace_back(rowloop_current_image.dispdescription);

		// FIXME: Using our own timestamp formatting instead of the system locale.
		// Can't easily specify time values in RFT_LISTDATA...
		tm_struct = localtime(&rowloop_current_image.lastmodificationtime);
		std::strftime(timestamp, 20, "%Y-%m-%d %R", tm_struct);
		data_row.emplace_back(timestamp);

		if (images[i].containswindowsimage == false)
			continue;
		
		data_row.emplace_back(
			rp_sprintf("%u.%u.%u.%u", rowloop_current_windowsver.majorversion,
				rowloop_current_windowsver.minorversion, rowloop_current_windowsver.buildnumber,
				rowloop_current_windowsver.spbuildnumber)); 
		data_row.emplace_back(rowloop_current_windowsinfo.editionid);
		const char *archstring;
		switch (rowloop_current_windowsinfo.arch) {
			default:
				archstring = nullptr;
				break;
			case Wim_Arch_x86:
				archstring = "x86";
				break;
			case Wim_Arch_ARM32:
				archstring = "ARM32";
				break;
			case Wim_Arch_IA64:
				archstring = "IA64";
				break;
			case Wim_Arch_AMD64:
				archstring = "x64";
				break;
			case Wim_Arch_ARM64:
				archstring = "ARM64";
				break;
		}
		if (archstring) {
			data_row.emplace_back(archstring);
		} else {
			data_row.emplace_back(rp_sprintf(C_("RomData", "Unknown (%u)"), rowloop_current_windowsinfo.arch));
		}
		data_row.emplace_back(rowloop_current_windowsinfo.languages.language);
	}	

	static const char *const field_names[] = {
		NOP_C_("Wim|Images", "#"),
		NOP_C_("Wim|Images", "Name"),
		NOP_C_("Wim|Images", "Description"),
		NOP_C_("Wim|Images", "Display Name"),
		NOP_C_("Wim|Images", "Display Desc."),
		NOP_C_("Wim|Images", "Last Modified"),
		NOP_C_("Wim|Images", "OS Version"),
		NOP_C_("Wim|Images", "Edition"),
		NOP_C_("Wim|Images", "Architecture"),
		NOP_C_("Wim|Images", "Language"),
	};
	std::vector<std::string>* const v_field_names = RomFields::strArrayToVector_i18n(
		"Wim|Images", field_names, ARRAY_SIZE(field_names));

	RomFields::AFLD_PARAMS params;
	params.flags = RomFields::RFT_LISTDATA_SEPARATE_ROW;
	params.headers = v_field_names;
	params.data.single = vv_data;
	// TODO: Header alignment?
	fields.addField_listData(C_("Wim", "Images"), &params);

	return 0;
}
#endif /* ENABLE_XML */

WimPrivate::WimPrivate(LibRpFile::IRpFile* file)
    : super(file, &romDataInfo)
{ 
	// Clear the WIM header struct.
	memset(&wimHeader, 0, sizeof(wimHeader));
}

int Wim::isRomSupported_static(const DetectInfo* info)
{
	assert(info != nullptr);
	assert(info->header.pData != nullptr);
	if (!info || !info->header.pData) {
		// No detection information.
		return -1;
	}

	const WIM_Header* const wimData = reinterpret_cast<const WIM_Header*>(info->header.pData);
	int ret = Wim_Unknown;

	// TODO: WLPWM_MAGIC
	if (!memcmp(wimData->magic, MSWIM_MAGIC, 8)) {
		// at least a wim 1.09, check the version
		// we do not necessarily need to check the
		// major version because it is always 
		// either 1 or 0 (in the case of esds)
		if (wimData->version.minor_version >= 13) {
			ret = Wim113_014;
		} else{ 
			ret = Wim109_112;
		}
	} else if (!memcmp(wimData->magic, MSWIMOLD_MAGIC, 4)) {
		// NOTE: This magic number is too generic.
		// Verify the file extension.
		if (info->ext && !strcasecmp(info->ext, ".wim")) {
			ret = Wim107_108;
		}
	}

	return ret;
}

Wim::Wim(LibRpFile::IRpFile* file)
	: super(new WimPrivate(file))
{
	RP_D(Wim);
	d->mimeType = "application/x-ms-wim";
	d->fileType = FileType::DiskImage;

	if (!d->file) {
		// Could not ref() the file handle.
		return;
	}

	// Seek to the beginning of the header.
	d->file->rewind();

	// Read the Wim header.
	size_t size = d->file->read(&d->wimHeader, sizeof(d->wimHeader));
	if (size != sizeof(d->wimHeader)) {
		UNREF_AND_NULL_NOCHK(d->file);
		return;
	}

	// Check if this Wim is supported.
	const DetectInfo info = {
		{0, sizeof(d->wimHeader), reinterpret_cast<const uint8_t*>(&d->wimHeader)},
		nullptr,	// ext (not needed for Wim)
		0		// szFile (not needed for Wim)
	};
	d->versionType = static_cast<WIM_Version_Type>(isRomSupported_static(&info));

	d->isValid = ((int)d->versionType >= 0);
	if (!d->isValid) {
		UNREF_AND_NULL_NOCHK(d->file);
		return;
	}

#if SYS_BYTEORDER == SYS_BIG_ENDIAN
	// Byteswap the WIM header.
	d->wimHeader.header_size	= le32_to_cpu(d->wimHeader.header_size);
	d->wimHeader.flags		= le32_to_cpu(d->wimHeader.flags);
	d->wimHeader.chunk_size		= le32_to_cpu(d->wimHeader.chunk_size);
	d->wimHeader.part_number	= le16_to_cpu(d->wimHeader.part_number);
	d->wimHeader.total_parts	= le16_to_cpu(d->wimHeader.total_parts);
	d->wimHeader.number_of_images	= le32_to_cpu(d->wimHeader.number_of_images);
	d->wimHeader.bootable_index	= le32_to_cpu(d->wimHeader.bootable_index);

	// Byteswap WIM_File_Resource objects.
	auto do_wfr_byteswap = [](WIM_File_Resource &wfr) {
		wfr.size          = le64_to_cpu(wfr.size);
		wfr.offset_of_xml = le64_to_cpu(wfr.offset_of_xml);
		wfr.not_important = le64_to_cpu(wfr.not_important);
	};
	do_wfr_byteswap(d->wimHeader.offset_table);
	do_wfr_byteswap(d->wimHeader.xml_resource);
	do_wfr_byteswap(d->wimHeader.boot_metadata_resource);
	do_wfr_byteswap(d->wimHeader.integrity_resource);
#endif /* SYS_BYTEORDER == SYS_BIG_ENDIAN */

	if (d->versionType == WIM_Version_Type::Wim107_108) {
		// the version offset is different so we have to get creative
		d->wimHeader.version.major_version = d->wimHeader.magic[6];
		d->wimHeader.version.minor_version = d->wimHeader.magic[5];
	}
}

const char* Wim::systemName(unsigned int type) const
{
	RP_D(const Wim);
	if (!d->isValid || !isSystemNameTypeValid(type))
		return nullptr;

	static_assert(SYSNAME_TYPE_MASK == 3,
		"Wim::systemName() array index optimization needs to be updated.");

	static const char *const sysNames[4] = {
		"Microsoft WIM",
		"WIM Image",
		"WIM",
		nullptr
	};

	return sysNames[type & SYSNAME_TYPE_MASK];
}

int Wim::loadFieldData(void)
{
	RP_D(Wim);
	if (!d->fields.empty()) {
		// Field data *has* been loaded...
		return 0;
	} else if (!d->file) {
		// File isn't open.
		return -EBADF;
	} else if (!d->isValid) {
		// Unknown ROM image type.
		return -EIO;
	}

	d->fields.reserve(6);	// Maximum of 6 fields. (5 if XML is disabled)
	char buffer[32];

	// if the version number is 14, add an indicator that it is an ESD
	if (d->wimHeader.version.minor_version == 14) {
		snprintf(buffer, sizeof(buffer), "%u.%02u (ESD)",
			d->wimHeader.version.major_version, d->wimHeader.version.minor_version);
	} else {
		snprintf(buffer, sizeof(buffer), "%u.%02u",
			d->wimHeader.version.major_version, d->wimHeader.version.minor_version);
	}
	d->fields.addField_string(C_("Wim", "WIM Version"), buffer, RomFields::STRF_TRIM_END);

	if (d->versionType != Wim113_014) {
		// The rest of the fields require Wim113_014 or later.
		return 0;
	}

	static const char* const wim_flag_names[] = {
		nullptr,
		NOP_C_("Wim|Flags", "Compressed"),
		NOP_C_("Wim|Flags", "Read-only"),
		NOP_C_("Wim|Flags", "Spanned"),
		NOP_C_("Wim|Flags", "Resource Only"),
		NOP_C_("Wim|Flags", "Metadata Only"),
		NOP_C_("Wim|Flags", "Write in progress"),
	};

	uint32_t wimflags = le32_to_cpu(d->wimHeader.flags);

	std::vector<std::string> *const v_wim_flag_names = RomFields::strArrayToVector_i18n(
		"RomData", wim_flag_names, ARRAY_SIZE(wim_flag_names));
	d->fields.addField_bitfield(C_("Wim", "Flags"),
		v_wim_flag_names, 3, wimflags);

	// loop through each compression flag and test if it is set
	int i;
	for (i = compress_xpress; i <= compress_xpress2; i = i << 1) {
		if (wimflags & i)
			break;
	}

	const char *compression_method;
	switch (i)  {
		case compress_xpress:
			compression_method = "XPRESS";
			break;
		case compress_lzx:
			compression_method = "LZX";
			break;
		case compress_lzms:
			compression_method = "LZMS";
			break;
		case compress_xpress2:
			compression_method = "XPRESS2";
			break;
		default:
			// if it has compression but the algorithm isn't 
			// accounted for, say it's unknown
			compression_method = (wimflags & has_compression)
				? C_("RomData", "Unknown")
				: C_("RomData", "None");
			break;
	}
	d->fields.addField_string(C_("Wim", "Compression Method"), compression_method);
	d->fields.addField_string(C_("Wim", "Part Number"),
		rp_sprintf("%u/%u", d->wimHeader.part_number, d->wimHeader.total_parts));
	d->fields.addField_string_numeric(C_("Wim", "Total Images"), d->wimHeader.number_of_images);

#ifdef ENABLE_XML
	// Add fields from the WIM image's XML manifest.
	d->addFields_XML();
#endif /* ENABLE_XML */

	return 0;
}

}