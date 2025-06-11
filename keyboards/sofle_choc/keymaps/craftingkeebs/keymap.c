/* Copyright 2023 Brian Low
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum sofle_layers {
  _QWERTY,
  _LOWER,
  _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  | ESC  |                    | `/~  |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   Q  |   W  |   E  |   R  |   T  | Tab  |                    |      |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  | Home |-------.    ,-------|  End |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  | Del  |-------|    |-------| BkSpc|   N  |   M  |   ,  |   .  |   /  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LGUI | Space| LALT | /Enter  /       \Space \  | RALT | Enter| RGUI | RCTL |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,   KC_ESC,                       KC_GRV,   KC_6,     KC_7,     KC_8,    KC_9,    KC_0,
    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,   KC_TAB,                       _______,  KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,
    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,  KC_HOME,                       KC_END,   KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN,
    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_DEL,    KC_MUTE,   KC_MPLY,KC_BSPC,  KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH,
                      KC_LCTL, KC_LGUI,  KC_SPC,  KC_LALT, KC_ENT,    KC_SPC, KC_RALT,  KC_ENT,  KC_RGUI, KC_RCTL
)


// [_LOWER] = LAYOUT(

// )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
};
#endif
