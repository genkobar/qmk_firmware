#include QMK_KEYBOARD_H
#include "keymap_icelandic.h"

#define _BASE 0
#define _RAISE 1
#define _LOWER 2
#define _SUPER 3

// Fillers to make layering more clear

#define ____ KC_TRNS

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN1

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base (qwerty)
 * +-----------------------------------------+                             +-----------------------------------------+
 * | ESC  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |      |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | TAB  |   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ;  |      |
 * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
 * | SHFT |   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   /  |      |
 * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
 * |      |      |  [   |   ]  |                                                         |      |      |      |      |
 * +---------------------------+--------------------+               +--------------------+---------------------------+
 *                             |      |      |      |               |      |      |      |
 *                             +------+      |      |               |      |      +------+
 *                             |      +------+------+               +------+------+      |
 *                             +------+      |      |               |      |      +------+
 *                                    +-------------+               +-------------+
 *
 */

[_BASE] = LAYOUT( \
    KC_ESC,  IS_Q,  IS_W,   IS_E,   IS_R,   IS_T,               IS_Y,   IS_U,   IS_I,   IS_O,   IS_P,   IS_ETH,   \
    KC_TAB,  IS_A,  IS_S,   IS_D,   IS_F,   IS_G,               IS_H,   IS_J,   IS_K,   IS_L,   IS_AE,  IS_ACUT,   \
    KC_LSFT, IS_Z,  IS_X,   IS_C,   IS_V,   IS_B,               IS_N,   IS_M,   IS_COMM,IS_DOT, IS_THRN,IS_ODIA, \
                    KC_LBRC,KC_RBRC,                                            KC_PLUS,KC_EQL,                    \
                                    RAISE,  KC_SPC,             KC_ENT, LOWER,                                     \
                                    KC_TAB, KC_HOME,            KC_END, KC_DEL,                                    \
                                    KC_BSPC,KC_GRV,             KC_LGUI,KC_LALT                                    \
),

[_LOWER] = LAYOUT(
    _______,_______,_______,_______,_______,KC_LBRC,            KC_RBRC, KC_P7, KC_P8,  KC_P9,  RESET,  KC_PLUS,   \
    _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,            KC_RPRN, KC_P4, KC_P5,  KC_P6,  KC_MINS,KC_PIPE,   \
    _______,_______,_______,_______,_______,_______,            _______, KC_P1, KC_P2,  KC_P3,  KC_EQL, KC_UNDS,   \
                                            _______,KC_PSCR,    _______, KC_P0,                                    \
                                            _______,_______,    _______,_______,                                   \
                                            _______,_______,    _______,_______,                                   \
                                            _______,_______,    _______,_______                                    \
),

[_RAISE] = LAYOUT(
    _______,RESET,  _______,_______,_______,KC_LBRC,            KC_RBRC,_______,KC_NLCK,KC_INS, KC_SLCK,KC_MUTE,   \
    _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,            KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,   \
    _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,KC_VOLD,   \
                                            _______,_______,    KC_EQL, _______,                                   \
                                            _______,_______,    _______,_______,                                   \
                                            _______,_______,    _______,_______,                                   \
                                            _______,_______,    _______,_______                                    \
)
};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
