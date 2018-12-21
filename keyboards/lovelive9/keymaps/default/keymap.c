#include QMK_KEYBOARD_H




//extern keymap_config_t keymap_config;

#define KC_KANJI KC_GRV
/*
#define _DIA 2
#define _YOU 3
#define _TIKA 4
#define _ZURA 5
#define _RUBY 6
#define _YOHANE 7
#define _RIKO 8
#define _MARI 9
#define _KANAN 10
*/
/*
enum Layer
{
  _QWERTY,
  DIA,
  YOU,
  TIKA,
  ZURA,
  RUBY,
  YOHANE,
  RIKO,
  MARI,
  KANAN
};
*/
enum Layer
{
  _QWERTY,
  _DIA,
  _YOU,
  _TIKA,
  _ZURA,
  _RUBY,
  _YOHANE,
  _RIKO,
  _MARI,
  _KANAN,
  _RUBY_SUB1,
  _RUBY_SUB2
};
/*
#define _QWERTY 0
#define _DIA 3
#define _YOU 4
#define _TIKA 5
#define _ZURA 6
#define _RUBY 7
#define _YOHANE 8
#define _RIKO 9
#define _MARI 10
#define _KANAN 11
*/
#define SEND_DIA 100
#define SEND_YOU 101
#define SEND_TIKA 102
#define SEND_ZURA 103
#define SEND_RUBY 104
#define SEND_YOHANE 105
#define SEND_RIKO 106
#define SEND_MARI 107
#define SEND_KANAN 108

#define _RUBY_SUB1 12
#define _RUBY_SUB2 13
//#define _CATLOCK 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DIA,
  YOU,
  TIKA,
  ZURA,
  RUBY,
  RUBY_SUB1,
  RUBY_SUB2,
  YOHANE,
  RIKO,
  MARI,
  KANAN
};

#define _______ KC_TRNS

int long_tap_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    //KC_1, KC_2, KC_3,KC_4, KC_5, KC_6, KC_7, KC_8, KC_9
    DIA, YOU, TIKA, ZURA, RUBY, YOHANE, RIKO, MARI, KANAN
//LTはカスタムキーコードも使えないので没
    //LT(_DIA, KC_A), LT(_YOU, KC_B), LT(_TIKA, KC_C), LT(_ZURA, SEND_ZURA), LT(_RUBY, SEND_RUBY), LT(_YOHANE, SEND_YOHANE), LT(_RIKO, SEND_RIKO), LT(_MARI, SEND_MARI), LT(_KANAN, SEND_KANAN)
  ),
  [_DIA] = LAYOUT(
    DIA, KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_LSFT
  ),

  [_YOU] = LAYOUT(
    KC_H, YOU, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_LSFT
  ),

  [_TIKA] = LAYOUT(
    KC_O, KC_P, TIKA, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_LSFT
  ),

  [_ZURA] = LAYOUT(
    KC_V, KC_W, KC_X, ZURA, KC_Y, KC_Z, KC_M, KC_N, KC_LSFT
  ),

//推しをたくさん押せるようにルビーちゃんには複数のレイヤー設定
  [_RUBY] = LAYOUT(
    KC_CIRC, KC_LPRN, KC_QUOT, RUBY_SUB1, RUBY, RUBY_SUB2, KC_LCBR, KC_EXLM, KC_LSFT
  ),
  [_RUBY_SUB1] = LAYOUT(
    KC_RCBR, KC_AT, KC_PIPE, RUBY_SUB1, RUBY, RUBY_SUB2, KC_HASH, KC_EQL, KC_LSFT
  ),
  [_RUBY_SUB2] = LAYOUT(
    KC_TILD, KC_DLR, KC_LBRC, RUBY_SUB1, RUBY, RUBY_SUB2, KC_PERC, KC_RBRC, KC_LSFT
  ),

  [_YOHANE] = LAYOUT(
    KC_0, KC_1, KC_2, KC_3, KC_4, YOHANE, KC_5, KC_6, KC_LSFT
  ),

  [_RIKO] = LAYOUT(
    KC_7, KC_8, KC_9, KC_PLUS, KC_MINS, KC_ASTR, RIKO, KC_SLSH, KC_LSFT
  ),

  [_MARI] = LAYOUT(
    KC_TAB, KC_DEL, KC_COMM, KC_SPC, KC_ENT, KC_BSPC, KC_DOT, MARI, KC_LSFT
  ),

  [_KANAN] = LAYOUT(
    KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_ENT, KC_BSPC, KC_AMPR, KC_KANJI, KANAN
  )
};

void check_tap_and_send_key(int MEMBER) {
  if (long_tap_timer < 400) {
    switch (MEMBER) {
      case SEND_DIA:
        SEND_STRING("KUROSAWA DIYA");
      break;
      case SEND_YOU:
        SEND_STRING("WATANABE YOU");
      break;
      case SEND_TIKA:
        SEND_STRING("TAKAMI TIKA");
      break;
      case SEND_ZURA:
        SEND_STRING("KUNIKIDA HANAMARU");
      break;
      case SEND_RUBY:
        SEND_STRING("KUROSAWA RUBY");
      break;
      case SEND_YOHANE:
        SEND_STRING("TSUSHIMA YOSHIKO");
      break;
      case SEND_RIKO:
        SEND_STRING("SAKURAUCHI RIKO");
      break;
      case SEND_MARI:
        SEND_STRING("OHARA MARI");
      break;
      case SEND_KANAN:
        SEND_STRING("MATSUURA KANAN");
      break;
      }
  }
  long_tap_timer = 0;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
/*
    case SEND_DIA:
      if (record->event.pressed) {
        SEND_STRING("DIA");
      }
      return false;
      break;
    case SEND_YOU:
      if (record->event.pressed) {
        SEND_STRING("YOU");
      }
      return false;
      break;
    case SEND_TIKA:
      if (record->event.pressed) {
        SEND_STRING("TIKA");
      }
      return false;
      break;
    case SEND_ZURA:
      if (record->event.pressed) {
        SEND_STRING("ZURA");
      }
      return false;
      break;
    case SEND_RUBY:
      if (record->event.pressed) {
        SEND_STRING("RUBY");
      }
      return false;
      break;
    case SEND_YOHANE:
      if (record->event.pressed) {
        SEND_STRING("YOHANE");
      }
      return false;
      break;
    case SEND_RIKO:
      if (record->event.pressed) {
        SEND_STRING("RIKO");
      }
      return false;
      break;
    case SEND_MARI:
      if (record->event.pressed) {
        SEND_STRING("MARI");
      }
      return false;
      break;
    case SEND_KANAN:
      if (record->event.pressed) {
        SEND_STRING("KANAN");
      }
      return false;
      break;
*/
    case DIA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_DIA);
      } else {
        check_tap_and_send_key(SEND_DIA);
        layer_off(_DIA);
      }
      return false;
      break;

    case YOU:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_YOU);
      } else {
        check_tap_and_send_key(SEND_YOU);
        layer_off(_YOU);
      }
      return false;
      break;

    case TIKA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_TIKA);
      } else {
        check_tap_and_send_key(SEND_TIKA);
        layer_off(_TIKA);
      }
      return false;
      break;

    case ZURA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_ZURA);
      } else {
        check_tap_and_send_key(SEND_ZURA);
        layer_off(_ZURA);
      }
      return false;
      break;

    case RUBY:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_RUBY);
      } else {
        check_tap_and_send_key(SEND_RUBY);
        layer_off(_RUBY);
      }
      return false;
      break;

    case RUBY_SUB1:
      if (record->event.pressed) {
        layer_on(_RUBY_SUB1);
      } else {
        layer_off(_RUBY_SUB1);
      }
      return false;
      break;
    case RUBY_SUB2:
      if (record->event.pressed) {
        layer_on(_RUBY_SUB2);
      } else {
        layer_off(_RUBY_SUB2);
      }
      return false;
      break;

    case YOHANE:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_YOHANE);
      } else {
        check_tap_and_send_key(SEND_YOHANE);
        layer_off(_YOHANE);
      }
      return false;
      break;

    case RIKO:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_RIKO);
      } else {
        check_tap_and_send_key(SEND_RIKO);
        layer_off(_RIKO);
      }
      return false;
      break;

    case MARI:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_MARI);
      } else {
        check_tap_and_send_key(SEND_MARI);
        layer_off(_MARI);
      }
      return false;
      break;

    case KANAN:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_KANAN);
      } else {
        check_tap_and_send_key(SEND_KANAN);
        layer_off(_KANAN);
      }
      return false;
      break;

  }

  return true;
}
void matrix_init_user(void) {
}

void matrix_scan_user(void) {
  if (long_tap_timer > 0) {
    long_tap_timer++;
  }
}
