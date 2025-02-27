/***************************************************************************
 * ROM Properties Page shell extension. (libromdata)                       *
 * WbfsReader.cpp: WBFS disc image reader.                                 *
 *                                                                         *
 * Copyright (c) 2016-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#include "stdafx.h"
#include "WbfsReader.hpp"
#include "librpbase/disc/SparseDiscReader_p.hpp"
#include "libwbfs.h"

// librpbase, librpfile
using namespace LibRpBase;
using LibRpFile::IRpFile;

namespace LibRomData {

class WbfsReaderPrivate final : public SparseDiscReaderPrivate {
	public:
		explicit WbfsReaderPrivate(WbfsReader *q);
		~WbfsReaderPrivate() final;

	private:
		typedef SparseDiscReaderPrivate super;
		RP_DISABLE_COPY(WbfsReaderPrivate)

	public:
		// WBFS structs.
		wbfs_t *m_wbfs;			// WBFS image.
		wbfs_disc_t *m_wbfs_disc;	// Current disc.

		const be16_t *wlba_table;	// Pointer to m_wbfs_disc->disc->header->wlba_table.

		/** WBFS functions. **/

		/**
		 * Read the WBFS header.
		 * @return Allocated wbfs_t on success; nullptr on error.
		 */
		wbfs_t *readWbfsHeader(void);

		/**
		 * Free an allocated WBFS header.
		 * This frees all associated structs.
		 * All opened discs *must* be closed.
		 * @param p wbfs_t struct.
		 */
		void freeWbfsHeader(wbfs_t *p);

		/**
		 * Open a disc from the WBFS image.
		 * @param p wbfs_t struct.
		 * @param index Disc index.
		 * @return Allocated wbfs_disc_t on success; nullptr on error.
		 */
		wbfs_disc_t *openWbfsDisc(wbfs_t *p, uint32_t index);

		/**
		 * Close a WBFS disc.
		 * This frees all associated structs.
		 * @param disc wbfs_disc_t.
		 */
		void closeWbfsDisc(wbfs_disc_t *disc);

		/**
		 * Get the non-sparse size of an open WBFS disc, in bytes.
		 * This scans the block table to find the first block
		 * from the end of wlba_table[] that has been allocated.
		 * @param disc wbfs_disc_t struct.
		 * @return Non-sparse size, in bytes.
		 */
		off64_t getWbfsDiscSize(const wbfs_disc_t *disc) const;
};

/** WbfsReaderPrivate **/

WbfsReaderPrivate::WbfsReaderPrivate(WbfsReader *q)
	: super(q)
	, m_wbfs(nullptr)
	, m_wbfs_disc(nullptr)
	, wlba_table(nullptr)
{ }

WbfsReaderPrivate::~WbfsReaderPrivate()
{
	if (m_wbfs_disc) {
		closeWbfsDisc(m_wbfs_disc);
	}
	if (m_wbfs) {
		freeWbfsHeader(m_wbfs);
	}
}

// from libwbfs.c
// TODO: Optimize this?
static inline uint8_t size_to_shift(uint32_t size)
{
	uint8_t ret = 0;
	while (size) {
		ret++;
		size >>= 1;
	}
	return ret-1;
}

#define ALIGN_LBA(x) (((x)+p->hd_sec_sz-1)&(~(size_t)(p->hd_sec_sz-1)))

/**
 * Read the WBFS header.
 * @return Allocated wbfs_t on success; nullptr on error.
 */
wbfs_t *WbfsReaderPrivate::readWbfsHeader(void)
{
	// Assume 512-byte sectors initially.
	unsigned int hd_sec_sz = 512;
	wbfs_head_t *head = static_cast<wbfs_head_t*>(malloc(hd_sec_sz));
	if (!head) {
		// ENOMEM
		return nullptr;
	}

	// Read the WBFS header.
	RP_Q(WbfsReader);
	q->m_file->rewind();
	size_t size = q->m_file->read(head, hd_sec_sz);
	if (size != hd_sec_sz) {
		// Read error.
		free(head);
		return nullptr;
	}

	// Check the WBFS magic.
	if (head->magic != cpu_to_be32(WBFS_MAGIC)) {
		// Invalid WBFS magic.
		// TODO: Better error code?
		free(head);
		return nullptr;
	}

	// Parse the header.
	// Based on libwbfs.c's wbfs_open_partition().

	// wbfs_t struct.
	wbfs_t *p = static_cast<wbfs_t*>(malloc(sizeof(wbfs_t)));
	if (!p) {
		// ENOMEM
		free(head);
		return nullptr;
	}

	// Since this is a disc image, we don't know the HDD sector size.
	// Use the value present in the header.
	if (head->hd_sec_sz_s < 0x09) {
		// Sector size is less than 512 bytes.
		// This isn't possible unless you're using
		// a Commodore 64 or an Apple ][.
		free(head);
		free(p);
		return nullptr;
	}
	p->hd_sec_sz = (1U << head->hd_sec_sz_s);
	p->hd_sec_sz_s = head->hd_sec_sz_s;
	p->n_hd_sec = be32_to_cpu(head->n_hd_sec);	// TODO: Use file size?

	// If the sector size is wrong, reallocate and reread.
	if (p->hd_sec_sz != hd_sec_sz) {
		hd_sec_sz = p->hd_sec_sz;
		free(head);
		head = static_cast<wbfs_head_t*>(malloc(hd_sec_sz));
		if (!head) {
			// ENOMEM
			free(p);
			return nullptr;
		}

		// Re-read the WBFS header.
		q->m_file->rewind();
		size = q->m_file->read(head, hd_sec_sz);
		if (size != hd_sec_sz) {
			// Read error.
			// TODO: Return errno?
			free(head);
			free(p);
			return nullptr;
		}
	}

	// Save the wbfs_head_t in the wbfs_t struct.
	p->head = head;

	// Constants.
	p->wii_sec_sz = 0x8000;
	p->wii_sec_sz_s = size_to_shift(0x8000);
	p->n_wii_sec = (p->n_hd_sec/0x8000)*p->hd_sec_sz;
	p->n_wii_sec_per_disc = 143432*2;	// support for dual-layer discs

	// WBFS sector size.
	p->wbfs_sec_sz_s = head->wbfs_sec_sz_s;
	p->wbfs_sec_sz = (1U << head->wbfs_sec_sz_s);

	// Disc size.
	p->n_wbfs_sec = p->n_wii_sec >> (p->wbfs_sec_sz_s - p->wii_sec_sz_s);
	p->n_wbfs_sec_per_disc = p->n_wii_sec_per_disc >> (p->wbfs_sec_sz_s - p->wii_sec_sz_s);
	p->disc_info_sz = static_cast<uint16_t>(ALIGN_LBA(sizeof(wbfs_disc_info_t) + p->n_wbfs_sec_per_disc*2));

	// Free blocks table.
	p->freeblks_lba = (p->wbfs_sec_sz - p->n_wbfs_sec/8) >> p->hd_sec_sz_s;
	p->freeblks = nullptr;
	p->max_disc = (p->freeblks_lba-1) / (p->disc_info_sz >> p->hd_sec_sz_s);
	if (p->max_disc > (p->hd_sec_sz - sizeof(wbfs_head_t)))
		p->max_disc = static_cast<uint16_t>(p->hd_sec_sz - sizeof(wbfs_head_t));

	p->n_disc_open = 0;
	return p;
}

/**
 * Free an allocated WBFS header.
 * This frees all associated structs.
 * All opened discs *must* be closed.
 * @param p wbfs_t struct.
 */
void WbfsReaderPrivate::freeWbfsHeader(wbfs_t *p)
{
	assert(p != nullptr);
	assert(p->head != nullptr);
	assert(p->n_disc_open == 0);

	// Free everything.
	free(p->head);
	free(p);
}

/**
 * Open a disc from the WBFS image.
 * @param p wbfs_t struct.
 * @param index Disc index.
 * @return Allocated wbfs_disc_t on success; non-zero on error.
 */
wbfs_disc_t *WbfsReaderPrivate::openWbfsDisc(wbfs_t *p, uint32_t index)
{
	// Based on libwbfs.c's wbfs_open_disc()
	// and wbfs_get_disc_info().
	RP_Q(WbfsReader);
	const wbfs_head_t *const head = p->head;
	uint32_t count = 0;
	for (uint32_t i = 0; i < p->max_disc; i++) {
		if (head->disc_table[i]) {
			if (count++ == index) {
				// Found the disc table index.
				wbfs_disc_t *disc = static_cast<wbfs_disc_t*>(malloc(sizeof(wbfs_disc_t)));
				if (!disc) {
					// ENOMEM
					return nullptr;
				}
				disc->p = p;
				disc->i = i;

				// Read the disc header.
				disc->header = static_cast<wbfs_disc_info_t*>(malloc(p->disc_info_sz));
				if (!disc->header) {
					// ENOMEM
					free(disc);
					return nullptr;
				}
				size_t size = q->m_file->seekAndRead((p->hd_sec_sz + (i*p->disc_info_sz)),
					disc->header, p->disc_info_sz);
				if (size != p->disc_info_sz) {
					// Error reading the disc information.
					free(disc->header);
					free(disc);
					return nullptr;
				}

				// TODO: Byteswap wlba_table[] here?
				// Removes unnecessary byteswaps when reading,
				// but may not be necessary if we're not reading
				// the entire disc.

				// Disc information read successfully.
				p->n_disc_open++;
				return disc;
			}
		}
	}

	// Disc not found.
	return nullptr;
}

/**
 * Close a WBFS disc.
 * This frees all associated structs.
 * @param disc wbfs_disc_t.
 */
void WbfsReaderPrivate::closeWbfsDisc(wbfs_disc_t *disc)
{
	assert(disc != nullptr);
	assert(disc->p != nullptr);
	assert(disc->p->n_disc_open > 0);
	assert(disc->header != nullptr);

	// Free the disc.
	disc->p->n_disc_open--;
	free(disc->header);
	free(disc);
}

/**
 * Get the non-sparse size of an open WBFS disc, in bytes.
 * This scans the block table to find the first block
 * from the end of wlba_table[] that has been allocated.
 * @param disc wbfs_disc_t struct.
 * @return Non-sparse size, in bytes.
 */
off64_t WbfsReaderPrivate::getWbfsDiscSize(const wbfs_disc_t *disc) const
{
	// Find the last block that's used on the disc.
	// NOTE: This is in WBFS blocks, not Wii blocks.
	const wbfs_t *const p = disc->p;
	int lastBlock = p->n_wbfs_sec_per_disc - 1;
	for (; lastBlock >= 0; lastBlock--) {
		if (wlba_table[lastBlock] != cpu_to_be16(0))
			break;
	}

	// lastBlock+1 * WBFS block size == filesize.
	return (static_cast<off64_t>(lastBlock) + 1) * static_cast<off64_t>(p->wbfs_sec_sz);
}

/** WbfsReader **/

WbfsReader::WbfsReader(IRpFile *file)
	: super(new WbfsReaderPrivate(this), file)
{
	if (!m_file) {
		// File could not be ref()'d.
		return;
	}

	// Read the WBFS header.
	RP_D(WbfsReader);
	d->m_wbfs = d->readWbfsHeader();
	if (!d->m_wbfs) {
		// Error reading the WBFS header.
		UNREF_AND_NULL_NOCHK(m_file);
		m_lastError = EIO;
		return;
	}

	// Open the first disc.
	d->m_wbfs_disc = d->openWbfsDisc(d->m_wbfs, 0);
	if (!d->m_wbfs_disc) {
		// Error opening the WBFS disc.
		d->freeWbfsHeader(d->m_wbfs);
		d->m_wbfs = nullptr;
		UNREF_AND_NULL_NOCHK(m_file);
		m_lastError = EIO;
		return;
	}

	// Save important values for later.
	d->wlba_table = d->m_wbfs_disc->header->wlba_table;
	d->block_size = d->m_wbfs->wbfs_sec_sz;
	d->pos = 0;	// Reset the read position.

	// Get the size of the WBFS disc.
	d->disc_size = d->getWbfsDiscSize(d->m_wbfs_disc);
}

/**
 * Is a disc image supported by this class?
 * @param pHeader Disc image header.
 * @param szHeader Size of header.
 * @return Class-specific disc format ID (>= 0) if supported; -1 if not.
 */
int WbfsReader::isDiscSupported_static(const uint8_t *pHeader, size_t szHeader)
{
	if (szHeader < sizeof(wbfs_head_t))
		return -1;

	const wbfs_head_t *head = reinterpret_cast<const wbfs_head_t*>(pHeader);
	if (head->magic != cpu_to_be32(WBFS_MAGIC)) {
		// Incorrect magic number.
		return -1;
	}

	// Make sure the sector size is at least 512 bytes.
	if (head->hd_sec_sz_s < 0x09) {
		// Sector size is less than 512 bytes.
		// This isn't possible unless you're using
		// a Commodore 64 or an Apple ][.
		return -1;
	}

	// This is a valid WBFS image.
	return 0;
}

/**
 * Is a disc image supported by this object?
 * @param pHeader Disc image header.
 * @param szHeader Size of header.
 * @return Class-specific system ID (>= 0) if supported; -1 if not.
 */
int WbfsReader::isDiscSupported(const uint8_t *pHeader, size_t szHeader) const
{
	return isDiscSupported_static(pHeader, szHeader);
}

/** SparseDiscReader functions. **/

/**
 * Get the physical address of the specified logical block index.
 *
 * @param blockIdx	[in] Block index.
 * @return Physical address. (0 == empty block; -1 == invalid block index)
 */
off64_t WbfsReader::getPhysBlockAddr(uint32_t blockIdx) const
{
	// Make sure the block index is in range.
	RP_D(const WbfsReader);
	assert(blockIdx < d->m_wbfs_disc->p->n_wbfs_sec_per_disc);
	if (blockIdx >= d->m_wbfs_disc->p->n_wbfs_sec_per_disc) {
		// Out of range.
		return -1;
	}

	// Get the physical block index.
	const unsigned int physBlockIdx = be16_to_cpu(d->wlba_table[blockIdx]);
	if (physBlockIdx == 0) {
		// Empty block.
		return 0;
	}

	// Convert to a physical block address and return.
	return (static_cast<off64_t>(physBlockIdx) * d->block_size);
}

}
