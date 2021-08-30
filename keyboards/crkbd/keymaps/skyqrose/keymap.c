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

#ifdef COMBO_ENABLE
enum combos {
  C_LBRC,
  C_LPRN,
  C_LCBR,
  C_RBRC,
  C_RPRN,
  C_RCBR,
  C_ENT,
  C_TAB,
  C_ESC,
};
const uint16_t PROGMEM combo_lbrc[] = {KC_E, KC_U, COMBO_END};
const uint16_t PROGMEM combo_lprn[] = {LGUI_T(KC_D), KC_J, COMBO_END};
const uint16_t PROGMEM combo_lcbr[] = {KC_C, KC_M, COMBO_END};
const uint16_t PROGMEM combo_rbrc[] = {KC_R, KC_I, COMBO_END};
const uint16_t PROGMEM combo_rprn[] = {KC_F, RGUI_T(KC_K), COMBO_END};
const uint16_t PROGMEM combo_rcbr[] = {KC_V, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_F, RSFT_T(KC_MINS), COMBO_END};
const uint16_t PROGMEM combo_tab[] = {LSFT(KC_A), KC_J, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_E, KC_I, COMBO_END};
combo_t key_combos[] = {
  [C_LBRC] = COMBO(combo_lbrc, KC_LBRC),
  [C_LPRN] = COMBO(combo_lprn, KC_LPRN),
  [C_LCBR] = COMBO(combo_lcbr, KC_LCBR),
  [C_RBRC] = COMBO(combo_rbrc, KC_RBRC),
  [C_RPRN] = COMBO(combo_rprn, KC_RPRN),
  [C_RCBR] = COMBO(combo_rcbr, KC_RCBR),
  [C_ENT] = COMBO(combo_ent, KC_ENT),
  [C_TAB] = COMBO(combo_tab, KC_TAB),
  [C_ESC] = COMBO(combo_esc, KC_ESC),
};

// instead of setting COMBO_COUNT in config.h, calculate it at compile time
uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);

#define COMBO_ONLY_FROM_LAYER L_BASE

// prevents holding combos, because I have shared mod+combo keys
// also requires COMBO_MUST_TAP_PER_COMBO
bool get_combo_must_tap(uint16_t index, combo_t *combo) { return true; }
#endif // COMBO_ENABLE

#ifdef KEY_OVERRIDE_ENABLE
const key_override_t shift_bspc_del = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t **key_overrides = (const key_override_t *[]){
  &shift_bspc_del,
  NULL
};
#endif // KEY_OVERRIDE_ENABLE

enum layers {
  L_BASE,
  L_NUMPUNC,
  L_NAV,
  L_SYSTEM,
  L_GAME,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_NO,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_NO, LSFT_T(KC_A), LCTL_T(KC_S), LGUI_T(KC_D), KC_F, KC_G,   KC_H, KC_J, RGUI_T(KC_K), RCTL_T(KC_L), RSFT_T(KC_MINS), KC_QUOT,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RALT,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               KC_TAB,  TT(1),   KC_BSPC,          KC_SPC,  TT(2),   KC_ENT
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_NUMPUNC] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_CALC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_EQL,           KC_PPLS, KC_SCLN, KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_NAV] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TRNS, TO(3),   KC_MPRV, KC_MPLY, KC_MNXT, KC_BRIU,          KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TRNS, KC_F24,  KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID,          KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TRNS, KC_PSCR, KC_MAIL, KC_F14,  KC_F15,  KC_F16,           KC_NO,   KC_BTN1, KC_BTN3, KC_BTN2, KC_NO,   KC_TRNS,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_SYSTEM] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TRNS, TO(0),   RESET,   KC_NO,   KC_NO,   KC_NO,            KC_PWR,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TRNS, TO(4),   KC_NO,   LCG_NRM, LCG_SWP, KC_NO,            KC_SLEP, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_TRNS,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TRNS, KC_CAPS, KC_NO,   KC_NO,   KC_NO,   TO(4),            KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_TRNS,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               TO(0), KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
//                            +--------+--------+--------+        +--------+--------+--------+
   ),
  [L_GAME] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TAB,  KC_1,    KC_Q,    KC_W,    KC_E,    KC_R,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_ESC,  KC_2,    KC_A,    KC_S,    KC_D,    KC_F,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_LSFT, KC_LSFT, KC_MINS, KC_LBRC, KC_RBRC, TO(0),            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               KC_LALT, KC_LCTL, KC_SPC,           KC_NO,   KC_NO,   KC_NO
//                            +--------+--------+--------+        +--------+--------+--------+
  )
};

#ifdef OLED_ENABLE
// Portrait orientation
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

// Custom Fonts
#define FONT_MOD_SHIFT 0x85
#define FONT_MOD_CTRL 0x86
#define FONT_MOD_ALT 0x87
#define FONT_MOD_GUI_COMMAND 0x88
#define FONT_MOD_GUI_WINDOWS 0x89
#define FONT_MOD_GUI_APPLE 0x8a
#define FONT_MOD_GUI_GNOME 0x8b
#define FONT_MOD_GUI_TUX 0x8c

#define FONT_LOCK 0xc5
#define FONT_LAYER_INDICATORS 0xc6 // through 0xc9
#define FONT_SWAP_ARROWS 0x8d

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

void render_alerts(void) {
  led_t host_led_state = host_keyboard_led_state();
  if(host_led_state.caps_lock) {
    oled_write_P(PSTR("CAPS"), false);
    oled_write_char(FONT_LOCK, false);
  }
  else if(keymap_config.swap_lctl_lgui) {
    oled_write_char(FONT_MOD_GUI_APPLE, false);
    oled_write_char(' ', false);
    oled_write_char(FONT_MOD_CTRL, false);
    oled_write_char(FONT_SWAP_ARROWS, false);
    oled_write_char(FONT_MOD_GUI_COMMAND, false);
  } else {
    render_space();
  }
}

int highest_layer_index(layer_state_t layer_state_copy) {
  int result = 0;
  while (layer_state_copy >>= 1) result++;
  return result;
}

void render_layer_state(void) {
    char unknown_layer_name[16] = {};
    oled_write("Layer", false);
    // show which of the first 10 layers are active
    for (int8_t i=8; i>=0; i-=2) {
      uint8_t layer_bits = (layer_state >> i) & 3;
      oled_write_char(FONT_LAYER_INDICATORS + layer_bits, false);
    }
    // give the name for the highest layer
    switch (highest_layer_index(layer_state)) {
        case L_BASE:
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
        case L_GAME:
            oled_write_ln_P(PSTR("Game"), false);
            break;
        default:
            snprintf(
                unknown_layer_name,
                sizeof(unknown_layer_name),
                "?? %2d",
                highest_layer_index(layer_state)
            );
            oled_write_ln(unknown_layer_name, false);
            break;
    }
}

char keycode_to_char(uint16_t keycode) {
  const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }
  if (keycode < 60) {
    return code_to_name[keycode];
  } else {
    return ' ';
  }
}

void render_position_hint(keypos_t key) {
  uint8_t layer = layer_switch_get_layer(key);
  uint16_t keycode = keymap_key_to_keycode(layer, key);
  char name = keycode_to_char(keycode);
  oled_write_char(name, false);
}

void render_layer_hint(void) {
  uint8_t row;
  uint8_t col;
  keypos_t key;
  if (is_keyboard_master()) {
    for (row=0; row < 4; row++) {
      for (col=1; col < 6; col++) {
        key = (keypos_t) { .row = row, .col = col };
        render_position_hint(key);
      }
    }
  } else {
    for (row=4; row < 8; row++) {
      for (col=5; col > 0; col--) {
        key = (keypos_t) { .row = row, .col = col };
        render_position_hint(key);
      }
    }
  }
}

char keylog_str[24] = {};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = keycode_to_char(keycode);

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%1dx%1d %ck%4x",
           record->event.key.row, record->event.key.col,
           name, keycode);
}

void render_keylog(void) {
    oled_write_ln(keylog_str, false);
}

void render_mods(void) {
  uint8_t modifiers = get_mods()|get_oneshot_mods();
  oled_write_char((modifiers & MOD_MASK_SHIFT) ? FONT_MOD_SHIFT : ' ', false);
  oled_write_char((modifiers & MOD_MASK_CTRL) ? FONT_MOD_CTRL : ' ', false);
  oled_write_char((modifiers & MOD_MASK_ALT) ? FONT_MOD_ALT : ' ', false);
  oled_write_char((modifiers & MOD_MASK_GUI) ? FONT_MOD_GUI_TUX : ' ', false);
  oled_write_char(' ', false);
}

void oled_task_user(void) {
  // 16 rows, 5 cols
  if (is_keyboard_master()) {
    render_logo(); // 0-3
    render_alerts(); // 4
    render_space(); // 5
    render_layer_state();  // 6-8
    render_layer_hint(); // 9-12
    oled_set_cursor(0, 13);
    render_keylog(); // 13-14
    oled_set_cursor(0, 15);
    render_mods(); // 15
  } else {
    render_logo(); // 0-3
    render_alerts(); // 4
    render_space(); // 5
    render_layer_state();  // 6-8
    render_layer_hint(); // 9-12
    oled_set_cursor(0, 13);
    render_keylog(); // 13-14
    oled_set_cursor(0, 15);
    render_mods(); // 15
  }
}

// called on every keypress
// return true to continue normal processing
// return false to stop processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE
