#include QMK_KEYBOARD_H

//extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

//#define KC_ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     KC_1,KC_2,KC_3,KC_4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSFT, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL, Z  , X  , C  , V  , B  ,HOME,     END , N  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       ADJT,LOWR, SPC,         SCET,RASE, ENT
  //                  `----+----+----'        `----+----+----'
  ),

	[_QWERTY] = LAYOUT(
KC_1, KC_2, KC_3, KC_4, KC_5, KC_ESC, KC_PGUP, KC_6, KC_7, KC_8, KC_9, KC_0,
KC_Q, KC_W, KC_E, KC_R, KC_T, KC_CAPS, KC_PGDN, KC_Y, KC_U, KC_I, KC_O, KC_P,
KC_A, KC_S, KC_D, LT(_LOWER, KC_F), KC_G, KC_HOME, KC_END, KC_H, KC_J, KC_K, KC_L, KC_SCLN,
KC_Z, KC_X, KC_C, KC_V, KC_B, KC_DEL, KC_UNDO, KC_AGIN, KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
KC_LALT, KC_SPC, KC_LSFT, KC_LCTL, KC_SPC, KC_ENT),
	[_LOWER] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_VOLU, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_VOLD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[_RAISE] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SLSH, KC_BSLS, KC_LCBR, KC_RCBR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO)
};
