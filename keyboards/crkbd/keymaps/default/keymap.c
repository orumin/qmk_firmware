
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

#ifdef COMPILE_NO_MIKU
  //#include "../lib/mode_icon_reader.c"
  #include "../lib/layer_state_reader.c"
  //#include "../lib/host_led_state_reader.c"
  //#include "../lib/logo_reader.c"
  //#include "../lib/keylogger.c"
  //#include "../lib/timelogger.c"
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

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};
//#define _CATLOCK 5
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  #ifdef COMPILE_MIKU
  LOWER,
  RAISE,
  ADJUST,
  #endif
  BACKLIT,
  RGBRST,
  RGB_MODE_NEON,
  RGB_MODE_ANARCHY/*,
  CAT_LOCK1,
  CAT_LOCK2,
  CAT_RETURN1,
  CAT_RETURN2*/
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

#define KC_LCATLOCK1 CAT_LOCK1
#define KC_LCATLOCK2 CAT_LOCK2
#define KC_LCATRETURN1 CAT_RETURN1
#define KC_LCATRETURN2 CAT_RETURN2

#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP
#define KC_GUAP  LALT_T(KC_APP)
//const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {20, 20, 5};
//const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {2, 50, 50};
//const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {25, 50, 50};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  #ifdef COMPILE_MIKU
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_BSPC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P, KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LSFT,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                   KC_H,  KC_J,  KC_K,  KC_L, KC_UP, KC_KANJI,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
   KC_LCTRL,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                   KC_N,  KC_M, KC_COMM, KC_LEFT, KC_DOWN, KC_RGHT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   KC_LGUI, LOWER, KC_SPC,      KC_ENT, RAISE, KC_GUAP \
                              //`--------------------'  `--------------------'
  ),
  [_LOWER] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_ESC,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                  KC_NO, KC_MINS, KC_EQL, KC_JYEN, KC_LBRC, KC_RBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TAB,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,      KC_LSPO, KC_NO, KC_NO,  KC_SCLN,  KC_QUOT,  KC_BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_TRNS,   KC_F11,   KC_F12, KC_NO, KC_KANJI, KC_ENT,        KC_RSPC, KC_NO,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_RO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  KC_TRNS, KC_TRNS, KC_DEL,    KC_NO, KC_TRNS, KC_APP \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
      KC_TRNS,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                   KC_6,  KC_7,  KC_8,  KC_9,  KC_0, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO,  KC_4,  KC_5,  KC_6, KC_QUOT, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_0,  KC_1,  KC_2,  KC_3, KC_DOT, KC_NO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  KC_TRNS, KC_TRNS, KC_NO,    KC_NO, KC_TRNS, KC_LALT \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
        KC_RST,  KC_LRST,  KC_KNRM,  KC_KSWP, KC_LPLAIN, KC_LRAINBOW,             KC_LSWIRL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       KC_LTOG,  KC_LHUI,  KC_LSAI,  KC_LVAI, KC_LSNAKE, KC_LNIGHT,                KC_LTEST, KC_NO, KC_NO, KC_NO,  KC_PGUP, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_LSMOD,  KC_LHUD,  KC_LSAD,  KC_LVAD, KC_LXMAS, KC_LGRADIENT,              KC_LNEON, KC_LANARCHY, KC_NO,  KC_HOME, KC_PGDN, KC_END,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  KC_TRNS, KC_TRNS, KC_NO,    KC_NO, KC_TRNS, KC_NO \
                              //`--------------------'  `--------------------'
  )
  #endif

  #ifdef COMPILE_NO_MIKU
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_BSPC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P, KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LSFT,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                   KC_H,  KC_J,  KC_K,  KC_L, KC_UP, KC_KANJI,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
   KC_LCTRL,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                   KC_N,  KC_M, KC_COMM, KC_LEFT, KC_DOWN, KC_RGHT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   KC_LGUI, KC_1, KC_SPC,      KC_ENT, KC_2, KC_GUAP \
                              //`--------------------'  `--------------------'
  )
  #endif

  /*,
  [_CATLOCK] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCATRETURN1,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, LCATRETURN2,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,              KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO \
                              //`--------------------'  `--------------------'
  )//キャットロックは未実装
  */
};

/*
#ifdef COMPILE_NO_MIKU
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 KC_NO, LOWER,  KC_NO,   KC_NO, RAISE,  KC_NO \
                              //`--------------------'  `--------------------'
  ),
  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST,  KC_NO,  KC_NO, LPLAIN, LRAINBOW,             LSWIRL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, LSNAKE, LNIGHT,                LTEST, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LSMOD,  LHUD,  LSAD,  LVAD, LXMAS, LGRADIENT,              LNEON, LANARCHY, KC_NO,  KC_NO,  KC_NO,   KC_NO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, KC_NO,    KC_NO, _____, KC_NO \
                              //`--------------------'  `--------------------'
  )
};
#endif
*/
int RGB_current_mode;
int press_state = 0;
int press_count = 0;
int neon_mode = 0;
bool led_anarchy = false;

//#ifdef COMPILE_MIKU
char miku_1_1[4][21] = {
  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
  {0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
  {0x00+24, 0x01+24, 0x02+24, 0x03+24, 0x04+24, 0x05+24, 0x06+24, 0x07+24, 0x08+24, 0x09+24, 0x0a+24, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
  {0x00+36, 0x01+36, 0x02+36, 0x03+36, 0x04+36, 0x05+36, 0x06+36, 0x07+36, 0x08+36, 0x09+36, 0x0a+36, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
};

bool miku_switch = true;
//#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
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
int hue = 0;
int last_time = 0;

void noizy_led(void) {

  last_time++;
  if (last_time > WEIGHT) {
    last_time = 0;
    for (int i=0; i<=6; i++ ) { //LEDは片方につき7個あるため、その数だけループ
       rgblight_sethsv_at((360 / 6 * i + hue) % 360, 255, 125, i);
     }
     hue += 20;
     if (hue > 360) {
       hue = 0;
     }
  }
}
#endif

void matrix_scan_user(void) {
   iota_gfx_task();
   if (neon_mode) {
     noizy_led();
   }
}

int miku_timer = 0;
int miku_layer = 0;
//int layer_4_switching_count = 0; //レイヤー4は、稀に描画
#ifdef COMPILE_MIKU
void increment_font_layer(void) {
    miku_layer++;
    miku_timer = 0;
}
#endif

//int shutter_time = 0;
void matrix_render_user(struct CharacterMatrix *matrix) {

  #ifdef COMPILE_MIKU
  //shutter_time++;
  //if (shutter_time == 2) {
    if(miku_switch) {
      set_shutter(0);
      miku_switch = false;
    } else {
      set_shutter(1);
      miku_switch = true;
    }
    //shutter_time = 0;
  //}

  matrix_write_ln(matrix, miku_1_1[0]);
  matrix_write_ln(matrix, miku_1_1[1]);
  matrix_write_ln(matrix, miku_1_1[2]);
  matrix_write(matrix, miku_1_1[3]);

  miku_timer++;
  if(miku_layer == 0) {
    set_font_num(0);
    if (miku_timer == 8) {
        increment_font_layer();
    }
  }
  if(miku_layer == 1) {
    set_font_num(1);
    if (miku_timer == 8) {
        increment_font_layer();
    }
  }
  if(miku_layer == 2) {
    set_font_num(2);
    if (miku_timer == 8) {
        increment_font_layer();
    }
  }
  if (miku_layer == 3) {
    miku_layer = 0;
  }
  /*
  if (layer_4_switching_count < 4) {
    if (miku_layer == 3) {
      miku_layer = 0;
      layer_4_switching_count++;
    }
  } else {
    if(miku_layer == 3) {
      set_font_num(3);
      if (miku_timer == 6) {
          increment_font_layer();
      }
    }
    if (miku_layer == 4) {
      miku_layer = 0;
      layer_4_switching_count = 0;
    }
  }
*/
  #endif

  #ifdef COMPILE_NO_MIKU
  matrix_write_ln(matrix, miku_1_1[0]);
  matrix_write_ln(matrix, miku_1_1[1]);
  matrix_write_ln(matrix, miku_1_1[2]);
  matrix_write(matrix, miku_1_1[3]);

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
  #ifdef COMPILE_MIKU
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
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
    #endif
        /*
    case CAT_LOCK1:
      if (record->event.pressed) {
        layer_on(_CATLOCK);
      }
      break;
    case CAT_RETURN1:
      if (IS_LAYER_ON(_CATLOCK)) {
        if (record->event.pressed) {
          layer_off(_CATLOCK);
        }
      }
      break;
      */
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
