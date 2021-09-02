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
#include "keycode_to_char.h"

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
  L_PUNC,
  L_NAV,
  L_SYS,
  L_GAME,
};
#define NUM_LAYERS 5

const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_ESC, LSFT_T(KC_A), LCTL_T(KC_S), LGUI_T(KC_D), KC_F, KC_G,
                                                       KC_H, KC_J, RGUI_T(KC_K), RCTL_T(KC_L), RSFT_T(KC_MINS), KC_QUOT,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RALT,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               KC_TAB, TT(L_PUNC), KC_BSPC,         KC_SPC, TT(L_NAV), TO(L_BASE)
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_PUNC] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, XXXXXXX, KC_MINS, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, LSFT_T(KC_1), LCTL_T(KC_2), LGUI_T(KC_3), KC_4, KC_5,
                                                          KC_6, KC_7, RGUI_T(KC_8), RCTL_T(KC_9), RSFT_T(KC_0), _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, KC_CALC, KC_SCLN, KC_COLN, KC_EQL,           KC_PPLS, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, _______, _______
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_NAV] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, TO(L_SYS), KC_MPRV, KC_MPLY, KC_MNXT, KC_BRIU,        XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, LSFT_T(KC_F24), LCTL_T(KC_MUTE), LGUI_T(KC_VOLD), KC_VOLU, KC_BRID,
                                                                   XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_CAPS, KC_MAIL, KC_APP,  KC_F15,  KC_F16,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, _______, _______
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_SYS] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, TO(L_GAME), XXXXXXX, XXXXXXX, XXXXXXX,       KC_PWR,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,          KC_SLEP, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, _______, _______
//                            +--------+--------+--------+        +--------+--------+--------+
   ),
  [L_GAME] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TAB,  KC_1,    KC_Q,    KC_W,    KC_E,    KC_R,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_ESC,  KC_2,    KC_A,    KC_S,    KC_D,    KC_F,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_LSFT, KC_LSFT, KC_MINS, KC_LBRC, KC_RBRC, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               KC_LALT, KC_LCTL, KC_SPC,           _______, XXXXXXX, _______
//                            +--------+--------+--------+        +--------+--------+--------+
  )
};

#ifdef OLED_ENABLE
// Portrait orientation
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

// Custom Fonts
#define FONT_MOD_CTRL 0x94
#define FONT_MOD_SHIFT 0x95
#define FONT_MOD_ALT 0x96
#define FONT_MOD_GUI_COMMAND 0x97
#define FONT_MOD_GUI_WINDOWS 0x98
#define FONT_MOD_GUI_APPLE 0x99
#define FONT_MOD_GUI_GNOME 0x9a
#define FONT_MOD_GUI_TUX 0x9b
#define FONT_SWAP_ARROWS 0x9c
#define FONT_LOCK 0x9d

#define FONT_LAYER_INDICATORS 0x85 // through 0x88

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_logo(void) {
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

// gives the icon for the highest active layer
void render_layer_icon(void) {
  const char icons[NUM_LAYERS][3][3] = {
    [L_BASE] = {
      {' ', 0x89, 0x8a},
      {0xa8, 0xa9, 0xaa},
      {0xc8, 0xc9, 0xca}
    },
    [L_PUNC] = {
      {0x8b, 0x8c, 0x8d},
      {0xab, 0xac, 0xad},
      {0xcb, 0xcc, 0xcd}
    },
    [L_NAV] = {
      {0x8e, 0x8f, 0x90},
      {0xae, 0xaf, 0xb0},
      {0xce, 0xcf, 0xd0}
    },
    [L_SYS] = {
      {0x91, 0x92, 0x93},
      {0xb1, 0xb2, 0xb3},
      {0xd1, 0xd2, 0xd3}
    },
    [L_GAME] = {
      {' ', ' ', ' '},
      {0xa5, 0xa6, 0xa7},
      {0xc5, 0xc6, 0xc7}
    },
  };
  const char blank[3][3] = {{' ', ' ', ' '}, {' ', '?', ' '}, {' ', ' ', ' '}};
  uint8_t layer = get_highest_layer(layer_state);
  const char (*icon)[3] = (layer < NUM_LAYERS) ? icons[layer] : blank;
  for (uint8_t i = 0; i < 3; i++) {
    oled_write_char(' ', false);
    oled_write_char(icon[i][0], false);
    oled_write_char(icon[i][1], false);
    oled_write_char(icon[i][2], false);
    oled_write_char(' ', false);
  }
}

// show which of the first 10 layers are active
void render_layer_bits(void) {
  for (int8_t i=8; i>=0; i-=2) {
    uint8_t layer_bits = (layer_state >> i) & 3;
    oled_write_char(FONT_LAYER_INDICATORS + layer_bits, false);
  }
}

void render_position_hint(keypos_t key) {
  uint8_t layer = layer_switch_get_layer(key);
  uint16_t keycode = keymap_key_to_keycode(layer, key);
  char name = keycode_to_char(keycode);
  oled_write_char(name, false);
}

void render_layout_hint(void) {
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
  //if (is_keyboard_master()) {
    render_logo(); // 0
    render_space(); // 1
    render_layer_icon(); // 2-4
    render_layer_bits();  // 5
    render_space(); // 6
    render_layout_hint(); // 7-10
    render_space(); // 11
    render_keylog(); // 12-13
    render_alerts(); // 14
    render_mods(); // 15
  //}
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
