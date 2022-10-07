const uint16_t keycode_to_char[][6] = {
  [KC_SPACE] = {
    0x20,
    0x0,
    0x0,
    0x30,
    0xa0,
    0x202f,
  },
  [KC_Y] = {
    0x6b,
    0x4b,
    0x21,
    0xa1,
    0x3ba,
    0xd7,
  },
  [KC_COMM] = {
    0x0,
    0x2013,
    0x22,
    0x32,
    0x3f1,
    0x21d2,
  },
  [KC_Z] = {
    0xfc,
    0xdc,
    0x23,
    0x0,
    0x0,
    0x222a,
  },
  [KC_6] = {
    0x36,
    0x24,
    0xa2,
    0xa3,
    0x26a5,
    0x2225,
  },
  [KC_X] = {
    0xf6,
    0xd6,
    0x24,
    0x0,
    0x3f5,
    0x2229,
  },
  [KC_M] = {
    0x6d,
    0x4d,
    0x25,
    0x31,
    0x3bc,
    0x21d4,
  },
  [KC_P0] = {
    0x30,
    0x2423,
    0x25,
    0x0,
    0x2030,
    0x25a1,
  },
  [KC_P] = {
    0x71,
    0x51,
    0x26,
    0x2b,
    0x3d5,
    0x211a,
  },
  [KC_DOT] = {
    0x2e,
    0x2022,
    0x27,
    0x33,
    0x3d1,
    0x21a6,
  },
  [KC_J] = {
    0x6e,
    0x4e,
    0x28,
    0x34,
    0x3bd,
    0x2115,
  },
  [KC_K] = {
    0x72,
    0x52,
    0x29,
    0x35,
    0x3c1,
    0x211d,
  },
  [KC_KP_ASTERISK] = {
    0x2a,
    0x2a,
    0x22c5,
    0xd7,
    0x2299,
    0x2297,
  },
  [KC_G] = {
    0x6f,
    0x4f,
    0x2a,
    0x0,
    0x3bf,
    0x2208,
  },
  [KC_0] = {
    0x30,
    0x201d,
    0x2019,
    0x2a,
    0x2080,
    0x2205,
  },
  [KC_KP_PLUS] = {
    0x2b,
    0x2b,
    0xb1,
    0x2213,
    0x2295,
    0x2214,
  },
  [KC_N] = {
    0x62,
    0x42,
    0x2b,
    0x3a,
    0x3b2,
    0x21d0,
  },
  [KC_KP_DOT] = {
    0x2c,
    0x2e,
    0x2c,
    0x0,
    0x2032,
    0x2033,
  },
  [KC_SCLN] = {
    0x64,
    0x44,
    0x3a,
    0x2c,
    0x3b4,
    0x394,
  },
  [KC_MINS] = {
    0x2d,
    0x2014,
    0x0,
    0x2d,
    0x2011,
    0xad,
  },
  [KC_KP_MINUS] = {
    0x2d,
    0x2d,
    0x2212,
    0x2216,
    0x2296,
    0x2238,
  },
  [KC_L] = {
    0x74,
    0x54,
    0x2d,
    0x36,
    0x3c4,
    0x2202,
  },
  [KC_QUOT] = {
    0x79,
    0x59,
    0x40,
    0x2e,
    0x3c5,
    0x2207,
  },
  [KC_KP_SLASH] = {
    0x2f,
    0x2f,
    0xf7,
    0x2044,
    0x2300,
    0x2223,
  },
  [KC_S] = {
    0x69,
    0x49,
    0x2f,
    0x0,
    0x3b9,
    0x222b,
  },
  [KC_9] = {
    0x39,
    0x201c,
    0x2018,
    0x2f,
    0x27e9,
    0x221d,
  },
  [KC_1] = {
    0x31,
    0xb0,
    0xb9,
    0xaa,
    0x2081,
    0xac,
  },
  [KC_P1] = {
    0x31,
    0x2666,
    0x2194,
    0x0,
    0x2264,
    0x230a,
  },
  [KC_2] = {
    0x32,
    0xa7,
    0xb2,
    0xba,
    0x2082,
    0x2228,
  },
  [KC_P2] = {
    0x32,
    0x2665,
    0x2193,
    0x0,
    0x222a,
    0x22c3,
  },
  [KC_3] = {
    0x33,
    0x2113,
    0xb3,
    0x2116,
    0x2083,
    0x2227,
  },
  [KC_P3] = {
    0x33,
    0x2660,
    0x21cc,
    0x0,
    0x2265,
    0x230b,
  },
  [KC_4] = {
    0x34,
    0xbb,
    0x203a,
    0x0,
    0x2640,
    0x22a5,
  },
  [KC_P4] = {
    0x34,
    0x2663,
    0x2190,
    0x0,
    0x2282,
    0x2286,
  },
  [KC_5] = {
    0x35,
    0xab,
    0x2039,
    0xb7,
    0x2642,
    0x2221,
  },
  [KC_P5] = {
    0x35,
    0x20ac,
    0x3a,
    0x0,
    0x22b6,
    0x22b7,
  },
  [KC_P6] = {
    0x36,
    0x2023,
    0x2192,
    0x0,
    0x2283,
    0x2287,
  },
  [KC_7] = {
    0x37,
    0x20ac,
    0xa5,
    0xa4,
    0x3f0,
    0x2192,
  },
  [KC_P7] = {
    0x37,
    0x2714,
    0x2195,
    0x0,
    0x226a,
    0x2308,
  },
  [KC_U] = {
    0x68,
    0x48,
    0x3c,
    0x37,
    0x3c8,
    0x3a8,
  },
  [KC_8] = {
    0x38,
    0x201e,
    0x201a,
    0x0,
    0x27e8,
    0x221e,
  },
  [KC_P8] = {
    0x38,
    0x2718,
    0x2191,
    0x0,
    0x2229,
    0x22c2,
  },
  [KC_I] = {
    0x67,
    0x47,
    0x3e,
    0x38,
    0x3b3,
    0x393,
  },
  [KC_P9] = {
    0x39,
    0x2020,
    0x0,
    0x0,
    0x226b,
    0x2309,
  },
  [KC_O] = {
    0x66,
    0x46,
    0x3d,
    0x39,
    0x3c6,
    0x3a6,
  },
  [KC_SLSH] = {
    0x6a,
    0x4a,
    0x3b,
    0x3b,
    0x3b8,
    0x398,
  },
  [KC_NUM_LOCK] = {
    0x0,
    0x0,
    0x3d,
    0x2260,
    0x2248,
    0x2261,
  },
  [KC_H] = {
    0x73,
    0x53,
    0x3f,
    0xbf,
    0x3c3,
    0x3a3,
  },
  [KC_E] = {
    0x6c,
    0x4c,
    0x5b,
    0x0,
    0x3bb,
    0x39b,
  },
  [KC_A] = {
    0x75,
    0x55,
    0x5c,
    0x0,
    0x0,
    0x2282,
  },
  [KC_R] = {
    0x63,
    0x43,
    0x5d,
    0x0,
    0x3c7,
    0x2102,
  },
  [KC_T] = {
    0x77,
    0x57,
    0x5e,
    0x0,
    0x3c9,
    0x3a9,
  },
  [KC_W] = {
    0x76,
    0x56,
    0x5f,
    0x0,
    0x0,
    0x221a,
  },
  [KC_B] = {
    0x7a,
    0x5a,
    0x60,
    0x0,
    0x3b6,
    0x2124,
  },
  [KC_D] = {
    0x61,
    0x41,
    0x7b,
    0x0,
    0x3b1,
    0x2200,
  },
  [KC_C] = {
    0xe4,
    0xc4,
    0x7c,
    0x0,
    0x3b7,
    0x2135,
  },
  [KC_F] = {
    0x65,
    0x45,
    0x7d,
    0x0,
    0x3b5,
    0x2203,
  },
  [KC_V] = {
    0x70,
    0x50,
    0x7e,
    0x0,
    0x3c0,
    0x3a0,
  },
  [KC_LBRC] = {
    0xdf,
    0x1e9e,
    0x17f,
    0x2212,
    0x3c2,
    0x2218,
  },
  [KC_Q] = {
    0x78,
    0x58,
    0x2026,
    0x0,
    0x3be,
    0x39e,
  },
};
