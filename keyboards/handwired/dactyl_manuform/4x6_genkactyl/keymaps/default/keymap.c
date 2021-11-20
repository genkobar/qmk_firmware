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

enum my_layers {
    _QWERTY,
    _HALMAK,
    _NUMSYM,
    _OSFUNC
};

#define HALMAK TG(_HALMAK)
#define OSFUNC MO(_OSFUNC)

// Mouse control short names
#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN2
#define KC_MB3 KC_MS_BTN3
#define KC_MB4 KC_MS_BTN4

// Control when held, Escape when tapped
#define LCTL_ESC MT(MOD_LCTL, KC_ESC)
#define RCTL_ESC MT(MOD_RCTL, KC_ESC)

#define HYPER LCTL(LALT(KC_LGUI))

// Firefox tab navigation
#define FF_LEFT LGUI(LALT(KC_LEFT))
#define FF_RIGHT LGUI(LALT(KC_RIGHT))

// Define a type for as many tap dance states as you need
typedef enum {
    // clang-format off
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP_HOLD
    // clang-format on
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    // clang-format off
    NUMSYMTAP,  // Our custom tap dance key; add any other tap dance keys to this enum
    // clang-format on
};

#define NUMSYM TD(NUMSYMTAP)

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

// =================================
//     KEYMAP DEFINITIONS
// =================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
/* Base (qwerty)
 *                   ,-------------------------------. ,-------------------------------.
 * ,-----------------|   W   |   E   |   R   |   T   | |   Y   |   U   |   I   |   O   |-----------------.
 * | NUMSYM  |   Q   |-------+-------+-------+-------| |-------+-------+-------+-------|   P   |  LBRC   |
 * |---------+-------|   S   |   D   |   F   |   G   | |   H   |   J   |   K   |   L   |-------+---------|
 * | LCTL_ES |   A   |-------+-------+-------+-------| |-------+-------+-------+-------| SCLN  |  QUOT   |
 * |---------+-------|   X   |   C   |   V   |   B   | |   N   |   M   | COMM  |  DOT  |-------+---------|
 * |  LSFT   |   Z   |-------+-------+---------------' `---------------+-------+-------| SLSH  | BSLASH  |
 * |---------+-------| LBRC  | RBRC  |                                 |NUMSYM |  EQL  |-------+---------|
 * | OSFUNC  | HYPER |---------------'                                 `---------------| MINS  |  BSPC   |
 * `-----------------'       ,-----------------------. ,-----------------------.       `-----------------'
 *                           | LGUI  |  SPC  | BSPC  | |  TAB  |  ENT  |LCTL_ES|
 *                           |-------|       |       | |       |       |-------|
 *                           | LALT  |-------+-------| |-------+-------| RSFT  |
 *                           `-------|LCTL_ES|NUMSYM | |  GRV  | RALT  |-------'
 *                                   `---------------' `---------------'       generated by [keymapviz] */

[_QWERTY] = LAYOUT( \
    KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_LBRC,   \
    LCTL_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,               KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT,   \
    KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_BSLASH, \
    OSFUNC,  HYPER, KC_LBRC,KC_RBRC,                                              KC_MINS, KC_EQL, HYPER, OSFUNC,   \
                            KC_LGUI, KC_SPC, KC_BSPC,         KC_ENT, KC_TAB, KC_GRV,                                 \
                            NUMSYM, HYPER, KC_LALT,           KC_RALT, LCTL_ESC, KC_RSFT                                  \
),

/* HALMAK
 *                   ,-------------------------------. ,-------------------------------.
 * ,-----------------|   L   |   R   |   B   |   Z   | | SCLN  |   Q   |   U   |   D   |-----------------.
 * |         |   W   |-------+-------+-------+-------| |-------+-------+-------+-------|   J   |         |
 * |---------+-------|   H   |   N   |   T   | COMM  | |  DOT  |   A   |   E   |   O   |-------+---------|
 * |         |   S   |-------+-------+-------+-------| |-------+-------+-------+-------|   I   |         |
 * |---------+-------|   M   |   V   |   C   | SLSH  | |   G   |   P   |   X   |   K   |-------+---------|
 * |         |   F   |-------+-------+---------------' `---------------+-------+-------|   Y   |         |
 * |---------+-------|       |       |                                 |       |       |-------+---------|
 * |         |       |---------------'                                 `---------------|       |         |
 * `-----------------'       ,-----------------------. ,-----------------------.       `-----------------'
 *                           |       |       |       | |       |       |       |
 *                           |-------|       |       | |       |       |-------|
 *                           |       |-------+-------| |-------+-------|       |
 *                           `-------|       |       | |       |       |-------'
 *                                   `---------------' `---------------'       generated by [keymapviz] */
[_HALMAK] = LAYOUT( \
    _______, KC_W,  KC_L,   KC_R,   KC_B,   KC_Z,                  KC_SCLN,   KC_Q,   KC_U,   KC_D,   KC_J,  _______,   \
    _______, KC_S,  KC_H,   KC_N,   KC_T,   KC_COMM,               KC_DOT,   KC_A,   KC_E,   KC_O,   KC_I, _______,   \
    _______, KC_F,  KC_M,   KC_V,   KC_C,   KC_SLSH,               KC_G,   KC_P,    KC_X,   KC_K,   KC_Y,_______, \
    _______,_______,_______,_______,                                             _______,_______,_______,_______,  \
                                    _______,_______,_______,    _______,_______,_______,                           \
                                    _______,_______,_______,    _______,_______,_______                           \
),

/* Numberpad
 *                   ,-------------------------------. ,-------------------------------.
 * ,-----------------|S(KC_7)|S(KC_8)|S(KC_9)| LBRC  | | RBRC  |  P7   |  P8   |  P9   |-----------------.
 * |  RESET  |       |-------+-------+-------+-------| |-------+-------+-------+-------| PLUS  |  HOME   |
 * |---------+-------|S(KC_4)|S(KC_5)|S(KC_6)| LPRN  | | RPRN  |  P4   |  P5   |  P6   |-------+---------|
 * |         |       |-------+-------+-------+-------| |-------+-------+-------+-------| MINS  |   END   |
 * |---------+-------|S(KC_1)|S(KC_2)|S(KC_3)|       | | PSCR  |  P1   |  P2   |  P3   |-------+---------|
 * |         |       |-------+-------+---------------' `---------------+-------+-------|  EQL  |  PGUP   |
 * |---------+-------|       |S(KC_0)|                                 |  P0   | PIPE  |-------+---------|
 * |         |       |---------------'                                 `---------------| UNDS  |  PGDN   |
 * `-----------------'       ,-----------------------. ,-----------------------.       `-----------------'
 *                           |       |       |       | |       |       |       |
 *                           |-------|       |       | |       |       |-------|
 *                           |       |-------+-------| |-------+-------|       |
 *                           `-------|       |       | |       |       |-------'
 *                                   `---------------' `---------------'       generated by [keymapviz] */
[_NUMSYM] = LAYOUT(
    RESET,  _______, S(KC_7), S(KC_8),  S(KC_9), S(KC_LBRC),      S(KC_RBRC), KC_P7, KC_P8,  KC_P9, KC_PLUS, KC_HOME,   \
    _______,_______, S(KC_4), S(KC_5),  S(KC_6), KC_LPRN,            KC_RPRN, KC_P4, KC_P5,  KC_P6, KC_MINS, KC_END,   \
    KC_PSCR,_______, S(KC_1), S(KC_2),  S(KC_3), KC_LBRC,            KC_RBRC, KC_P1, KC_P2,  KC_P3, KC_EQL,  KC_PGUP,   \
    _______,_______,_______, S(KC_0),                                                KC_P0,KC_PIPE, KC_UNDS, KC_PGDN,     \
                                    _______,_______,_______,    _______,_______,_______,                           \
                                    _______,_______,_______,    _______,_______,_______                            \
),

/* OS & function keys
 *                   ,-------------------------------. ,-------------------------------.
 * ,-----------------|       | MPRV  | MPLY  | MNXT  | |FF_LEFT|FF_RIGH| NLCK  |  INS  |-----------------.
 * |  PAUS   | RESET |-------+-------+-------+-------| |-------+-------+-------+-------|       |  VOLU   |
 * |---------+-------|       |       |       |       | | LEFT  | DOWN  |  UP   | RGHT  |-------+---------|
 * |  SLCK   |       |-------+-------+-------+-------| |-------+-------+-------+-------|       |  VOLD   |
 * |---------+-------|       |       |       |       | |  ML   |  MD   |  MU   |  MR   |-------+---------|
 * |         |       |-------+-------+---------------' `---------------+-------+-------|       |  MUTE   |
 * |---------+-------|       |       |                                 |       |       |-------+---------|
 * |         |       |---------------'                                 `---------------|       | HALMAK  |
 * `-----------------'       ,-----------------------. ,-----------------------.       `-----------------'
 *                           |       |  MB1  |  MB3  | |  MB4  |  MB2  |       |
 *                           |-------|       |       | |       |       |-------|
 *                           | ACL0  |-------+-------| |-------+-------|       |
 *                           `-------| ACL1  | ACL2  | |       |       |-------'
 *                                   `---------------' `---------------'       generated by [keymapviz] */
[_OSFUNC] = LAYOUT(
    KC_PAUS,RESET,  KC_F1, KC_F2,  KC_F3,  KC_F4,             FF_LEFT, FF_RIGHT, KC_NLCK,KC_INS, _______,KC_VOLU,   \
    KC_SLCK,_______,KC_F5, KC_F6,  KC_F7,  KC_F8,             KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT,_______,KC_VOLD,   \
    _______,_______,KC_F9, KC_F10, KC_F11, KC_F12,            KC_ML,   KC_MD,    KC_MU,  KC_MR, _______,KC_MUTE,   \
    _______,_______,_______,HALMAK,                                              KC_MPRV,KC_MPLY,KC_MNXT,_______,\
                            _______,KC_MB1,KC_MB3,          KC_MB4,KC_MB2,_______,                           \
                            _______,_______,_______,        KC_ACL0,KC_ACL1,KC_ACL2                           \
)
};
// clang-format on

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed)
            return TD_SINGLE_TAP;
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2)
        return TD_DOUBLE_TAP_HOLD;
    else
        return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {.is_press_action = true, .state = TD_NONE};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NUMSYM);
            break;
        case TD_DOUBLE_TAP_HOLD:
            layer_on(_OSFUNC);
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NUMSYM);
    } else if (ql_tap_state.state == TD_DOUBLE_TAP_HOLD) {
        layer_off(_OSFUNC);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {[NUMSYMTAP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)};
