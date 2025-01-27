/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

enum custom_keycodes {
    DPARENTH = SAFE_RANGE,
    /*
    DBRACE,
    DBRACKET,
    DDQUOT,
    DQUOT,
    SDQUOT,
    SQUOT,
    TILDE,
    ESZETT,*/
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_N O
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
                        // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
                          KC_DELETE,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_CAPS,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                            KC_MINS,    KC_W,    KC_L,    KC_R,    KC_B,    KC_Z,     KC_SCLN,    KC_Q,    KC_U,    KC_D,    KC_J, KC_TAB,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
               KC_ESC,GUI_T(KC_S),LSFT_T(KC_H),LALT_T(KC_N),LCTL_T(KC_T),KC_COMM,     KC_DOT ,LCTL_T(KC_A),RALT_T(KC_E),LSFT_T(KC_O),LT(LAYER_RAISE,KC_I),KC_BSPC,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                            KC_EQL ,    KC_F,    KC_M,    KC_V,    KC_C,KC_ENTER,      KC_G, KC_P,  KC_X   ,KC_K  , KC_Y, KC_SLSH,
                        // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                                            KC_LEFT, KC_SPC,KC_RGHT,      KC_UP,   MO(LAYER_LOWER),
                                                                    KC_BTN1,DF(LAYER_RAISE),    KC_DOWN
                        //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
                        // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
                              KC_F12,   KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,      KC_F6,    KC_F7,    KC_F8,   KC_F9,  KC_F10,  KC_F11,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                             XXXXXXX, KC_RBRC, KC_RCBR, KC_RPRN,KC_QUOT, XXXXXXX,    XXXXXXX,  KC_MPLY,  KC_PGDN, KC_PGUP, KC_MNXT, XXXXXXX,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                             XXXXXXX, KC_LBRC, KC_LCBR, KC_LPRN,KC_DQUO, XXXXXXX,    KC_PSCR,  KC_LEFT,  KC_DOWN,   KC_UP,  KC_RGHT,KC_TRNS,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                            KC_GRV, KC_ASTR , KC_PIPE, KC_BSLS, KC_HASH,KC_AMPR,      KC_AT, KC_EXLM, KC_TILD, KC_PERC,  KC_DLR, KC_CIRC,
                        // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                                    RCS(KC_TAB),KC_SPC,LCTL(KC_TAB),    DF(LAYER_RAISE), XXXXXXX,
                                                                    KC_BTN1,LALT(KC_TAB),    KC_BTN2
                        //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
                        // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
                            XXXXXXX,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,  EE_CLR,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                            XXXXXXX, MS_WHLL, MS_WHLU, MS_WHLD, MS_WHLR, XXXXXXX,    KC_BTN4, KC_BTN1, DRGSCRL, KC_BTN2, XXXXXXX, KC_BTN4,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                            XXXXXXX, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    LCTL(KC_W),RCS(KC_TAB),KC_BTN3,LCTL(KC_TAB),XXXXXXX, XXXXXXX,
                        // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                                        KC_BTN2, SNIPING, KC_BTN3,    DF(LAYER_BASE), DF(LAYER_BASE),
                                                                XXXXXXX, KC_BTN2,    DF(LAYER_BASE)
                        //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
                        // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
                            KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                                KC_T,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                                KC_G, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
                        // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                                KC_B, KC_LCTL,    PT_Z,    KC_X,    KC_C,    KC_V,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_LALT,
                        // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                                        KC_BTN2, KC_SPC, DRGSCRL,    DF(LAYER_BASE),  KC_ESC,
                                                                KC_BTN1, KC_BTN3,     KC_DEL
                        //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DPARENTH:
        if (record->event.pressed) {
            SEND_STRING("()" SS_TAP(X_LEFT));
        }
        break;

    case DBRACE:
        if (record->event.pressed) {
            SEND_STRING("{}" SS_TAP(X_LEFT));
        }
        break;

    case DBRACKET:
        if (record->event.pressed) {
            SEND_STRING("[]" SS_TAP(X_LEFT));
        }
        break;

    case DDQUOT:
        if (record->event.pressed) {
            SEND_STRING("\" \" " SS_TAP(X_LEFT));
        }
        break;

    case DQUOT:
        if (record->event.pressed) {
            SEND_STRING("' ' " SS_TAP(X_LEFT));
        }
        break;

    case SDQUOT:
        if (record->event.pressed) {
            SEND_STRING("\" ");
        }
        break;

    case SQUOT:
        if (record->event.pressed) {
            SEND_STRING("' ");
        }
        break;

    case TILDE:
        if (record->event.pressed) {
            SEND_STRING("~ ");
        }
        break;

    }
    return true;
};
*/

// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_S):
            return 130;
        case LSFT_T(KC_I):
            return 130;
        default:
            return TAPPING_TERM;
    }
}

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
