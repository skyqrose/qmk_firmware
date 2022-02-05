#include QMK_KEYBOARD_H

enum layers {
    L_NORM,
    L_BASE,
    L_NUM,
    L_SYS,
};

#ifdef KEY_OVERRIDE_ENABLE
#define norm_layer_mask (1 << L_NORM)
#define custom_layer_mask ((1 << L_BASE) | (1 << L_NUM) | (1 << L_SYS))
const key_override_t norm_bspc_del = ko_make_with_layers(MOD_MASK_SHIFT, KC_BSPC, KC_DEL, norm_layer_mask);
const key_override_t custom_del = ko_make_with_layers(MOD_MASK_SHIFT, LCMD_T(KC_SPC), KC_DEL, custom_layer_mask);
const key_override_t comm_scln = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, KC_SCLN, custom_layer_mask);
const key_override_t dot_cln = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT, KC_COLN, custom_layer_mask);
const key_override_t **key_overrides = (const key_override_t *[]){
  &norm_bspc_del,
  &custom_del,
  &comm_scln,
  &dot_cln,
  NULL
};
#endif // KEY_OVERRIDE_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_NORM] = LAYOUT_ortho_5x12(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  TO(L_BASE), TO(L_NORM), KC_LALT, KC_LCTL, KC_LGUI, KC_SPC,
                                                        KC_SPC,  KC_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  [L_BASE] = LAYOUT_ortho_5x12(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    XXXXXXX,
  LT(L_NUM, KC_ESC),
           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, LT(L_NUM, KC_MINS),
  KC_ENT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  _______, _______, _______, KC_LALT, KC_LCTL, LSFT_T(KC_BSPC),
                                               LCMD_T(KC_SPC), MO(L_SYS), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [L_NUM] = LAYOUT_ortho_5x12(
  _______, XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX, XXXXXXX,
  _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PERC, KC_DLR,  KC_4,    KC_5,    KC_6,    KC_ASTR, KC_PLUS,
  _______, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, KC_HASH, KC_CIRC, KC_1,    KC_2,    KC_3,    KC_GRV,  KC_EQL,
  _______, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, KC_TILD, KC_0,    _______, _______, _______, KC_AMPR,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [L_SYS] = LAYOUT_ortho_5x12(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
  _______, KC_CAPS, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, _______, _______, _______, _______, _______, LCMD_T(KC_DEL), _______, _______, _______, _______, _______
  )

};
