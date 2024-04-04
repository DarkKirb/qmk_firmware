// Copyright 2022 Charlotte 🦝 Delenk (@DarkKirb)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPLIT_HAND_PIN GP16
#define SPLIT_HAND_PIN_LOW_IS_LEFT

// Rows are doubled up for split keyboard support
#define MATRIX_ROWS 10
#define MATRIX_COLS 6
#define DEBUG_MATRIX_SCAN_RATE

#define UNICODE_SELECTED_MODES UC_LNX, UC_MAC, UC_WINC

#define OLED_DISPLAY_128X64

#define ONESHOT_TAP_TOGGLE 2

#define SERIAL_USART_HALF_DUPLEX
#define SERIAL_USART_TX_PIN GP18
//#define SERIAL_USART_RX_PIN GP19
//#define SERIAL_USART_PIN_SWAP

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
