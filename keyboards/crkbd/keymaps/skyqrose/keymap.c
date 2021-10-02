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

enum custom_keycodes {
  /* If tapped, then KC_BSPC
   * If tapped and GUI is pressed, then KC_GRV for switching windows within an application
   * If tapped and SHFT is pressed, then KC_ESC
   * If held, then either LCTL or LGUI depending on THUMB_MOD
   * Set to an unused basic keycode so it can be used in mod tap
   */
  C_MODBSPC = SAFE_RANGE,
  // Set THUMB_MOD to LCTL
  C_TCTL,
  // Set THUMB_MOD to RCTL
  C_TGUI,
};

#ifdef KEY_OVERRIDE_ENABLE
const key_override_t comm_scln = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t dot_cln = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t gui_bspc_tild = ko_make_basic(MOD_MASK_GUI, LGUI_T(KC_BSPC), KC_GRV); // application switching
const key_override_t sft_bspc_esc = ko_make_basic(MOD_MASK_SHIFT, LGUI_T(KC_BSPC), KC_ESC);
const key_override_t ctl_bspc_del = ko_make_basic(MOD_MASK_CTRL, LGUI_T(KC_BSPC), KC_DEL);
const key_override_t **key_overrides = (const key_override_t *[]){
  &comm_scln,
  &dot_cln,
  &gui_bspc_tild,
  &sft_bspc_esc,
  &ctl_bspc_del,
  NULL
};
#endif // KEY_OVERRIDE_ENABLE

#ifdef TAPPING_FORCE_HOLD_PER_KEY
// keep tapping_force_hold off for most keys to allow double taps
// but turn it on for some keys that are likely to be quickly tapped then held when typing
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return false;
    }
}
#endif // TAPPING_FORCE_HOLD_PER_KEY

// TO(), but it takes effect when releasing instead of when pressing
// see comment on TO() in quantum_keycode.h
#define TO_RELEASE(layer) (TO(layer) ^ 0x30)

enum layers {
  L_BASE,
  L_NUM,
  L_PUNC,
  L_BRC,
  L_NAV,
  L_SYS,
  L_FN,
  L_LAYR,
  L_GAME,
};
#define NUM_LAYERS 9

const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    XXXXXXX, LALT_T(KC_Q), LCTL_T(KC_W), LGUI_T(KC_E), LSFT_T(KC_R), KC_T,
                                                  KC_Y, RSFT_T(KC_U), RGUI_T(KC_I), RCTL_T(KC_O), RALT_T(KC_P), XXXXXXX,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    XXXXXXX, LSFT_T(KC_A), KC_S, LT(L_NUM,KC_D), LT(L_PUNC,KC_F), KC_G,
                                                   KC_H, LT(L_BRC,KC_J), LT(L_SYS,KC_K), KC_L, RSFT_T(KC_MINS), XXXXXXX,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    XXXXXXX, LT(L_FN,KC_Z), KC_X, KC_C, KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, XXXXXXX,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                     MO(L_LAYR), KC_TAB, LGUI_T(KC_BSPC),          LSFT_T(KC_SPC), LT(L_NAV,KC_ENT), TO(L_BASE)
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_NUM] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, XXXXXXX,          KC_9,    KC_3,    KC_4,    KC_5,    KC_6,    _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, KC_CALC,          KC_8,    KC_0,    KC_1,    KC_2,    KC_MINS, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_7,    XXXXXXX, KC_SCLN, KC_COLN, KC_SLSH, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, _______, _______
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_PUNC] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, XXXXXXX,          KC_PERC, KC_CIRC, KC_ASTR, KC_HASH, KC_DLR,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,          KC_TILD, KC_EQL,  KC_PLUS, KC_AT,   KC_GRV,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_AMPR, KC_PIPE, KC_QUES, KC_EXLM, KC_BSLS, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, _______, _______
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_BRC] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_LABK, KC_RABK, KC_LPRN, KC_RPRN, XXXXXXX,          XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, _______, _______
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_NAV] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, XXXXXXX,          XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_APP,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, _______, _______
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_SYS] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_PSCR, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,          XXXXXXX, KC_RSFT, KC_RGUI, KC_RCTL, KC_RALT, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, KC_SLEP,          XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, KC_BRID, XXXXXXX, KC_BRIU, KC_PWR,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, _______, _______
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_FN] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, XXXXXXX,          XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, _______, _______
//                            +--------+--------+--------+        +--------+--------+--------+
   ),

  [L_LAYR] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, C_TCTL,  C_TGUI,  KC_CAPS, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, XXXXXXX, TO(L_NUM), TO(L_PUNC), TO(L_GAME),
                                                               XXXXXXX, TO(L_BRC), TO(L_SYS), XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    _______, TO(L_FN), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               _______, _______, _______,          _______, TO(L_NAV), _______
//                            +--------+--------+--------+        +--------+--------+--------+
  ),

  [L_GAME] = LAYOUT_split_3x6_3(
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_TAB,  KC_1,    KC_Q,    KC_W,    KC_E,    KC_R,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_ESC,  KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
    KC_LGUI, KC_LSFT, KC_MINS, KC_C,    KC_LBRC, KC_RBRC,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
// +--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+
                               KC_LALT, KC_LCTL, KC_SPC,           XXXXXXX, XXXXXXX, _______
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
    [L_NUM] = {
      {0x8b, 0x8c, 0x8d},
      {0xab, 0xac, 0xad},
      {0xcb, 0xcc, 0xcd}
    },
    [L_PUNC] = {
      {' ', ' ', ' '},
      {' ', '@', ' '},
      {' ', ' ', ' '}
    },
    [L_BRC] = {
      {'/', ' ', '\\'},
      {'|', ' ', '|'},
      {'\\', ' ', '/'}
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
    [L_FN] = {
      {' ', ' ', ' '},
      {' ', 'F', 'n'},
      {' ', ' ', ' '}
    },
    [L_LAYR] = {
      {' ', ' ', ' '},
      {' ', '=', ' '},
      {' ', ' ', ' '}
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
  if (keycode == C_TCTL || keycode == C_TGUI) {
    return false;
  }
  return true;
}
