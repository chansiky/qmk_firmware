#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_ortho_5x14(
   KC_TILD, KC_1,     KC_2,    KC_3,   KC_4,    KC_5,    KC_BSPC,   KC_INS,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,\
   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,   KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
   KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_RBRC,  KC_MINS,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,\
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LALT,  KC_RALT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT), \
    RAISE,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_LCTL,  KC_RCTL,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, LOWER \
  ),

  [_LOWER] = LAYOUT_ortho_5x14(
  _______, _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______, _______, _______, _______,\
   KC_GRV, KC_COMM,    KC_7,    KC_8,    KC_9,  KC_DOT,    _______,  _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______,\
  KC_MINS,    KC_0,    KC_4,    KC_5,    KC_6, KC_PPLS,    _______,  _______, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, KC_MINS,\
  _______, KC_UNDS,    KC_1,    KC_2,    KC_3,  KC_EQL,    _______,  _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_UNDS, _______,\
  _______, _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______, _______, _______, _______ \
  ),

  [_RAISE] = LAYOUT_ortho_5x14(
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,\
   KC_DEL, KC_LPRN, KC_SLSH,   KC_UP, KC_BSLS, KC_RPRN,  _______,  _______, _______, KC_INS, KC_LPRN, KC_RPRN,  KC_PIPE,  KC_DEL,\
  KC_CAPS, KC_LBRC, KC_LEFT, KC_DOWN,KC_RIGHT, KC_RBRC,  _______,  _______, _______, KC_LCBR, KC_LBRC, KC_RBRC,  KC_RCBR, KC_GRV,\
  KC_ENT,KC_LCBR,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,KC_RCBR,_______, _______, _______, _______, KC_LABK, KC_RABK, KC_BSLS, _______,\
  _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______ \
  ),

  [_ADJUST] = LAYOUT_ortho_5x14(
  _______, _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______, _______, _______, _______,\
  KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12,  KC_PGUP, _______,  _______, KC_PAST, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______,\
  KC_HOME,   KC_F4,   KC_F5,   KC_F6,  KC_F11,  KC_END,  _______,  _______, KC_PPLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_0, KC_PMNS,\
  _______,   KC_F1,   KC_F2,   KC_F3,  KC_F10,  KC_PGDN, _______,  _______, KC_EQL, KC_KP_1,  KC_KP_2, KC_KP_3, KC_UNDS, _______,\
  _______, _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______, _______, _______, _______ \
  )
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
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
