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
#include QMK_KEYBOARD_H
#include "keymap_icelandic.h"

#define _BASE 0
#define _HALMAK 1
#define _NUMPAD 2
#define _SYMBOLS 3
#define _OSFUNC 4

// Dashes (macOS)
#define KC_NDSH LALT(KC_MINS)
#define KC_MDSH S(LALT(KC_MINS))

// Fillers to make layering more clear

#define ____ KC_TRNS

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define HYPER LCTL(LALT(KC_LGUI))

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN1

#define HALMAK TG(_HALMAK)
#define NUMPAD MO(_NUMPAD)
#define SYMBOLS MO(_SYMBOLS)
#define OSFUNC MO(_OSFUNC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base (qwerty)
 * +-----------------------------------------+                             +-----------------------------------------+
 * | ESC  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |   [  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | TAB  |   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ;  |   '  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | LSHFT|   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   /  |   \  |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 * | OS   | LALT |  [   |   ]  |                                                         |   +  |   =  |   -  | RSHFT|
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             |      |      |      |               |      |      |      |
 *                             +------+      |      |               |      |      +------+
 *                             |      +------+------+               +------+------+      |
 *                             +------+      |      |               |      |      +------+
 *                                    +-------------+               +-------------+
 *
 */

// // Home row mods
// Turned them all off because I activated them while typing
// #define GUI_A MT(MOD_LGUI, KC_A)
// #define ALT_S MT(MOD_LALT, KC_S)
// #define SFT_D MT(MOD_LSFT, KC_D)
// #define CTK_F MT(MOD_LCTL, KC_F)

// // !! I disabled them on the right side because I need to use j/k for vim-like up/down
// #define CTL_J MT(MOD_RCTL, KC_J)
// #define SFT_K MT(MOD_RSFT, KC_K)
// #define ALT_L MT(MOD_LALT, KC_L)
// #define GUI_SCLN MT(MOD_RGUI, KC_SCLN)

// Control when held, Escape when tapped
#define LCTL_ESC MT(MOD_LCTL, KC_ESC)
#define RCTL_ESC MT(MOD_LCTL, KC_ESC)

[_BASE] = LAYOUT( \
    KC_TAB,  KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,   \
    LCTL_ESC, KC_A,  KC_S,   KC_D,   KC_F,  KC_G,               KC_H,   KC_J,   KC_K,   KC_L, KC_SCLN, KC_QUOT,   \
    KC_LSFT, KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_BSLASH, \
    OSFUNC,HYPER,KC_LBRC,KC_RBRC,                                             KC_RALT,KC_EQL,KC_MINS,KC_BSPC,  \
                            KC_LGUI, KC_BSPC, KC_ENT,       KC_TAB, KC_SPC, RCTL_ESC,                           \
                            KC_LALT, LCTL_ESC, NUMPAD,      KC_GRV, KC_RALT, KC_RSFT                    \
),

[_HALMAK] = LAYOUT( \
    _______, KC_W,  KC_L,   KC_R,   KC_B,   KC_Z,                  KC_SCLN,   KC_Q,   KC_U,   KC_D,   KC_J,   KC_LBRC,   \
    _______, KC_S,  KC_H,   KC_N,   KC_T,   KC_COMM,               KC_DOT,   KC_A,   KC_E,   KC_O,   KC_I, KC_QUOT,   \
    _______, KC_F,  KC_M,   KC_V,   KC_C,   KC_SLSH,               KC_G,   KC_P,   KC_X,KC_K, KC_Y,_______, \
    _______,_______,_______,_______,                                             _______,_______,_______,_______,  \
                                    _______,_______,_______,    _______,_______,_______,                           \
                                    _______,_______,_______,    _______,_______,_______                           \
),

/* Numberpad
 * +-----------------------------------------+                             +-----------------------------------------+
 * |      |      |      |      |      |   [  |                             |   ]  |   7  |   8  |   9  | Reset|   +  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      | Home | PGUP | PGDN | END  |   (  |                             |   )  |   4  |   5  |   6  |   -  |   |  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                             |      |   1  |   2  |   3  |   =  |   _  |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 * |      |      |      |      |                                                         |      |   0  |      |      |
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             | PrScr|      |      |               |      |      |      |
 *                             +------+      |      |               |      |      +------+
 *                             |      +------+------+               +------+------+      |
 *                             +------+      |      |               |      |      +------+
 *                                    +-------------+               +-------------+
 *
 */

[_NUMPAD] = LAYOUT(
    _______,_______,_______,_______,_______,KC_LBRC,            KC_RBRC, KC_P7, KC_P8,  KC_P9,  RESET,  KC_PLUS,   \
    _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,            KC_RPRN, KC_P4, KC_P5,  KC_P6,  KC_MINS,KC_PIPE,   \
    SYMBOLS,_______,_______,_______,_______,_______,            _______, KC_P1, KC_P2,  KC_P3,  KC_EQL, KC_UNDS,   \
    _______,_______,_______,KC_PSCR,                                            KC_P0,_______,_______,_______,     \
                                    _______,_______,SYMBOLS,    _______,_______,_______,                           \
                                    _______,_______,_______,    _______,_______,_______                            \
),

/* Symbols
 * +-----------------------------------------+                             +-----------------------------------------+
 * |      |      |      |      |      |   [  |                             |   ]  |   7  |   8  |   9  | Reset|   +  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      | Home | PGUP | PGDN | END  |   (  |                             |   )  |   4  |   5  |   6  |   -  |   |  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                             |      |   1  |   2  |   3  |   =  |   _  |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 * |      |      |      |      |                                                         |      |   0  |      |      |
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             | PrScr|      |      |               |      |      |      |
 *                             +------+      |      |               |      |      +------+
 *                             |      +------+------+               +------+------+      |
 *                             +------+      |      |               |      |      +------+
 *                                    +-------------+               +-------------+
 *
 */

[_SYMBOLS] = LAYOUT(
    _______, KC_F1, KC_F2, KC_F3, KC_F4,_______,                _______, S(KC_7), S(KC_8),  S(KC_9), _______, _______,   \
    _______, KC_F5, KC_F6, KC_F7, KC_F8,_______,                _______, S(KC_4), S(KC_5),  S(KC_6), _______, _______,   \
    _______, KC_F9,KC_F10,KC_F11,KC_F12,_______,                _______, S(KC_1), S(KC_2),  S(KC_3), _______, KC_NDSH,   \
    _______,_______,_______,_______,                                              S(KC_0),  _______, _______, KC_MDSH,   \
                                    _______,_______,_______,    _______,_______,_______,                           \
                                    _______,_______,_______,    _______,_______,_______                          \
),

/* OS Controls
 * +-----------------------------------------+                             +-----------------------------------------+
 * |      | Reset|      |      |      |   [  |                             |   ]  |      | NmLck|Insert| ScLck| Mute |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      |  <-  |   ^  |   v  |  ->  |   (  |                             |   )  | Prev | Play | Next |      | VolUp|
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                             |      |      |      |      |      | VolDn|
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 * |      |      |      |      |                                                         |   =  |      |      |      |
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             |      |      |      |               |      |      |      |
 *                             +------+      |      |               |      |      +------+
 *                             |      +------+------+               +------+------+      |
 *                             +------+      |      |               |      |      +------+
 *                                    +-------------+               +-------------+
 *
 */

[_OSFUNC] = LAYOUT(
    KC_PAUS,RESET,  _______,KC_MPRV,KC_MPLY,KC_MNXT,            FF_LEFT, FF_RIGHT,KC_NLCK,KC_INS, _______,KC_VOLU,   \
    KC_SLCK,_______,_______,_______,_______,_______,            KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT,_______,KC_VOLD,   \
    _______,_______,_______,_______,_______,_______,            KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,KC_MUTE,   \
    _______,_______,_______,_______,                                            _______,_______,_______,_______,\
                                    _______,KC_BTN1,KC_BTN3,    KC_BTN4,KC_BTN2,_______,                           \
                                    KC_ACL0,KC_ACL1,KC_ACL2,    _______,_______,_______                           \
)
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
