#ifndef LOVELIVE_BLADE11_H
#define LOVELIVE_BLADE11_H

#include "quantum.h"
#ifdef RGBLIGHT_ENABLE
//rgb led driver
#include "ws2812.h"
#endif
#include "rgblight.h"
#define LAYOUT( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10 \
) \
{ \
	{ k00 }, \
	{ k01 }, \
	{ k02 }, \
	{ k03 }, \
	{ k04 }, \
	{ k05 }, \
  { k06 }, \
  { k07 }, \
	{ k08 }, \
	{ k09 }, \
  { k10 } \
}
#endif
