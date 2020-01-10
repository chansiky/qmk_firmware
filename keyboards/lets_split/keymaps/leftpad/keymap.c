#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12( \
 KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
 KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,\
 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT), \
  RAISE,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,    KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, LOWER \
),

[_COLEMAK] = LAYOUT_ortho_4x12( \
 _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,\
 _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,\
 _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,\
 _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______ \
),

[_DVORAK] = LAYOUT_ortho_4x12( \
 _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,\
 _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,\
 _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,\
 _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______ \
),

[_LOWER] = LAYOUT_ortho_4x12( \
  KC_GRV, KC_ENT ,   KC_7,    KC_8,    KC_9, KC_BSPC,    KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______, _______,\
 KC_QUOT, KC_MINS,   KC_4,    KC_5,    KC_6, KC_PPLS,    KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,\
 _______, KC_UNDS,   KC_1,    KC_2,    KC_3,  KC_EQL,    KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,\
 _______, _______,   KC_0,  KC_COMM, _______, KC_DOT,    _______, _______, _______, _______, _______, _______\
),

[_RAISE] = LAYOUT_ortho_4x12( \
  KC_DEL, KC_SLSH,   KC_UP, KC_BSLS, KC_LPRN, KC_RPRN,   _______, _______, KC_LPRN, KC_RPRN,  KC_INS,  KC_DEL, \
  KC_INS, KC_LEFT, KC_DOWN,KC_RIGHT, KC_LBRC, KC_RBRC,   _______, _______, KC_LBRC, KC_RBRC, KC_TILD,  KC_GRV, \
 _______, KC_SCLN, KC_LCBR, KC_RCBR, KC_LABK, KC_RABK,   _______, _______, KC_LABK, KC_RABK, KC_BSLS, KC_PIPE, \
 _______, _______, _______, _______, _______, _______,   _______, _______, KC_LCBR, KC_RCBR, _______, _______ \
),

[_ADJUST] =  LAYOUT_ortho_4x12( \
 KC_PGUP, KC_HOME,   KC_F7,   KC_F8,   KC_F9,  KC_F12,   _______,    KC_7,    KC_8,    KC_9, _______, _______, \
 KC_PGDN,  KC_END,   KC_F4,   KC_F5,   KC_F6,  KC_F11,   _______,    KC_4,    KC_5,    KC_6, KC_MINS, KC_PPLS, \
 _______, KC_MUTE,   KC_F1,   KC_F2,   KC_F3,  KC_F10,   _______,    KC_1,    KC_2,    KC_3, KC_UNDS,  KC_EQL, \
 _______, _______, _______, _______, _______, _______,      KC_0, _______, _______, _______, _______, _______ \
)

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
  }
  return true;
}
