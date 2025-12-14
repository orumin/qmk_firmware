/* Copyright 2021 Kan-Ru Chen <kanru@kanru.info>
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

#include "quantum.h"

#ifdef CONNECTION_ENABLE
#    include "connection.h"
#    include "lufa.h"
     static bool usb_connected = false;
     static bool force_usb = false;
#endif

#ifdef BLUETOOTH_ENABLE
#    include "bluetooth.h"
#    include "send_string.h"
     extern uint8_t power_save_level;
#endif

#ifdef BLUETOOTH_BLUEFRUIT_LE_UART
#    include "bluefruit_le.h"
#    include "bluefruit_le_uart.h"
     enum BLE_NEXT_ACTION {
         BLE_NOTHING = 0,
         BLE_START_ADV,
         BLE_STOP_ADV,
         BLE_DEL_BONDS,
     } bluefruit_le_set_code = 0;
#endif

void hhkb_led_on(uint8_t led) {
    switch (led) {
        case 1:
            gpio_write_pin_high(F4);
            break;
        case 2:
            gpio_write_pin_high(F1);
            break;
        case 3:
            gpio_write_pin_high(F0);
            break;
    }
}

void hhkb_led_off(uint8_t led) {
    switch (led) {
        case 1:
            gpio_write_pin_low(F4);
            break;
        case 2:
            gpio_write_pin_low(F1);
            break;
        case 3:
            gpio_write_pin_low(F0);
            break;
    }
}

void keyboard_pre_init_kb(void) {
    // BT power up
    gpio_set_pin_output(D5);
    gpio_write_pin_low(D5);

    // Row selectors
    gpio_set_pin_output(B0);
    gpio_set_pin_output(B1);
    gpio_set_pin_output(B2);

    // Col selectors
    gpio_set_pin_output(B3);
    gpio_set_pin_output(B4);
    gpio_set_pin_output(B5);

    // Key strobe
    gpio_set_pin_output(B6);
    gpio_write_pin_high(B6);

    // Key: input with pull-up
    gpio_set_pin_input_high(D7);

    // Unused pins on Pro2 ANSI
    // Input with pull up to save power
    gpio_set_pin_input_high(C6);
    gpio_set_pin_input_high(C7);

    // LED pin configuration
    gpio_set_pin_output(F0);
    gpio_set_pin_output(F1);
    gpio_set_pin_output(F4);
    gpio_write_pin_low(F0);
    gpio_write_pin_low(F1);
    gpio_write_pin_low(F4);

    // Turn on switch PCB
    gpio_set_pin_output(D6);
    gpio_write_pin_low(D6);

#ifdef BLUETOOTH_BLUEFRUIT_LE_UART
    (void)bluefruit_le_set_mode_leds(false);
#endif

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    if (connection_get_host() != CONNECTION_HOST_BLUETOOTH &&
          USB_DeviceState == DEVICE_STATE_Configured) {
        usb_connected = true;
        connection_set_host_noeeprom(CONNECTION_HOST_USB);
    }
}

void suspend_power_down_kb(void) {

#ifdef BLUETOOTH_BLUEFRUIT_LE_UART
    (void)bluefruit_le_set_mode_leds(false);
#endif

    if (power_save_level > 2) {
        // Disable UART TX to avoid current leakage
        UCSR1B &= ~_BV(TXEN1);
        // Power down BLE module
        gpio_write_pin_high(D5);
    }

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    // Power up BLE module
    gpio_write_pin_low(D5);
    // Enable UART TX
    UCSR1B |= _BV(TXEN1);

#ifdef BLUETOOTH_BLUEFRUIT_LE_UART
    (void)bluefruit_le_set_mode_leds(true);
#endif

    suspend_wakeup_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);

    gpio_write_pin(F1, IS_LAYER_ON_STATE(state, 1));
    gpio_write_pin(F0, IS_LAYER_ON_STATE(state, 2));

    return state;
}

void housekeeping_task_user() {
#ifdef BLUETOOTH_ENABLE
#ifdef BLUETOOTH_BLUEFRUIT_LE_UART
    if (power_save_level <= 1) {
        switch (bluefruit_le_set_code) {
            case BLE_START_ADV:
              bluefruit_le_change_discoverable(true);
              bluefruit_le_set_code = 0;
              break;
            case BLE_STOP_ADV:
              bluefruit_le_change_discoverable(false);
              bluefruit_le_set_code = 0;
              break;
            case BLE_DEL_BONDS:
              bluefruit_le_delbonds();
              bluefruit_le_set_code = BLE_START_ADV;
              break;
            default:
              break;
        }
    }
#endif
    if (!force_usb) {
        if(bluetooth_is_connected() && connection_get_host() != CONNECTION_HOST_BLUETOOTH) {
            connection_set_host(CONNECTION_HOST_BLUETOOTH);
        } else if (!usb_connected && (USB_DeviceState == DEVICE_STATE_Configured)) {
            force_usb = true;
            usb_connected = true;
        }
    } else {
        if (connection_get_host() != CONNECTION_HOST_USB) {
            usb_connected = true;
            connection_set_host(CONNECTION_HOST_USB);
        } else if (USB_DeviceState != DEVICE_STATE_Configured) {
            force_usb = false;
            usb_connected = false;
        }
    }
#endif
}

bool command_extra(uint8_t code) {
    switch (code) {
        case KC_B:
            clear_keyboard();
            wait_us(1000);
            bootloader_jump();
            break;
        case KC_P:
            power_save_level ^= 1;
            break;
#ifdef BLUETOOTH_ENABLE
        case KC_U:
            force_usb ^= 1;
            break;
            break;
#endif
#ifdef BLUETOOTH_BLUEFRUIT_LE_UART
        case KC_I:
        case KC_O:
        case KC_R:
            if (code == KC_I) {
                bluefruit_le_set_code = BLE_START_ADV;
            } else if (code == KC_O) {
                bluefruit_le_set_code = BLE_STOP_ADV;
            } else {
                bluefruit_le_set_code = BLE_DEL_BONDS;
            }
            break;
#endif
        default:
            return false;
    }
    return true;
}
