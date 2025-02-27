/***************************************************************************
 * ROM Properties Page shell extension. (GTK+)                             *
 * AchSpritesheet.hpp: Achievement spritesheets loader.                    *
 *                                                                         *
 * Copyright (c) 2020-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

#include "PIMGTYPE.hpp"

namespace AchSpritesheet {

/**
 * Load the specified Achievements icon sprite sheet.
 * Caller must free it after use.
 * @param gray If true, load the grayscale version.
 * @param iconSize Icon size. (16, 24, 32, 64)
 * @return PIMGTYPE, or nullptr on error.
 */
PIMGTYPE load(int iconSize, bool gray = false);

};
