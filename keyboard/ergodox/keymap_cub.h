static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Keymap: Default Layer in QWERTY
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   ~    |   1  |   2  |   3  |   4  |   5  |   \  |           |   -  |   6  |   7  |   8  |   9  |   0  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  | ~L5  |           | ~L6  |   Y  |   U  |   I  |   O  |   P  |   [    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab/Shf|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------|  L0  |           | ~L7  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |   ]    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L5  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L6  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | +L2  | Home |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  End |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     */

    KEYMAP(  // Layer0: default, leftled:none
        // left hand
        NO,  NO,  NO,  NO,  NO,  NO,  NO,
        NO,  NO,  NO,  NO,  NO,  NO,  NO,
        NO,  NO,  NO,  NO,  NO,  NO,
        NO,  NO,  NO,  NO,  NO,  NO,  NO,
        NO,  NO,  NO,  NO,  NO,
                                      NO,  NO,
                                           NO,
                                 NO,  NO,  NO,
        // right hand
             NO,  NO,  NO,  NO,  FN1, FN2, FN3,
             NO,  NO,  NO,  NO,  FN4, FN5, FN6,
                  NO,  NO,  NO,  FN7, FN8, FN9,
             NO,  NO,  NO,  NO,  NO,  NO,  NO,
                       NO,  NO,  NO,  NO,  NO,
        NO,  NO,
        NO,
        NO,  NO,  NO
    ),
};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
    LED_L1_KEY,
    LED_L2_KEY,
    LED_L3_KEY,
    LED_R1_KEY,
    LED_R2_KEY,
    LED_R3_KEY,
    LED_CZ_KEY,
    LED_CP_KEY,
    LED_CM_KEY,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(TEENSY_KEY),                    // FN0  - Teensy key
    ACTION_FUNCTION(LED_L1_KEY),                    // FN1
    ACTION_FUNCTION(LED_L2_KEY),                    // FN2
    ACTION_FUNCTION(LED_L3_KEY),                    // FN3
    ACTION_FUNCTION(LED_R1_KEY),                    // FN4
    ACTION_FUNCTION(LED_R2_KEY),                    // FN5
    ACTION_FUNCTION(LED_R3_KEY),                    // FN6
    ACTION_FUNCTION(LED_CZ_KEY),                    // FN7
    ACTION_FUNCTION(LED_CP_KEY),                    // FN8
    ACTION_FUNCTION(LED_CM_KEY),                    // FN9
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    switch (id) {
        case TEENSY_KEY:
            clear_keyboard();
            print("\n\nJump to bootloader... ");
            _delay_ms(250);
            bootloader_jump(); // should not return
            print("not supported.\n");
            break;

        case LED_L1_KEY: if (event->event.pressed) led_left  ^= (1<<0); break;
        case LED_L2_KEY: if (event->event.pressed) led_left  ^= (1<<1); break;
        case LED_L3_KEY: if (event->event.pressed) led_left  ^= (1<<2); break;
        case LED_R1_KEY: if (event->event.pressed) led_right ^= (1<<0); break;
        case LED_R2_KEY: if (event->event.pressed) led_right ^= (1<<1); break;
        case LED_R3_KEY: if (event->event.pressed) led_right ^= (1<<2); break;
        case LED_CZ_KEY: if (event->event.pressed) led_counter_max = 10; break;
        case LED_CP_KEY: if (event->event.pressed) led_counter_max += 3; break;
        case LED_CM_KEY: if (event->event.pressed) led_counter_max -= 3; break;
    }
}

