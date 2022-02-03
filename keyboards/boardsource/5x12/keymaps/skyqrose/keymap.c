#include QMK_KEYBOARD_H

enum layers {
    L_STANDARD,
    L_BASE,
    L_NUMPUNC,
    L_SYS,
};

#ifdef KEY_OVERRIDE_ENABLE
#define colon_layer_mask ((1 << L_BASE) | (1 << L_NUMPUNC))
const key_override_t comm_scln = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, KC_SCLN, colon_layer_mask);
const key_override_t dot_cln = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT, KC_COLN, colon_layer_mask);
const key_override_t **key_overrides = (const key_override_t *[]){
  &comm_scln,
  &dot_cln,
  NULL
};
#endif // KEY_OVERRIDE_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_STANDARD] = LAYOUT_ortho_5x12(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  TO(L_BASE), TO(L_STANDARD), KC_LALT, KC_LCTL, KC_LGUI, KC_SPC,
  KC_SPC,  KC_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  [L_BASE] = LAYOUT_ortho_5x12(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_GRV,  XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_TAB,  XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,LSFT(KC_TAB),XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
  TO(L_BASE), TO(L_STANDARD), KC_LALT, LSFT_T(KC_ESC), LCTL_T(KC_SPC), LCMD_T(KC_ENT),
  MO(L_SYS), LT(L_NUMPUNC, KC_SPC), RSFT_T(KC_BSPC), KC_DEL, XXXXXXX, XXXXXXX
  ),

  [L_NUMPUNC] = LAYOUT_ortho_5x12(
  XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX,
  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PERC, _______, XXXXXXX, KC_AMPR, KC_4,    KC_5,    KC_6,    KC_UNDS,
  KC_GRV,  KC_TILD, KC_LPRN, KC_RPRN, KC_EQL,  _______, XXXXXXX, KC_PIPE, KC_1,    KC_2,    KC_3,    KC_MINS,
  KC_BSLS, XXXXXXX, KC_LBRC, KC_RBRC, KC_PLUS, _______, XXXXXXX, XXXXXXX, KC_0,    _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [L_SYS] = LAYOUT_ortho_5x12(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_CIRC, KC_ASTR, KC_HASH, KC_DLR,
  KC_CAPS, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )

};
