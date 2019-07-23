/* Copyright 2018 takashiski
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
#include QMK_KEYBOARD_H

#define PORT_TYPEB 0
#define PORT_TYPED 1
#define NORMALIZE_IDX 4
#define NORMALIZE_SAMPLE 4

/*******************************
   Please adjust thise parameters
********************************/
#define CAPMATRIXCOL 4
#define CAPMATRIXROW /* 2 */2
#define KEY_THRESHOLD 1070 /* bigger than 1.2 */
#define NOISE_THRESHOLD 0

/**********************************
   Define Matrix PIN
***********************************/
const uint16_t cap_col[2][CAPMATRIXCOL] = {{PORT_TYPEB,PORT_TYPEB,PORT_TYPEB,PORT_TYPEB},
                                           {PINB1,     PINB3,     PINB2,     PINB6     }};
const uint16_t cap_row[2][CAPMATRIXROW] = {{PORT_TYPEB, PORT_TYPEB},
                                           {PINB4     ,PINB5      }};

int led_array[8] = {4,5,6,7,3,2,1,0};

uint16_t key_threshold[CAPMATRIXCOL][CAPMATRIXROW] = {{2491,794},
                                                      {2495,902},
                                                      {1715,771},
													  {1403,824}};

/* Sampling Buffer */
uint16_t sample_buffer[NORMALIZE_IDX][CAPMATRIXCOL][CAPMATRIXROW] = {0};
/* Sample Index */
uint16_t sample_index = 0;
/* Result of calibration */
uint16_t calibrate_result[CAPMATRIXCOL][CAPMATRIXROW] = {0};

/* Dummy */
const uint16_t PROGMEM keymaps[1][MATRIX_ROWS][MATRIX_COLS]={0};

bool hoge = true;

void row_sampling(uint16_t* out){
  uint16_t row_before_cnt[CAPMATRIXROW];
  uint16_t row_cnt[CAPMATRIXROW];

  for(uint8_t i=0;i<CAPMATRIXROW;i++){
	row_before_cnt[i]=0;
    row_cnt[i]=0;
  }

  for(uint8_t i=0;i<CAPMATRIXROW;i++){
    for(uint32_t cnt=1; cnt<0x2FF;cnt++){
      if(row_before_cnt[i]==0){
	    if(!bit_is_clear (PINB,cap_row[1][i])){
		  row_before_cnt[i] = cnt;
		}
	  }else{
        if(bit_is_clear (PINB,cap_row[1][i])){
	      if((row_before_cnt[i]+NOISE_THRESHOLD)<cnt){
	  	    row_cnt[i]++;
			row_before_cnt[i]=0;
	      }
	    }
	  }
	}
  }
  /* OUTPUT */
  for(uint8_t i=0;i<CAPMATRIXROW;i++){
	  out[i] += row_cnt[i];
  }
}

void row_sampling_idx(uint32_t idx, uint32_t col){
  for(uint8_t i=0;i<CAPMATRIXROW;i++){
    sample_buffer[idx][col][i] = 0;
  }
  for(uint8_t i=0;i<NORMALIZE_SAMPLE;i++){
    row_sampling(&sample_buffer[idx][col][0]);
  }
}

/* Getter function : Key val */
uint32_t get_key_val(uint16_t col, uint16_t row){
  uint32_t sum=0;
  for(uint8_t i=0;i<NORMALIZE_IDX;i++){
    sum += (uint32_t)sample_buffer[i][col][row];
  }
  return sum;
}

/* Port Setting and Calibrate Key Val */
void matrix_init_user(void) {
  debug_enable = true;
  //gblight_enable();
  //rgblight_sethsv_at(90,255,150,0);
  /************************
    Debug OUTPUT PORT
  *************************/
  DDRB |= (unsigned int)(_BV(PINB5));

  /*************************
    Initial PORT Setting
  **************************/
  for(uint8_t i=0;i<CAPMATRIXCOL;i++)
  {
    /************************
      OUTPUT PORT Setting
	*************************/
    if(cap_col[0][i] == PORT_TYPEB){
	  DDRB |= (unsigned int)(_BV(cap_col[1][i]));
	}
	else{
      DDRD |= (unsigned int)(_BV(cap_col[1][i]));
	}
  }

  for(uint8_t i=0;i<CAPMATRIXROW;i++)
  {
    /************************
      INPUT PORT Setting
	*************************/
	if(cap_row[0][i] == PORT_TYPEB){
	  DDRB &= ~(unsigned int)(_BV(cap_row[1][i]));
	}
	else{
      DDRD &= ~(unsigned int)(_BV(cap_row[1][i]));
	}
  }

  /******************************
    Calibrate Key Val (Measurement)
  *******************************/
  for(uint8_t col=0;col<CAPMATRIXCOL;col++){
    /* COL Select */
    for(uint8_t i=0;i<CAPMATRIXCOL;i++){
	  if(cap_col[0][i] == PORT_TYPEB){
	    PORTB &= ~_BV(cap_col[1][i]);
	  }
	  else{
	    PORTD &= ~_BV(cap_col[1][i]);
	  }
	}
	if(cap_col[0][col] == PORT_TYPEB){
      PORTB |= _BV(cap_col[1][col]);
	}
	else{
	  PORTD |= _BV(cap_col[1][col]);
	}
	_delay_us(100);
	/* Sampling */
    for(uint8_t i=0;i<NORMALIZE_IDX;i++){
      row_sampling_idx(i, col);
    }
  }

  /******************************
    Calibrate Key Val (Key Value setup)
  *******************************/
  for(uint8_t col=0;col<CAPMATRIXCOL;col++){
    for(uint8_t row=0;row<CAPMATRIXROW;row++){
	  calibrate_result[col][row] = get_key_val(col, row);
	}
  }
}

int aaa = 0;
/* Main Loop */
void matrix_scan_user(void) {

  /******************************
    Key value update
  *******************************/
  for(uint8_t col=0;col<CAPMATRIXCOL;col++){
    /******************************
      Colmun Select
    *******************************/
    for(uint8_t i=0;i<CAPMATRIXCOL;i++){
	  PORTB &= ~_BV(cap_col[1][i]);
	}
	PORTB |= _BV(cap_col[1][col]);
	_delay_us(100);
	/* Row Sampling */
    row_sampling_idx(sample_index, col);
	/* update index */
	sample_index = (sample_index+1)%NORMALIZE_IDX;
  }


  /************************************
    Debug Code
  *************************************/
  /*
  uint8_t col,row;

  col = 0;
  row = 0;
  if((((uint32_t)get_key_val(col, row))*KEY_THRESHOLD) < ((uint32_t)calibrate_result[col][row])*1000){
    PORTB |= _BV(PINB5);
  }else{
    PORTB &= ~_BV(PINB5);
  }
  */
 aaa++;
 if (aaa == 3) {
  uprintf(" \n");
      uprintf("%u  ",(uint32_t)get_key_val(0, 0));
      uprintf("%u  ",(uint32_t)get_key_val(1, 0));
      uprintf("%u  ",(uint32_t)get_key_val(2, 0));
      uprintf("%u  \n",(uint32_t)get_key_val(3, 0));
      uprintf("%u  ",(uint32_t)get_key_val(0, 1));
      uprintf("%u  ",(uint32_t)get_key_val(1, 1));
      uprintf("%u  ",(uint32_t)get_key_val(2, 1));
      uprintf("%u  \n",(uint32_t)get_key_val(3, 1));
aaa = 0;
}
//uprintf("%u\n", (uint32_t)get_key_val(col,row));
  /* Is key val Bigger than calibrated threshold? */


  hoge = !hoge;

  if (hoge) {
	for(uint8_t col=0;col<4;col++) {
	  for(uint8_t row=0;row<2;row++) {
		//if((((uint32_t)get_key_val(col, row))*1000) > ((uint32_t)calibrate_result[col][row])*key_threshold[col][row]){
		if((((uint32_t)get_key_val(col, row))*KEY_THRESHOLD) < ((uint32_t)calibrate_result[col][row])*1000){
          //PORTB |= _BV(PINB5);
		  sethsv(180, 250, 100, (LED_TYPE *)&led[led_array[row*4+col]]);
		}else{
		  //PORTB &= ~_BV(PINB5);
		  sethsv(20,250, 50, (LED_TYPE *)&led[led_array[row*4+col]]);
		}
	  }
	}
	rgblight_set();
  }

  /************************************
     If you wait to look up the key status
     Please call
	   get_key_val(col,row)*10
	 and comparate with
	   calibrate_result[col][row]*KEY_THRESHOLD
   ************************************/
	return;

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
