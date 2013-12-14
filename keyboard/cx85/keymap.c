/*
Copyright 2013 Jarl Stefansson <jarl.stefansson@gmail.com>

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
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "keycode.h"
#include "action.h"
#include "action_code.h"
#include "action_macro.h"
#include "bootloader.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "cx85.h"

/* CX85 Physical Layout
* ,------------------------.
* |Esc || 7 |  8 |  9 || - |
* |------------------------|
* |No  || 4 |  5 |  6 || E+|
* |--------------------- N |
* |Del || 1 |  2 |  3 || T |
* |--------------------- E |
* |Yes ||    0   |  . || R |
* `------------------------'
* The physical to logical mapping of the CX85 is  strange
* The left most colum maps as a bottom row
* The ESC key is in a row of it's own and is the first row
*
* CX85 Logical Matrix Layout
* ---------------------.
* ESC  n/a n/a n/a     |
* NO   7   8   9       |
* DEL  4   5   6       |
* YES  1   2   3       |
* 0    .   -   +Enter  |
*----------------------'
*/

/* Atari CX85 keymap */
#define KEYMAP(                                                 \
    k00, k11,k12,k13,   k43,                                    \
    k10, k21,k22,k23,   k42,                                    \
    k20, k31,k32,k33,                                           \
    k30,   k40,  k41                                            \
   )                                                            \
   {                                                            \
    { KC_##k00, KC_NO,    KC_NO,    KC_NO   },                  \
    { KC_##k10, KC_##k11, KC_##k12, KC_##k13},                  \
    { KC_##k20, KC_##k21, KC_##k22, KC_##k23},                  \
    { KC_##k30, KC_##k31, KC_##k32, KC_##k33},                  \
    { KC_##k40, KC_##k41, KC_##k42, KC_##k43}                   \
   }

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Layer 0
    KEYMAP(ESC,  P7, P8,  P9,  PMNS, \
           TAB,  P4, P5,  P6,  PENT, \
           BSPC, P1, P2,  P3,        \
           FN1,  P0, PDOT
    ),
    // Layer 1
    KEYMAP(TRNS, FN7,  FN8,  FN9,  PMNS, \
           TRNS, FN4,  FN5,  FN6,  PENT, \
           TRNS, FN1,  FN2,  FN3,        \
           FN1,  FN0,  PDOT
    ),
    // Layer2
    KEYMAP(FN4,  P7,    UP,   P9,    VOLD, \
           FN2,  LEFT,  P5,   RIGHT, VOLU, \
           FN3,  P1,    DOWN, P3,          \
           ESC,  P0,    PDOT
    ),
    // Layer 3 - FreeCiv
    KEYMAP(FN4,  P7,  P8,  P9,  PMNS, \
           FN2,  P4,  P5,  P6,  FN6,  \
           FN3,  P1,  P2,  P3,        \
           ESC,  P0,  PDOT
    ),
};

/* IDs for user defined functions */
enum function_id {
    TEENSY_KEY,
};

/* IDs for macros */
enum macro_id {
    PUB_KEY,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(TEENSY_KEY),                    // FN0 - Teensy key
    ACTION_LAYER_MOMENTARY(1),                      // FN1 - switch to Layer1
    ACTION_LAYER_SET(2, ON_PRESS),                  // FN2 - push Layer2
    ACTION_LAYER_SET(3, ON_PRESS),                  // FN3 - push Layer3
    ACTION_LAYER_SET(0, ON_PRESS),                  // FN4 - push Layer0
    ACTION_MODS_KEY(MOD_LSFT, KC_ENT),              // FN5 - Shift + Enter, FreeCiv
    ACTION_MACRO(PUB_KEY)                           // FN6 - Macro, type SSH pub key
};

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    tap_t tap = record->tap;

    switch (id) {
        case PUB_KEY:
            return (event.pressed ?
                    MACRO( I(0), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}


void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}

#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    if (layer < KEYMAPS_SIZE) {
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
    } else {
        // fall back to layer 0
        return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
    }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}
