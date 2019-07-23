/* Copyright 2019 ginjake and kano_v
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * compile command = make infinity_plus3:default:avrdude
 */
#include <stdio.h>
#include <print.h>
 #include QMK_KEYBOARD_H

 enum Layer
 {
   _QWERTY
 };


 enum custom_keycodes {
   QWERTY = SAFE_RANGE,
   DIA,
   ZURA,
   RUBY,
   YOHANE,
 };

#define PERIOD 140

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]={
  [_QWERTY] = LAYOUT(
    RUBY, YOHANE, ZURA
  ),
};

void matrix_init_user(void) {
  debug_enable = true;
  eeconfig_update_rgblight_default();
  rgblight_enable();
  //DDRB &= ~(unsigned int)0x4; /* B2 IN */
  //DDRB |= (unsigned int)0x18;  /* B3 B4 OUT */
  //PORTB &= ~(unsigned int)0x1C;
  //PORTB |= _BV(PB4);
}

int pre_push = false;
int hoge = 0;
int cnt_sum = 0;
int cnt_divide_5 = 0;
int average = 0;
int push_wait = 0;

void matrix_scan_user(void) {

//PORTB |= _BV(PB4);
    volatile unsigned int cntarr[5];
    volatile unsigned int cnt = 0;
	int i=0;

	for(i=0;i<5;i++)
	{
      while((bit_is_clear (PINB,PINB2)) && (cnt < 0xFFFF))
      {
        cnt++;
      }
	  if(cnt >= 0xFFFF)
      {
	    goto ERR_END;
      }
	  cnt = 0;
      while((!bit_is_clear (PINB,PINB2)) && (cnt < 0xFFFF))
      {
        cnt++;
      }
	  if(cnt >= 0xFFFF)
      {
	    goto ERR_END;
	  }
	  cntarr[i] = cnt;
	}
	cnt = 0;
	for(i=0;i<5;i++)
	{
	  cnt += cntarr[i];
	}

  cnt_divide_5 = cnt/5;

  if (push_wait > 0) {
    push_wait += -1;
  }

//cntの値を平均で測る
  if (hoge > PERIOD) {
    average = cnt_sum/PERIOD;

    if (average > 39) {
      if (pre_push == true) {
          SEND_STRING("A");
          rgblight_sethsv_at(16, 255, 150, 0);
          push_wait = 200;

          //QMK_TOOLBOXにデバッグ用の数値を出力する
          print("|");
          uprintf("%d", average);
      } else {
        pre_push = true;
      }
  } else if (average > 35) {
      if (pre_push == true) {
        if (push_wait == 0) { //深く押し込んだ後、離すときに浅く押した判定になってしまうのを阻止
          SEND_STRING("B");
          rgblight_sethsv_at(180, 255, 150, 0);

          //QMK_TOOLBOXにデバッグ用の数値を出力する
          print("|");
          uprintf("%d", average);
        }
      } else {
        pre_push = true;
      }
    } else {
      if (pre_push == true) {
        rgblight_sethsv_at(270, 255, 40, 0);
      }
      pre_push = false;
    }
      cnt_sum = 0;
      hoge = 0;
  } else {
      cnt_sum += cnt_divide_5;
  }

    hoge++;

/*
    if(cnt_divide_5 < press_time)
	{
	  PORTB &= ~(_BV(PB4));
	  push_flag++;
    if(push_flag < -10) {
      push_flag = 0;
    }
  }
	else
	{
    */
      //PORTB |= _BV(PB4);
//	}
	return;
ERR_END:
    PORTB &= ~(_BV(PB4));
      print("ERROR");
	return;

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
/*
    case DIA:
      if (record->event.pressed) {
        press_time += 30;
        //char buf[12];
        //snprintf(buf, 12, "%d", press_time);
        //dprint("\nDEBUG: enabled.\n");
        print("press_time");
        uprintf("%d", press_time);
        //puts(buf); // "-99"
        SEND_STRING("ab");
      }
      break;
*/
      case RUBY:
        if (record->event.pressed) {
          SEND_STRING("RUBY");
        }
      break;
      case YOHANE:
        if (record->event.pressed) {
          SEND_STRING("YOSHIKO");
        }
      break;
      case ZURA:
        if (record->event.pressed) {
          SEND_STRING("HANAMARU");
        }
      break;
  }
  return true;
}
