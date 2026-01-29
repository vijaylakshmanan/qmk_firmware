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
//#include "sofle.h"
#include "oled_driver.h"
#include "timer.h"

#include QMK_KEYBOARD_H

enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _BOTH
};

enum planck_keycodes {
  PASS = SAFE_RANGE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define BOTH MO(_BOTH)

// For tracking time
static uint32_t oled_timer = 0;

#define MATRIX_WIDTH 21  // Adjust based on OLED width
#define MATRIX_HEIGHT 8  // Adjust based on OLED height
static char matrix_chars[] = "01ABCDEF";  // You can customize this
static uint8_t matrix_state[MATRIX_WIDTH];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  | ESC  |                    | `/~  |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   Q  |   W  |   E  |   R  |   T  | Home |                    |  End |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  | Tab  |-------.    ,-------| Caps |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  | Del  |-------|    |-------| BkSpc|   N  |   M  |   ,  |   .  |   /  |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            | LCTL | LGUI | Space| Lower| /LALT  /        \ RALT \  | Raise | Enter| Shift| RCTL |
 *            |      |      |      |      |/      /          \      \ |       |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,   KC_ESC,                       KC_GRV,   KC_6,     KC_7,     KC_8,    KC_9,    KC_0,
    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,   KC_HOME,                      KC_END,  KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,
    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,   KC_TAB,                       KC_CAPS,   KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN,
    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_DEL,    KC_MUTE,  KC_MPLY, KC_BSPC,  KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH,
                      KC_LCTL, KC_LGUI,  KC_SPC,  LOWER, KC_LALT,     KC_RALT, RAISE, KC_ENT,  KC_LSFT, KC_RCTL
),

 /*
 * LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |LCA(E)|LCA(R)|LCA(T)|      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |LCA(D)|LCA(F)|LCA(G)|      |-------.    ,-------|      | Left | Down |  Up  | Right|      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Shift|      |LCA(<)|      |LCA(>)|      |-------|    |-------|      |      |      |      |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_LOWER] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,        KC_F4,     KC_F5,         KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,
    _______, _______, LCA(KC_E),    LCA(KC_R), LCA(KC_T),     _______,                      _______, _______, _______, _______,  _______, _______,
    _______, _______, LCA(KC_D),    LCA(KC_F), LCA(KC_G),     _______,                      _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
    KC_LSFT, _______, LCA(KC_LEFT), _______,   LCA(KC_RIGHT), _______,  _______,   _______, _______, _______, _______, _______,  _______, KC_LSFT,
                      _______,      _______,   _______,       _______, _______,    _______, BOTH,    _______,  _______, _______
),

/*
 * RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |  /   | \or| |  {   |  }   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |  [/{ | ]/}  |  (   |  )   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |-------|    |-------|      |  -/_ |  =/+ |   |  |  ./> | '/"" |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______,       _______,       _______,
    _______, _______, _______, _______, _______, _______,                      _______, _______, KC_SLSH, KC_NUBS,       LSFT(KC_LBRC), LSFT(KC_RBRC),
    _______, _______, _______, _______, _______, _______,                      _______, _______, KC_LBRC, KC_RBRC,       LSFT(KC_9),    LSFT(KC_0),
    KC_LSFT, _______, _______, _______, _______, _______,  _______,   _______, _______, KC_MINS, KC_EQL,  LSFT(KC_BSLS), KC_DOT,        KC_QUOT,
                      _______, _______, _______,    BOTH, _______,    _______, _______,  _______,  _______, _______
),

/*
 * BOTH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |  /   | \or| |  {   |  }   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | PASS |      |      |-------.    ,-------|      |      |  [/{ | ]/}  |  (   |  )   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |-------|    |-------|      |  -/_ |  =/+ |   |  |  ./> | '/"" |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_BOTH] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______,  _______, _______,
    _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______,  _______, _______,
    _______, _______, _______,    PASS, _______, _______,                      _______, _______, _______, _______,  _______, _______,
    _______, _______, _______, _______, _______, _______,  _______,   _______, _______, _______, _______, _______,  _______, _______,
                      _______, _______, _______, _______, _______,    _______, _______,  _______,  _______, _______
)

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PASS:
      if (record->event.pressed) {
        SEND_STRING();
      } else {
      }
      break;
  }
  return true;
};

// Render HH:MM clock using internal timer
void show_wpm(void) {
    // static char time_str[6];
    // uint32_t ms = timer_read32() / 1000;
    // uint8_t hour = (ms / 3600) % 24;
    // uint8_t minute = (ms / 60) % 60;

    // snprintf(time_str, sizeof(time_str), "%02d:%02d", hour, minute);
    // oled_clear();
    // oled_write_ln(time_str, false);

  char wpm_str[10];
  snprintf(wpm_str, sizeof(wpm_str), "WPM: %03d", get_current_wpm());
  oled_write_ln(wpm_str, false);

}

// Render Caps Lock + Modifiers
void render_status_keys(void) {
    oled_clear();

    // CAPS LOCK
    if (host_keyboard_led_state().caps_lock) {
        oled_write_ln("CAPS LOCK", false);
    } else {
        oled_write_ln("caps off", false);
    }

    // Modifier keys
    uint8_t mod = get_mods() | get_oneshot_mods();
    oled_write_ln("", false); // Spacer

    if (mod & MOD_MASK_SHIFT) oled_write_ln("SHIFT", false);
    if (mod & MOD_MASK_CTRL)  oled_write_ln("CTRL", false);
    if (mod & MOD_MASK_ALT)   oled_write_ln("ALT", false);
    if (mod & MOD_MASK_GUI)   oled_write_ln("GUI", false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_270;
    }
}

void init_matrix_animation(void) {
    for (int i = 0; i < MATRIX_WIDTH; i++) {
        matrix_state[i] = rand() % MATRIX_HEIGHT;
    }
}

void render_matrix(void) {
    oled_clear();
    for (int x = 0; x < MATRIX_WIDTH; x++) {
        for (int y = 0; y < MATRIX_HEIGHT; y++) {
            if (y == matrix_state[x]) {
                char c = matrix_chars[rand() % (sizeof(matrix_chars) - 1)];
                oled_set_cursor(x, y);
                oled_write_char(c, false);
            }
        }
        matrix_state[x] = (matrix_state[x] + 1) % MATRIX_HEIGHT;
    }
}

// Update timeout
bool oled_task_user(void) {
    // Refresh OLED timeout
    oled_timer = timer_read32();

    // LEFT HALF
    if (is_keyboard_master()) {
        show_wpm();
    } else {
        show_wpm();
    }
    return false;
}

void keyboard_post_init_user(void) {
    srand(timer_read());  // Seed random for Matrix
    init_matrix_animation();
}