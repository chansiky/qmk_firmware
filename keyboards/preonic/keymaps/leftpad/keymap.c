/* Copyright 2015-2017 Jack Humbert
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

#include "preonic.h"
#include "action_layer.h"

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = {
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT)},
    {RAISE,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,    KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, LOWER}
  },
  [_LOWER] = {
    {_______, _______,_______, _______, _______, _______,   _______, _______, _______, _______, _______, _______},
    {KC_GRV, KC_COMM,    KC_7,    KC_8,    KC_9,  KC_DOT,   KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______},
    {KC_UNDS, KC_MINS,    KC_4,    KC_5,    KC_6, KC_PPLS,   KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______},
    {_______,    KC_0,    KC_1,    KC_2,    KC_3,  KC_EQL,   KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______ }
  },
  [_RAISE] = {
    {_______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_DEL },
    {KC_PGUP, KC_HOME,   KC_F7,   KC_F8,   KC_F9,  KC_F12,   _______, _______, KC_LPRN, KC_RPRN,  KC_INS,  KC_DEL},
    {KC_PGDN,  KC_END,   KC_F4,   KC_F5,   KC_F6,  KC_F11,   _______, _______, KC_LBRC, KC_RBRC, KC_TILD,  KC_GRV},
    {_______, KC_MUTE,   KC_F1,   KC_F2,   KC_F3,  KC_F10,   _______, _______, KC_LCBR, KC_RCBR, KC_BSLS, KC_PIPE},
    {_______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______}
  },
  [_ADJUST] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {KC_DEL, KC_SLSH,   KC_UP, KC_BSLS, KC_LPRN, KC_RPRN,   _______,    KC_7,    KC_8,    KC_9, _______, _______},
    {KC_INS, KC_LEFT, KC_DOWN,KC_RIGHT, KC_LBRC, KC_RBRC,   KC_PPLS,    KC_4,    KC_5,    KC_6, KC_MINS, KC_UNDS},
    {_______, KC_SCLN, KC_LCBR, KC_RCBR, KC_LABK, KC_RABK,    KC_EQL,    KC_1,    KC_2,    KC_3,    KC_0, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};
