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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    // clang-format off
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _UPPER
    // clang-format on
};


// Layer toggling behavior definitions
#define COLEMAK TG(_COLEMAK)
#define LOWER MO(_LOWER)
#define UPPER MO(_UPPER)

// Control when held, Escape when tapped
#define CT_ESC LCTL_T(KC_ESC)

// I use Hammerspoon scripts with ctrl-alt and hyper for window management
#define CALT LCTL(KC_LALT)
#define HYPER LCTL(LALT(KC_LGUI))  // Hyper key modifier defined as CTRL+ALT+SUPER

// Firefox tab navigation
#define FF_L LGUI(LALT(KC_LEFT))
#define FF_R LGUI(LALT(KC_RIGHT))

// =================================
//     KEYMAP DEFINITIONS
// =================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

[_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,  KC_2,   KC_3,   KC_4, KC_5,             KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,  KC_W,   KC_E,   KC_R, KC_T,             KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC,   \
    CT_ESC,  KC_A,  KC_S,   KC_D,   KC_F, KC_G,             KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,   \
    KC_LSFT, KC_Z,  KC_X,   KC_C,   KC_V, KC_B,             KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLASH, \
                KC_LBRC, KC_RBRC,        _______,     _______,        KC_MINS, KC_EQL,                     \
                        KC_LGUI, KC_SPC, KC_BSPC,         KC_TAB, KC_ENT, KC_GRV,                            \
                        CALT,    LOWER,  KC_LALT,                 UPPER, CT_ESC                             \
),

[_COLEMAK] = LAYOUT( \
    _______,_______,_______,_______,_______,_______,          _______,_______,_______,_______,_______,_______,\
    _______, KC_Q, KC_W, KC_F, KC_P, KC_G,                        KC_J, KC_L, KC_U, KC_Y, KC_SCLN, _______,   \
    _______, KC_A, KC_R, KC_S, KC_T, KC_D,                        KC_H, KC_N, KC_E, KC_I, KC_O, _______,   \
    _______, KC_Z, KC_X, KC_C, KC_V, KC_B,                        KC_K, KC_M, _______, _______, _______, _______,   \
                    _______,_______,        _______,            _______,      _______,_______,           \
                            _______,_______,_______,            _______,_______,_______,                 \
                            _______,_______,_______,                    _______,_______                  \
),

[_LOWER] = LAYOUT(
    _______,_______,_______,_______,_______,_______,          _______,_______,_______,_______,_______,_______,\
    RESET,  _______, S(KC_7), S(KC_8),  S(KC_9), S(KC_LBRC),      S(KC_RBRC), KC_P7, KC_P8,  KC_P9, KC_PGUP, KC_HOME, \
    _______,_______, S(KC_4), S(KC_5),  S(KC_6), KC_LPRN,            KC_RPRN, KC_P4, KC_P5,  KC_P6, KC_PGDN, KC_END,  \
    KC_PSCR,_______, S(KC_1), S(KC_2),  S(KC_3), KC_LBRC,            KC_RBRC, KC_P1, KC_P2,  KC_P3, KC_UNDS, KC_EQL,  \
                     _______, S(KC_0),      _______,            _______,             KC_P0,KC_PIPE,                   \
                            _______,_______,_______,            _______,_______,_______,                              \
                            _______,_______,_______,                    _______,_______                               \
),

[_UPPER] = LAYOUT(
    RGB_TOG,_______,_______,_______,_______,_______,          _______,_______,_______,_______,_______,_______,\
    RGB_MODE_PLAIN,_______,KC_F1, KC_F2,  KC_F3,  KC_F4,             FF_L,    FF_R,    KC_NLCK,KC_INS, _______,KC_VOLU, \
    RGB_MODE_RAINBOW,_______,KC_F5, KC_F6,  KC_F7,  KC_F8,             KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,_______,KC_VOLD, \
    COLEMAK,_______,KC_F9, KC_F10, KC_F11, KC_F12,            KC_MS_L, KC_MS_D, KC_MS_U,KC_MS_R,_______,KC_MUTE, \
                 _______, _______,          _______,        _______,            _______,_______,                 \
                            KC_BTN3,KC_BTN1,KC_BTN2,        KC_ACL0,KC_ACL1,KC_ACL2,                             \
                            KC_MPRV,KC_MPLY,KC_MNXT,                _______, _______                            \
)
};
// clang-format on

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}
