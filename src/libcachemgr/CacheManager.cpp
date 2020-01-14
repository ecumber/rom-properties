/***************************************************************************
 * ROM Properties Page shell extension. (libcachemgr)                      *
 * CacheManager.cpp: Local cache manager.                                  *
 *                                                                         *
 * Copyright (c) 2016-2020 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#ifdef _WIN32
# include "stdafx.h"
#endif
#include "CacheManager.hpp"

// librpbase
#include "librpbase/file/RpFile.hpp"
#include "librpbase/file/FileSystem.hpp"
using namespace LibRpBase;
using namespace LibRpBase::FileSystem;

// libcachecommon
#include "cache_common.hpp"

// Windows includes.
#ifdef _WIN32
# include "libwin32common/RpWin32_sdk.h"
#endif /* _WIN32 */

// C includes. (C++ namespace)
#include <ctime>

// C++ includes.
#include <string>
using std::string;

// TODO: DownloaderFactory?
#ifdef _WIN32
# include "UrlmonDownloader.hpp"
#else
# include "CurlDownloader.hpp"
#endif

namespace LibCacheMgr {

// Semaphore used to limit the number of simultaneous downloads.
// TODO: Determine the best number of simultaneous downloads.
// TODO: Test this on XP with IEIFLAG_ASYNC.
Semaphore CacheManager::m_dlsem(2);

CacheManager::CacheManager()
{
	// TODO: DownloaderFactory?
#ifdef _WIN32
	m_downloader = new UrlmonDownloader();
#else
	m_downloader = new CurlDownloader();
#endif

	// TODO: Configure this somewhere?
	m_downloader->setMaxSize(4*1024*1024);
}

CacheManager::~CacheManager()
{
	delete m_downloader;
}

/** Proxy server functions. **/
// NOTE: This is only useful for downloaders that
// can't retrieve the system proxy server normally.

/**
 * Get the proxy server.
 * @return Proxy server URL.
 */
string CacheManager::proxyUrl(void) const
{
	return m_proxyUrl;
}

/**
 * Set the proxy server.
 * @param proxyUrl Proxy server URL. (Use nullptr or blank string for default settings.)
 */
void CacheManager::setProxyUrl(const char *proxyUrl)
{
	if (proxyUrl) {
		m_proxyUrl = proxyUrl;
	} else {
		m_proxyUrl.clear();
	}
}

/**
 * Set the proxy server.
 * @param proxyUrl Proxy server URL. (Use blank string for default settings.)
 */
void CacheManager::setProxyUrl(const string &proxyUrl)
{
	m_proxyUrl = proxyUrl;
}

/**
 * Download a file.
 *
 * @param url URL.
 * @param cache_key Cache key.
 *
 * If the file is present in the cache, the cached version
 * will be retrieved. Otherwise, the file will be downloaded.
 *
 * If the file was not found on the server, or it was not found
 * the last time it was requested, an empty string will be
 * returned, and a zero-byte file will be stored in the cache.
 *
 * @return Absolute path to the cached file.
 */
string CacheManager::download(
	const string &url,
	const string &cache_key)
{
	// Check the main cache key.
	string cache_filename = LibCacheCommon::getCacheFilename(cache_key);
	if (cache_filename.empty()) {
		// Error obtaining the cache key filename.
		return string();
	}

	// Lock the semaphore to make sure we don't
	// download too many files at once.
	SemaphoreLocker locker(m_dlsem);

	// Check if the file already exists.
	if (!access(cache_filename, R_OK)) {
		// File exists.
		// Is it larger than 0 bytes?
		int64_t sz = filesize(cache_filename);
		if (sz == 0) {
			// File is 0 bytes, which indicates it didn't exist
			// on the server. If the file is older than a week,
			// try to redownload it.
			// TODO: Configurable time.
			// TODO: How should we handle errors?
			time_t filetime;
			if (get_mtime(cache_filename, &filetime) != 0)
				return string();

			const time_t systime = time(nullptr);
			if ((systime - filetime) < (86400*7)) {
				// Less than a week old.
				return string();
			}

			// More than a week old.
			// Delete the cache file and redownload it.
			if (delete_file(cache_filename) != 0)
				return string();
		} else if (sz > 0) {
			// File is larger than 0 bytes, which indicates
			// it was cached successfully.
			return cache_filename;
		}
	}

	// Check if the URL is blank.
	// This is allowed for some databases that are only available offline.
	if (url.empty()) {
		// Blank URL. Don't try to download anything.
		// Don't mark the file as unavailable by creating a
		// 0-byte dummy file, either.
		return string();
	}

	// Make sure the subdirectories exist.
	// NOTE: The filename portion MUST be kept in cache_filename,
	// since the last component is ignored by rmkdir().
	if (rmkdir(cache_filename) != 0) {
		// Error creating subdirectories.
		return string();
	}

	// TODO: Keep-alive cURL connections (one per server)?
	m_downloader->setUrl(url);
	m_downloader->setProxyUrl(m_proxyUrl);
	int ret = m_downloader->download();

	// Write the file to the cache.
	RpFile *const file = new RpFile(cache_filename, RpFile::FM_CREATE_WRITE);
	if (ret != 0 || !file->isOpen()) {
		// Error downloading the file, or error opening
		// the file in the local cache.
		file->unref();

		// TODO: Only keep a negative cache if it's a 404.
		// Keep the cached file as a 0-byte file to indicate
		// a "negative" hit, but return an empty filename.
		return string();
	}

	// Write the file.
	file->write((void*)m_downloader->data(), m_downloader->dataSize());

	// Save the original URL as an extended attribute.
	// This will also set the mtime if it's available.
	file->setOriginInfo(url, m_downloader->mtime());

	// We're done here.
	file->close();	// NOTE: May be redundant.
	file->unref();

	// Return the cache filename.
	return cache_filename;
}

/**
 * Check if a file has already been cached.
 * @param cache_key Cache key.
 * @return Filename in the cache, or empty string if not found.
 */
string CacheManager::findInCache(const string &cache_key)
{
	// Get the cache key filename.
	string cache_filename = LibCacheCommon::getCacheFilename(cache_key);
	if (cache_filename.empty()) {
		// Error obtaining the cache key filename.
		return string();
	}

	// Return the filename if the file exists.
	return (!access(cache_filename, R_OK) ? cache_filename : string());
}

}
