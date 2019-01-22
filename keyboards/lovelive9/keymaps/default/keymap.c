#include QMK_KEYBOARD_H
#include "process_unicode.h"

//#include "v1.h"

//Following line allows macro to read current RGB settings

extern rgblight_config_t rgblight_config;
rgblight_config_t RGB_current_config;

//#include "rgblight.h"

//rgb led driver
//#include "ws2812.h"
//#include "ws2812.c"
//extern keymap_config_t keymap_config;
#define KC_KANJI KC_GRV
/*
const uint32_t PROGMEM unicode_map[]=
{
    0x9ED0,//beer
    0x203D,//hatching chick
    0x1F40D,//heart with arrow
    0x1f607,//innocent
    0x1f647,//bow
    0x1f914,//thinking face
    0x1f644,//rolling eye
    0x1f363, //sushi
    0x1f4b8,//money with wings
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
  _RUBY_SUB2,
  _RUBY_SUB3,
  _SCHOOL_IDOL_FESTIVAL
};

#define SEND_DIA 100
#define SEND_YOU 101
#define SEND_TIKA 102
#define SEND_ZURA 103
#define SEND_RUBY 104
#define SEND_YOHANE 105
#define SEND_RIKO 106
#define SEND_MARI 107
#define SEND_KANAN 108

//#define _RUBY_SUB1 112
//#define _RUBY_SUB2 113
//#define _RUBY_SUB3 114
//#define _SCHOOL_IDOL_FESTIVAL 115
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
  RUBY_SUB3,
  YOHANE,
  RIKO,
  MARI,
  KANAN,
  TO_SCHOOL_IDOL_FESTIVAL,
  RETURN_SCHOOL_IDOL_FESTIVAL
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
  [_RUBY_SUB3] = LAYOUT(
    TO_SCHOOL_IDOL_FESTIVAL, KC_DLR, KC_LBRC, RUBY_SUB1, RUBY, RUBY_SUB2, KC_PERC, KC_RBRC, RETURN_SCHOOL_IDOL_FESTIVAL
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
  ),
  [_SCHOOL_IDOL_FESTIVAL] = LAYOUT(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9
  ),
};

void check_tap_and_send_key(int MEMBER) {
  if(false) {
  //if (long_tap_timer < 400) {
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

int aqours_color_h[] = { 26, 340, 150,   0, 199, 220, 53, 265, 322};
int aqours_color_s[] = {255, 255, 255, 255, 255, 255, 255, 255, 255};
int aqours_color_v[] = {155, 155, 155, 155, 155, 155, 155, 155, 155};

void LED_default_set(void) {
  sethsv(aqours_color_h[2], aqours_color_s[2], aqours_color_v[2], (LED_TYPE *)&led[0]);
  sethsv(aqours_color_h[7], aqours_color_s[7], aqours_color_v[7], (LED_TYPE *)&led[1]);
  sethsv(aqours_color_h[1], aqours_color_s[1], aqours_color_v[1], (LED_TYPE *)&led[2]);
  sethsv(aqours_color_h[5], aqours_color_s[5], aqours_color_v[5], (LED_TYPE *)&led[3]);
  sethsv(aqours_color_h[8], aqours_color_s[8], aqours_color_v[8], (LED_TYPE *)&led[4]);
  sethsv(aqours_color_h[6], aqours_color_s[6], aqours_color_v[6], (LED_TYPE *)&led[5]);
  sethsv(aqours_color_h[0], aqours_color_s[0], aqours_color_v[0], (LED_TYPE *)&led[6]);
  sethsv(aqours_color_h[4], aqours_color_s[4], aqours_color_v[4], (LED_TYPE *)&led[7]);
  sethsv(aqours_color_h[3], aqours_color_s[3], aqours_color_v[3], (LED_TYPE *)&led[8]);
  rgblight_set();
}


void LED_layer_set(int aqours_index) {

  for (int c = 0; c < 9; c++) {
      sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index], (LED_TYPE *)&led[c]);
  }
  rgblight_set();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

    case DIA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_DIA);
        LED_layer_set(3);
      } else {
        check_tap_and_send_key(SEND_DIA);
        layer_off(_DIA);
        LED_default_set();
      }
      return false;
      break;

    case YOU:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_YOU);
        LED_layer_set(4);
      } else {
        check_tap_and_send_key(SEND_YOU);
        layer_off(_YOU);
        LED_default_set();
      }
      return false;
      break;

    case TIKA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_TIKA);
        LED_layer_set(0);
      } else {
        check_tap_and_send_key(SEND_TIKA);
        layer_off(_TIKA);
        LED_default_set();
      }
      return false;
      break;

    case ZURA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_ZURA);
        LED_layer_set(6);
      } else {
        check_tap_and_send_key(SEND_ZURA);
        layer_off(_ZURA);
        LED_default_set();
      }
      return false;
      break;

    case RUBY:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_RUBY);
        LED_layer_set(8);
      } else {
        check_tap_and_send_key(SEND_RUBY);
        layer_off(_RUBY);
        LED_default_set();
      }
      return false;
      break;
    case RUBY_SUB1:
      if (record->event.pressed) {
        layer_on(_RUBY_SUB1);
        if (IS_LAYER_ON(_RUBY_SUB1) && IS_LAYER_ON(_RUBY_SUB2)) {
          layer_on(_RUBY_SUB3);
        } else {
          layer_off(_RUBY_SUB3);
        }
      } else {
        layer_off(_RUBY_SUB1);
      }
      return false;
      break;
    case RUBY_SUB2:
      if (record->event.pressed) {
        layer_on(_RUBY_SUB2);
        if (IS_LAYER_ON(_RUBY_SUB1) && IS_LAYER_ON(_RUBY_SUB2)) {
          layer_on(_RUBY_SUB3);
        } else {
          layer_off(_RUBY_SUB3);
        }
      } else {
        layer_off(_RUBY_SUB2);
      }
      return false;
      break;

    case YOHANE:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_YOHANE);
        LED_layer_set(5);
      } else {
        check_tap_and_send_key(SEND_YOHANE);
        layer_off(_YOHANE);
        LED_default_set();
      }
      return false;
      break;

    case RIKO:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_RIKO);
        LED_layer_set(1);
      } else {
        check_tap_and_send_key(SEND_RIKO);
        layer_off(_RIKO);
        LED_default_set();
      }
      return false;
      break;

    case MARI:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_MARI);
        LED_layer_set(7);
      } else {
        check_tap_and_send_key(SEND_MARI);
        layer_off(_MARI);
        LED_default_set();
      }
      return false;
      break;

    case KANAN:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_KANAN);
        LED_layer_set(2);
      } else {
        check_tap_and_send_key(SEND_KANAN);
        layer_off(_KANAN);
        LED_default_set();
      }
      return false;
      break;

    case TO_SCHOOL_IDOL_FESTIVAL:
      if (record->event.pressed) {
        LED_default_set();
        layer_on(_SCHOOL_IDOL_FESTIVAL);
      }
      return false;
      break;
    case RETURN_SCHOOL_IDOL_FESTIVAL:
      if (record->event.pressed) {
        layer_off(_SCHOOL_IDOL_FESTIVAL);
      }
      return false;
      break;
  }

  if (IS_LAYER_ON(_SCHOOL_IDOL_FESTIVAL)) {
    switch (keycode) {

      case KC_1:
        if (record->event.pressed) {
          rgblight_sethsv_at(aqours_color_h[3], 255, 255, 8);
        } else {
          rgblight_sethsv_at(aqours_color_h[3], aqours_color_s[3], aqours_color_v[3], 8);
        }
        break;
      case KC_2:
        if (record->event.pressed) {
          rgblight_sethsv_at(aqours_color_h[4], 255, 255, 7);
        } else {
          rgblight_sethsv_at(aqours_color_h[4], aqours_color_s[4], aqours_color_v[4], 7);
        }
        break;
      case KC_3:
        if (record->event.pressed) {
          rgblight_sethsv_at(aqours_color_h[0], 255, 255, 6);
        } else {
          rgblight_sethsv_at(aqours_color_h[0], aqours_color_s[0], aqours_color_v[0], 6);
        }
        break;
      case KC_4:
        if (record->event.pressed) {
          rgblight_sethsv_at(aqours_color_h[6], 255, 255, 5);
        } else {
          rgblight_sethsv_at(aqours_color_h[6], aqours_color_s[6], aqours_color_v[6], 5);
        }
        break;
      case KC_5:
        if (record->event.pressed) {
          rgblight_sethsv_at(aqours_color_h[8], 255, 255, 4);
        } else {
          rgblight_sethsv_at(aqours_color_h[8], aqours_color_s[8], aqours_color_v[8], 4);
        }
        break;
      case KC_6:
        if (record->event.pressed) {
          rgblight_sethsv_at(aqours_color_h[5], 255, 255, 3);
        } else {
          rgblight_sethsv_at(aqours_color_h[5], aqours_color_s[5], aqours_color_v[5], 3);
        }
        break;
      case KC_7:
        if (record->event.pressed) {
          rgblight_sethsv_at(aqours_color_h[1], 255, 255, 2);
        } else {
          rgblight_sethsv_at(aqours_color_h[1], aqours_color_s[1], aqours_color_v[1], 2);
        }
        break;
      case KC_8:
        if (record->event.pressed) {
          rgblight_sethsv_at(aqours_color_h[7], 255, 255, 1);
        } else {
          rgblight_sethsv_at(aqours_color_h[7], aqours_color_s[7], aqours_color_v[7], 1);
        }
          break;
    case KC_9:
      if (record->event.pressed) {
        rgblight_sethsv_at(aqours_color_h[2], 255, 255, 0);
      } else {
        rgblight_sethsv_at(aqours_color_h[2], aqours_color_s[2], aqours_color_v[2], 0);
      }
      break;
      }
  }

  return true;
}
void matrix_init_user(void) {
  LED_default_set();
}

void matrix_scan_user(void) {

  if (long_tap_timer > 0) {
    long_tap_timer++;
  }
}
