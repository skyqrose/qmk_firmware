#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keycode_to_char.h"

const char keycode_chars[0x74] = {
  /* 0x00 */ ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd',
  /* 0x08 */ 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
  /* 0x10 */ 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  /* 0x18 */ 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',
  /* 0x20 */ '3', '4', '5', '6', '7', '8', '9', '0',
  /* 0x28 */ 0xD8, // ent
  /* 0x29 */ 0xD9, // esc
  /* 0x2A */ 0xDB, // bspc
  /* 0x2B */ 0x1A, // tab
  /* 0x2C */ '_' /* space*/, '-', '=', '[',
  /* 0x30 */ ']', '\\', '#', ';', '\'', '`', ',', '.',
  /* 0x38 */ '/',
  /* 0x39 */ 0x9D,  // caps
  /* 0x3a */ 'f', 'f', 'f', 'f', 'f', 'f', // f1-6
  /* 0x40 */ 'f', 'f', 'f', 'f', 'f', 'f', // f7-12
  /* 0x46 */ 0xDE, // printscreen
  /* 0x47 */ 0x9D, // scroll lock
  /* 0x48 */ ' ', ' ', 0x11, 0x1e, // pause, insert, home pgup
  /* 0x4a */ 0xDA, 0x10, 0x1F, 0x1A, // del, end, pgdn, right
  /* 0x50 */ 0x1B, 0x19, 0x18, 0x9D, // left, down, up, numlock
  /* 0x54 */ '/', '*', '-', '+', // keypad
  /* 0x58 */ 0xD8 /* enter */, '1', '2', '3', '4', '5', '6', '7', // keypad
  /* 0x60 */ '8', '9', '0', '.',
  /* 0x64 */ '\\', 0xDF, 0xDC, '=', // nonus bslash, app, power, kp eq
  /* 0x68 */ 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', // f 13-20
  /* 0x70 */ 'F', 'F', 'F', 'F', // f 21-24
};

const char keycode_chars_shifted[0x39] = {
  /* 0x00 */ ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D',
  /* 0x08 */ 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
  /* 0x10 */ 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  /* 0x18 */ 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '@',
  /* 0x20 */ '#', '$', '%', '^', '&', '*', '(', ')',
  /* 0x28 */ 0xD8, // ent
  /* 0x29 */ 0xD9, // esc
  /* 0x2A */ 0xDB, // bspc
  /* 0x2B */ 0x1A, // tab
  /* 0x2C */ '_' , '_', '+', '{',
  /* 0x30 */ '}', '|', '#', ':', '"', '~', '<', '>',
  /* 0x38 */ '?',
};

char upper_keycode_chars(uint16_t keycode) {
  switch (keycode) {
    case KC_PWR : // 0xA5
      return 0xDC;
    case KC_SLEP: // 0xA6
      return 0xDD;
    case KC_MUTE: // 0xA8
      return 0xBB;
    case KC_VOLU: // 0xA9
      return 0xBD;
    case KC_VOLD: // 0xAA
      return 0xBC;
    case KC_MNXT: // 0xAB
      return 0xBA;
    case KC_MPRV: // 0xAC
      return 0xB8;
    case KC_MPLY: // 0xAE
      return 0xB9;
    case KC_MAIL: // 0xB1
      return 0x9E;
    case KC_CALC: // 0xB2
      return 0x9F;
    case KC_BRIU: // 0xBD
      return 0xBF;
    case KC_BRID: // 0xBE
      return 0xBE;
    case KC_LCTL: // 0xE0
      return 0x94;
    case KC_LSFT: // 0xE1
      return 0x95;
    case KC_LALT: // 0xE2
      return 0x96;
    case KC_LGUI: // 0xE3
      return 0x9B; // tux
    case KC_RCTL: // 0xE4
      return 0x94;
    case KC_RSFT: // 0xE5
      return 0x95;
    case KC_RALT: // 0xE6
      return 0x96;
    case KC_RGUI: // 0xE7
      return 0x9B; // tux
    default:
      return ' ';
  }
}

enum layers {
  L_BASE,
  L_LAYR,
  L_NUM,
  L_PUNC,
  L_BRC,
  L_NAV,
  L_SYS,
  L_FN,
  L_GAME,
};
char layer_keycodes(uint8_t layer) {
  switch (layer) {
    case L_BASE:
      return 'A';
    case L_LAYR:
      return '=';
    case L_NUM:
      return '#';
    case L_PUNC:
      return '@';
    case L_BRC:
      return '[';
    case L_NAV:
      return 0x12; // up+down arrows
    case L_SYS:
      return '*';
    case L_FN:
      return 'F';
    case L_GAME:
      return 'G';
    default:
      return '?';
  }
}

char shifted_keycodes(uint16_t keycode) {
  switch (keycode) {
    case KC_TILD: // LSFT(KC_GRV) ~
      return '~';
    case KC_EXLM: // LSFT(KC_1) !
      return '!';
    case KC_AT: // LSFT(KC_2) @
      return '@';
    case KC_HASH: // LSFT(KC_3) #
      return '#';
    case KC_DLR: // LSFT(KC_4) $
      return '$';
    case KC_PERC: // LSFT(KC_5) %
      return '%';
    case KC_CIRC: // LSFT(KC_6) ^
      return '^';
    case KC_AMPR: // LSFT(KC_7) &
      return '&';
    case KC_ASTR: // LSFT(KC_8) *
      return '*';
    case KC_LPRN: // LSFT(KC_9) (
      return '(';
    case KC_RPRN: // LSFT(KC_0) )
      return ')';
    case KC_UNDS: // LSFT(KC_MINS) _
      return '_';
    case KC_PLUS: // LSFT(KC_EQL) +
      return '+';
    case KC_LCBR: // LSFT(KC_LBRC) {
      return '{';
    case KC_RCBR: // LSFT(KC_RBRC) }
      return '}';
    case KC_LABK: // LSFT(KC_COMM) <
      return '<';
    case KC_RABK: // LSFT(KC_DOT) >
      return '>';
    case KC_COLN: // LSFT(KC_SCLN) :
      return ':';
    case KC_PIPE: // LSFT(KC_BSLS) |
      return '|';
    case KC_QUES: // LSFT(KC_SLSH) ?
      return '?';
    case KC_DQT: // LSFT(KC_QUOT) "
      return '"';
    default:
      return ' ';
  }
}

char keycode_to_char(uint16_t keycode) {
  if (keycode >= QK_TO && keycode <= QK_ONE_SHOT_LAYER_MAX) {
    uint8_t layer = keycode & 0xF;
    return layer_keycodes(layer);
  }
  if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
    return shifted_keycodes(keycode);
  }
  bool shift = (get_mods()|get_oneshot_mods()) & MOD_MASK_SHIFT;
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }
  if (shift && keycode < sizeof(keycode_chars_shifted)) {
    return keycode_chars_shifted[keycode];
  }
  if (keycode < sizeof(keycode_chars)) {
    return keycode_chars[keycode];
  }
  return upper_keycode_chars(keycode);
}
