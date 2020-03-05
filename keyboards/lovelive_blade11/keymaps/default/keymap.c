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
  _LOCK,
  _PARTY,
};



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
  TO_PARTY,
  TO_QWERTY,
  RAINBOW,
  STREAM,
  ANARCHY,
  SNOW_HALATION,
};
int aqours_index = 0;
int aqours_led_anim_index = 0;

int pov_mode = 0;
#define ELECTRIC_BOARD_LENGTH 52
int electric_board_data[5][ELECTRIC_BOARD_LENGTH] = {
  {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0},
  {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0},
  {0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0},
  {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0},
  {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
};
/*
  ■                    ■    ■               ■   ■
■■■■■               ■■■■■■■  ■              ■     ■
  ■      ■■■■■■        ■         ■■■■■■     ■■
■■■■■               ■  ■  ■                 ■  ■■
  ■                ■   ■   ■                ■
  */
int read_num = 0;
int pov_switch_time = 100;
int pov_switch_count =0;

#define _______ KC_TRNS

int long_tap_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    TIKA, RIKO, KANAN, DIA, YOU, YOHANE, ZURA, MARI, RUBY, RGB_TOG, TG(_LOCK)
  ),
  [_LOCK] = LAYOUT(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, TO_PARTY, RGB_TOG, KC_TRNS
  ),
  [_PARTY] = LAYOUT(
    RAINBOW, STREAM, ANARCHY, SNOW_HALATION, KC_5, KC_6, KC_7, KC_8, TO_QWERTY, RGB_TOG, KC_TRNS
  ),
};

int aqours_color_h[] = { 26, 340, 150,   0, 199, 220, 53, 265, 322};
int aqours_color_s[] = {255, 165, 255, 255, 255, 350, 255, 255, 255};
int aqours_color_v[] = {255, 255, 255, 255, 255, 255, 200, 255, 255};



void LED_layer_set(int aqours_index) {
  //i2c_init();
  //i2c_send(0xb0, (uint8_t*)led, 3 * RGBLED_NUM);
  for (int c = 0; c < 16; c++) {
      sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index], (LED_TYPE *)&led[c]);
  }
  rgblight_set();
}

int mode_rainbow = false;
int mode_stream = false;
int mode_anarchy = false;
int mode_snow_halation = false;

void mode_reset(void) {
  mode_rainbow = false;
  mode_stream = false;
  mode_anarchy = false;
  mode_snow_halation = false;
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

    case DIA:
      if (record->event.pressed) {
        aqours_index = 3;
        aqours_led_anim_index = 0;
        SEND_STRING("KUROSAWA DIYA");
      }
      return false;
      break;

    case YOU:
      if (record->event.pressed) {
        aqours_index = 4;
        aqours_led_anim_index = 0;
        SEND_STRING("WATANABE YOU");
      }
      return false;
      break;

    case TIKA:
      if (record->event.pressed) {
        aqours_index = 0;
        aqours_led_anim_index = 0;
        SEND_STRING("TAKAMI TIKA");
      }
      return false;
      break;

    case ZURA:
      if (record->event.pressed) {
        aqours_index = 6;
        aqours_led_anim_index = 0;
        SEND_STRING("KUNIKIDA HANAMARU");
      }
      return false;
      break;

    case RUBY:
      if (record->event.pressed) {
        aqours_index = 8;
        aqours_led_anim_index = 0;
        SEND_STRING("KUROSAWA RUBY");
      }
      return false;
      break;
    case YOHANE:
      if (record->event.pressed) {
        aqours_index = 5;
        aqours_led_anim_index = 0;
        SEND_STRING("TSUSHIMA YOSHIKO");
      }
      return false;
      break;

    case RIKO:
      if (record->event.pressed) {
        aqours_index = 1;
        aqours_led_anim_index = 0;
        SEND_STRING("SAKURAUCHI RIKO");
      }
      return false;
      break;

    case MARI:
      if (record->event.pressed) {
        aqours_index = 7;
        aqours_led_anim_index = 0;
        SEND_STRING("OHARA MARI");
      }
      return false;
      break;

    case KANAN:
      if (record->event.pressed) {
        aqours_index = 2;
        aqours_led_anim_index = 0;
        SEND_STRING("MATSUURA KANAN");
      }
      return false;
      break;

    case RAINBOW:
      if (record->event.pressed) {
        mode_reset();
        mode_rainbow = true;
        SEND_STRING("RAINBOW");
      }
      return false;
    break;

    case STREAM:
      if (record->event.pressed) {
        mode_reset();
        mode_stream = true;
        SEND_STRING("STREAM");
      }
      return false;
    break;

    case ANARCHY:
      if (record->event.pressed) {
        mode_reset();
        mode_anarchy = true;
        SEND_STRING("ANARCHY");
      }
      return false;
    break;

    case SNOW_HALATION:
      if (record->event.pressed) {
        mode_reset();
        mode_snow_halation = true;
        SEND_STRING("SNOW");
      }
      return false;
    break;

    case TO_QWERTY:
      if (record->event.pressed) {
        layer_on(_QWERTY);
      }
      return false;
    break;

    case TO_PARTY:
      if (record->event.pressed) {
        layer_on(_PARTY);
      }
      return false;
    break;
  }
  return true;
}


int aqours_led_timer_count = 0;
//int aqours_led_auto_timer_count = 0;
void aqours_led(void) {
  aqours_led_timer_count++;
  if (aqours_led_timer_count > 500) {
    aqours_led_timer_count = 0;
    if (aqours_led_anim_index < 6) {
      sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index]-30, (LED_TYPE *)&led[aqours_led_anim_index]);
      sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index]-30, (LED_TYPE *)&led[11-aqours_led_anim_index]);
      aqours_led_anim_index++;
      rgblight_set();
    }
  }
}


void matrix_init_user(void) {
  LED_layer_set(3);
  //qk_ucis_start();
  //set_unicode_input_mode(UC_WIN);
  /*
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
  */
}

int time_count = 0;
void led_rainbow(void) {
  if(time_count > 500) {
    for (int k=0;k<12;k++) {
      sethsv(360/12*k, 255, 255, (LED_TYPE *)&led[k]);
      time_count = 0;
    }
    rgblight_set();
  }
}


int stream_count = 0;
void led_stream(void) {
  if(time_count > 500) {
    stream_count++;
    for (int k=0;k<12;k++) {
      sethsv(360/12*k, 255, 255, (LED_TYPE *)&led[(k+stream_count) % 12]);
      time_count = 0;
    }
    rgblight_set();
    if (stream_count > 1000) {
      stream_count = 0;
    }
  }
}


void led_anarchy(void) {
  if(time_count > 100) {
    for (int k=0;k<12;k++) {
      sethsv(rand()%360, 255, 255, (LED_TYPE *)&led[k]);
      time_count = 0;
    }
    rgblight_set();
  }
}

void led_snow_halation(void) {
  if(time_count > 400) {
    for (int k=0;k<6;k++) {
      sethsv(26, 255, 255, (LED_TYPE *)&led[k*2]);
      sethsv(26, 30, 255, (LED_TYPE *)&led[k*2+1]);
      rgblight_set();
      time_count = 0;
    }
  }
}
void matrix_scan_user(void) {

    time_count++;
    if (time_count > 10000) {
      time_count = 0;
    }
    if (mode_rainbow) {
      led_rainbow();
    }
    if (mode_stream) {
      led_stream();
    }
    if (mode_anarchy) {
      led_anarchy();
    }
    if (mode_snow_halation) {
      led_snow_halation();
    }
    aqours_led();
}
