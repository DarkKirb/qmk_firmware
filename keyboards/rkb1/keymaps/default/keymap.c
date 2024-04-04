#include QMK_KEYBOARD_H

enum custom_keycodes {
    COMPOSE = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_NO,   KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_NO,   KC_Z, KC_X, KC_C, KC_V, KC_B,
        KC_LCTL, KC_NO,KC_LGUI,KC_LALT,KC_NO,KC_NO,
        KC_NO, KC_NO, KC_NO, KC_SPC
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case COMPOSE:
            if (record->event.pressed) {
                register_code(KC_TAB);
                register_code(KC_CAPS_LOCK);
            } else {
                unregister_code(KC_TAB);
                unregister_code(KC_CAPS_LOCK);
            }
            break;
    }
    return true;
}
