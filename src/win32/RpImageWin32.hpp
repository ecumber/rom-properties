/***************************************************************************
 * ROM Properties Page shell extension. (Win32)                            *
 * RpImageWin32.hpp: rp_image to Win32 conversion functions.               *
 *                                                                         *
 * Copyright (c) 2016-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

#include "common.h"
namespace LibRpTexture {
	class rp_image;
}

// C includes.
#include <stdint.h>

namespace RpImageWin32 {

/**
 * Convert an rp_image to HBITMAP.
 * @param image		[in] rp_image
 * @param bgColor	[in] Background color for images with alpha transparency. (ARGB32 format)
 * @return HBITMAP, or nullptr on error.
 */
HBITMAP toHBITMAP(const LibRpTexture::rp_image *image, uint32_t bgColor);

/**
 * Convert an rp_image to HBITMAP.
 * This version resizes the image.
 * @param image		[in] rp_image
 * @param bgColor	[in] Background color for images with alpha transparency. (ARGB32 format)
 * @param size		[in] If non-zero, resize the image to this size.
 * @param nearest	[in] If true, use nearest-neighbor scaling.
 * @return HBITMAP, or nullptr on error.
 */
HBITMAP toHBITMAP(const LibRpTexture::rp_image *image, uint32_t bgColor, SIZE size, bool nearest);

/**
 * Convert an rp_image to HBITMAP.
 * This version preserves the alpha channel.
 * @param image		[in] rp_image
 * @return HBITMAP, or nullptr on error.
 */
HBITMAP toHBITMAP_alpha(const LibRpTexture::rp_image *image);

/**
 * Convert an rp_image to HBITMAP.
 * This version preserves the alpha channel and resizes the image.
 * @param image		[in] rp_image
 * @param size		[in] If non-zero, resize the image to this size.
 * @param nearest	[in] If true, use nearest-neighbor scaling.
 * @return HBITMAP, or nullptr on error.
 */
HBITMAP toHBITMAP_alpha(const LibRpTexture::rp_image *image, SIZE size, bool nearest);

/**
 * Convert an rp_image to HICON.
 * @param image rp_image.
 * @return HICON, or nullptr on error.
 */
HICON toHICON(const LibRpTexture::rp_image *image);

/**
 * Convert an HBITMAP to rp_image.
 * @param hBitmap HBITMAP.
 * @return rp_image.
 */
LibRpTexture::rp_image *fromHBITMAP(HBITMAP hBitmap);

/**
 * Convert an HBITMAP to HICON.
 * @param hBitmap HBITMAP.
 * @return HICON, or nullptr on error.
 */
HICON toHICON(HBITMAP hBitmap);

/**
 * Extract an HBITMAP sprite from an rp_image sprite sheet.
 * Caller must delete the HBITMAP after use.
 * @param imgSpriteSheet	[in] rp_image sprite sheet
 * @param x			[in] X pos
 * @param y			[in] Y pos
 * @param width			[in] Width
 * @param height		[in] Height
 * @param dpi			[in,opt] DPI value.
 * @return Sub-bitmap, or nullptr on error.
 */
HBITMAP getSubBitmap(const LibRpTexture::rp_image *img, int x, int y, int w, int h, UINT dpi = 96);

}
