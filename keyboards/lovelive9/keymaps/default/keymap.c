#include QMK_KEYBOARD_H

// Tap Dance Declarations
enum {
  ENT_5 = 0,
  ZERO_7
};

// Macro Declarations
enum {
  DBL_0 = 0
};


//extern keymap_config_t keymap_config;

enum layers {
  _BASE,
  _FUNC
};



#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   *         ,------.
   *         |   1  |
   *     ,------+------.
   *     |   2  |   3  |
   * ,------+------+------.
   * |   4  | FUNC |   6  |
   * `--------------------'
   */
  [0] = LAYOUT(
            KC_1,
         KC_2, KC_3,
    KC_4, MO(_FUNC), KC_6, KC_7, KC_8, KC_9
  )


};


/*
qk_tap_dance_action_t tap_dance_actions[] = {
  [KC_4] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_2),
  [KC_3] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_5)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
      switch(id) {
          case DBL_0:
              SEND_STRING("00");
              return false;
      }
  }
  return MACRO_NONE;
};
*/
void matrix_init_user(void) {
}
