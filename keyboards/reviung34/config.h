/*
Copyright 2019 gtips

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x4E03
#define DEVICE_VER      0x0001
#define MANUFACTURER    gtips
#define PRODUCT         reviung34

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 9

#define MATRIX_ROW_PINS { F4, F5, F6, F7 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B1, B3, B2, B6 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* RGB underglow */
#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
#  define RGBLED_NUM 9
#  define RGBLIGHT_HUE_STEP 8
#  define RGBLIGHT_SAT_STEP 8
#  define RGBLIGHT_VAL_STEP 8
#  define RGBLIGHT_LIMIT_VAL 255
#  define RGBLIGHT_SLEEP
#  define RGBLIGHT_EFFECT_BREATHING
#  define RGBLIGHT_EFFECT_RAINBOW_MOOD
#  define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#  define RGBLIGHT_EFFECT_SNAKE
#  define RGBLIGHT_EFFECT_KNIGHT
#  define RGBLIGHT_EFFECT_CHRISTMAS
#  define RGBLIGHT_EFFECT_STATIC_GRADIENT
#  define RGBLIGHT_EFFECT_RGB_TEST
#  define RGBLIGHT_EFFECT_ALTERNATING
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
