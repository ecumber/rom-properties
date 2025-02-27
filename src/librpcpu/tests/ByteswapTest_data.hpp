/***************************************************************************
 * ROM Properties Page shell extension. (librpcpu/tests)                   *
 * ByteswapTest_data.hpp: Data for ByteswapTest.                           *
 *                                                                         *
 * Copyright (c) 2016-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

// NOLINTBEGIN(misc-definitions-in-headers)

/**
 * Original test data.
 */
const uint8_t ByteswapTest::bswap_orig[TEST_ARRAY_SIZE] = {
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
	0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
	0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0xEF,0xCD,0xAB,0x89,0x67,0x45,0x23,0x01,
};

/**
 * 16-bit byteswapped test data.
 */
const uint8_t ByteswapTest::bswap_16b[TEST_ARRAY_SIZE] = {
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
	0x23,0x01,0x67,0x45,0xAB,0x89,0xEF,0xCD,0xDC,0xFE,0x98,0xBA,0x54,0x76,0x10,0x32,
	0x32,0x10,0x76,0x54,0xBA,0x98,0xFE,0xDC,0xCD,0xEF,0x89,0xAB,0x45,0x67,0x01,0x23,
};

/**
 * 32-bit byteswapped test data.
 */
const uint8_t ByteswapTest::bswap_32b[TEST_ARRAY_SIZE] = {
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
	0x67,0x45,0x23,0x01,0xEF,0xCD,0xAB,0x89,0x98,0xBA,0xDC,0xFE,0x10,0x32,0x54,0x76,
	0x76,0x54,0x32,0x10,0xFE,0xDC,0xBA,0x98,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,
};

// NOLINTEND(misc-definitions-in-headers)
