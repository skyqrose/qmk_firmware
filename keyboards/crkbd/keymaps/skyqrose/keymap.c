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

enum layers {
  L_BASE,
  L_NUM,
  L_SYS,
  L_NORM,
  L_GAME,
};
#define NUM_LAYERS 5

#ifdef KEY_OVERRIDE_ENABLE
#define custom_layer_mask ((1 << L_BASE) | (1 << L_NUM) | (1 << L_SYS))
const key_override_t comm_scln = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, KC_SCLN, custom_layer_mask);
const key_override_t dot_cln = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT, KC_COLN, custom_layer_mask);
const key_override_t num_7 = ko_make_with_layers(MOD_MASK_SHIFT, KC_4, KC_7, custom_layer_mask);
const key_override_t num_8 = ko_make_with_layers(MOD_MASK_SHIFT, KC_5, KC_8, custom_layer_mask);
const key_override_t num_9 = ko_make_with_layers(MOD_MASK_SHIFT, KC_6, KC_9, custom_layer_mask);
const key_override_t **key_overrides = (const key_override_t *[]){
  &comm_scln,
  &dot_cln,
  &num_7,
  &num_8,
  &num_9,
  NULL
};
#endif // KEY_OVERRIDE_ENABLE

const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_MINS,
  KC_ENT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                  KC_LCTL, LSFT_T(KC_BSPC), LCMD_T(KC_DEL), LT(L_NUM, KC_SPC), LT(L_SYS, KC_SPC), XXXXXXX
  ),

  [L_NUM] = LAYOUT_split_3x6_3(
  _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PERC,          KC_DLR,  KC_4,    KC_5,    KC_6,    KC_ASTR, KC_PLUS,
  _______, KC_LABK, KC_RABK, KC_LPRN, KC_RPRN, KC_HASH,          KC_CIRC, KC_1,    KC_2,    KC_3,    KC_GRV,  KC_MINS,
  _______, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,          KC_TILD, KC_0,    _______, _______, _______, KC_AMPR,
                                 _______, _______, _______, _______, _______, _______
  ),

  [L_SYS] = LAYOUT_split_3x6_3(
  _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,          XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
  _______, KC_CAPS, KC_VOLD, KC_MUTE, KC_VOLU, TO(L_GAME),       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______, _______, _______, _______, _______, _______
  ),

  [L_GAME] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_1,    KC_Q,    KC_W,    KC_E,    KC_R,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,             KC_H,    KC_J,    KC_K,    KC_L,    KC_T,    _______,
    KC_LGUI, KC_LSFT, KC_MINS, KC_C,    KC_LBRC, KC_RBRC,          KC_N,    KC_M,    KC_C,    KC_X,    KC_Z,    KC_RSFT,
                               KC_LALT, KC_LCTL, KC_SPC,           KC_ENT,  KC_SPC,  TO(L_BASE)
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
    [L_NUM] = {
      {0x8b, 0x8c, 0x8d},
      {0xab, 0xac, 0xad},
      {0xcb, 0xcc, 0xcd}
    },
    [L_SYS] = {
      {0x8e, 0x8f, 0x90},
      {0xae, 0xaf, 0xb0},
      {0xce, 0xcf, 0xd0}
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

char keylog_str[11] = {};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = keycode_to_char(keycode);

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%1xx%1x %ck%4x",
           record->event.key.row & 0xF, record->event.key.col & 0xF,
           name, keycode);
}

void render_keylog(void) {
    oled_write(keylog_str, false);
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
  oled_set_cursor(/*col*/ 0, /*row*/ 0);
  render_logo(); // 0
  render_space(); // 1
  render_layer_icon(); // 2-4
  render_space(); // 5
  render_layout_hint(); // 6-9
  render_space(); // 10
  if (is_keyboard_master()) {
    render_keylog(); // 11-12
  } else {
    render_layer_bits();  // 11
    render_space(); // 12
  }
  render_alerts(); // 13
  render_mods(); // 14
}
#endif // OLED_ENABLE

// called on every keypress
// return true to continue normal processing
// return false to stop processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  led_t host_led_state = host_keyboard_led_state();
  uint8_t modifiers = get_mods()|get_oneshot_mods();
#ifdef OLED_ENABLE
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
#endif // OLED_ENABLE
  // turn - to _ if caps lock is pressed
  if(host_led_state.caps_lock && keycode == RSFT_T(KC_MINS)) {
    if (record->event.pressed) {
      if (modifiers && MOD_BIT(KC_LSFT)) {
        unregister_code(KC_LSFT);
        tap_code(KC_MINS);
        register_code(KC_LSFT);
      } else {
        register_code(KC_LSFT);
        tap_code(KC_MINS);
        unregister_code(KC_LSFT);
      }
    }
    return false;
  }
  return true;
}
