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

#define _BASE 0
#define _HALMAK 1
#define _NUMPAD 2
#define _SYMBOLS 3
#define _OSFUNC 4
#define _ACUTE 5

#define HALMAK TG(_HALMAK)
#define NUMPAD MO(_NUMPAD)
#define SYMBOLS MO(_SYMBOLS)
#define OSFUNC MO(_OSFUNC)

// Dashes (macOS)
#define KC_NDSH LALT(KC_MINS)
#define KC_MDSH S(LALT(KC_MINS))

// Fillers to make layering more clear

#define ____ KC_TRNS

#define SFT_ESC SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC ALT_T(KC_SPC)
#define SFT_ENT SFT_T(KC_ENT)

#define HYPER LCTL(LALT(KC_LGUI))

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
#define RCTL_ESC MT(MOD_LCTL, KC_ESC)

// Firefox tab navigation
#define FF_LEFT LGUI(LALT(KC_LEFT))
#define FF_RIGHT LGUI(LALT(KC_RIGHT))

// Define a type for as many tap dance states as you need
typedef enum { TD_NONE, TD_UNKNOWN, TD_SINGLE_TAP, TD_SINGLE_HOLD, TD_DOUBLE_TAP_HOLD } td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    NUMSYMTAP,  // tap and hold for Number-symbols, double-tap and hold for F-keys, tap for Enter
    ACUTETAP,   // tap for Acute vowels, shift-tap for double quote
};

#define NUMSYM TD(NUMSYMTAP)
#define ACUTE TD(ACUTETAP)

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void numsym_finished(qk_tap_dance_state_t *state, void *user_data);
void numsym_reset(qk_tap_dance_state_t *state, void *user_data);
void acute_finished(qk_tap_dance_state_t *state, void *user_data);
void acute_reset(qk_tap_dance_state_t *state, void *user_data);

enum unicode_names {
    ETH_UPPER,
    ETH_LOWER,
    AE_LOWER,
    AE_UPPER,
    THRN_LOWER,
    THRN_UPPER,
    ODIA_LOWER,
    ODIA_UPPER,
    AACUTE_L,
    AACUTE_U,
    EACUTE_L,
    EACUTE_U,
    IACUTE_L,
    IACUTE_U,
    OACUTE_L,
    OACUTE_U,
    UACUTE_L,
    UACUTE_U,
    YACUTE_L,
    YACUTE_U,
};

const uint32_t PROGMEM unicode_map[] = {
    [ETH_LOWER]  = 0xF0,    // ð
    [ETH_UPPER]  = 0xD0,    // Ð
    [AE_LOWER]   = 0xE6,    // æ
    [AE_UPPER]   = 0xC6,    // Æ
    [THRN_LOWER] = 0xFE,    // þ
    [THRN_UPPER] = 0xDE,    // Þ
    [ODIA_LOWER] = 0xF6,    // ö
    [ODIA_UPPER] = 0xD6,    // Ö
    [AACUTE_L]   = 0x00E1,  // á
    [AACUTE_U]   = 0x00C1,  // Á
    [EACUTE_L]   = 0x00E9,  // é
    [EACUTE_U]   = 0x00C9,  // É
    [IACUTE_L]   = 0x00ED,  // í
    [IACUTE_U]   = 0x00CD,  // Í
    [OACUTE_L]   = 0x00F3,  // ó
    [OACUTE_U]   = 0x00D3,  // Ó
    [UACUTE_L]   = 0x00FA,  // ú
    [UACUTE_U]   = 0x00DA,  // Ú
    [YACUTE_L]   = 0x00FD,  // ý
    [YACUTE_U]   = 0x00DD,  // Ý
};

#define GY_ETH XP(ETH_LOWER, ETH_UPPER)
#define GY_AE XP(AE_LOWER, AE_UPPER)
#define GY_THRN XP(THRN_LOWER, THRN_UPPER)
#define GY_ODIA XP(ODIA_LOWER, ODIA_UPPER)
#define GY_AACUTE XP(AACUTE_L, AACUTE_U)
#define GY_EACUTE XP(EACUTE_L, EACUTE_U)
#define GY_IACUTE XP(IACUTE_L, IACUTE_U)
#define GY_OACUTE XP(OACUTE_L, OACUTE_U)
#define GY_UACUTE XP(UACUTE_L, UACUTE_U)
#define GY_YACUTE XP(YACUTE_L, YACUTE_U)

// #define GY_ACUTE XP(ACUTE, S(KC_QUOT))

void oneshot_layer_changed_user(uint8_t layer) {
    if (layer == _ACUTE) {
        println("Oneshot layer ACUTE on");
    }
    if (!layer) {
        println("Oneshot layer off");
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base (qwerty)
 *                   ,-------------------------------. ,-------------------------------.
 * ,-----------------|   W   |   E   |   R   |   T   | |   Y   |   U   |   I   |   O   |-----------------.
 * | NUMSYM  |   Q   |-------+-------+-------+-------| |-------+-------+-------+-------|   P   |  LBRC   |
 * |---------+-------|   S   |   D   |   F   |   G   | |   H   |   J   |   K   |   L   |-------+---------|
 * | LCTL_ES |   A   |-------+-------+-------+-------| |-------+-------+-------+-------| SCLN  |  QUOT   |
 * |---------+-------|   X   |   C   |   V   |   B   | |   N   |   M   | COMM  |  DOT  |-------+---------|
 * |  LSFT   |   Z   |-------+-------+---------------' `---------------+-------+-------| SLSH  | BSLASH  |
 * |---------+-------| LBRC  | RBRC  |                                 |NUMPAD |  EQL  |-------+---------|
 * | OSFUNC  | HYPER |---------------'                                 `---------------| MINS  |  BSPC   |
 * `-----------------'       ,-----------------------. ,-----------------------.       `-----------------'
 *                           | LGUI  |  SPC  | BSPC  | |  TAB  |  ENT  |LCTL_ES|
 *                           |-------|       |       | |       |       |-------|
 *                           | LALT  |-------+-------| |-------+-------| RSFT  |
 *                           `-------|LCTL_ES|NUMSYM | |  GRV  | RALT  |-------'
 *                                   `---------------' `---------------'       generated by [keymapviz] */

[_BASE] = LAYOUT( \
    NUMSYM,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_LBRC,   \
    LCTL_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,               KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, ACUTE,   \
    KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_BSLASH, \
    OSFUNC,  HYPER, KC_LBRC,KC_RBRC,                                              NUMPAD, KC_EQL, KC_MINS, KC_BSPC,   \
                            KC_LGUI, KC_SPC, KC_BSPC,        KC_TAB, KC_ENT, LCTL_ESC,                                 \
                            KC_LALT, LCTL_ESC,NUMSYM,         KC_GRV, KC_RALT, KC_RSFT                                  \
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
[_NUMPAD] = LAYOUT(
    RESET,  _______, S(KC_7), S(KC_8),  S(KC_9), KC_LBRC,            KC_RBRC, KC_P7, KC_P8,  KC_P9,  KC_PLUS, KC_HOME,   \
    _______,_______, S(KC_4), S(KC_5),  S(KC_6), KC_LPRN,            KC_RPRN, KC_P4, KC_P5,  KC_P6,  KC_MINS,KC_END,   \
    _______,_______, S(KC_1), S(KC_2),  S(KC_3), _______,            KC_PSCR, KC_P1, KC_P2,  KC_P3,  KC_EQL, KC_PGUP,   \
    _______,_______,_______, S(KC_0),                                                 KC_P0,KC_PIPE,KC_UNDS,KC_PGDN,     \
                                    _______,_______,_______,    _______,_______,_______,                           \
                                    _______,_______,_______,    _______,_______,_______                            \
),

/* Symbols
 *                   ,-------------------------------. ,-------------------------------.
 * ,-----------------|       |       |       | LBRC  | | RBRC  |  F1   |  F2   |  F3   |-----------------.
 * |         |       |-------+-------+-------+-------| |-------+-------+-------+-------|  F4   |         |
 * |---------+-------|       |       |       | LPRN  | | RPRN  |  F5   |  F6   |  F7   |-------+---------|
 * |         |       |-------+-------+-------+-------| |-------+-------+-------+-------|  F8   |         |
 * |---------+-------|       |       |       |       | |       |  F9   |  F10  |  F11  |-------+---------|
 * |         |       |-------+-------+---------------' `---------------+-------+-------|  F12  |  NDSH   |
 * |---------+-------|       |       |                                 |       |       |-------+---------|
 * |         |       |---------------'                                 `---------------|       |  MDSH   |
 * `-----------------'       ,-----------------------. ,-----------------------.       `-----------------'
 *                           |       |       |       | |       |       |       |
 *                           |-------|       |       | |       |       |-------|
 *                           |       |-------+-------| |-------+-------|       |
 *                           `-------|       |       | |       |       |-------'
 *                                   `---------------' `---------------'       generated by [keymapviz] */
[_SYMBOLS] = LAYOUT(
    _______,_______,_______,_______,_______,KC_LBRC,                KC_RBRC, KC_F1, KC_F2,  KC_F3,  KC_F4, _______,   \
    _______,_______,_______,_______,_______,KC_LPRN,                KC_RPRN, KC_F5, KC_F6,  KC_F7,  KC_F8, _______,   \
    _______,_______,_______,_______,_______,_______,                _______, KC_F9, KC_F10, KC_F11, KC_F12, KC_NDSH,   \
    _______,_______,_______,_______,                                            _______,_______,_______, KC_MDSH,   \
                                    _______,_______,_______,    _______,_______,_______,                           \
                                    _______,_______,_______,    _______,_______,_______                          \
),

/* OS Controls
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
    KC_PAUS,RESET,  _______,KC_MPRV,KC_MPLY,KC_MNXT,            FF_LEFT, FF_RIGHT, KC_NLCK,KC_INS, _______,KC_VOLU,   \
    KC_SLCK,_______,_______,_______,_______,_______,            KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT,_______,KC_VOLD,   \
    _______,_______,_______,_______,_______,_______,            KC_ML,   KC_MD,    KC_MU,  KC_MR, _______,KC_MUTE,   \
    _______,_______,_______,_______,                                              _______,_______,_______,HALMAK,\
                            _______,KC_MB1,KC_MB3,          KC_MB4,KC_MB2,_______,                           \
                            KC_ACL0,KC_ACL1,KC_ACL2,        _______,_______,_______                           \
),

    /* Acute characters QWERTY */
    [_ACUTE] = LAYOUT(
        _______,_______,_______, GY_EACUTE,_______,_______,     GY_YACUTE, GY_UACUTE, GY_IACUTE, GY_OACUTE,_______,_______, \
        _______, GY_AACUTE,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______, \
        _______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______, \
        _______,_______,_______,_______,                                        _______,_______,_______,_______, \
                                _______,_______,_______,        _______,_______,_______, \
                                _______,_______,_______,        _______,_______,_______ \
)
};

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
static td_tap_t numsym_tap_state = {.is_press_action = true, .state = TD_NONE};
static td_tap_t acute_tap_state = {.is_press_action = true, .state = TD_NONE};

// Functions that control what our tap dance key does
void numsym_finished(qk_tap_dance_state_t *state, void *user_data) {
    numsym_tap_state.state = cur_dance(state);
    switch (numsym_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NUMPAD);
            break;
        case TD_DOUBLE_TAP_HOLD:
            layer_on(_SYMBOLS);
            break;
        default:
            break;
    }
}

void numsym_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (numsym_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NUMPAD);
    } else if (numsym_tap_state.state == TD_DOUBLE_TAP_HOLD) {
        layer_off(_SYMBOLS);
    }
    numsym_tap_state.state = TD_NONE;
}

// Functions that control what our tap dance key does
void acute_finished(qk_tap_dance_state_t *state, void *user_data) {
    acute_tap_state.state = cur_dance(state);
    switch (acute_tap_state.state) {
        case TD_SINGLE_TAP:
            set_oneshot_layer(_ACUTE, ONESHOT_START); set_oneshot_layer(_ACUTE, ONESHOT_PRESSED); break;
            break;
        case TD_SINGLE_HOLD:
            layer_on(_ACUTE);
            break;
        default:
            break;
    }
}

void acute_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (acute_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_ACUTE);
    }
    acute_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [NUMSYMTAP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, numsym_finished, numsym_reset, 275),
    [ACUTETAP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, acute_finished, acute_reset, 200)
    };

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TRNS:
        case KC_NO:
          /* Always cancel one-shot layer when another key gets pressed */
          if (record->event.pressed && is_oneshot_layer_active())
          clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
          return true;
        case RESET:
          /* Don't allow reset from oneshot layer state */
          if (record->event.pressed && is_oneshot_layer_active()){
            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            return false;
          }
          return true;
        default:
            return true;
    }
    return true;
}
