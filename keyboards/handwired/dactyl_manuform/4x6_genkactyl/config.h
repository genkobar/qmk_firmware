/* Copyright 2021 Valdimar Björn Ásgeirsson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x3437
#define DEVICE_VER      0x0001

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// row-driven
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, B3 }
#define MATRIX_COL_PINS { B2, B6, B5, B4, E6, D7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define MASTER_RIGHT

#define ENCODERS_PAD_A {D2}
#define ENCODERS_PAD_B {D4}

#define ENCODER_RESOLUTIONS { 4, 4, 4, 1}
#define UNUSED_PINS
