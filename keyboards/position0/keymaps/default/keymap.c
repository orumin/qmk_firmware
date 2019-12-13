/* Copyright 2010 sirojake
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
 * compile command = make namecard2x4/rev2:default:avrdude
 */
#include <print.h>
#include QMK_KEYBOARD_H
// Use Dynamic macro
//#include "dynamic_macro.h"
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define SELECTOR_NUM 4
#define KEY_NUM 16

#define INPUT_NUM 2
/**********************************
   Define Matrix PIN
***********************************/
uint8_t selector_pin[SELECTOR_NUM] = {PIND7,PINE6,PINB4,PINB5};
volatile uint8_t* selector_port[SELECTOR_NUM] = {&PORTD,&PORTE,&PORTB,&PORTB};
volatile uint8_t* selector_ddr[SELECTOR_NUM] = {&DDRD, &DDRE, &DDRB, &DDRB};
uint8_t input_pin[INPUT_NUM] = {PIND4,PINC6};
volatile uint8_t* input_port[INPUT_NUM] = {&PIND,&PINC};
volatile uint8_t* input_ddr[INPUT_NUM] = {&DDRD,&DDRC};

uint8_t key_val[INPUT_NUM][KEY_NUM] = {0};
uint8_t registerCount[28] = {0};
uint8_t registerCountReset[28] = {0};
char str[2] = {0}; //デバッグ用


/* Dummy */
const uint16_t PROGMEM keymaps[1][MATRIX_ROWS][MATRIX_COLS]={0};
uint16_t OriginKeymaps[26] = { \
 KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, \
 KC_7, KC_8, KC_A, KC_B, KC_C, KC_D, KC_E, \
 KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, \
 KC_M, KC_O, KC_P, KC_Q, KC_R};

 uint16_t keyPositions[2][16] = {\
 { 20, 19, 12,  5, 17, 10, 11, 99, 99, 24, 25, 3, 4, 18, 6, 13}, \
 { 16, 15,  8, 99, 99, 22, 23, 99, 99, 21, 14, 7, 0,  1,  2,  9} \
};
/* Port Setting and Calibrate Key Val */
void matrix_init_user(void) {

     debug_enable = true;

  /*************************
    Initial PORT Setting
  **************************/
  for(uint8_t i=0;i<SELECTOR_NUM;i++)
  {
    /************************
      OUTPUT PORT Setting
	  *************************/
	  *selector_ddr[i] |= (unsigned int)(_BV(selector_pin[i]));
  }
  for(uint8_t i=0;i<INPUT_NUM;i++)
  {
    /************************
      INPUT PORT Setting
	  *************************/
	  *input_ddr[i] &= ~(unsigned int)(_BV(input_pin[i]));
  }
  /* Internal Pullup */
  PORTB=0b11111111;
  PORTC=0b11111111;
  PORTD=0b11111111;
  PORTE=0b11111111;

  str[1] = '\0';
}

/* Main Loop */

void matrix_scan_user(void) {

  /******************************
    Key value update
  *******************************/
  for(uint8_t key=0;key<KEY_NUM;key++){
    /******************************
      Colmun Select
    *******************************/
    for(uint8_t i=0;i<SELECTOR_NUM;i++){
      if((key >> i) & 1){
        *selector_port[i] |= _BV(selector_pin[i]);
      }
      else{
        *selector_port[i] &= ~_BV(selector_pin[i]);
      }
    }
    _delay_us(1200);
    for(uint8_t i=0;i<INPUT_NUM;i++){
      if(bit_is_clear(*input_port[i], input_pin[i])){
        key_val[i][key] = 0;
      }
      else{
        key_val[i][key] = 1;
      }
    }
  }

for (uint8_t c=0;c<INPUT_NUM;c++){
  for (uint8_t key=0;key<KEY_NUM;key++){
    uint8_t key_index = 0;
    /*
    　本当はどちらのＡＴＭＥＧＡ３２８Ｐの信号か区別する必要がある(cの値)も含める必要があるけど、
    　どのキーがどっちだったか忘れたので一旦無視。
    */
    //key_index = key + c*12;
    if(key_val[c][key]){
        if (registerCount[key_index] == 1) {
            tap_code(OriginKeymaps[keyPositions[c][key]]);
            registerCount[key_index] = 2;
        }
        if (registerCount[key_index] == 0) {
            tap_code(OriginKeymaps[keyPositions[c][key]]);
            registerCount[key_index] = 30;
        }
        if (registerCount[key_index] > 0) {
            registerCount[key_index] += -1;
        }
        //5フレーム連続で検知しなかったら、押されなかったとみなす
        registerCountReset[key_index] = 5;
    } else {
        if (registerCount[key_index] > 0 && registerCountReset[key_index] > 0){
            registerCountReset[key_index] += -1;
            //連続で検知しなかったので、押されなかった。連打防止カウントを初期化する
            if (registerCountReset[key_index] == 0) {
                registerCount[key_index] = 0;
            }
        }
    }
  }
}

	return;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {
}
