#pragma once

// Only contains ASCII characters, because the rest is sparsely mapped
const struct decoded_key key_qwertz_mapping[] = {
    {KC_SPC, 1, 0},                  // " "
    {KC_1, 2, 0},                    // !
    {KC_2, 2, 0},                    // "
    {KC_NUHS, 1, 0},                 // #
    {KC_4, 2, 0},                    // $
    {KC_5, 2, 0},                    // %
    {KC_6, 2, 0},                    // &
    {KC_NUHS, 2, 0},                 // '
    {KC_8, 2, 0},                    // (
    {KC_9, 2, 0},                    // )
    {KC_RBRC, 2, 0},                 // *
    {KC_RBRC, 1, 0},                 // +
    {KC_COMM, 1, 0},                 // ,
    {KC_SLSH, 1, 0},                 // -
    {KC_DOT, 1, 0},                  // .
    {KC_7, 2, 0},                    // /
    {KC_0, 1, 0},                    // 0
    {KC_1, 1, 0},                    // 1
    {KC_2, 1, 0},                    // 2
    {KC_3, 1, 0},                    // 3
    {KC_4, 1, 0},                    // 4
    {KC_5, 1, 0},                    // 5
    {KC_6, 1, 0},                    // 6
    {KC_7, 1, 0},                    // 7
    {KC_8, 1, 0},                    // 8
    {KC_9, 1, 0},                    // 9
    {KC_DOT, 2, 0},                  // :
    {KC_COMM, 2, 0},                 // ;
    {KC_NUBS, 1, 0},                 // <
    {KC_0, 2, 0},                    // =
    {KC_NUBS, 2, 0},                 // >
    {KC_MINS, 2, 0},                 // ?
    {KC_Q, 4, 0},                    // @
    {KC_A, 2, 0},                    // A
    {KC_B, 2, 0},                    // B
    {KC_C, 2, 0},                    // C
    {KC_D, 2, 0},                    // D
    {KC_E, 2, 0},                    // E
    {KC_F, 2, 0},                    // F
    {KC_G, 2, 0},                    // G
    {KC_H, 2, 0},                    // H
    {KC_I, 2, 0},                    // I
    {KC_J, 2, 0},                    // J
    {KC_K, 2, 0},                    // K
    {KC_L, 2, 0},                    // L
    {KC_M, 2, 0},                    // M
    {KC_N, 2, 0},                    // N
    {KC_O, 2, 0},                    // O
    {KC_P, 2, 0},                    // P
    {KC_Q, 2, 0},                    // Q
    {KC_R, 2, 0},                    // R
    {KC_S, 2, 0},                    // S
    {KC_T, 2, 0},                    // T
    {KC_U, 2, 0},                    // U
    {KC_V, 2, 0},                    // V
    {KC_W, 2, 0},                    // W
    {KC_X, 2, 0},                    // X
    {KC_Z, 2, 0},                    // Y
    {KC_Y, 2, 0},                    // Z
    {KC_8, 4, 0},                    // [
    {KC_MINS, 4, 0},                 // '\'
    {KC_9, 4, 0},                    // ]
    {KC_NO, 0, DECODED_KEY_SPECIAL}, // ^
    {KC_SLSH, 2, 0},                 // _
    {KC_NO, 0, DECODED_KEY_SPECIAL}, // `
    {KC_A, 1, 0},                    // a
    {KC_B, 1, 0},                    // b
    {KC_C, 1, 0},                    // c
    {KC_D, 1, 0},                    // d
    {KC_E, 1, 0},                    // e
    {KC_F, 1, 0},                    // f
    {KC_G, 1, 0},                    // g
    {KC_H, 1, 0},                    // h
    {KC_I, 1, 0},                    // i
    {KC_J, 1, 0},                    // j
    {KC_K, 1, 0},                    // k
    {KC_L, 1, 0},                    // l
    {KC_M, 1, 0},                    // m
    {KC_N, 1, 0},                    // n
    {KC_O, 1, 0},                    // o
    {KC_P, 1, 0},                    // p
    {KC_Q, 1, 0},                    // q
    {KC_R, 1, 0},                    // r
    {KC_S, 1, 0},                    // s
    {KC_T, 1, 0},                    // t
    {KC_U, 1, 0},                    // u
    {KC_V, 1, 0},                    // v
    {KC_W, 1, 0},                    // w
    {KC_X, 1, 0},                    // x
    {KC_Z, 1, 0},                    // y
    {KC_Y, 1, 0},                    // z
    {KC_7, 4, 0},                    // {
    {KC_NUBS, 4, 0},                 // |
    {KC_0, 4, 0},                    // }
    {KC_RBRC, 4, 0}                  // ~
};

struct sparse_decoded_key {
    uint16_t           key;
    struct decoded_key decoded_key;
};

const struct sparse_decoded_key key_qwertz_sparse_mapping[] = {{NBSPACE, {KC_SPC, 4, 0}},  // Non-breaking space
                                                               {INVEXCL, {KC_5, 4, 0}},    // ¡
                                                               {SECTION, {KC_3, 2, 0}},    // §
                                                               {LDGUILM, {KC_V, 4, 0}},    // «
                                                               {SHYPHEN, {KC_SLSH, 4, 0}}, // soft hyphen
                                                               {DEGREE, {KC_GRV, 2, 0}},   // °
                                                               {SUPTWO, {KC_2, 4, 0}},     // ²
                                                               {SUPTHRE, {KC_3, 4, 0}},    // ³
                                                               {MIDDOT, {KC_DOT, 7, 0}},   // ·
                                                               {SUPONE, {KC_I, 7, 0}},     // ¹
                                                               {RDGUILM, {KC_C, 4, 0}},    // »
                                                               {INVQMRK, {KC_6, 4, 0}},    // ¿
                                                               {CA_DIA, {KC_QUOT, 2, 0}},  // Ä
                                                               {CO_DIA, {KC_SCLN, 2, 0}},  // Ö
                                                               {CU_DIA, {KC_LBRC, 2, 0}},  // Ü
                                                               {SZLIG, {KC_MINS, 1, 0}},   // ß
                                                               {A_DIA, {KC_QUOT, 1, 0}},   // ä
                                                               {O_DIA, {KC_SCLN, 1, 0}},   // ö
                                                               {U_DIA, {KC_LBRC, 1, 0}},   // ü
                                                               {LONG_S, {KC_LBRC, 7, 0}},  // ſ
                                                               {MU, {KC_M, 4, 0}},         // μ
                                                               {CSZLIG, {KC_H, 4, 0}},     // ẞ
                                                               {ENDASH, {KC_N, 4, 0}},     // –
                                                               {EMDASH, {KC_4, 4, 0}},     // —
                                                               {LSQUOT, {KC_DOT, 4, 0}},   // ‘
                                                               {RSQUOT, {KC_1, 4, 0}},     // ’
                                                               {LDQUOT, {KC_V, 7, 0}},     // “
                                                               {RDQUOT, {KC_B, 7, 0}},     // ”
                                                               {LODQUOT, {KC_X, 7, 0}},    // „
                                                               {ELLIPS, {KC_DOT, 4, 0}},   // …
                                                               {NNBSP, {KC_SPC, 7, 0}},    // narrow non-breaking space
                                                               {PRIME, {KC_F, 4, 0}},      // ′
                                                               {DPRIME, {KC_G, 4, 0}},     // ″
                                                               {LSGUILM, {KC_B, 4, 0}},    // ‹
                                                               {RSGUILM, {KC_Z, 4, 0}},    // ›
                                                               {EURO, {KC_E, 4, 0}},       // €
                                                               {EMPTYST, {KC_D, 4, 0}},    // ∅
                                                               {LEQUAL, {KC_A, 4, 0}},     // ≤
                                                               {GEQUAL, {KC_O, 4, 0}},     // ≥

                                                               {CIRCUM, {KC_GRV, 1, DECODED_KEY_ONESHOT}},
                                                               {HACEK, {KC_W, 3, DECODED_KEY_ONESHOT}},
                                                               {DOTABVE, {KC_EQL, 3, DECODED_KEY_ONESHOT}},
                                                               {DOTBLOW, {KC_SCLN, 3, DECODED_KEY_ONESHOT}},
                                                               {GRAVE, {KC_EQL, 2, DECODED_KEY_ONESHOT}},
                                                               {CEDILLE, {KC_J, 4, DECODED_KEY_ONESHOT}},
                                                               // TODO: disambiguate CEDILLE and OGONEK somehow
                                                               {OGONEK, {KC_L, 4, DECODED_KEY_ONESHOT}},
                                                               {DIARESS, {KC_R, 4, DECODED_KEY_ONESHOT}},
                                                               {MACRON, {KC_T, 4, DECODED_KEY_ONESHOT}},
                                                               {ACUTE, {KC_EQL, 1, DECODED_KEY_ONESHOT}},
                                                               {TILDE, {KC_I, 4, DECODED_KEY_ONESHOT}},
                                                               {DBLACUT, {KC_Y, 4, DECODED_KEY_ONESHOT}},
                                                               {SPLENIS, {KC_LBRC, 4, DECODED_KEY_ONESHOT}},
                                                               {BREVE, {KC_U, 4, DECODED_KEY_ONESHOT}},

                                                               {0, {0, 0, 0}}};
