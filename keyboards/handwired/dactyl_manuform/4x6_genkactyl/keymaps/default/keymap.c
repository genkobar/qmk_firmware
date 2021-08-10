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
#include "keymap_us_international.h"

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

// Control when held, Escape when tapped
#define LCTL_ESC MT(MOD_LCTL, KC_ESC)
#define RCTL_ESC MT(MOD_LCTL, KC_ESC)

// Firefox tab navigation
#define FF_LEFT LGUI(LALT(KC_LEFT))
#define FF_RIGHT LGUI(LALT(KC_RIGHT))

enum unicode_names {
    THORN,
    AE,
    ETH
};

const uint32_t PROGMEM unicode_map[] = {
    [THORN]  = 0x00FE,  // þ
    [AE] = 0x00E6,  // æ
    [ETH]  = 0x00F0, // ð
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base (qwerty)
 * Notes on Icelandic typing:
 * Accented characters are typed with the apostrophe on from the US-international input method.
 * When typed before vowels, it will apply an accent to that vowel; otherwise it will type an apostrophe.
 * It will type " when shifted, but this also applies umlauts to viable characters, creating a way for us
 * to type ö without using a button on the keyboard.
 * Finally, since this 4x6 has some extra buttons in the 4th row, I moved æ and þ down there. It will take some
 * getting used to, but I think this will be better than continuing to switch between US and Icelandic input methods.
 * +-----------------------------------------+                             +-----------------------------------------+
 * | TAB  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |   ð  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |CTLESC|   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ;  |   '  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | LSHFT|   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   /  |   \  |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 * | OS   | HYPER |  [   |   ]  |                                                         |     |   æ  |   þ  |   -  |
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             |      |      |      |               |      |      |      |
 *                             +------+      |      |               |      |      +------+
 *                             |      +------+------+               +------+------+      |
 *                             +------+      |      |               |      |      +------+
 *                                    +-------------+               +-------------+
 */

[_BASE] = LAYOUT( \
    KC_TAB,   US_Q,   US_W,   US_E,   US_R,   US_T,               US_Y,   US_U,   US_I,   US_O,   US_P,    X(ETH),   \
    LCTL_ESC, US_A,   US_S,   US_D,   US_F,   US_G,               US_H,   US_J,   US_K,   US_L,   US_SCLN, US_ACUT,   \
    KC_LSFT,  US_Z,   US_X,   US_C,   US_V,   US_B,               US_N,   US_M,   US_COMM,US_DOT, US_SLSH, US_BSLS, \
    OSFUNC,  HYPER, US_LBRC,US_RBRC,                                              X(AE), X(THORN), US_EQL, US_MINS,   \
                            KC_LGUI, KC_BSPC, KC_ENT,       KC_TAB, KC_SPC, RCTL_ESC,                                 \
                            KC_LALT, LCTL_ESC, NUMPAD,      US_DGRV, KC_RALT, KC_RSFT                                  \
),

/* Numberpad
 * +-----------------------------------------+                             +-----------------------------------------+
 * |      |      |      |      |      |   [  |                             |   ]  |   7  |   8  |   9  | Reset|   +  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      | Home | PGUP | PGDN | END  |   (  |                             |   )  |   4  |   5  |   6  |   -  |   |  |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      |      |      |      |      |   {  |                             |   }  |   1  |   2  |   3  |   =  |   _  |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 * |      |      |      |      |                                                         |      |   0  |      |      |
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             |      |      | SYMB |               |      |      |      |
 *                             +------+      | LAYER|               |      |      +------+
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
 * |      |  F1  |  F2  |  F3  |  F4  |      |                             |      |   &  |   *  |   (  |      |      |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |                             |      |   $  |   %  |   ^  |      |      |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      |  F9  | F10  | F11  | F12  |      |                             |      |   !  |   @  |   #  |      |      |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 * |      |      |      |      |                                                         |   )  |      |      |      |
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             |      |      | SYMB |               |      |      |      |
 *                             +------+      | LAYER|               |      |      +------+
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
 * | BrtUp| Reset|      | Prev | Play | Next |                             | Tab<-|Tab-> | NmLck|Insert|      | VolUp|
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | BrtDn|      |      |      |      |      |                             |  <-  |   ^  |   v  |  ->  |      | VolDn|
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                             | M L  | M UP | M DN | M R  |      | Mute |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 * |      |      |      |      |                                                         |   =  |      |      |      |
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             |      | M B1 | M B3 |               | M B4 | M B2 |      |
 *                             +------+      |      |               |      |      +------+
 *                             | MAcl0+------+------+               +------+------+      |
 *                             +------+ MAcl1| MAcl2|               |      |      +------+
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
