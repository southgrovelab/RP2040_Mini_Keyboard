// Copyright 2026 Niclas Söderlund
// SPDX-License-Identifier: GPL-2.0-or-later

// RP2040 Mini Keyboard - Pickels 3D LAB
//
//   Knapp:      1      2      3      4
//   Normal:     Esc    Tab    Enter  F1 (kort) / Ctrl+Alt+Del (lång)
//   Pilläge:    Left   Up     Down   Right
//
//   Knapp 1 + 4 samtidigt: växla mellan normalläge och pilläge.
//   Håll in knapp 1 när stickan sätts i: starta i BOOTSEL (RPI-RP2).

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _ARROWS,
};

// Kort tryck = F1, långtryck = Ctrl+Alt+Del (hanteras i process_record_user)
#define F1_CAD LT(0, KC_F1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_TAB,  KC_ENT,  F1_CAD
    ),
    [_ARROWS] = LAYOUT(
        KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
    ),
};

// Knapp 1 + knapp 4 växlar pilläget
const uint16_t PROGMEM toggle_combo[] = {KC_ESC, F1_CAD, COMBO_END};
combo_t key_combos[] = {
    COMBO(toggle_combo, TG(_ARROWS)),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case F1_CAD:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCTL(LALT(KC_DEL)));
                return false;
            }
            break;
    }
    return true;
}

void keyboard_post_init_user(void) {
    gpio_set_pin_output(ARROW_LED_PIN);
    gpio_write_pin_low(ARROW_LED_PIN);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin(ARROW_LED_PIN, layer_state_cmp(state, _ARROWS));
    return state;
}
