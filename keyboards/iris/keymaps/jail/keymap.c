#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

#define KC_       KC_TRNS
#define KC_LOWR   LT(_LOWER, KC_F)  // LOWER
#define KC_RISE   LT(_RAISE, KC_LSFT)  // RAISE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
      1  , 2  , 3  , 4  , 5  ,ESC,                PGUP, 6  , 7  , 8  , 9  , 0  ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      Q  , W  , E  , R  , T  ,CAPS,               PGDN, Y  , U  , I  , O  , P  ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      A  , S  , D  ,LOWR, G  ,HOME                END,  H  , J  , K  , L  ,SCLN,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
      Z  , X  , C  , V  , B  ,DEL, UNDO      AGIN,BKSPC, N  , M  ,COMM,DOT,SLSH
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT, SPC,RISE,        LCTL,SPC, ENT
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
      F1 , F2 , F3 , F4 , F5 , F6 ,                F7 , F8 , F9 ,F10 , F11, F12,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      NO , NO , NO , NO , NO , NO ,                NO , NO , NO , NO , NO , NO ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      NO , NO , NO ,TRNS, NO , NO ,               VOLU,LEFT,DOWN, UP ,RGTH, NO ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
      NO , NO , NO , NO , NO , NO ,TRNS,      NO ,VOLD, NO , NO , NO , NO , NO ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                        NO , NO , NO ,         NO  , NO , NO
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
      NO , NO , NO , NO , NO , NO ,                NO , NO , NO , NO , NO , NO ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      NO , NO , NO , NO , NO , NO ,                NO , NO ,SLSH,BSLS,LCBR,RCBR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      NO , NO , NO , NO , NO , NO ,                NO , NO ,LBRC,RBRC,LPRN,RPRN,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
      NO , NO , NO , NO , NO , NO , NO ,      NO , NO ,MINS,EQL ,PIPE, NO , NO ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                        NO , NO ,TRNS ,         NO , NO , NO
  //                  `----+----+----'        `----+----+----'
  )
};
