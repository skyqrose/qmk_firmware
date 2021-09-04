/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

// Hand configuration
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#define USE_MATRIX_I2C
#define USE_SERIAL_PD2

// allow showing data on secondary hand's oled
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

#define TAPPING_FORCE_HOLD_PER_KEY
#define TAPPING_TERM 140
#define TAPPING_TOGGLE 1
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define RETRO_TAPPING

#define OLED_FONT_H "keyboards/crkbd/keymaps/skyqrose/glcdfont.c"

// Combos
// #define COMBO_ENABLE // set by rules.mk
// #define COMBO_COUNT 0 // counted at compile time by COMBO_LEN instead
#define COMBO_TERM 60
// My combos are all length 2, I'll never need more than length 6
#define EXTRA_SHORT_COMBOS
// I have combos that use mod keys. Tap for a combo, hold for a mod.
// along with definition of get_combo_must_tap
#define COMBO_MUST_TAP_PER_COMBO

#define FORCE_NKRO
#define USB_POLLING_INTERVAL_MS 2
#define QMK_KEYS_PER_SCAN 6
