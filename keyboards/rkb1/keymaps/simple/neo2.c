#include "neo2.h"
#include "action_util.h"
#include "keycode.h"
#include "quantum.h"

static bool pressingLsft, pressingRsft, pressingCaps, pressingNUHS, pressingNUBS, pressingRalt, lockingShift, lockingMod4;

void track_neo2_modifier_state(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LEFT_SHIFT:
            pressingLsft = record->event.pressed;
            lockingShift ^= pressingLsft && pressingRsft;
            break;
        case KC_RIGHT_SHIFT:
            pressingRsft = record->event.pressed;
            lockingShift ^= pressingLsft && pressingRsft;
            break;
        case KC_CAPS:
            pressingCaps = record->event.pressed;
            break;
        case KC_NUHS:
            pressingNUHS = record->event.pressed;
            break;
        case KC_NUBS:
            pressingNUBS = record->event.pressed;
            lockingMod4 ^= pressingNUBS && pressingRalt;
            break;
        case KC_RALT:
            pressingRalt = record->event.pressed;
            lockingMod4 ^= pressingNUBS && pressingRalt;
            break;
    }
}

static int getLayer(void) {
    bool mod2 = lockingShift ^ pressingLsft ^ pressingRsft;
    bool mod3 = pressingCaps | pressingNUHS;
    bool mod4 = lockingMod4 ^ pressingNUBS ^ pressingRalt;
    if (mod4 && mod3) return 5;
    if (mod4) return 3;
    if (mod3 && mod2) return 4;
    if (mod3) return 2;
    if (mod2) return 1;
    return 0;
}
#include "keyToCharTable.h"
uint32_t keystroke_to_unicode(uint16_t keycode) {
    size_t elements = sizeof(keycode_to_char) / (6 * sizeof(uint16_t));
    if (keycode > elements) {
        return 0;
    }
    return (uint32_t)keycode_to_char[keycode][getLayer()];
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_LSFT:
        case KC_RSFT:
        case KC_CAPS:
        case KC_NUHS:
        case KC_NUBS:
        case KC_RALT:
            return true;

        default:
            return getLayer() != 3; // Deactivate Caps Word.
    }
}
