/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#pragma once

#include "quantum.h"

 #define LAYOUT( \
   L00, L01, L02, L03, L04, L05,           R01, R02, R03, R04, R05, R06, \
   L10, L11, L12, L13, L14, L15,           R11, R12, R13, R14, R15, R16, \
   L20, L21, L22, L23, L24, L25,           R21, R22, R23, R24, R25, R26, \
   L30, L31, L32, L33, L34, L35, L36, R30, R31, R32, R33, R34, R35, R36, \
   L40, L41, L42, L43, L44, L45, L46, R40, R41, R42, R43, R44, R45, R46  \
   ) \
   { \
     { L03, L04, L05, L02, L01, KC_NO, L00 }, \
     { L13, L14, L15, L12, L11, KC_NO, L10 }, \
     { L23, L24, L25, L22, L21, KC_NO, L20 }, \
     { L33, L34, L35, L32, L31, L36, L30 }, \
     { L43, L44, L45, L42, L41, L46, L40 }, \
     { R02, R03, R04, R01, KC_NO, R05, R06 }, \
     { R12, R13, R14, R11, KC_NO, R15, R16 }, \
     { R22, R23, R24, R21, KC_NO, R25, R26 }, \
     { R32, R33, R34, R31, R30, R35, R36 }, \
     { R42, R43, R44, R41, R40, R45, R46 }, \
   }
