#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

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

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_AJST ADJUST
#define KC_LOWR LOWER
#define KC_RASE RAISE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 */
  [_QWERTY] = LAYOUT_kc(
  //    ,----+       ----+   ----+   ----+   ----+   ----+   ----.    ,   ----+   ----+   ----+   ----+   ----+   ----+   ----.
         PGUP,    GRV,    1  ,    2  ,    3  ,    4  ,    5  ,         6  ,    7 ,    8  ,    9  ,    0  ,   BSPC,   DEL,
  //    |----+       ----+   ----+   ----+   ----+   ----+   ----|    |   ----+   ----+   ----+   ----+   ----+   ----+   ----|
         PGDN,    TAB,    Q  ,    W  ,    E  ,    R  ,    T  ,         Y  ,    U ,    I  ,    O  ,    P  ,   LBRC,  RBRC,
  //    |----+       ----+   ----+   ----+   ----+   ----+   ----|    |   ----+   ----+   ----+   ----+   ----+   ----+   ----|
         HOME,    ESC,    A  ,    S  ,    D  ,    F  ,    G  ,         H  ,    J ,    K  ,    L  ,   SCLN,   QUOT,   ENT,
  //    |----+       ----+   ----+   ----+   ----+   ----+   ----|    |   ----+   ----+   ----+   ----+   ----+   ----+   ----|
          END,   LSFT,    Z  ,    X  ,    C  ,    V  ,    B  ,         N  ,    M ,   COMM,   DOT ,   SLSH,   RSFT,  BSLS,
  //`    ----+       ----+   ----+   ----+   ----+   ----+   ----'    `   ----+   ----+   ----+   ----+   ----+   ----+   ----|
         BTN1,   BTN2,   LCTL,   LALT,   LGUI,   LOWR,   SPC ,        SPC ,  RASE,   RGUI,   RALT,   RCTL,    ENT,  EQL
  //`    ----+   ----+  ----+   ----+   ----+   ----+   ----'    `        ----+   ----+   ----+   ----+   ----+   ----+   ----'
  ),

/* Lower
*/
  [_LOWER] = LAYOUT_kc(
  //,----   +----   +   ----+   ----+   ----+   ----+   ----.    ,   ----+   ----+   ----+   ----+   ----+   ----+   ----.
            ,       ,       ,       ,       ,       ,       ,            ,       ,       ,       ,       ,       ,       ,
  //|----   +----   +   ----+   ----+   ----+   ----+   ----|    |   ----+   ----+   ----+   ----+   ----+   ----+   ----|
            ,       ,     F9,    F10,    F11,    F12,       ,            ,      7,      8,      9,   SLSH,   PAST,       ,
  //|----   +----   +   ----+   ----+   ----+   ----+   ----|    |   ----+   ----+   ----+   ----+   ----+   ----+   ----|
            ,       ,     F5,     F6,     F7,     F8,       ,            ,      4,      5,      6,   MINS,    EQL,       ,
  //|----   +----   +   ----+   ----+   ----+   ----+   ----|    |   ----+   ----+   ----+   ----+   ----+   ----+   ----|
            ,       ,     F1,     F2,     F3,     F4,       ,            ,      1,      2,      3,   UNDS,   PPLS,       ,
  //|----   +----   +   ----+   ----+   ----+   ----+   ----|    |   ----+   ----+   ----+   ----+   ----+   ----+   ----|
            ,       ,       ,       ,       ,       ,       ,            ,      0,       ,       ,       ,       ,
  //`----   +----   +   ----+   ----+   ----+   ----+   ----'    `   ----+   ----+   ----+   ----+   ----+   ----+   ----'
  ),

/* Raise
 */
  [_RAISE] = LAYOUT_kc(
  //,----   +----   +   ----+   ----+   ----+   ----+   ----.    ,          ----+   ----+   ----+   ----+   ----+   ----+
            ,       ,       ,       ,       ,       ,       ,            ,      ,      ,        ,       ,       ,       ,
  //|----   +----   +   ----+   ----+   ----+   ----+   ----|    |          ----+   ----+   ----+   ----+   ----+   ----|
            ,       ,   TILD,   HOME,     UP,    END,   PGUP,            ,   INS,   LPRN,   RPRN,    INS,       ,       ,
  //|----   +----   +   ----+   ----+   ----+   ----+   ----|    |          ----+   ----+   ----+   ----+   ----+   ----|
            ,   CAPS,    GRV,   LEFT,   DOWN,  RIGHT,   PGDN,            ,   DEL,   LBRC,   RBRC,   PIPE,    ENT,       ,
  //|----   +----   +   ----+   ----+   ----+   ----+   ----|    |          ----+   ----+   ----+   ----+   ----+   ----|
            ,       ,   BRID,   BRIU,   VOLD,   VOLU,   MUTE,            ,  BSPC,   LCBR,   RCBR,   BSLS,       ,       ,
  //|----   +----   +   ----+   ----+   ----+   ----+   ----|    |          ----+   ----+   ----+   ----+   ----+   ----|
            ,       ,       ,       ,       ,       ,       ,            ,      ,       ,       ,       ,       ,
  //`----   +----   +   ----+   ----+   ----+   ----+   ----'    `          ----+   ----+   ----+   ----+   ----+   ----'
  ),

  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
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
