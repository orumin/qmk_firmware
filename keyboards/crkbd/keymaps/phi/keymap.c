#include "crkbd.h"

/* GLOBAL VARS */

#define BASE     0
#define RAISE    1
#define FUNCTION 2
#define MOUSE    3
#define WHEEL    4

#define L_BASE     0
#define L_RAISE    (2 << (RAISE - 1))
#define L_FUNCTION (2 << (FUNCTION - 1))
#define L_MOUSE    (2 << (MOUSE - 1))
#define L_WHEEL    (2 << (WHEEL - 1))

/* FEATURES */

#ifdef RGBLIGHT_ENABLE
#include "./rgb.c"
#endif
#ifdef TAP_DANCE_ENABLE
#include "dance.c"
#endif
#ifdef SSD1306OLED
#include "./oled.c"
#endif

/* KEYCODE DEFINITIONS */

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

#define KC_D_MOUS LT(MOUSE, KC_D)
#define KC_L1_RAI LT(RAISE, KC_LANG1)
#define KC_L2_ALT LALT_T(KC_LANG2)
#define KC_WEEL   MO(WHEEL)

#ifdef TAP_DANCE_ENABLE
#define KC_ESC_FN TD(TD_ESC_FUNC)
#define KC_SFCL   TD(TD_SHIFT_CAPS)
#else
#define KC_ESC_FN LT(FUNC, KC_ESC)
#define KC_SFCL   KC_LSFT
#endif

#define KC_RST  RESET
#define KC_MUP  KC_MS_U
#define KC_MDN  KC_MS_D
#define KC_MLFT KC_MS_L
#define KC_MRGT KC_MS_R
#define KC_WUP  KC_WH_U
#define KC_WDN  KC_WH_D
#define KC_WLFT KC_WH_L
#define KC_WRGT KC_WH_R

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    JYEN , Q    , W    , E    , R    , T    ,                  Y    , U    , I    , O    , P    , MINS , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    LCTL , A    , S    ,D_MOUS, F    , G    ,                  H    , J    , K    , L    , SCLN , QUOT , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    SFCL , Z    , X    , C    , V    , B    ,                  B    , N    , M    , COMM , DOT  , SLSH , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------|
                               L2_ALT, SPC  ,ESC_FN,    TAB  , ENT  ,L1_RAI \
//                            `--------------------'  `--------------------'
),

[RAISE] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    BSPC , 1    , 2    , 3    , 4    , 5    ,                  6    , 7    , 8    , 9    , 0    , EQL  , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , BSLS , LCBR , LPRN , LBRC ,                  RBRC , RPRN , RCBR , PIPE , UP   , PLUS , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , EXLM , AT   , HASH , DLR  , PERC ,                  CIRC , AMPR , ASTR , LEFT , DOWN , RGHT , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , ____ ,    RST  , ____ , XXXX  \
//                            `--------------------'  `--------------------'
),

[FUNCTION] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , F1   , F2   , F3   , F4   , F5   ,                  F6   , F7   , F8   , F9   , PSCR , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , LGUI ,                  ____ , ____ , ____ , ____ , PGUP , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , ____ , ____ , HOME , PGDN , END , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , XXXX ,    ____ , ____ , ____  \
//                            `--------------------'  `--------------------'
),

[MOUSE] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , WEEL , ____ , ACL0 , ____ ,                  MLFT , MDN  , MUP  , MRGT , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , BTN1 , BTN2 ,                  ____ , ____ , ____ , ____ , ____ , ____ , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , ____ ,    ____ , ____ , ____  \
//                            `--------------------'  `--------------------'
),

[WHEEL] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  WRGT , WUP  , WDN  , WLFT , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , ____ , ____ , ____ , ____ , ____ , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , ____ ,    ____ , ____ , ____  \
//                            `--------------------'  `--------------------'
),

};

void rgblight_task_user (void) {
  #ifdef RGBLIGHT_ENABLE
    update_rgblight(false);
  #endif
}

void matrix_init_user(void) {
  #ifdef SSD1306OLED
    oled_init();
  #endif
}

void matrix_scan_user(void) {
  #ifdef SSD1306OLED
    oled_update();
  #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef SSD1306OLED
    oled_record_event(keycode, record);
  #endif
    return true;
}
