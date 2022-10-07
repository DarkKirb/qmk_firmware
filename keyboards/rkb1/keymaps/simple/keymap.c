#include "keycode.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include "keymap_steno.h"
#include "raw_hid.h"
#include "neo2.h"
#include "compose.h"
enum {
  _MAIN,
  _NUMPAD,
  _PLOVER,
  _MOUSE,
  _GAMING,
  _SYS,
  _NAV,
  _FN,
  _EMPTY
};

#define LAYOUT(k0A, k0B, k0C, k0D, k0E, k0F, k5A, k5B, k5C, k5D, k5E, k5F, k1A, k1B, k1C, k1D, k1E, k1F, k6A, k6B, k6C, k6D, k6E, k6F, k2A, k2B, k2C, k2D, k2E, k2F, k7A, k7B, k7C, k7D, k7E, k7F, k3A, k3B, k3C, k3D, k3E, k3F, k8A, k8B, k8C, k8D, k8E, k8F, k4C, k4D, k4E, k4F, k9C, k9D, k9E, k9F) LAYOUT_ortho_4x6_2x2uc(k0A, k0B, k0C, k0D, k0E, k0F, k1A, k1B, k1C, k1D, k1E, k1F, k2A, k2B, k2C, k2D, k2E, k2F, k3A, k3B, k3C, k3D, k3E, k3F, k4C, k4D, k4E, k4F, k5A, k5B, k5C, k5D, k5E, k5F, k6A, k6B, k6C, k6D, k6E, k6F, k7A, k7B, k7C, k7D, k7E, k7F, k8A, k8B, k8C, k8D, k8E, k8F, k9C, k9D, k9E, k9F)
#define STN_PLS STN_NB
#define STN_HAT STN_NC
#define RA(k) RALT(k)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT(
      KC_ESC , KC_Q   , KC_W   , KC_E       , KC_R   , KC_T   , KC_Y   , KC_U       , KC_I      , KC_O   , KC_P    , KC_LBRC,
      KC_TAB , KC_A   , KC_S   , KC_D       , KC_F   , KC_G   , KC_H   , KC_J       , KC_K      , KC_L   , KC_SCLN , KC_QUOT,
      KC_LSFT, KC_Z   , KC_X   , KC_C       , KC_V   , KC_B   , KC_N   , KC_M       , KC_COMM   , KC_DOT , KC_SLSH , KC_LEAD,
      KC_LCTL, KC_LGUI, KC_LALT, KC_NUBS    , TT(_FN), _______, KC_LOCK, TG(_PLOVER), KC_RALT   , KC_RGUI, KC_APP  , KC_RCTL,
                        KC_CAPS, TT(_GAMING), KC_SPC , KC_LSFT,                       TT(_MOUSE), TT(_NUMPAD), TT(_NAV), TT(_SYS)
  ),
  [_NUMPAD] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PDOT, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
                      _______, _______, KC_P0,   _______,                   _______, _______, _______, _______
  ),
  [_PLOVER] = LAYOUT(
    STN_N1,  STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NA,
    STN_PLS, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
    STN_PLS, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                      STN_HAT, STN_HAT, STN_A,   STN_O,                     STN_HAT, STN_HAT, STN_E,   STN_U
  ),
  [_MOUSE] = LAYOUT(
    _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, KC_BTN3, KC_WH_U, KC_BTN4, _______, _______,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______,
    _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______,                   _______, _______, _______, _______
  ),
  [_GAMING] = LAYOUT(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______,
    KC_LALT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
    _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______,                   _______, _______, _______, _______
  ),
  [_SYS] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, _______, _______, _______, _______, KC_PAUS, _______, _______, _______, _______, KC_RBRC,
    _______, _______, _______, _______, KC_PSCR, _______, _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______,                   _______, _______, _______, _______
  ),
  [_NAV] = LAYOUT(
    _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, RA(KC_Y),KC_7,    KC_8,    KC_9, RA(KC_P), RA(KC_LBRC),
    _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  RA(KC_H),KC_4,    KC_5,    KC_6, RA(KC_SCLN), RA(KC_QUOT),
    _______, KC_ESC,  KC_TAB,  KC_PSTE, KC_ENT,  KC_UNDO, RA(KC_N),KC_1,    KC_2,    KC_3, RA(KC_SLSH), _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                      _______, _______, KC_0,    _______,                   _______, _______, _______, _______
  ),
  [_EMPTY] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______,                   _______, _______, _______, _______
  ),
};

#ifdef RAW_ENABLE
// custom HID code
static uint32_t enable_until = 0;

static bool is_steno_on(void) {
    if (enable_until < timer_read32()) {
        return false;
    }
    return get_highest_layer(layer_state) == _PLOVER;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length != 3) {
        enable_until = 0; // Unknown input
        return;
    }
    if (memcmp(data, "STN", 3) == 0) {
        // You need to send a packet every 10s
        enable_until = timer_read32() + 20000;
    } else {
        enable_until = 0;
    }
}

matrix_row_t last_matrix[MATRIX_ROWS];

void matrix_scan_kb(void) {
    matrix_scan_user();
    if (likely(!is_steno_on())) {
        return;
    }

    matrix_row_t new_matrix[MATRIX_ROWS];

    for (int row = 0; row < MATRIX_ROWS; row++) {
        new_matrix[row] = matrix_get_row(row);
    }

    if (memcmp(new_matrix, last_matrix, sizeof(last_matrix)) == 0) {
        return;
    }

    memcpy(last_matrix, new_matrix, sizeof(last_matrix));

    uint8_t buffer[RAW_EPSIZE];
    buffer[0] = 'S';
    buffer[1] = 'T';
    buffer[2] = 'N';
    memcpy(buffer + 3, new_matrix, sizeof(new_matrix));
    raw_hid_send(buffer, sizeof(buffer));
}

static void send_unicode_chunk(const char * data, size_t length) {
  uint8_t buffer[RAW_EPSIZE];
  memset(buffer, 0, sizeof(buffer));
  buffer[0] = 'U';
  buffer[1] = 'N';
  buffer[2] = 'I';
  memcpy(buffer + 3, data, length);
  raw_hid_send(buffer, sizeof(buffer));
}

#define UNI_CHUNKSIZE (RAW_EPSIZE - 3)

/*void send_unicode_string(const char * str) {
  size_t length = strlen(str);
  while(length > UNI_CHUNKSIZE) {
    send_unicode_chunk(str, UNI_CHUNKSIZE);
    str += UNI_CHUNKSIZE;
    length -= UNI_CHUNKSIZE;
  }
  send_unicode_chunk(str, length);
}*/

void register_unicode(uint32_t codepoint) {
  uint8_t buffer[4];
  size_t size;
  if(codepoint < 0x80) {
    buffer[0] = (uint8_t)codepoint;
    size = 1;
  } else if(codepoint < 0x800) {
    buffer[1] = 0x80 | (uint8_t)(codepoint & 0x3F);
    codepoint >>= 6;
    buffer[0] = 0xC0 | (uint8_t)(codepoint);
    size = 2; 
  } else if(codepoint < 0x10000) {
    buffer[2] = 0x80 | (uint8_t)(codepoint & 0x3F);
    codepoint >>= 6;
    buffer[1] = 0x80 | (uint8_t)(codepoint & 0x3F);
    codepoint >>= 6;
    buffer[0] = 0xE0 | (uint8_t)(codepoint);
    size = 3;
  } else {
    buffer[3] = 0x80 | (uint8_t)(codepoint & 0x3F);
    codepoint >>= 6;
    buffer[2] = 0x80 | (uint8_t)(codepoint & 0x3F);
    codepoint >>= 6;
    buffer[1] = 0x80 | (uint8_t)(codepoint & 0x3F);
    codepoint >>= 6;
    buffer[0] = 0xF0 | (uint8_t)(codepoint);
    size = 4;
  }
  send_unicode_chunk((char *)buffer, size);
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  track_neo2_modifier_state(keycode, record);
  process_compose(keycode, record);
}

#endif
