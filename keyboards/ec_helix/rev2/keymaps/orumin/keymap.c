#include QMK_KEYBOARD_H
#include "bootloader.h"
#include"keymap_jp.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    RGBRST
};

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    * ,-----------------------------------------.             ,-----------------------------------------.
    * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  `   |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  | Alt  |Space |   N  |   M  |   ,  |   .  |   /  |  [   |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |Adjust| Esc  |      | GUI  |Shift |Lower |Space |Enter |Raise |Shift |   -  |   =  |   \  |  ]   |
    * `-------------------------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT( \
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LALT,         KC_SPC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LBRC , \
        MO(_ADJUST), KC_ESC, _______, KC_LGUI,  KC_LSFT, MO(_LOWER), KC_SPC,       KC_ENT, MO(_RAISE),  KC_RSFT , KC_MINS, KC_EQL, KC_BSLS,   KC_RBRC \
    ),
    /* Lower
    * ,-----------------------------------------.             ,-----------------------------------------.
    * |   ~  |   !  |   @  |   #  | End  |   %  |             |   ^  |   &  |   *  |   (  | Home |      |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |PageUp|PageDn|   )  |      |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   =  |   +  |   \  |   |  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F7  |  F8  |  F9  |  F10 |  F11 | Alt  | Alt  |  F12 |      |      | Home | End  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      | GUI  |Shift |      | Ctrl | Ctrl |      |Shift | Next | Vol- | Vol+ | Play |
    * `-------------------------------------------------------------------------------------------------'
    */
                    
    [_LOWER] = LAYOUT( \
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_END,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_HOME, _______, \
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_PGUP, KC_PGDN, KC_RPRN, _______, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,    KC_EQL, KC_PLUS, KC_BSLS, KC_PIPE, _______, \
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_LALT, KC_LALT, KC_F12,  _______, _______, KC_HOME, KC_END,  _______, \
        _______, _______, _______, KC_LGUI, KC_LSFT, _______, KC_LCTL, KC_LCTL, MO(_ADJUST), KC_RSFT, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
    ),

    /* Raise
    * ,-----------------------------------------.             ,-----------------------------------------.
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  | F10  | F11  | F12  |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      |      |      |      |      |      |             |      |      |      |      | Up   | Del  |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      |      |      |      |      |      |             | Bksp |Enter |      |      | Left |Right |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      | Alt  | Alt  |      |      |      |      | Down | ESC  |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      | GUI  |Shfit |      | Ctrl | Ctrl |      |Shift | Next | Vol- | Vol+ | Play |
    * `-------------------------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT( \
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                         KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, \
        _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______,   KC_UP,  KC_DEL, \
        _______, _______, _______, _______, _______, _______,                       KC_BSPC,  KC_ENT, _______, _______, KC_LEFT, KC_RIGHT, \
        _______, _______, _______, _______, _______, _______,     KC_LALT, KC_LALT, _______, _______, _______, _______, KC_DOWN,  KC_ESC, \
        _______, _______, _______, KC_LGUI, KC_LSFT, MO(_ADJUST), KC_LCTL, KC_LCTL, _______, KC_RSFT, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
    ),

    /* Adjust (Lower + Raise)
    * ,-----------------------------------------.             ,-----------------------------------------.
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      | Reset|RGBRST|      |      |      |             |      |      |      |      |      |  Del |
    * |------+------+------+------+------+------|             |------+------+------+------+------+------|
    * |      |      |      |Aud on|Audoff| Mac  |             | Left | Down |  Up  |Right |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      | Win  | Alt  | Alt  |      |Colemk|RGB ON| HUE+ | SAT+ | VAL+ |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      | GUI  |Shfit |      | Ctrl | Ctrl |      |Shift | MODE | HUE- | SAT- | VAL- |
    * `-------------------------------------------------------------------------------------------------'
    */
    [_ADJUST] =  LAYOUT( \
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
        RGB_MOD, RESET,   RGBRST,  _______, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL, \
        _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,                   KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT,  _______, _______, \
        _______, _______, _______, _______, _______, AG_SWAP, KC_LALT, KC_LALT, _______, RGB_MODE_SNAKE, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
        _______, _______, _______, KC_LGUI, KC_LSFT, _______, KC_LCTL, KC_LCTL, _______, KC_RSFT, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
    )
};


__attribute__ ((weak))
void get_matrix_key_val(uint8_t col, uint8_t row, uint8_t* val, uint8_t *threshold){
    *val=0;
    *threshold=0;
    (void)col;
    (void)row;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
            #endif
        break;
    }
    return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
    static uint32_t last_timer=0;
    uint32_t timer_now = timer_read32();
    // 100msに一回
    if (TIMER_DIFF_32(timer_now, last_timer) > 100) {
        last_timer = timer_now;
        #ifdef OLED_DRIVER_ENABLE
            oled_task_user();
        #endif

        #ifdef CONSOLE_ENABLE
        uint8_t col,row,val,threshold;
        // for Debug
        col = 1;
        row = 2;
        get_matrix_key_val(col, row, &val, &threshold);
        uprintf("col=%d row=%d val=%d threshold=%d\n", col, row, val, threshold);
        #endif
    }
}
#ifdef OLED_DRIVER_ENABLE
static void render_logo(void) {

    static const char helix_logo[] PROGMEM ={
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
        0};
    oled_write_P(helix_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_helix_master()) {
      return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

static void render_layer_status(void) {
    // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        oled_write_P(PSTR("Default"), false);
        break;
        case _RAISE:
        oled_write_P(PSTR("Raise"), false);
        break;
        case _LOWER:
        oled_write_P(PSTR("Lower"), false);
        break;
        case _ADJUST:
        oled_write_P(PSTR("Adjust"), false);
        break;
        default:
        oled_write_P(PSTR("Undef-"), false);
    }
}

static void render_status(void) {
    render_layer_status();
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    oled_write_P(PSTR("\n"), false);
}

void oled_task_user(void) {
    if (is_helix_master()) {
        render_status();
    } else {
        render_logo();
        oled_scroll_left();  // Turns on scrolling
    }
}
#endif
