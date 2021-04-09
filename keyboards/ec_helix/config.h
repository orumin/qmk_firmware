#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001
#define MANUFACTURER ginjake
#define PRODUCT ec_helix
#define DESCRIPTION helix only for varmilo EC switch or NiZ switch

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

/* Soft Serial defines */
#define SOFT_SERIAL_PIN D2

/* Select hand configuration */
#define MASTER_LEFT
//#define MASTER_RIGHT
// #define EE_HANDS

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }

// wiring of each half
#define MATRIX_COLS 7
#define MATRIX_COL_PINS { F4, F5, F6 }

// custom matrix
#define CHARGE_PIN B2
#define ADC_PIN B6

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

// keyboard RGB LED support
#define RGBLED_NUM 54
#define RGBLED_SPLIT {27, 27}
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 100
#define RGBLIGHT_VAL_STEP 10
#define RGBLIGHT_HUE_STEP 17
#define RGBLIGHT_SAT_STEP 17
/*
#define LED_LAYOUT( \
    L50, L40, L30, L20, L10,           R10, R20, R30, R40, R50, \
    L51, L41, L31, L21, L11,           R11, R21, R31, R41, R51, \
    L52, L42, L32, L22, L12,           R12, R22, R32, R42, R52, \
    L53, L43, L33, L23, L13, L00, R00, R13, R23, R33, R43, R53, \
    L54, L44, L34, L24, L14, L01, R01, R14, R24, R34, R44, R54 \
) { \
   L54, L40, L34, L20, L14, \
   L53, L41, L33, L21, L13, \
   L52, L42, L32, L22, L12, \
   L51, L43, L31, L23, L11, L00, \
   L50, L44, L30, L24, L10, L01, \
        R14, R20, R34, R40, R54, \
        R13, R21, R33, R41, R53, \
        R12, R22, R32, R42, R52, \
   R00, R11, R23, R31, R43, R51, \
   R01, R10, R24, R30, R44, R50 \
}

#define RGBLIGHT_LED_MAP LED_LAYOUT( \
     0,  1,  2,  3,  4,               31, 30, 29, 28, 27, \
     5,  6,  7,  8,  9,               36, 35, 34, 33, 32, \
    10, 11, 12, 13, 14,               41, 40, 39, 38, 37, \
    15, 16, 17, 18, 19, 20,       47, 46, 45, 44, 43, 42, \
    21, 22, 23, 24, 25, 26,       53, 52, 51, 50, 49, 48)
*/
#define OLED_FONT_H "customfont.h"
#define OLED_TIMEOUT 60000

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value for Helix keyboard
//  120  RGBoff, OLEDoff
//  120  OLED
//  330  RGB 6
//  300  RGB 32
//  310  OLED & RGB 32
  #define USB_MAX_POWER_CONSUMPTION 400
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif
