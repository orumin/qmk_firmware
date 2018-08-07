#include "crkbd.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#include "LUFA/Drivers/Peripheral/TWI.h"
#include "./oled.c"

extern keymap_config_t keymap_config;

/* LAYER DEFINITIONS */

#define BASE     0
#define SYMB     1
#define FUNCTION 2
#define MOUSE    3
#define WHEEL    4

/* KEYCODE DEFINITIONS */

/* invalid / blank keys */
#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

/* layers */
#define KC_D_MOUS LT(MOUSE, KC_D)
#define KC_L1_FNC LT(FUNCTION, KC_LANG1)
#define KC_L2_ALT LALT_T(KC_LANG2)
#define KC_WEEL   MO(WHEEL)
#define KC_SP_SFT LSFT_T(KC_SPC)
#define KC_ENT_SB LT(SYMB, KC_ENT)

/* aliases */
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
    LSFT , Z    , X    , C    , V    , B    ,                  B    , N    , M    , COMM , DOT  , SLSH , \
//`------+------+------+------+------+------+------.  |------+------+------+------+------+------+------|
                               L2_ALT,SP_SFT, ESC  ,    TAB  ,ENT_SB,L1_FNC \
//                            `--------------------'  `--------------------'
),

[SYMB] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , 1    , 2    , 3    , 4    , 5    ,                  6    , 7    , 8    , 9    , 0    , EQL  , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , LCBR , LPRN , LBRC ,                  RBRC , RPRN , RCBR , PIPE , ____ , PLUS , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , EXLM , AT   , HASH , DLR  , PERC ,                  CIRC , AMPR , ASTR , ____ , ____ , BSLS , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , ____ ,    ____ , ____ , ____  \
//                            `--------------------'  `--------------------'
),

[FUNCTION] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , ____ , ____ , PGUP , ____ , ____ ,                  ____ , ____ , UP   , ____ , PSCR , BSPC , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , HOME , PGDN , END  , LGUI ,                  ____ , LEFT , DOWN , RGHT , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , F1   , F2   , F3   , F4   , F5   ,                  F6   , F7   , F8   , F9   , F10  , ____ , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , ____ ,    RST  , ____ , ____  \
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

void matrix_init_user(void) {
    oled_init();
}

void matrix_scan_user(void) {
    oled_update();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    oled_record_event(keycode, record);
    return true;
}

/* void persistent_default_layer_set(uint16_t default_layer) { */
/*   eeconfig_update_default_layer(default_layer); */
/*   default_layer_set(default_layer); */
/* } */
