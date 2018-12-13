#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
rgblight_config_t RGB_current_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define X 0
#define Y 1
#define KC_LPLAIN  RGB_MODE_PLAIN
#define KC_LBREATHE  RGB_MODE_BREATHE
#define KC_LRAINBOW  RGB_MODE_RAINBOW
#define KC_LSWIRL  RGB_MODE_SWIRL
#define KC_LSNAKE  RGB_MODE_SNAKE
#define KC_LNIGHT  RGB_MODE_KNIGHT
#define KC_LXMAS  RGB_MODE_XMAS
#define KC_LGRADIENT  RGB_MODE_GRADIENT
#define KC_LTEST RGB_MODE_RGBTEST

//#define KC_LAQOURS_N AQOURS_N
#define KC_LCATLOCK1 CAT_LOCK1
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  KANA,
  EISU,
  RGBRST,
  AQOURS_NEXT,
  AQOURS_PRE,
  AQOURS_AUTO,
  CROSS,
  CROSS_END
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

int aqours_index = -1;
//int aqours_color_h[] = { 26, 340, 120,   0, 199,   0, 53, 280, 322};
int aqours_color_h[] = { 26, 340, 150,   0, 199, 220, 53, 265, 322};
int aqours_color_s[] = {255, 165, 255, 255, 255, 350, 255, 255, 255};
int aqours_color_v[] = {255, 255, 255, 255, 255, 255, 200, 255, 255};
int aqours_led_anim_index = 0;
int push_key_index[] = {0, 0};
int CROSS_led_anim_index = -1;
bool aqours_mode;
bool aqours_auto_mode = false;
bool CROSS_mode = false;

//keyのmatrixの位置とLEDの番号を紐づける
int combined_key_to_led[] =
{
  0,1,2,3,4,5,
  11,10,9,8,7,6,
  12,13,14,15,16,17,
  23,22,21,20,19,18
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Esc  |ADJUST| Win  | Alt  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|
   * `-----------------------------------------'             `-----------------------------------------'
   */
   /*
[_QWERTY] = LAYOUT_ortho_4x12(
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      KC_ESC,  ADJUST,  KC_LGUI, KC_LALT, LOWER,   KC_SPC,                    KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),
*/
[_QWERTY] = LAYOUT_ortho_4x12(
      AQOURS_NEXT,  KC_Q,    KC_W,    KC_E,    KC_E,    KC_E,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      AQOURS_PRE, KC_A,    KC_S,    KC_D,    KC_E,    KC_E,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      AQOURS_AUTO, KC_Z,    KC_X,    KC_C,    KC_E,    KC_E,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      CROSS,  CROSS,  CROSS_END, _RAISE, LOWER,   KC_E,                    AQOURS_NEXT,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),
  /* Colemak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   F  |   P  |   G  |             |   J  |   L  |   U  |   Y  |   ;  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   R  |   S  |   T  |   D  |             |   H  |   N  |   E  |   I  |   O  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   K  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Esc  |ADJUST| Alt  | Win  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_COLEMAK] = LAYOUT_ortho_4x12( \
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
      KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      KC_ESC,  ADJUST,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,                    KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  /* Dvorak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |  /   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |             |   B  |   M  |   W  |   V  |   Z  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Esc  |ADJUST| Alt  | Win  |LOWER |Space |             | Space| RAISE| Left | Down |  Up  | Right|
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_DVORAK] = LAYOUT_ortho_4x12( \
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL, \
      KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT , \
      KC_ESC,  ADJUST,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,                    KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   -  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      | Home | End  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_LOWER] = LAYOUT_ortho_4x12( \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
      _______, _______, _______, _______, _______, _______,                   KC_MINS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, KC_HOME, KC_END,  _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_RAISE] = LAYOUT_ortho_4x12( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|RGBRST|Aud on|Audoff|      |             |      |Qwerty|Colemk|Dvorak|      | Ins  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |RGB ON| HUE+ | SAT+ | VAL+ | Mac  |             | Win  |  -   |   =  |Print |ScLock|Pause |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | MODE | HUE- | SAT- | VAL- |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      | EISU | EISU | EISU |             | KANA | KANA | Home |PageDn|PageUp| End  |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_ADJUST] =  LAYOUT_ortho_4x12( \
      _______, RESET,   RGBRST,  KC_LPLAIN, KC_LRAINBOW, KC_LSNAKE,           KC_LNIGHT, KC_LXMAS,  KC_LGRADIENT, KC_LSWIRL,  _______, KC_INS, \
      _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, AG_NORM,                   AG_SWAP, KC_MINS, KC_EQL,  KC_PSCR, KC_SLCK, KC_PAUS,\
      _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,                   _______, _______, _______, _______, _______, _______,\
      _______, _______, _______, EISU,    EISU,    EISU,                      KANA,    KANA,    KC_HOME, KC_PGDN, KC_PGUP, KC_END\
      )
};

// define variables for reactive RGB
bool TOG_STATUS = false;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      rgblight_mode_noeeprom(RGB_current_config.mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;

    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
           rgblight_mode_noeeprom(16);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode_noeeprom(RGB_current_config.mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            rgblight_mode_noeeprom(15);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode_noeeprom(RGB_current_config.mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;

    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode_noeeprom(RGB_current_config.mode);
          rgblight_step();
          RGB_current_config.mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;

    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
         SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;

    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_config = rgblight_config;
        }
      #endif
      break;

      //オタクな光り方
      case AQOURS_NEXT:
        #ifdef RGBLIGHT_ENABLE
          if (record->event.pressed) {
            if (!aqours_mode) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_config = rgblight_config;
            }
            aqours_auto_mode = false;
            aqours_index++;
            if (aqours_index == 9) {
              aqours_index = 0;
            }
            aqours_led_anim_index = 0;
            aqours_mode = 1;
          }
      #endif
      break;
      //オタクな光り方
      case AQOURS_PRE:
        #ifdef RGBLIGHT_ENABLE
          if (record->event.pressed) {
            if (!aqours_mode) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_config = rgblight_config;
            }
            aqours_auto_mode = false;
            aqours_index += -1;
            if (aqours_index < 0) {
              aqours_index = 8;
            }
            aqours_led_anim_index = 0;
            aqours_mode = 1;
          }
        #endif
        break;
      case AQOURS_AUTO:
        if (record->event.pressed) {
          if (!aqours_mode) {
              eeconfig_update_rgblight_default();
              rgblight_enable();
              RGB_current_config = rgblight_config;
          }
          aqours_auto_mode = true;
          aqours_mode = 1;
        }
        break;
      //サザンクロス
      case CROSS:
        #ifdef RGBLIGHT_ENABLE
          if (record->event.pressed) {
            CROSS_mode = 1;
          }
        #endif
        break;
      //サザンクロスおわり
      case CROSS_END:
        #ifdef RGBLIGHT_ENABLE
          if (record->event.pressed) {
            CROSS_mode = 0;
          }
        #endif
        break;
  }
  if (CROSS_mode == 1) {
    if (record->event.pressed) {
      for (uint8_t c = 0; c < MATRIX_COLS; c++) {
       for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
         if (matrix_is_on(r, c)) {
           if (c <= MATRIX_COLS) {
               if(is_master) {
                 push_key_index[X] = c;
                 push_key_index[Y] = r;
                 CROSS_led_anim_index = 0;
               }
           } else {
               if(!is_master) {
                 push_key_index[X] = c-(MATRIX_COLS);
                 push_key_index[Y] = r;
                 CROSS_led_anim_index = 0;
               }
           }
           rgblight_set();
           break;
         }
       }
     }
    }
  }
  return true;
}


int cross_led_lag_count = 0;
int cross_led_color_lag_count = 0;
int cross_state[24];
void CROSS_led(void) {
  if (CROSS_led_anim_index > -1) {
    cross_led_lag_count++;
    if (cross_led_lag_count > 50) {
      cross_led_lag_count = 0;

      int key_num;
      //上
      if (push_key_index[Y] - CROSS_led_anim_index >= 0) {
          key_num = (push_key_index[Y] - CROSS_led_anim_index) * MATRIX_COLS + push_key_index[X];
          cross_state[combined_key_to_led[key_num]] = 1;
      }
      //下
      if (push_key_index[Y] + CROSS_led_anim_index < 4) {
          key_num = (push_key_index[Y] + CROSS_led_anim_index) * MATRIX_COLS + push_key_index[X];
          cross_state[combined_key_to_led[key_num]] = 1;
      }
      //左
      if (push_key_index[X] - CROSS_led_anim_index >= 0) {
          key_num = (push_key_index[Y]) * MATRIX_COLS + push_key_index[X] - CROSS_led_anim_index;
          cross_state[combined_key_to_led[key_num]] = 1;
      }
      //右
      if (push_key_index[X] + CROSS_led_anim_index < MATRIX_COLS) {
          key_num = (push_key_index[Y]) * MATRIX_COLS + push_key_index[X] + CROSS_led_anim_index;
          cross_state[combined_key_to_led[key_num]] = 1;
      }

      CROSS_led_anim_index++;
      if (CROSS_led_anim_index > 6) {
        CROSS_led_anim_index = -1;
      }
    }
  }

  cross_led_color_lag_count++;
  if (cross_led_color_lag_count == 3) {
    cross_led_color_lag_count = 0;
    for (int i=0;i<24;i++) {
        if(cross_state[i] > 0 && cross_state[i] < 1080) {
          cross_state[i]+=8;
          sethsv((cross_state[i]+i*60)%360, 255, 255, (LED_TYPE *)&led[i]);
        }
     }
     rgblight_set();
   }
}

int aqours_led_timer_count = 0;
int aqours_led_auto_timer_count = 0;
void aqours_led(void) {
  if (aqours_auto_mode) {
    aqours_led_auto_timer_count++;
    if (aqours_led_auto_timer_count > 1600) {
       aqours_led_auto_timer_count= 0;
       aqours_index++;
       aqours_led_anim_index = 0;
       if (aqours_index == 9) {
         aqours_index = 0;
       }
    }
  }
  aqours_led_timer_count++;
  if (aqours_led_timer_count > 100) {
    aqours_led_timer_count = 0;
    if (aqours_led_anim_index < 6) {
      sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index]-30, (LED_TYPE *)&led[aqours_led_anim_index]);
      sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index]-20, (LED_TYPE *)&led[11 - aqours_led_anim_index]);
      sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index]-10, (LED_TYPE *)&led[12 + aqours_led_anim_index]);
      sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index], (LED_TYPE *)&led[23 - aqours_led_anim_index]);
      aqours_led_anim_index++;
      rgblight_set();
    }
  }
}


void matrix_scan_user(void) {

   for (uint8_t c = 0; c < MATRIX_COLS; c++) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
      if (matrix_is_on(r, c)) {
        if (c <= MATRIX_COLS) {
            if(is_master) {
              sethsv(20+5*(MATRIX_COLS*r+c), 255, 255, (LED_TYPE *)&led[combined_key_to_led[MATRIX_COLS*r+c]]);
            }
        } else {
            if(!is_master) {
              int row_num = c-(MATRIX_COLS);
              sethsv(20+5*(MATRIX_COLS*r+row_num), 255, 255, (LED_TYPE *)&led[combined_key_to_led[MATRIX_COLS*r+c]]);
            }
        }
        rgblight_set();
        break;
      }
    }
  }
   if (aqours_mode) {
     aqours_led();
   }
   if (CROSS_mode) {
     CROSS_led();
   }
}


void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      rgblight_init();
      RGB_current_config = rgblight_config;
    #endif
}
