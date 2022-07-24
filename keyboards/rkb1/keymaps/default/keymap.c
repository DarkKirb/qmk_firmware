#include QMK_KEYBOARD_H
#include "keymap_steno.h"

// I don’t take constructive criticism sorry
enum custom_keycodes {
    SPACE = SAFE_RANGE, // " "
    EXCLAM,             // !
    QUOT,               // "
    NUMBER,             // #
    DOLLAR,             // $
    PERCENT,            // %
    AMPSAND,            // &
    AAPOSTR,            // '
    LPARENS,            // (
    RPARENS,            // )
    ASTERSK,            // *
    PLUS,               // +
    COMMA,              // ,
    HYPHMIN,            // -
    PERIOD,             // .
    FSLASH,             // /
    ZERO,               // 0
    ONE,                // 1
    TWO,                // 2
    THREE,              // 3
    FOUR,               // 4
    FIVE,               // 5
    SIX,                // 6
    SEVEN,              // 7
    EIGHT,              // 8
    NINE,               // 9
    COLON,              // :
    SEMCOL,             // ;
    LESSTHN,            // <
    EQUALS,             // =
    GREATER,            // >
    QUESTN,             // ?
    AT,                 // @
    CA,                 // A
    CB,                 // B
    CC,                 // C
    CD,                 // D
    CE,                 // E
    CF,                 // F
    CG,                 // G
    CH,                 // H
    CI,                 // I
    CJ,                 // J
    CK,                 // K
    CL,                 // L
    CM,                 // M
    CN,                 // N
    CO,                 // O
    CP,                 // P
    CQ,                 // Q
    CR,                 // R
    CS,                 // S
    CT,                 // T
    CU,                 // U
    CV,                 // V
    CW,                 // W
    CX,                 // X
    CY,                 // Y
    CZ,                 // Z
    LBRACKT,            // [
    BSLASH,             // '\'
    RBRACKT,            // ]
    ACIRCUM,            // ^
    LOWLINE,            // _
    AGRAVE,             // `
    A,                  // a
    B,                  // b
    C,                  // c
    D,                  // d
    E,                  // e
    F,                  // f
    G,                  // g
    H,                  // h
    I,                  // i
    J,                  // j
    K,                  // k
    L,                  // l
    M,                  // m
    N,                  // n
    O,                  // o
    P,                  // p
    Q,                  // q
    R,                  // r
    S,                  // s
    T,                  // t
    U,                  // u
    V,                  // v
    W,                  // w
    X,                  // x
    Y,                  // y
    Z,                  // z
    LBRACE,             // {
    VRTLINE,            // |
    RBRACE,             // }
    ATILDE,             // ~
    NBSPACE,            //   (U+00A0)
    INVEXCL,            // ¡
    CENTSGN,            // ¢
    POUND,              // £
    CURENCY,            // ¤
    YEN,                // ¥
    SECTION,            // §
    FEMORD,             // ª
    LDGUILM,            // «
    NOTSIGN,            // ¬
    SHYPHEN,            // ­ (U+00AD)
    DEGREE,             // °
    PLSMNS,             // ±
    SUPTWO,             // ²
    SUPTHRE,            // ³
    MIDDOT,             // ·
    SUPONE,             // ¹
    MASCORD,            // º
    RDGUILM,            // »
    INVQMRK,            // ¿
    CA_DIA,             // Ä
    CO_DIA,             // Ö
    MULTSGN,            // ×
    CU_DIA,             // Ü
    SZLIG,              // ß
    A_DIA,              // ä
    O_DIA,              // ö
    DIVSGN,             // ÷
    U_DIA,              // ü
    LONG_S,             // ſ
    CGAMMA,             // Γ
    CDELTA,             // Δ
    CTHETA,             // Θ
    CLAMBDA,            // Λ
    CXI,                // Ξ
    CPI,                // Π
    CSIGMA,             // Σ
    CPHI,               // Φ
    CPSI,               // Ψ
    COMEGA,             // Ω
    ALPHA,              // α
    BETA,               // β
    GAMMA,              // γ
    DELTA,              // δ
    EPSILON,            // ε
    ZETA,               // ζ
    ETA,                // η
    THETA,              // θ
    IOTA,               // ι
    KAPPA,              // κ
    LAMBDA,             // λ
    MU,                 // μ
    NU,                 // ν
    XI,                 // ξ
    OMICRON,            // ο
    PI,                 // π
    RHO,                // ρ
    FSIGMA,             // ς
    SIGMA,              // σ
    TAU,                // τ
    UPSILON,            // υ
    PHI,                // φ
    CHI,                // χ
    PSI,                // ψ
    OMEGA,              // ω
    VRTHETA,            // ϑ
    VARPHI,             // ϕ
    VARKPPA,            // ϰ
    VARRHO,             // ϱ
    LUNEPS,             // ϵ
    CSZLIG,             // ẞ
    NBHYP,              // ‑ (U+2011)
    ENDASH,             // –
    EMDASH,             // —
    LSQUOT,             // ‘
    RSQUOT,             // ’
    LOSQUOT,            // ‚
    LDQUOT,             // “
    RDQUOT,             // ”
    LODQUOT,            // „
    DAGGER,             // †
    BULLET,             // •
    TRIBLLT,            // ‣
    ELLIPS,             // …
    NNBSP,              //   (U+202F)
    PERMILL,            // ‰
    PRIME,              // ′
    DPRIME,             // ″
    LSGUILM,            // ‹
    RSGUILM,            // ›
    FRACTSL,            // ⁄
    SUBZERO,            // ₀
    SUBONE,             // ₁
    SUBTWO,             // ₂
    SUBTHRE,            // ₃
    EURO,               // €
    COMPLEX,            // ℂ
    SCRIPTL,            // ℓ
    NATURAL,            // ℕ
    NUMERO,             // №
    RATIONL,            // ℚ
    REAL,               // ℝ
    INTEGER,            // ℤ
    ALEF,               // ℵ
    LEFTARR,            // ←
    UPARROW,            // ↑
    RIGHTAR,            // →
    DOWNARR,            // ↓
    LRARROW,            // ↔
    UDARROW,            // ↕
    RARRBAR,            // ↦
    RLHARPO,            // ⇌
    LDBLARR,            // ⇐
    RDBLARR,            // ⇒
    LRDBARR,            // ⇔
    FORALL,             // ∀
    PARTDRV,            // ∂
    THREXST,            // ∃
    EMPTYST,            // ∅
    NABLA,              // ∇
    ELEMOF,             // ∈
    MINUS,              // −
    MINPLS,             // ∓
    DOTPLUS,            // ∔
    SETMINS,            // ∖
    RINGOP,             // ∘
    SQRT,               // √
    PROPTO,             // ∝
    INFINIT,            // ∞
    MEASANG,            // ∡
    DIVIDES,            // ∣
    PARALLL,            // ∥
    LAND,               // ∧
    LOR,                // ∨
    INTRSCT,            // ∩
    UNION,              // ∪
    INTEGRL,            // ∫
    DOTMINS,            // ∸
    ALMSTEQ,            // ≈
    NOTEQAL,            // ≠
    IDENTCL,            // ≡
    LEQUAL,             // ≤
    GEQUAL,             // ≥
    MCHLESS,            // ≪
    MCHGRTR,            // ≫
    SUBSET,             // ⊂
    SUPRSET,            // ⊃
    SUBEQL,             // ⊆
    SUPREQL,            // ⊇
    CPLUS,              // ⊕
    CMINUS,             // ⊖
    CTIMES,             // ⊛
    CDOT,               // ⊙
    UPTACK,             // ⊥
    ORIGNAL,            // ⊶
    IMAGEOF,            // ⊷
    NARYINT,            // ⋂
    NARYUNI,            // ⋃
    DOTOPER,            // ⋅
    DIAMETR,            // ⌀
    LCEILNG,            // ⌈
    RCEILNG,            // ⌉
    LFLOOR,             // ⌊
    RFLOOR,             // ⌋
    OPNBOX,             // ␣
    WHTSQAR,            // □
    SPADE,              // ♠
    CLUBS,              // ♣
    HEART,              // ♥
    DIAMOND,            // ♦
    FEMALE,             // ♀
    MALE,               // ♂
    MALEFEM,            // ⚥
    CHECKMK,            // ✔
    XBALLOT,            // ✘
    LANGLE,             // ⟨
    RANGLE,             // ⟩

    CIRCUM,           // ^
    HACEK,            //  ̌
    TURNED,           // ↻
    DOTABVE,          //  ̇
    HOOK,             // ˞
    DOTBLOW,          // .
    GRAVE,            // `
    CEDILLE,          // ¸
    OGONEK = CEDILLE, // ˛
    RING,             // °
    DIARESS,          //  ̈
    SPASPER,          // ῾
    MACRON,           //  ̄
    ACUTE,            // ´
    TILDE,            // ˜
    SOLIDUS,          // /
    DBLACUT,          // ˝
    SPLENIS,          // ᾿
    BREVE,            // ˘
    VECTARR,          // →

    // Miscellaneous
    LEFTTAB, // tab but backwards

    COMPOSE,
    PASTHRU,
    LLOCK,
    NEO2,
    QWERTZ,
    QWERTY,
};

static void register_layer1(uint16_t key) {
    register_code16(key);
}
static void register_layer2(uint16_t key) {
    register_code16(S(key));
}
static void register_layer3(uint16_t key) {
    register_code(KC_CAPS_LOCK);
    register_code16(key);
}
static void register_layer4(uint16_t key) {
    register_code(KC_RALT);
    register_code16(key);
}
static void register_layer5(uint16_t key) {
    register_code(KC_CAPS_LOCK);
    register_code16(S(key));
}
static void register_layer6(uint16_t key) {
    register_code(KC_CAPS_LOCK);
    register_code(KC_RALT);
    register_code16(key);
}
static void tap_layer4(uint16_t key);
static void register_layer7(uint16_t key) {
    tap_layer4(KC_GRV);
    register_code16(key);
}
static void unregister_layer1(uint16_t key) {
    unregister_code16(key);
}
static void unregister_layer2(uint16_t key) {
    unregister_code16(S(key));
}
static void unregister_layer3(uint16_t key) {
    unregister_code(KC_CAPS_LOCK);
    unregister_code16(key);
}
static void unregister_layer4(uint16_t key) {
    unregister_code(KC_RALT);
    unregister_code16(key);
}
static void unregister_layer5(uint16_t key) {
    unregister_code(KC_CAPS_LOCK);
    unregister_code16(S(key));
}
static void unregister_layer6(uint16_t key) {
    unregister_code(KC_CAPS_LOCK);
    unregister_code(KC_RALT);
    unregister_code16(key);
}
static void unregister_layer7(uint16_t key) {
    unregister_code16(key);
}
static void tap_layer1(uint16_t key) {
    register_layer1(key);
    wait_ms(1);
    unregister_layer1(key);
}
static void tap_layer2(uint16_t key) {
    register_layer2(key);
    wait_ms(1);
    unregister_layer2(key);
}
static void tap_layer3(uint16_t key) {
    register_layer3(key);
    wait_ms(1);
    unregister_layer3(key);
}
static void tap_layer4(uint16_t key) {
    register_layer4(key);
    wait_ms(1);
    unregister_layer4(key);
}
static void tap_layer5(uint16_t key) {
    register_layer5(key);
    wait_ms(1);
    unregister_layer5(key);
}
static void tap_layer6(uint16_t key) {
    register_layer6(key);
    wait_ms(1);
    unregister_layer6(key);
}
static void tap_layer7(uint16_t key) {
    tap_layer4(KC_GRV);
    tap_code16(key);
}

static void register_on_layer(uint16_t key, uint8_t layer) {
    switch (layer) {
        case 1:
            register_layer1(key);
            break;
        case 2:
            register_layer2(key);
            break;
        case 3:
            register_layer3(key);
            break;
        case 4:
            register_layer4(key);
            break;
        case 5:
            register_layer5(key);
            break;
        case 6:
            register_layer6(key);
            break;
        case 7:
            register_layer7(key);
            break;
    }
}
static void unregister_on_layer(uint16_t key, uint8_t layer) {
    switch (layer) {
        case 1:
            unregister_layer1(key);
            break;
        case 2:
            unregister_layer2(key);
            break;
        case 3:
            unregister_layer3(key);
            break;
        case 4:
            unregister_layer4(key);
            break;
        case 5:
            unregister_layer5(key);
            break;
        case 6:
            unregister_layer6(key);
            break;
        case 7:
            unregister_layer7(key);
            break;
    }
}
static void tap_on_layer(uint16_t key, uint8_t layer) {
    switch (layer) {
        case 1:
            tap_layer1(key);
            break;
        case 2:
            tap_layer2(key);
            break;
        case 3:
            tap_layer3(key);
            break;
        case 4:
            tap_layer4(key);
            break;
        case 5:
            tap_layer5(key);
            break;
        case 6:
            tap_layer6(key);
            break;
        case 7:
            tap_layer7(key);
            break;
    }
}

enum layers { _L1, _L2, _L3, _L4, _L5, _L6, _L7, _L8, _L9, FN, KP1, KP2, KP3, STN };

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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L1] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, X,       V,       L,       C,       W,       K,       H,       G,       F,       Q,       SZLIG,
        CIRCUM,  U,       I,       A,       E,       O,       S,       N,       R,       T,       D,       Y,
        DIARESS, U_DIA,   O_DIA,   A_DIA,   P,       Z,       B,       M,       COMMA,   PERIOD,  J,       XXXXXXX,
        KC_LCTL, OSL(FN), KC_LGUI, KC_LALT, PASTHRU, TG(KP1), TG(STN), LLOCK,   KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          TT(_L6), TT(_L2), TT(_L3), KC_SPC,                    TT(_L7), TT(_L4), TT(_L5), KC_SPC
    ),
    [_L2] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, CX,      CV,      CL,      CC,      CW,      CK,      CH,      CG,      CF,      CQ,      CSZLIG,
        HACEK,   CU,      CI,      CA,      CE,      CO,      CS,      CN,      CR,      CT,      CD,      CY,
        SPASPER, CU_DIA,  CO_DIA,  CA_DIA,  CP,      CZ,      CB,      CM,      ENDASH,  BULLET,  CJ,      XXXXXXX,
        LSHCTL,  OSL(FN), LSHGUI,  LSHALT,  PASTHRU, TG(KP1), TG(STN),  LLOCK,   RSHALT,  RSHGUI,  SHAPP,   RSHCTL,
                          TT(_L6), TT(_L2), TT(_L6), KC_SPC,                    XXXXXXX, XXXXXXX, TT(_L8), KC_SPC
    ),
    [_L3] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, ELLIPS,  LOWLINE, LBRACKT, RBRACKT, ACIRCUM, EXCLAM,  LESSTHN, GREATER, EQUALS,  AMPSAND, LONG_S,
        DOTABVE, BSLASH,  FSLASH,  LBRACE,  RBRACE,  ASTERSK, QUESTN,  LPARENS, RPARENS, HYPHMIN, COLON,   AT,
        ACUTE,   NUMBER,  DOLLAR,  VRTLINE, ATILDE,  AGRAVE,  PLUS,    PERCENT, QUOT,    AAPOSTR, SEMCOL,  XXXXXXX,
        KC_LCTL, OSL(FN), KC_LGUI, KC_LALT, PASTHRU, TG(KP1), TG(STN), LLOCK,   KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          TT(_L6), TT(_L6), TT(_L3), KC_SPC,                    TT(_L7), TT(_L7), XXXXXXX, KC_SPC
    ),
    [_L4] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, INVEXCL, SEVEN,   EIGHT,   NINE,    PLUS,    MINUS,
        DOTBLOW, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  INVQMRK, FOUR,    FIVE,    SIX,     COMMA,   PERIOD,
        SOLIDUS, KC_ESC,  KC_TAB,  KC_PSTE, KC_ENT,  KC_UNDO, COLON,   ONE,     TWO,     THREE,   SEMCOL,  KC_RSFT,
        RLTCTL,  OSL(FN), RLTGUI,  RLTALT,  PASTHRU, TG(KP1), TG(STN), LLOCK,   KC_RALT, RLTRGUI, RLTAPP,  RLTRCTL,
                          XXXXXXX, XXXXXXX, TT(_L7), ZERO,                      TT(_L7), TT(_L4), TT(_L9), ZERO
    ),
    [_L5] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, ONE,     TWO,     THREE,   FOUR,    FIVE,    SIX,     SEVEN,   EIGHT,   NINE,    ZERO,    HYPHMIN,
        CEDILLE, DEGREE,  SECTION, SCRIPTL, RDGUILM, LDGUILM, DOLLAR,  EURO,    LODQUOT, LDQUOT,  RDQUOT,  EMDASH,
        SPLENIS, SUPONE,  SUPTWO,  SUPTHRE, RSGUILM, LSGUILM, CENTSGN, YEN,     LOSQUOT, LSQUOT,  RSQUOT,  HYPHMIN,
        KC_LCTL, OSL(FN), KC_LGUI, KC_LALT, PASTHRU, TG(KP1), TG(STN), LLOCK,   KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          XXXXXXX, TT(_L8), XXXXXXX, KC_SPC,                    TT(_L9), XXXXXXX, TT(_L5), KC_SPC
    ),
    [_L6] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, XI,      XXXXXXX, LAMBDA,  CHI,     OMEGA,   KAPPA,   PSI,     GAMMA,   PHI,     VARPHI,  FSIGMA,
        TURNED,  XXXXXXX, IOTA,    ALPHA,   EPSILON, OMICRON, SIGMA,   NU,      RHO,     TAU,     DELTA,   UPSILON,
        MACRON,  XXXXXXX, LUNEPS,  ETA,     PI,      ZETA,    BETA,    MU,      VARRHO,  VRTHETA, THETA,   XXXXXXX,
        LSHCTL,  OSL(FN), LSHGUI,  LSHALT,  PASTHRU, TG(KP1), TG(STN), LLOCK,   RSHALT,  RSHGUI,  SHAPP,   RSHCTL,
                          TT(_L6), TT(_L6), TT(_L6), KC_SPC,                    XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC
    ),
    [_L7] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, CXI,     SQRT,    CLAMBDA, COMPLEX, COMEGA,  MULTSGN, CPSI,    CGAMMA,  CPHI,    RATIONL, RINGOP,
        HOOK,    SUBSET,  INTEGRL, FORALL,  THREXST, ELEMOF,  CSIGMA,  NATURAL, REAL,    PARTDRV, CDELTA,  NABLA,
        TILDE,   UNION,   INTRSCT, ALEF,    CPI,     INTEGER, LDBLARR, LRDBARR, RDBLARR, RARRBAR, CTHETA,  XXXXXXX,
        RLTCTL,  OSL(FN), RLTGUI,  RLTALT,  PASTHRU, TG(KP1), TG(STN), LLOCK,   KC_RALT, RLTRGUI, RLTAPP,  RLTRCTL,
                          XXXXXXX, XXXXXXX, TT(_L7), KC_SPC,                    TT(_L7), TT(_L7), XXXXXXX, KC_SPC
    ),
    [_L8] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, FEMORD,  MASCORD, NUMERO,  XXXXXXX, MIDDOT,  POUND,   CURENCY, KC_TAB,  FSLASH,  ASTERSK, HYPHMIN,
        RING,    SUBONE,  SUBTWO,  SUBTHRE, FEMALE,  MALE,    MALEFEM, VARKPPA, LANGLE,  RANGLE,  SUBZERO, NBHYP,
        BREVE,   NOTSIGN, LOR,     LAND,    UPTACK,  MEASANG, PARALLL, RIGHTAR, INFINIT, PROPTO,  EMPTYST, SHYPHEN,
        KC_LCTL, OSL(FN), KC_LGUI, KC_LALT, PASTHRU, TG(KP1), TG(STN), LLOCK,   KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          XXXXXXX, TT(_L8), XXXXXXX, KC_SPC,                    XXXXXXX, XXXXXXX, TT(_L8), KC_SPC
    ),
    [_L9] = LAYOUT_ortho_4x6_2x2uc(
        COMPOSE, XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, KC_WH_U, KC_BTN4, XXXXXXX,
        GRAVE,   XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN6, KC_WH_D, KC_BTN5, XXXXXXX,
        DBLACUT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, OSL(FN), KC_LGUI, KC_LALT, PASTHRU, TG(KP1), TG(STN), LLOCK,   KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                          XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,                    TT(_L9), XXXXXXX, TT(_L9), KC_SPC
    ),
    [FN] = LAYOUT_ortho_4x6_2x2uc(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NEO2,    XXXXXXX, XXXXXXX, XXXXXXX, QWERTY,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTZ,  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [KP1] = LAYOUT_ortho_4x6_2x2uc(
        KC_NLCK, KC_TAB,  KC_PSLS, KC_PAST, KC_PMNS, XXXXXXX, XXXXXXX, LEFTTAB, FSLASH,  ASTERSK, HYPHMIN, XXXXXXX,
        XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, XXXXXXX, XXXXXXX, CHECKMK, XBALLOT, DAGGER,  PLUS,    XXXXXXX,
        XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PENT, XXXXXXX, XXXXXXX, CLUBS,   EURO,    TRIBLLT, KC_PENT, XXXXXXX,
        XXXXXXX, KC_P1,   KC_P2,   KC_P7,   KC_PDOT, TG(KP1), XXXXXXX, DIAMOND, HEART,   SPADE,   PERIOD,  XXXXXXX,
                          TG(KP2), TG(KP3), KC_P0,   KC_P0,                     TG(KP2), TG(KP3), OPNBOX,  OPNBOX
    ),
    [KP2] = LAYOUT_ortho_4x6_2x2uc(
        XXXXXXX, EQUALS,  DIVSGN,  DOTOPER, MINUS,   XXXXXXX, XXXXXXX, NOTEQAL, FRACTSL, MULTSGN, SETMINS, XXXXXXX,
        XXXXXXX, UDARROW, UPARROW, VECTARR, PLSMNS,  XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_PGUP, MINPLS,  XXXXXXX,
        XXXXXXX, LEFTARR, COLON,   RIGHTAR, KC_PENT, XXXXXXX, XXXXXXX, KC_LEFT, XXXXXXX, KC_RGHT, KC_PENT, KC_RSFT,
        XXXXXXX, LRARROW, DOWNARR, RLHARPO, COMMA,   TG(KP1), XXXXXXX, KC_END,  KC_DOWN, KC_PGDN, KC_DEL,  XXXXXXX,
                          TG(KP2), TG(KP3), PERCENT, PERCENT,                   TG(KP2), TG(KP3), KC_PSTE, KC_PSTE
    ),
    [KP3] = LAYOUT_ortho_4x6_2x2uc(
        XXXXXXX, ALMSTEQ, DIAMETR, CDOT,    CMINUS,  XXXXXXX, XXXXXXX, IDENTCL, DIVIDES, CTIMES,  DOTMINS, XXXXXXX,
        XXXXXXX, MCHLESS, INTRSCT, MCHGRTR, CPLUS,   XXXXXXX, XXXXXXX, LCEILNG, NARYINT, RCEILNG, DOTPLUS, XXXXXXX,
        XXXXXXX, SUBSET,  ORIGNAL, SUPRSET, KC_PENT, XXXXXXX, XXXXXXX, SUBEQL,  IMAGEOF, SUPREQL, KC_PENT, XXXXXXX,
        XXXXXXX, LEQUAL,  UNION,   GEQUAL,  PRIME,   TG(KP1), XXXXXXX, LFLOOR,  NARYUNI, RFLOOR,  DPRIME,  XXXXXXX,
                          TG(KP2), TG(KP3), PERMILL, PERMILL,                   TG(KP2), TG(KP3), WHTSQAR, WHTSQAR
    ),
    [STN] = LAYOUT_ortho_4x6_2x2uc(
        STN_N1,  STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NA,
        STN_PLS, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
        STN_PLS, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(STN), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          STN_HAT, STN_HAT, STN_A,   STN_O,                     STN_HAT, STN_HAT, STN_E,   STN_U
    ),
};
// clang-format on

uint16_t layout          = NEO2;
bool     lock_layer_held = false;

#define DECODED_KEY_USE_UNICODE 1
#define DECODED_KEY_ONESHOT 2
#define DECODED_KEY_SPECIAL 4

struct decoded_key {
    uint16_t keycode;
    uint8_t  layer;
    uint8_t  flags;
};

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LLOCK:
            if (record->event.pressed) {
                lock_layer_held = true;
            } else {
                lock_layer_held = false;
            }
            break;
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
    steno_set_mode(STENO_MODE_GEMINI);
}
