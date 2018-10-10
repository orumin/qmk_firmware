
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
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16
#define _CATLOCK 5
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  RGB_MODE_NEON,
  RGB_MODE_ANARCHY,
  CAT_LOCK1,
  CAT_LOCK2,
  CAT_RETURN1,
  CAT_RETURN2
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
        RST,  LRST,  KNRM,  KSWP, LPLAIN, LRAINBOW,             LSWIRL, XXXXX, XXXXX, XXXXX, XXXXX, LCATLOCK1,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, LSNAKE, LNIGHT,                LTEST, XXXXX, XXXXX, XXXXX,  PGUP, LCATLOCK2,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LSMOD,  LHUD,  LSAD,  LVAD, LXMAS, LGRADIENT,              LNEON, LANARCHY, XXXXX,  HOME,  PGDN,   END,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, XXXXX,    XXXXX, _____, XXXXX \
                              //`--------------------'  `--------------------'
  ),
  [_CATLOCK] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        XXXXX,  XXXXX,  XXXXX,  XXXXX, XXXXX, XXXXX,             XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, LCATRETURN1,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       XXXXX,  XXXXX,  XXXXX,  XXXXX, XXXXX, XXXXX,                XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, LCATRETURN2,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,  XXXXX,  XXXXX,  XXXXX, XXXXX, XXXXX,              XXXXX, XXXXX, XXXXX,  XXXXX,  XXXXX,   XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  XXXXX, XXXXX, XXXXX,    XXXXX, XXXXX, XXXXX \
                              //`--------------------'  `--------------------'
  )//キャットロックは未実装
};

/*
#ifdef COMPILE_NO_MIKU
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                 XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,   XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                 XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 XXXXX, LOWER,  XXXXX,   XXXXX, RAISE,  XXXXX \
                              //`--------------------'  `--------------------'
  ),
  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST,  XXXXX,  XXXXX, LPLAIN, LRAINBOW,             LSWIRL, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, LSNAKE, LNIGHT,                LTEST, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LSMOD,  LHUD,  LSAD,  LVAD, LXMAS, LGRADIENT,              LNEON, LANARCHY, XXXXX,  XXXXX,  XXXXX,   XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, XXXXX,    XXXXX, _____, XXXXX \
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

#ifdef COMPILE_MIKU
char miku_1_1[4][21] = {
  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
  {0x00+12, 0x01+12, 0x02+12, 0x03+12, 0x04+12, 0x05+12, 0x06+12, 0x07+12, 0x08+12, 0x09+12, 0x0a+12, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
  {0x00+24, 0x01+24, 0x02+24, 0x03+24, 0x04+24, 0x05+24, 0x06+24, 0x07+24, 0x08+24, 0x09+24, 0x0a+24, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
  {0x00+36, 0x01+36, 0x02+36, 0x03+36, 0x04+36, 0x05+36, 0x06+36, 0x07+36, 0x08+36, 0x09+36, 0x0a+36, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
};

bool miku_switch = true;
#endif

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

void noizy_led(void) {
  static int last_time = 0;
  if (timer_elapsed(last_time) > WEIGHT) {
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

void matrix_render_user(struct CharacterMatrix *matrix) {

  #ifdef COMPILE_MIKU

  if(miku_switch) {
    set_shutter(0);
    miku_switch = false;
  } else {
    set_shutter(1);
    miku_switch = true;
  }

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
    matrix_write_ln(matrix, read_layer_state());

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
    case CAT_LOCK1:
      if (record->event.pressed) {
        layer_on(_CATLOCK);
      }
      break;
    case CAT_RETURN1:
      if (record->event.pressed) {
        layer_off(_CATLOCK);
      }
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
