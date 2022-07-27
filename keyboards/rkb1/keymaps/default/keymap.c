#include QMK_KEYBOARD_H
#include "keymap_steno.h"
#include "keymap.h"
#include "raw_hid.h"

static void tap_on_layer(uint16_t key, uint8_t layer);
static void register_on_layer(uint16_t key, uint8_t layer) {
    if (layer == 2 || layer == 5) {
        register_code(KC_LSHIFT);
    }
    if (layer == 3 || layer == 5 || layer == 6) {
        register_code(KC_CAPS_LOCK);
    }
    if (layer == 4 || layer == 6) {
        register_code(KC_RALT);
    }
    if (layer == 7) {
        tap_on_layer(KC_GRV, 4);
    }
    register_code16(key);
}
static void unregister_on_layer(uint16_t key, uint8_t layer) {
    unregister_code16(key);
    if (layer == 2 || layer == 5) {
        unregister_code(KC_LSHIFT);
    }
    if (layer == 3 || layer == 5 || layer == 6) {
        unregister_code(KC_CAPS_LOCK);
    }
    if (layer == 4 || layer == 6) {
        unregister_code(KC_RALT);
    }
}
static void tap_on_layer(uint16_t key, uint8_t layer) {
    register_on_layer(key, layer);
    wait_ms(1);
    unregister_on_layer(key, layer);
}

#define LSHCTL S(KC_LCTL)
#define LSHGUI S(KC_LGUI)
#define LSHALT S(KC_LALT)
#define RSHCTL S(KC_RCTL)
#define RSHGUI S(KC_RGUI)
#define SHAPP S(KC_APP)
#define RSHALT S(KC_RALT)

#define RLTCTL RALT(KC_LCTL)
#define RLTGUI RALT(KC_LGUI)
#define RLTALT RALT(KC_LALT)
#define RLTRCTL RALT(KC_RCTL)
#define RLTRGUI RALT(KC_RGUI)
#define RLTAPP RALT(KC_APP)

#define STN_PLS STN_NB
#define STN_HAT STN_NC

#define LAYOUT(k0A, k0B, k0C, k0D, k0E, k0F, k5A, k5B, k5C, k5D, k5E, k5F, k1A, k1B, k1C, k1D, k1E, k1F, k6A, k6B, k6C, k6D, k6E, k6F, k2A, k2B, k2C, k2D, k2E, k2F, k7A, k7B, k7C, k7D, k7E, k7F, k3A, k3B, k3C, k3D, k3E, k3F, k8A, k8B, k8C, k8D, k8E, k8F, k4C, k4D, k4E, k4F, k9C, k9D, k9E, k9F) LAYOUT_ortho_4x6_2x2uc(k0A, k0B, k0C, k0D, k0E, k0F, k1A, k1B, k1C, k1D, k1E, k1F, k2A, k2B, k2C, k2D, k2E, k2F, k3A, k3B, k3C, k3D, k3E, k3F, k4C, k4D, k4E, k4F, k5A, k5B, k5C, k5D, k5E, k5F, k6A, k6B, k6C, k6D, k6E, k6F, k7A, k7B, k7C, k7D, k7E, k7F, k8A, k8B, k8C, k8D, k8E, k8F, k9C, k9D, k9E, k9F)

#define LS(layer) OSL(layer)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L1] = LAYOUT(
        COMPOSE, X,       V,       L,       C,       W,       K,       H,       G,       F,       Q,       SZLIG,
        CIRCUM,  U,       I,       A,       E,       O,       S,       N,       R,       T,       D,       Y,
        DIARESS, U_DIA,   O_DIA,   A_DIA,   P,       Z,       B,       M,       COMMA,   PERIOD,  J,       XXXXXXX,
        KC_LCTL, LS(FN),  KC_LGUI, KC_LALT, PASTHRU, LS(KP1), TG(STN), OLEDON,  KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          LS(_L2), LS(_L6), KC_SPC,  LS(_L3),                   LS(_L4), LS(_L7), KC_SPC,  LS(_L5)
    ),
    [_L2] = LAYOUT(
        COMPOSE, CX,      CV,      CL,      CC,      CW,      CK,      CH,      CG,      CF,      CQ,      CSZLIG,
        HACEK,   CU,      CI,      CA,      CE,      CO,      CS,      CN,      CR,      CT,      CD,      CY,
        SPASPER, CU_DIA,  CO_DIA,  CA_DIA,  CP,      CZ,      CB,      CM,      ENDASH,  BULLET,  CJ,      XXXXXXX,
        LSHCTL,  LS(FN),  LSHGUI,  LSHALT,  PASTHRU, LS(KP1), TG(STN), OLEDON,  RSHALT,  RSHGUI,  SHAPP,   RSHCTL,
                          LS(_L2), LS(_L6), KC_SPC,  LS(_L6),                   XXXXXXX, XXXXXXX, KC_SPC,  LS(_L8)
    ),
    [_L3] = LAYOUT(
        COMPOSE, ELLIPS,  LOWLINE, LBRACKT, RBRACKT, ACIRCUM, EXCLAM,  LESSTHN, GREATER, EQUALS,  AMPSAND, LONG_S,
        DOTABVE, BSLASH,  FSLASH,  LBRACE,  RBRACE,  ASTERSK, QUESTN,  LPARENS, RPARENS, HYPHMIN, COLON,   AT,
        ACUTE,   NUMBER,  DOLLAR,  VRTLINE, ATILDE,  AGRAVE,  PLUS,    PERCENT, QUOT,    AAPOSTR, SEMCOL,  XXXXXXX,
        KC_LCTL, LS(FN),  KC_LGUI, KC_LALT, PASTHRU, LS(KP1), TG(STN), OLEDON,  KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          LS(_L6), LS(_L6), KC_SPC,  LS(_L3),                   LS(_L7), LS(_L7), KC_SPC,  XXXXXXX
    ),
    [_L4] = LAYOUT(
        COMPOSE, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, INVEXCL, SEVEN,   EIGHT,   NINE,    PLUS,    MINUS,
        DOTBLOW, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  INVQMRK, FOUR,    FIVE,    SIX,     COMMA,   PERIOD,
        SOLIDUS, KC_ESC,  KC_TAB,  KC_PSTE, KC_ENT,  KC_UNDO, COLON,   ONE,     TWO,     THREE,   SEMCOL,  KC_RSFT,
        RLTCTL,  LS(FN),  RLTGUI,  RLTALT,  PASTHRU, LS(KP1), TG(STN), OLEDON,  KC_RALT, RLTRGUI, RLTAPP,  RLTRCTL,
                          XXXXXXX, XXXXXXX, ZERO,    LS(_L7),                   LS(_L4), LS(_L7), ZERO,    LS(_L9)
    ),
    [_L5] = LAYOUT(
        COMPOSE, ONE,     TWO,     THREE,   FOUR,    FIVE,    SIX,     SEVEN,   EIGHT,   NINE,    ZERO,    HYPHMIN,
        CEDILLE, DEGREE,  SECTION, SCRIPTL, RDGUILM, LDGUILM, DOLLAR,  EURO,    LODQUOT, LDQUOT,  RDQUOT,  EMDASH,
        SPLENIS, SUPONE,  SUPTWO,  SUPTHRE, RSGUILM, LSGUILM, CENTSGN, YEN,     LOSQUOT, LSQUOT,  RSQUOT,  HYPHMIN,
        KC_LCTL, LS(FN),  KC_LGUI, KC_LALT, PASTHRU, LS(KP1), TG(STN), OLEDON,  KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          LS(_L8), XXXXXXX, KC_SPC,  XXXXXXX,                   XXXXXXX, LS(_L9), KC_SPC,  LS(_L5)
    ),
    [_L6] = LAYOUT(
        COMPOSE, XI,      XXXXXXX, LAMBDA,  CHI,     OMEGA,   KAPPA,   PSI,     GAMMA,   PHI,     VARPHI,  FSIGMA,
        TURNED,  XXXXXXX, IOTA,    ALPHA,   EPSILON, OMICRON, SIGMA,   NU,      RHO,     TAU,     DELTA,   UPSILON,
        MACRON,  XXXXXXX, LUNEPS,  ETA,     PI,      ZETA,    BETA,    MU,      VARRHO,  VRTHETA, THETA,   XXXXXXX,
        LSHCTL,  LS(FN),  LSHGUI,  LSHALT,  PASTHRU, LS(KP1), TG(STN), OLEDON,  RSHALT,  RSHGUI,  SHAPP,   RSHCTL,
                          LS(_L6), LS(_L6), KC_SPC,  LS(_L6),                   XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX
    ),
    [_L7] = LAYOUT(
        COMPOSE, CXI,     SQRT,    CLAMBDA, COMPLEX, COMEGA,  MULTSGN, CPSI,    CGAMMA,  CPHI,    RATIONL, RINGOP,
        HOOK,    SUBSET,  INTEGRL, FORALL,  THREXST, ELEMOF,  CSIGMA,  NATURAL, REAL,    PARTDRV, CDELTA,  NABLA,
        TILDE,   UNION,   INTRSCT, ALEF,    CPI,     INTEGER, LDBLARR, LRDBARR, RDBLARR, RARRBAR, CTHETA,  XXXXXXX,
        RLTCTL,  LS(FN),  RLTGUI,  RLTALT,  PASTHRU, LS(KP1), TG(STN), OLEDON,  KC_RALT, RLTRGUI, RLTAPP,  RLTRCTL,
                          XXXXXXX, XXXXXXX, KC_SPC,  LS(_L7),                   LS(_L7), LS(_L7), KC_SPC,  XXXXXXX
    ),
    [_L8] = LAYOUT(
        COMPOSE, FEMORD,  MASCORD, NUMERO,  XXXXXXX, MIDDOT,  POUND,   CURENCY, KC_TAB,  FSLASH,  ASTERSK, HYPHMIN,
        RING,    SUBONE,  SUBTWO,  SUBTHRE, FEMALE,  MALE,    MALEFEM, VARKPPA, LANGLE,  RANGLE,  SUBZERO, NBHYP,
        BREVE,   NOTSIGN, LOR,     LAND,    UPTACK,  MEASANG, PARALLL, RIGHTAR, INFINIT, PROPTO,  EMPTYST, SHYPHEN,
        KC_LCTL, LS(FN),  KC_LGUI, KC_LALT, PASTHRU, LS(KP1), TG(STN), OLEDON,  KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          LS(_L8), XXXXXXX, KC_SPC,  XXXXXXX,                   XXXXXXX, XXXXXXX, KC_SPC,  LS(_L8)
    ),
    [_L9] = LAYOUT(
        COMPOSE, XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, KC_WH_U, KC_BTN4, XXXXXXX,
        GRAVE,   XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN6, KC_WH_D, KC_BTN5, XXXXXXX,
        DBLACUT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, LS(FN),  KC_LGUI, KC_LALT, PASTHRU, LS(KP1), TG(STN), OLEDON,  KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX,                   XXXXXXX, LS(_L9), KC_SPC,  LS(_L9)
    ),
    [KP1] = LAYOUT(
        KC_NLCK, KC_TAB,  KC_PSLS, KC_PAST, KC_PMNS, XXXXXXX, XXXXXXX, LEFTTAB, FSLASH,  ASTERSK, HYPHMIN, XXXXXXX,
        XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, XXXXXXX, XXXXXXX, CHECKMK, XBALLOT, DAGGER,  PLUS,    XXXXXXX,
        XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PENT, XXXXXXX, XXXXXXX, CLUBS,   EURO,    TRIBLLT, KC_PENT, XXXXXXX,
        XXXXXXX, KC_P1,   KC_P2,   KC_P7,   KC_PDOT, LS(KP1), OLEDON,  DIAMOND, HEART,   SPADE,   PERIOD,  XXXXXXX,
                          LS(KP2), LS(KP3), KC_P0,   KC_P0,                     LS(KP2), LS(KP3), OPNBOX,  OPNBOX
    ),
    [KP2] = LAYOUT(
        XXXXXXX, EQUALS,  DIVSGN,  DOTOPER, MINUS,   XXXXXXX, XXXXXXX, NOTEQAL, FRACTSL, MULTSGN, SETMINS, XXXXXXX,
        XXXXXXX, UDARROW, UPARROW, VECTARR, PLSMNS,  XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_PGUP, MINPLS,  XXXXXXX,
        XXXXXXX, LEFTARR, COLON,   RIGHTAR, KC_PENT, XXXXXXX, XXXXXXX, KC_LEFT, XXXXXXX, KC_RGHT, KC_PENT, KC_RSFT,
        XXXXXXX, LRARROW, DOWNARR, RLHARPO, COMMA,   LS(KP1), OLEDON,  KC_END,  KC_DOWN, KC_PGDN, KC_DEL,  XXXXXXX,
                          LS(KP2), LS(KP3), PERCENT, PERCENT,                   LS(KP2), LS(KP3), KC_PSTE, KC_PSTE
    ),
    [KP3] = LAYOUT(
        XXXXXXX, ALMSTEQ, DIAMETR, CDOT,    CMINUS,  XXXXXXX, XXXXXXX, IDENTCL, DIVIDES, CTIMES,  DOTMINS, XXXXXXX,
        XXXXXXX, MCHLESS, INTRSCT, MCHGRTR, CPLUS,   XXXXXXX, XXXXXXX, LCEILNG, NARYINT, RCEILNG, DOTPLUS, XXXXXXX,
        XXXXXXX, SUBSET,  ORIGNAL, SUPRSET, KC_PENT, XXXXXXX, XXXXXXX, SUBEQL,  IMAGEOF, SUPREQL, KC_PENT, XXXXXXX,
        XXXXXXX, LEQUAL,  UNION,   GEQUAL,  PRIME,   LS(KP1), OLEDON,  LFLOOR,  NARYUNI, RFLOOR,  DPRIME,  XXXXXXX,
                          LS(KP2), LS(KP3), PERMILL, PERMILL,                   LS(KP2), LS(KP3), WHTSQAR, WHTSQAR
    ),
    [STN] = LAYOUT(
        STN_N1,  STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NA,
        STN_PLS, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
        STN_PLS, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(STN), OLEDON,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          STN_HAT, STN_HAT, STN_A,   STN_O,                     STN_HAT, STN_HAT, STN_E,   STN_U
    ),
    [FN] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NEO2,    XXXXXXX, XXXXXXX, XXXXXXX, QWERTY,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTZ,  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, OLEDON,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};
// clang-format on

uint16_t layout = NEO2;

#include "key_unicode_table.h"
#include "key_neo2_table.h"
#include "key_qwerty_table.h"
#include "key_qwertz_table.h"

static struct decoded_key decode_key_neo2(uint16_t keycode, keyrecord_t *record) {
    return key_neo2_mapping[keycode - SAFE_RANGE];
}
static struct decoded_key decode_key_qwerty(uint16_t keycode, keyrecord_t *record) {
    struct decoded_key dk = {0, 0, DECODED_KEY_USE_UNICODE};
    if (keycode > ATILDE) return dk;
    return key_qwerty_mapping[keycode - SAFE_RANGE];
}
static struct decoded_key decode_key_qwertz(uint16_t keycode, keyrecord_t *record) {
    struct decoded_key dk = {KC_NO, 0, DECODED_KEY_SPECIAL};
    if (keycode >= SAFE_RANGE && keycode <= ATILDE) dk = key_qwertz_mapping[keycode - SAFE_RANGE];
    if (!(dk.flags & DECODED_KEY_SPECIAL)) return dk;
    for (int i = 0; key_qwertz_sparse_mapping[i].key != 0; i++) {
        if (key_qwertz_sparse_mapping[i].key == keycode) {
            return key_qwertz_sparse_mapping[i].decoded_key;
        }
    }
    switch (keycode) {
        default:
            dk.keycode = KC_NO;
            dk.layer   = 0;
            dk.flags   = DECODED_KEY_USE_UNICODE;
            break;
        case ACIRCUM:
            tap_on_layer(KC_GRV, 1);
            tap_on_layer(KC_GRV, 1);
            break;
        case AGRAVE:
            tap_on_layer(KC_EQL, 2);
            tap_on_layer(KC_EQL, 2);
            break;
    }
    return dk;
}
static const char *decode_key_unicode(uint16_t keycode) {
    return key_unicode_mappings[keycode - SAFE_RANGE];
}

static void process_key(uint16_t keycode, keyrecord_t *record) {
    struct decoded_key key;
    switch (layout) {
        case NEO2:
            key = decode_key_neo2(keycode, record);
            break;
        case QWERTY:
            key = decode_key_qwerty(keycode, record);
            break;
        case QWERTZ:
            key = decode_key_qwertz(keycode, record);
            break;
    }
    if (key.flags & DECODED_KEY_SPECIAL) return; // Already handled
    if (!(key.flags & DECODED_KEY_USE_UNICODE)) {
        if (record->event.pressed) {
            if (key.flags & DECODED_KEY_ONESHOT) {
                tap_on_layer(key.keycode, key.layer);
            } else {
                register_on_layer(key.keycode, key.layer);
            }
        } else {
            if (!(key.flags & DECODED_KEY_ONESHOT)) {
                unregister_on_layer(key.keycode, key.layer);
            }
        }
    } else {
        // it’s oneshot, we can’t replicate press-and-hold cases
        send_unicode_string(decode_key_unicode(keycode));
    }
}

#ifdef OLED_ENABLE
static struct {
    bool     force_on;
    uint32_t keep_on_until;
} oled_timer;

static void oled_turn_on(void) {
    oled_timer.force_on = true;
}
static void oled_turn_off(void) {
    oled_timer.force_on      = false;
    oled_timer.keep_on_until = 0;
}
static void oled_turn_on_for(uint32_t msec) {
    oled_timer.keep_on_until = timer_read32() + msec;
}
static bool oled_is_on(void) {
    return oled_timer.force_on || (timer_read32() < oled_timer.keep_on_until);
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    static uint16_t oledon_timer;
#endif
    switch (keycode) {
#ifdef OLED_ENABLE
        case OLEDON:
            if (record->event.pressed) {
                oledon_timer = timer_read();
                oled_turn_on();
            } else {
                oled_turn_off();
                if (timer_elapsed(oledon_timer) < 200) {
                    oled_turn_on_for(30000);
                }
            }
            break;
#endif
        case NEO2:
        case QWERTY:
        case QWERTZ:
            if (record->event.pressed) {
                layout = keycode;
            }
            break;
        default:
            if ((keycode >= SPACE) && (keycode < COMPOSE)) {
                process_key(keycode, record);
            }
            break;
    }
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %u, time: %u, interrupt: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

void matrix_init_user(void) {
#ifdef STENO_ENABLE
    steno_set_mode(STENO_MODE_GEMINI);
#endif
#ifdef OLED_ENABLE
    oled_turn_on_for(60000);
#endif
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (!oled_is_on()) {
        oled_off();
        return false;
    }
    oled_on();
    oled_clear();
    oled_write("Layer: ", false);

    switch (get_highest_layer(layer_state)) {
        case _L1:
            oled_write_ln("Lowercase", false);
            break;
        case _L2:
            oled_write_ln("Uppercase", false);
            break;
        case _L3:
            oled_write_ln("Special", false);
            break;
        case _L4:
            oled_write_ln("Navigation", false);
            break;
        case _L5:
            oled_write_ln("Number Row (L1-3)", false);
            break;
        case _L6:
            oled_write_ln("Greek (lower)", false);
            break;
        case _L7:
            oled_write_ln("Math symbols", false);
            break;
        case _L8:
            oled_write_ln("Number Row (L4-6)", false);
            break;
        case _L9:
            oled_write_ln("Mouse", false);
            break;
        case KP1:
            oled_write_ln("Keypad (L1-2)", false);
            break;
        case KP2:
            oled_write_ln("Keypad (L3-4)", false);
            break;
        case KP3:
            oled_write_ln("Keypad (L5-6)", false);
            break;
        case STN:
            oled_write_ln("Stenography", false);
            break;
        case FN:
            oled_write_ln("Function", false);
            break;
        default:
            oled_write_ln("Unknown", false);
            break;
    }

    oled_write("Layout: ", false);
    switch (layout) {
        case NEO2:
            oled_write_ln("Neo 2", false);
            break;
        case QWERTY:
            oled_write_ln("QWERTY", false);
            break;
        case QWERTZ:
            oled_write_ln("QWERTZ", false);
            break;
        default:
            oled_write_ln("Unknown", false);
            break;
    }

    led_t led_state = host_keyboard_led_state();
    oled_write(led_state.num_lock ? "NUM " : "    ", false);
    oled_write(led_state.caps_lock ? "CAP " : "    ", false);
    oled_write(led_state.scroll_lock ? "SCR " : "    ", false);

    return false;
}
#endif

#ifdef RAW_ENABLE
// custom HID code
static uint32_t enable_until = 0;

static bool is_steno_on(void) {
    if (enable_until < timer_read32()) {
        return false;
    }
    return get_highest_layer(layer_state) == STN;
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
#endif
