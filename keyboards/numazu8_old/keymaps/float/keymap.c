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
#define NORMALIZE_IDX 5
#define NORMALIZE_SAMPLE 5

/*******************************
   Please adjust thise parameters
********************************/
#define CAPMATRIXCOL 4
#define CAPMATRIXROW /* 2 */1
#define KEY_THRESHOLD 15 /* bigger than 1.2 */
#define NOISE_THRESHOLD 5

/**********************************
   Define Matrix PIN
***********************************/
const uint16_t cap_col[2][CAPMATRIXCOL] = {{PORT_TYPEB,PORT_TYPEB,PORT_TYPEB,PORT_TYPEB},
                                           {PINB1,     PINB3,     PINB2,     PINB6     }};
const uint16_t cap_row[2][CAPMATRIXROW] = {{PORT_TYPEB/*,PORT_TYPEB*/},
                                           {PINB4     /*,PINB5     */}};


/* Sampling Buffer */
uint16_t sample_buffer[NORMALIZE_IDX][CAPMATRIXCOL][CAPMATRIXROW] = {0};
/* Sample Index */
uint16_t sample_index = 0;
/* Result of calibration */
uint16_t calibrate_result[CAPMATRIXCOL][CAPMATRIXROW] = {0};

/* Dummy */
const uint16_t PROGMEM keymaps[1][MATRIX_ROWS][MATRIX_COLS]={0};



void row_sampling(uint16_t* out){
  /* ROW <= 32 */
  uint32_t result_bmp = 0;
  uint16_t row_start_idx[CAPMATRIXROW]={0};
  uint16_t row_end_idx[CAPMATRIXROW]  ={0};

  for(uint8_t i=0;i<CAPMATRIXROW;i++){
    result_bmp |= 1<<i;
  }

  for(uint32_t cnt=1; result_bmp && (cnt<0xFFF) ;cnt++)
  {
    for(uint8_t i=0;i<CAPMATRIXROW;i++){
	  if(row_start_idx[i] == 0){
	    if(cap_row[0][i] == PORT_TYPEB){
		  /* Wait until PIN is High */
		  if(bit_is_clear (PINB,cap_row[1][i])){
		    row_start_idx[i]= cnt;
		  }
		}
		else{
		  if(bit_is_clear (PIND,cap_row[1][i])){
		    row_start_idx[i]= cnt;
		  }
		}
	  }
	  else{
	    if(row_end_idx[i] == 0){
		  if(cap_row[0][i] == PORT_TYPEB){
		    /* Wait until PIN is Low */
		    if(!bit_is_clear (PINB,cap_row[1][i])){
			  if((cnt - row_start_idx[i]) < NOISE_THRESHOLD){
			    row_start_idx[i] =0;
				continue;
			  }
		      row_end_idx[i]= cnt;
			  result_bmp &= ~(1<<i);
		    }
	  	  }
	  	  else{
		    if(!bit_is_clear (PIND,cap_row[1][i])){
			  if((cnt - row_start_idx[i]) < NOISE_THRESHOLD){
			    row_start_idx[i] =0;
				continue;
			  }
		      row_end_idx[i]= cnt;
			  result_bmp &= ~(1<<i);
		    }
		  }
		}
	  }
	}
  }
  /* OUTPUT */
  for(uint8_t i=0;i<CAPMATRIXROW;i++){
    if(row_start_idx[i]<row_end_idx[i]){
	  /* row_end_idx[i]-row_start_idx[i] is time@PIN=HIGH */
	  out[i] += (row_end_idx[i]-row_start_idx[i]);
	}
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
uint16_t get_key_val(uint16_t col, uint16_t row){
  uint32_t sum=0;
  for(uint8_t i=0;i<NORMALIZE_IDX;i++){
    sum += sample_buffer[i][col][row];
  }
  return sum/NORMALIZE_IDX;
}

/* Port Setting and Calibrate Key Val */
void matrix_init_user(void) {

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

	/* Row Sampling */
    row_sampling_idx(sample_index, col);
	/* update index */
	sample_index = (sample_index+1)%NORMALIZE_IDX;
  }


  /************************************
    Debug Code
  *************************************/
  uint8_t col,row;
  col = 3;
  row = 0;

  /* Is key val Bigger than calibrated threshold? */
  if((((uint32_t)get_key_val(col, row))*10) > ((uint32_t)calibrate_result[col][row])*KEY_THRESHOLD){
    PORTB |= _BV(PINB5);
  }
  else{
    PORTB &= ~_BV(PINB5);
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
