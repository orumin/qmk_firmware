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

#define OLED_FONT_H "glcdfont.c"

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
