#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_KANJI KC_GRV
#define L_TOG  RGB_TOG
#define L_HUI  RGB_HUI
#define L_HUD  RGB_HUD
#define L_SAI  RGB_SAI
#define L_SAD  RGB_SAD
#define L_VAI  RGB_VAI
#define L_VAD  RGB_VAD
#define L_MOD RGB_MOD
#define L_PLAIN  RGB_MODE_PLAIN
#define L_BREATHE  RGB_MODE_BREATHE
#define L_RAINBOW  RGB_MODE_RAINBOW
#define L_SWIRL  RGB_MODE_SWIRL
#define L_SNAKE  RGB_MODE_SNAKE
#define L_NIGHT  RGB_MODE_KNIGHT
#define L_XMAS  RGB_MODE_XMAS
#define L_GRADIENT  RGB_MODE_GRADIENT
#define L_TEST RGB_MODE_RGBTEST
#define L_NEON RGB_MODE_NEON
#define L_ANARCHY RGB_MODE_ANARCHY
#define KC_GUAP  LALT_T(KC_APP)

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

#ifdef OLED_MIKU

const char *read_miku(void) {
  static char miku[] = {
      0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, '\n',
      0x00+12, 0x01+12, 0x02+12, 0x03+12, 0x04+12, 0x05+12, 0x06+12, 0x07+12, 0x08+12, 0x09+12, 0x0a+12,'\n',
      0x00+24, 0x01+24, 0x02+24, 0x03+24, 0x04+24, 0x05+24, 0x06+24, 0x07+24, 0x08+24, 0x09+24, 0x0a+24, '\n',
      0x00+36, 0x01+36, 0x02+36, 0x03+36, 0x04+36, 0x05+36, 0x06+36, 0x07+36, 0x08+36, 0x09+36, 0x0a+36, 0x00};

  return miku;
}

bool oled_switch = true;

#else
    #include "../lib/mode_icon_reader.c"
    #include "../lib/layer_state_reader.c"
    #include "../lib/host_led_state_reader.c"
    //#include "../lib/logo_reader.c"
    #include "../lib/keylogger.c"
    #include "../lib/timelogger.c"

    // When add source files to SRC in rules.mk, you can use functions.

    //const char *read_logo(void);
    //void set_keylog(uint16_t keycode, keyrecord_t *record);
    //const char *read_keylog(void);
    //const char *read_keylogs(void);
    const char *read_layer_state(void);
    const char *read_mode_icon(bool swap);
    const char *read_host_led_state(void);
    void set_timelog(void);
    const char *read_timelog(void);

#endif



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
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
         RESET,  RGBRST,  KC_NO,  KC_NO, L_PLAIN, L_RAINBOW,             L_SWIRL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         L_TOG,  L_HUI,  L_SAI,  L_VAI, L_SNAKE, L_NIGHT,                KC_NO, KC_NO, KC_NO, KC_NO,  KC_PGUP, KC_NO,\
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        L_MOD,  L_HUD,  L_SAD,  L_VAD, L_XMAS, L_GRADIENT,              KC_NO, KC_NO, KC_NO,  KC_HOME, KC_PGDN, KC_END,\
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    KC_TRNS, KC_TRNS, KC_NO,    KC_NO, KC_TRNS, KC_NO \
                                //`--------------------'  `--------------------'
    )
};

int RGB_current_mode;

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


void matrix_scan_user(void) {
   iota_gfx_task();
}

int oled_timer = 0;
int oled_layer = 0;


void matrix_render_user(struct CharacterMatrix *matrix) {

  #ifdef OLED_MIKU
  #else
      matrix_write_ln(matrix, read_layer_state());
     // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
      matrix_write_ln(matrix, read_host_led_state());
      //matrix_write_ln(matrix, read_timelog());

  #endif

}


void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

int shutter_count = 0;
void iota_gfx_task_user(void) {

    #ifdef OLED_MIKU
      shutter_count++;
      if (shutter_count > 7) {
          shutter_count = 0;
          set_shutter(oled_switch);
          oled_switch = !oled_switch;

          set_force_dirty(true);

          struct CharacterMatrix matrix;
          matrix_clear(&matrix);
          matrix_write(&matrix, read_miku());

          oled_timer++;
          set_font_num(oled_layer);
          if (oled_timer == 10) {
              oled_timer = 0;
              oled_layer++;
          }
          if (oled_layer == 3) {
            oled_layer = 0;
          }

      matrix_render_user(&matrix);
      matrix_update(&display, &matrix);
  }
  #else
      struct CharacterMatrix matrix;
      matrix_clear(&matrix);
      matrix_render_user(&matrix);
      matrix_update(&display, &matrix);
  #endif
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    //set_keylog(keycode, record);
#endif
#ifdef OLED_MIKU
#else
     set_timelog();
#endif
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}
