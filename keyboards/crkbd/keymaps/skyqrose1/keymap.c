/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include <stdio.h>

enum layers {
  L_ALPHA,
  L_NUMPUNC,
  L_NAV,
  L_SYSTEM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_ALPHA] = LAYOUT_split_3x6_3(
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
      KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
      KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G,
      KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,
      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_DEL,
      TT(L_NAV), KC_LGUI, KC_LCTL, KC_SPC, TT(L_NUMPUNC), KC_RALT
  ),
  [L_NUMPUNC] = LAYOUT_split_3x6_3(
      KC_TRNS, KC_LT, KC_GT, KC_LCBR, KC_RCBR, KC_CALC,
      KC_PPLS, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
      KC_TRNS, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_QUOT,
      KC_MINS, KC_4, KC_5, KC_6, KC_PAST, KC_TRNS,
      KC_TRNS, KC_GRV, KC_BSLS, KC_EQL, KC_SCLN, KC_COMM,
      KC_DOT, KC_1, KC_2, KC_3, KC_SLSH, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(L_ALPHA), KC_TRNS
  ),
  [L_NAV] = LAYOUT_split_3x6_3(
      KC_TRNS, TO(L_SYSTEM), KC_MPRV, KC_MPLY, KC_MNXT, KC_BRIU,
      KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_TRNS,
      KC_TRNS, KC_F24, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID,
      KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS,
      KC_TRNS, KC_PSCR, KC_MAIL, KC_F14, KC_F15, KC_F16,
      KC_NO, KC_BTN1, KC_BTN3, KC_BTN2, KC_NO, KC_TRNS,
      TO(L_ALPHA), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [L_SYSTEM] = LAYOUT_split_3x6_3(
      KC_TRNS, TO(L_ALPHA), RESET, RGB_TOG, CG_NORM, CG_SWAP,
      KC_PWR, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
      KC_TRNS, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,
      KC_SLEP, KC_F4, KC_F5, KC_F6, KC_F11, KC_TRNS,
      KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,
      KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,
      TO(L_ALPHA), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

#ifdef OLED_DRIVER_ENABLE
// Portrait orientation
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

int highest_layer_index(layer_state_t layer_state_copy) {
  int result = 0;
  while (layer_state_copy >>= 1) result++;
  return result;
}

void render_layer_state(void) {
    char unknown_layer_name[16] = {};
    oled_write_P(PSTR("Layer: "), false);
    switch (highest_layer_index(layer_state)) {
        case L_ALPHA:
            oled_write_ln_P(PSTR("A"), false);
            break;
        case L_NUMPUNC:
            oled_write_ln_P(PSTR("#"), false);
            break;
        case L_NAV:
            oled_write_ln_P(PSTR("Nav"), false);
            break;
        case L_SYSTEM:
            oled_write_ln_P(PSTR("Sys"), false);
            break;
        default:
            snprintf(
                unknown_layer_name,
                sizeof(unknown_layer_name),
                "? (%2d) (%3lu)",
                highest_layer_index(layer_state),
                layer_state
            );
            oled_write_ln(unknown_layer_name, false);
            break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void render_keylog(void) {
    oled_write_ln(keylog_str, false);
}

#define FONT_BLANK 0x00
#define FONT_MOD_SHIFT 0x85
#define FONT_MOD_CTRL 0x86
#define FONT_MOD_ALT 0x87
#define FONT_MOD_GUI_COMMAND 0x88
#define FONT_MOD_GUI_WINDOWS 0x89
#define FONT_MOD_GUI_APPLE 0x8a
#define FONT_MOD_GUI_GNOME 0x8b
#define FONT_MOD_GUI_TUX 0x8C
void render_mods(void) {
  uint8_t modifiers = get_mods()|get_oneshot_mods();
  oled_write_char(
      (modifiers & MOD_MASK_SHIFT)
      ? FONT_MOD_SHIFT
      : FONT_BLANK
  , false);
  oled_write_char(
      (modifiers & MOD_MASK_CTRL)
      ? FONT_MOD_CTRL
      : FONT_BLANK
  , false);
  oled_write_char(
      (modifiers & MOD_MASK_ALT)
      ? FONT_MOD_ALT
      : FONT_BLANK
  , false);
  oled_write_char(
      (modifiers & MOD_MASK_GUI)
      ? FONT_MOD_GUI_TUX
      : FONT_BLANK
  , false);
  oled_write_char(FONT_BLANK, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_logo();
        render_space();
        render_mods();
        render_space();
        render_layer_state();
        render_space();
        render_keylog();
    } else {
        render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE
#include QMK_KEYBOARD_H
