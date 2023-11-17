/*  -*-  eval: (turn-on-orgtbl); -*-
 * kanru's HHKB Layout
 *
 * Copyright 2021 Kan-Ru Chen <kanru@kanru.info>
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
 */

#include "action.h"
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdio.h>

#include "command.h"

#ifdef BATTERY_ENABLE
#include "battery.h"
#endif
#ifdef BLUETOOTH_ENABLE
#    include "bluetooth.h"
#endif
#ifdef BLUETOOTH_BLUEFRUIT_LE_UART
#    include "bluefruit_le_uart.h"
#endif

enum custom_layers {
    BASE,
    HHKB,
    MOUSE,
};

enum my_keycodes {
    BATT_ST = SAFE_RANGE,
    CONN_ST, // Show BT Connection status
    FAC_RST, // Factory reset (BLE Controller)
    DISC_ON, // BT discoverable on
    DISC_OF, // BT discoverable off
    DEL_BND, // Clear paired device
    SW_DRVR, // toggle BT/USB
};

static bool lctrl_pressed = false;
static bool exceptionaly_ctrl_layer_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
            lctrl_pressed = record->event.pressed;
            break;
#ifdef BATTERY_ENABLE
        case BATT_ST:
            if (record->event.pressed) {
                char vbat[8];
                uint8_t level = battery_get_percent();
                snprintf(vbat, sizeof(vbat), "%d", level);
                send_string(vbat);
            }
            return false;
#endif
#ifdef BLUETOOTH_ENABLE
        case CONN_ST:
            if (record->event.pressed) {
                send_string(bluetooth_is_connected()? "connected" : "not connected");
            }
        case SW_DRVR:
            if (record->event.pressed) {
                command_extra(KC_U);
            }
            return false;
#endif
#ifdef BLUETOOTH_BLUEFRUIT_LE_UART
        case FAC_RST:
             if (record->event.pressed) {
                bluefruit_le_factory_reset();
            }
        case DISC_ON:
            if (record->event.pressed) {
                command_extra(KC_I);
            }
            return false;
        case DISC_OF:
            if (record->event.pressed) {
                command_extra(KC_O);
            }
            return false;
        case DEL_BND:
            if (record->event.pressed) {
                command_extra(KC_R);
            }
            return false;
#endif
        default:
            if (lctrl_pressed || exceptionaly_ctrl_layer_pressed) {
                switch (keycode) {
                    case KC_H:
                        if (record->event.pressed) {
                            unregister_code(KC_LCTL);
                            register_code(KC_BSPC);
                            exceptionaly_ctrl_layer_pressed = true;
                        } else {
                            unregister_code(KC_BSPC);
                            if (lctrl_pressed) {
                                register_code(KC_LCTL);
                            }
                            exceptionaly_ctrl_layer_pressed = false;
                        }
                        return false;
                }
            }
            break;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE Level: Default Layer
     +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
     | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
     |-----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-----+
     | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  | Delete |
     |--------+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+--------+
     | R_Ctrl   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |      Enter |
     |------------+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+------+-----+
     | R_Shift    |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  L_Shift | Fn0 |
     +-------+----+-+---+-----++----+-----+-----+-----+-----+----++-----+---+-+----+-----+-----+
             | Fn0  |   LGUI   |              Space              |   RGUI   | RAlt |
             +------+----------+---------------------------------+----------+------+
    */

    [BASE] = LAYOUT_60_hhkb( //  default layer
        LT(MOUSE, KC_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(HHKB),
        MO(HHKB), KC_LGUI, KC_SPC, KC_RGUI, KC_RALT),

    /* Layer HHKB: HHKB mode (HHKB Fn)
     +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
     | Pwr | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
     |-----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-----+
     | Caps   |     |CnnSt| BAT |     |     |     |     |PrScn|ScrLk|Pause|  Up |     | BackSpc|
     |--------+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+--------+
     |          |VolDn|VolUp| Mute|     |     |     |     | Home| PgUp| Left|Right|      Enter |
     |------------+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+------+-----+
     |            |     |     |     |Reset|     |     |     | End | Down|     |          |     |
     +-------+----+-+---+-----++----+-----+-----+-----+-----+----++-----+---+-+----+-----+-----+
             |      |          |                                 |          |      |
             +------+----------+---------------------------------+----------+------+
    */

    [HHKB] = LAYOUT_60_hhkb(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, KC_TRNS, CONN_ST, BATT_ST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP, KC_TRNS, KC_BSPC,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, FAC_RST, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    /* Layer MOUSE: Mouse Key mode (ESC)
     +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
     |-----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-----+
     |        | BTN1| WH_U|     |     |     |     |     |     |     |     |     |     |        |
     |--------+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+--------+
     |          | BTN2| WH_D|     |     |     | MS_L| MS_D| MS_U| MS_R|     |     |            |
     |------------+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+-+---+------+-----+
     |            | BTN3|     |     |     |     |     |     |     |     |     |          |     |
     +-------+----+-+---+-----++----+-----+-----+-----+-----+----++-----+---+-+----+-----+-----+
             |      |          |                                 |          |      |
             +------+----------+---------------------------------+----------+------+
    */

    [MOUSE] = LAYOUT_60_hhkb(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, MS_BTN1, MS_WHLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, MS_BTN2, MS_WHLD, KC_TRNS, KC_TRNS, KC_TRNS, MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, MS_BTN3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};
// clang-format on
