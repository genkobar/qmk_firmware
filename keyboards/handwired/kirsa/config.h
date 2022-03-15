/*
Copyright 2022 Valdimar Björn Ásgeirsson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x984a
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER genkobar
#define PRODUCT      kirsa

/* mouse config */
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D3

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Enables This makes it easier for fast typists to use dual-function keys */
#define PERMISSIVE_HOLD

#define MASTER_RIGHT

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

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Enable encoder support */
#define ENCODERS_PAD_A {D2}
#define ENCODERS_PAD_B {D4}

#define ENCODER_RESOLUTIONS { 4, 4, 4, 1}
#define UNUSED_PINS
