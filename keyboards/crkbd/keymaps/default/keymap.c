#include QMK_KEYBOARD_H
#include "bootloader.h"

//#include "action_layer.h"
//#include "action_util.h"
//#include "eeconfig.h"
//#include "keymap_jp.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef COMPILE_SUB
#include "../lib/mode_icon_reader.c"
#include "../lib/layer_state_reader.c"
#include "../lib/host_led_state_reader.c"
//#include "../lib/logo_reader.c"
#include "../lib/keylogger.c"
#include "../lib/timelogger.c"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

//extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  RGB_MODE_NEON,
  RGB_MODE_ANARCHY
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_KANJI KC_GRV

#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADJUST ADJUST
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSMOD RGB_SMOD
#define KC_LPLAIN  RGB_MODE_PLAIN
#define KC_LBREATHE  RGB_MODE_BREATHE
#define KC_LRAINBOW  RGB_MODE_RAINBOW
#define KC_LSWIRL  RGB_MODE_SWIRL
#define KC_LSNAKE  RGB_MODE_SNAKE
#define KC_LNIGHT  RGB_MODE_KNIGHT
#define KC_LXMAS  RGB_MODE_XMAS
#define KC_LGRADIENT  RGB_MODE_GRADIENT
#define KC_LTEST RGB_MODE_RGBTEST
#define KC_LNEON RGB_MODE_NEON
#define KC_LANARCHY RGB_MODE_ANARCHY
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP
#define KC_GUAP  LALT_T(KC_APP)
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {20, 20, 5};
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {2, 50, 50};
const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {25, 50, 50};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        BSPC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     A,     S,     D,     F,     G,                      H,     J,     K,     L,    UP,   KANJI,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LCTRL,     Z,     X,     C,     V,     B,                      N,     M,  COMM,  LEFT,  DOWN,  RGHT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER,  SPC,      ENT, RAISE,  GUAP \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,    F1,    F2,    F3,    F4,    F5,                  XXXXX,  MINS,   EQL,  JYEN,  LBRC,  RBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TAB,    F6,    F7,    F8,    F9,   F10,                  XXXXX, XXXXX, XXXXX,  SCLN,  QUOT,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,   F11,   F12, XXXXX, KANJI,   ENT,                  XXXXX, XXXXX,  COMM,   DOT,  SLSH,    RO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____,   DEL,    XXXXX, _____,   APP \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,     4,     5,     6,  QUOT, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                      0,     1,     2,     3,   DOT, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, XXXXX,    XXXXX, _____,  LALT \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST,  KNRM,  KSWP, LPLAIN, LRAINBOW,             LSWIRL, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, LSNAKE, LNIGHT,                LTEST, XXXXX, XXXXX, XXXXX,  PGUP, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LSMOD,  LHUD,  LSAD,  LVAD, LXMAS, LGRADIENT,              LNEON, LANARCHY, XXXXX,  HOME,  PGDN,   END,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, XXXXX,    XXXXX, _____, XXXXX \
                              //`--------------------'  `--------------------'
  )
};


int RGB_current_mode;
int press_state = 0;
int press_count = 0;
int neon_mode = 0;
bool led_anarchy = false;

#ifdef COMPILE_MAIN
char miku[2][4][21] = {
  {
    { 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    { 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}
  },
  {
    { 0x21+12, 0x22+12, 0x23+12, 0x24+12, 0x25+12, 0x26+12, 0x27+12, 0x28+12, 0x29+12, 0x2a+12, 0x2b+12, 0x2c+12, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    { 0x41+12, 0x42+12, 0x43+12, 0x44+12, 0x45+12, 0x46+12, 0x47+12, 0x48+12, 0x49+12, 0x4a+12, 0x4b+12, 0x4c+12, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    { 0x61+12, 0x62+12, 0x63+12, 0x64+12, 0x65+12, 0x66+12, 0x67+12, 0x68+12, 0x69+12, 0x6a+12, 0x6b+12, 0x6c+12, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    { 0x81+12, 0x82+12, 0x83+12, 0x84+12, 0x85+12, 0x86+12, 0x87+12, 0x88+12, 0x89+12, 0x8a+12, 0x8b+12, 0x8c+12, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}
  }
};



bool miku_switch = true;
int smile = 0;
void oled_mode_write(int mode)
{
  if (mode == 0) {
    for(int i=0; i<=1; i++ ) {
      miku[i][1][14] = 0x01;
      miku[i][1][15] = 0x01;
      miku[i][1][16] = 0x01;
      miku[i][2][14] = 0x01;
      miku[i][2][15] = 0x01;
      miku[i][2][16] = 0x01;
    }
  }
  if (mode == 1) {
    for(int i=0; i<=1; i++ ) {
      miku[i][1][14] = 0x39;
      miku[i][1][15] = 0x3a;
      miku[i][1][16] = 0x3b;
      miku[i][2][14] = 0x59;
      miku[i][2][15] = 0x5a;
      miku[i][2][16] = 0x5b;
    }
  }
  if (mode == 2) {
    for(int i=0; i<=1; i++ ) {
      miku[i][1][14] = 0x79;
      miku[i][1][15] = 0x7a;
      miku[i][1][16] = 0x7b;
      miku[i][2][14] = 0x99;
      miku[i][2][15] = 0x9a;
      miku[i][2][16] = 0x9b;
    }
  }
  if (mode == 3) {
    for(int i=0; i<=1; i++ ) {
      miku[i][1][14] = 0x3c;
      miku[i][1][15] = 0x3d;
      miku[i][1][16] = 0x3e;
      miku[i][2][14] = 0x5c;
      miku[i][2][15] = 0x5d;
      miku[i][2][16] = 0x5e;
    }
  }
}
#endif
/*

*/
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
#ifdef COMPILE_MAIN
    oled_mode_write(1);
#endif
  } else {
    layer_off(layer3);
    //oled_mode_write(0);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

#define WEIGHT 10 // ミリ秒
int pikapika = 0;
int step_pika = 30;

void noizy_led(void) {
  static int last_time = 0;
  if (timer_elapsed(last_time) > WEIGHT) {
    last_time = timer_read();
    for(int i=0; i<=5; i++ ) {
      int brightness = 255;
      if (pikapika % 8 == 1) {
        brightness = 50;
      }
      if (pikapika % 8 == 4) {
        brightness = 150;
      }
      if (i % 2 == 0) {
        rgblight_sethsv_at((360/step_pika*(pikapika)) % 360, brightness, 125, i);
      } else {
        rgblight_sethsv_at((360/step_pika*((pikapika+step_pika/2))) % 360, brightness, 125, i);
      }
    }
    pikapika++;
    if (pikapika == step_pika) {
      pikapika = 0;
    }
  }
}
// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
   if (neon_mode) {
     noizy_led();
   }
}


void matrix_render_user(struct CharacterMatrix *matrix) {
  //struct CharacterMatrix matrix;
  //is_master
  #ifdef COMPILE_MAIN
  if (smile > 0) {
    smile += -1;
    if (smile == 0) {
      miku[0][2][8] = 0x69;
      miku[0][2][9] = 0x6a;
      miku[1][2][8] = 0x75;
      miku[1][2][9] = 0x76;
    }
  }
    if(miku_switch) {
      matrix_write_ln(matrix, miku[0][0]);
      matrix_write_ln(matrix, miku[0][1]);
      matrix_write_ln(matrix, miku[0][2]);
      matrix_write(matrix, miku[0][3]);
      miku_switch = false;
    } else {
      matrix_write_ln(matrix, miku[1][0]);
      matrix_write_ln(matrix, miku[1][1]);
      matrix_write_ln(matrix, miku[1][2]);
      matrix_write(matrix, miku[1][3]);
      miku_switch = true;
    }
  #endif

  #ifdef COMPILE_SUB
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  #endif

}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

int smile_key_count;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef COMPILE_MAIN
  if (record->event.pressed) {
    smile_key_count++;
    if(smile_key_count == 50) {
      smile = 8;
      smile_key_count = 0;
      miku[0][2][8] = 0x02;
      miku[0][2][9] = 0x03;
      miku[1][2][8] = 0x05;
      miku[1][2][9] = 0x06;
    }
    //set_keylog(keycode, record);
    //set_timelog();
  }
  #endif
  if (led_anarchy) {
    if (record->event.pressed) {
      for(int i=0; i<=6; i++ ) {
        rgblight_sethsv_at(360/6*i, 255, 125, i);
      }
    } else {
      for(int i=0; i<=6; i++ ) {
        rgblight_sethsv_at(360/14*press_count, 255, 125, i);
      }

      press_count++;
      if (press_count == 14) {
        press_count = 0;
      }
    }
  }
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        #ifdef COMPILE_MAIN
          oled_mode_write(3);
        #endif
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        #ifdef COMPILE_MAIN
          oled_mode_write(0);
        #endif
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        #ifdef COMPILE_MAIN
          oled_mode_write(2);
        #endif
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef COMPILE_MAIN
          oled_mode_write(0);
        #endif
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    //治安が最悪のモード
    case RGB_MODE_ANARCHY:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
            if (led_anarchy == 1) {
              led_anarchy = 0;
            } else {
              led_anarchy = 1;
            }
        }
      #endif
      break;
    //キータッチごとに色が変わる
    case RGB_MODE_NEON:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = 1;
            if (neon_mode == 1) {
              neon_mode = 0;
            } else {
              neon_mode = 1;
            }
        }
      #endif
      break;
  }
  return true;
}

#endif
