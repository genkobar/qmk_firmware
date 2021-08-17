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

#define HALMAK TG(_HALMAK)
#define NUMPAD MO(_NUMPAD)
#define SYMBOLS MO(_SYMBOLS)
#define OSFUNC MO(_OSFUNC)

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
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    NUMSYM, // Our custom tap dance key; add any other tap dance keys to this enum
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);



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
 * | OS   | HYPER |  [   |   ]  |                                                        |      |   æ  |   þ  | BKSP |
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             |      |      |      |               |      |      |      |
 *                             +------+      |      |               |      |      +------+
 *                             |      +------+------+               +------+------+      |
 *                             +------+      |      |               |      |      +------+
 *                                    +-------------+               +-------------+
 */

[_BASE] = LAYOUT( \
    KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_LBRC,   \
    LCTL_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,               KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT,   \
    KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_BSLASH, \
    OSFUNC,  HYPER, KC_LBRC,KC_RBRC,                                              NUMPAD, KC_EQL, KC_MINS, KC_BSPC,   \
                            KC_LGUI, KC_SPC, KC_BSPC,       KC_TAB, KC_ENT, RCTL_ESC,                                 \
                            KC_LALT, LCTL_ESC, TD(NUMSYM),      KC_GRV, KC_RALT, KC_RSFT                                  \
),

[_HALMAK] = LAYOUT( \
    _______, KC_W,  KC_L,   KC_R,   KC_B,   KC_Z,                  KC_SCLN,   KC_Q,   KC_U,   KC_D,   KC_J,  _______,   \
    _______, KC_S,  KC_H,   KC_N,   KC_T,   KC_COMM,               KC_DOT,   KC_A,   KC_E,   KC_O,   KC_I, _______,   \
    _______, KC_F,  KC_M,   KC_V,   KC_C,   KC_SLSH,               KC_G,   KC_P,    KC_X,   KC_K,   KC_Y,_______, \
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
    _______,_______,_______,_______,_______,_______,            _______, KC_P1, KC_P2,  KC_P3,  KC_EQL, KC_UNDS,   \
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
    _______,_______,_______,_______,_______,_______,            KC_ML,KC_MD,KC_MU,KC_MR,_______,KC_MUTE,   \
    _______,_______,_______,_______,                                            _______,_______,_______,_______,\
                                    _______,KC_MB1,KC_MB3,    KC_MB4,KC_MB2,_______,                           \
                                    KC_ACL0,KC_ACL1,KC_ACL2,    _______,_______,_______                           \
)
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP_HOLD;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
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

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NUMPAD);
    } else if (ql_tap_state.state == TD_DOUBLE_TAP_HOLD) {
        layer_off(_SYMBOLS);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [NUMSYM] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};
