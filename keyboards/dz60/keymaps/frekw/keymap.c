
#include QMK_KEYBOARD_H

#define ______ KC_TRNS
#define FN_SPC LT(_FL, KC_SPC)

enum keyboard_layers {
                      _BL = 0, // Base Layer
                      _FL      // Function Layer
                      // _CL      // Control Layer
};

enum custom_keycodes {
                      ALT_AE = SAFE_RANGE,
                      ALT_AU,
                      ALT_OU
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t current_mods = get_mods();
  uint8_t  alternate = get_mods() & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT));
  uint8_t shifted = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));

  switch (keycode) {
  case ALT_AE: {
    if (record->event.pressed) {
      if (alternate) {
        clear_mods();
        SEND_STRING(SS_RALT("u"));
        set_mods(shifted);
        SEND_STRING("a");
        set_mods(current_mods);
      } else {
        register_code(KC_QUOT);
      }
    } else {
      unregister_code(KC_QUOT);
    }

    return true;
  }
  case ALT_AU: {
    if (record->event.pressed) {
      if (alternate) {
        SEND_STRING(SS_RALT("a"));
      } else {
        register_code(KC_LBRC);
      }
    } else {
      unregister_code(KC_LBRC);
    }
    return true;
  }

  case ALT_OU: {
    if (record->event.pressed) {
      if (alternate) {
        clear_mods();
        SEND_STRING(SS_RALT("u"));
        set_mods(shifted);
        SEND_STRING("o");
        set_mods(current_mods);
      } else {
        register_code(KC_SCLN);
      }
    } else {
      unregister_code(KC_SCLN);
    }

    return true;
  }
  }

  return true;
}

  /*
  ,-----------------------------------------------------------------------------------------.
| ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
|-----------------------------------------------------------------------------------------+
| Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
|-----------------------------------------------------------------------------------------+
| Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
|-----------------------------------------------------------------------------------------+
| Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |     Rshift      |
|-----------------------------------------------------------------------------------------+
| Ctrl |  Alt  |  Cmd  |              Space                |  Cmd  | Fun |  Alt  |  Ctrl  |
`-----------------------------------------------------------------------------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BL] = LAYOUT_60_ansi(
		KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    ALT_AU,  KC_RBRC, KC_BSLS,
		KC_ESC,            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    ALT_OU,  ALT_AE,           KC_ENT,
		KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
		KC_LCTL,  KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(_FL),          KC_RALT, KC_RCTL),

	[_FL] = LAYOUT_60_ansi(
		KC_GRAVE, KC_F1,  KC_F2,       KC_F3,     KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,          KC_DEL,
		______,           KC_HOME,     KC_UP,     KC_END,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, ______, RESET,
		______,           KC_LEFT,     KC_DOWN,   KC_RIGHT, ______,  ______,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, ______,  ______,          ______,
		______,           KC__VOLDOWN, KC__VOLUP, KC__MUTE, KC_MPLY, KC_MRWD, KC_MFFD, ______,  ______,  KC_BRMD,  KC_BRMU,                  ______,
		______,    ______, ______,                                   ______,                             ______,  ______,           ______, ______)
};
