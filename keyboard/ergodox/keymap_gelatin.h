static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Keymap: Layer 0 with Gelatin keyboard layout
     * Note that this layout requires a custom OS keyboard map to work correctly.
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  +L1   | 1 !¡ |  2 @ | 3 #  | 4 $ §| 5 % ˝|˘ ̑ ˚ |           |˘ ̑ · | 6 ^ ̏| 7 &  | 8 *  | 9 +  | 0 =  |   L0   |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  Tab   |   Q  |   W  |   F  |   P  |   G  | ˆ ˇ  |           | | ?  |   J  |   L  |   U  | Y ¥  |' " ~ |  Esc   |
     * |--------+------+------+------+------+------|  *   |           | ¿ ¦  |------+------+------+------+------+--------|
     * | ´` ¨   |   N  |  R ® | S ẞ  |  T Þ | D Ð  |------|           |------|   H  |  A Æ | E €  |I ı İ |  O Œ | - _ ¯  |
     * |--------+------+------+------+------+------| RAlt |           | RAlt |------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |C © ¢ |   V  |   B  |      |           |      |   K  |  M ™ |  ,;¸ |  .:˛ | / \ /| RShift |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | LCtrl| LGui | LAlt |  <(  |  {[  |                                       |  ]}  |  )>  | LAlt | RGui | RCtrl|
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | ~L1  | ~L2  |       | ~L2  | ~L1  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | PgUp |       | Home |      |      |
     *                                 | BkSp | Del  |------|       |------| Enter| Space|
     *                                 |      |      | PgDn |       | End  |      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(  // layer 0 : default
        // left hand
        FN1,            1,      2,      3,      4,        5,   NONUS_HASH,
        TAB,            Q,      W,      F,      P,        G,   GRAVE,
        NONUS_BSLASH,   N,      R,      S,      T,        D,
        LSFT,           Z,      X,      C,      V,        B,   RALT,
        LCTL,           LGUI,   LALT,   SCOLON, LBRACKET,
                                                FN1,     FN1,
                                                          PGUP,
                                        BSPC,   DEL,      PGDN,
        // right hand
        INT1,   6,      7,         8,      9,      0,      FN0,
        SLASH,  J,      L,         U,      Y,      QUOT,   ESC,
                H,      A,         E,      I,      O,      MINUS,
        RALT,   K,      M,         COMM,   DOT,    BSLASH, RSFT,
                        RBRACKET,  EQUAL,  LALT,   RGUI,   RCTL,
            FN1,       FN1,
            HOME,
            END,        ENT,       SPC
    ),     
    /* 
     * Keymap: Layer 0 USB Key Usage IDs (HEX)
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  +L1   | 0x1E | 0x1F | 0x20 | 0x21 | 0x22 | 0x32 |           | 0x87 | 0x23 | 0x24 | 0x25 | 0x26 | 0x27 |   L0   |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  0x2B  | 0x14 | 0x1A | 0x09 | 0x13 | 0x0A | 0x35 |           | 0x38 | 0x0D | 0x0F | 0x18 | 0x1C | 0x34 |  0x29  |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |  0x64  | 0x11 | 0x15 | 0x16 | 0x17 | 0x07 |------|           |------| 0x0B | 0x04 | 0x08 | 0x0C | 0x12 |  0x2D  |
     * |--------+------+------+------+------+------| 0xE6 |           | 0xE6 |------+------+------+------+------+--------|
     * |  0xE1  | 0x1D | 0x1B | 0x06 | 0x19 | 0x05 |      |           |      | 0x0E | 0x10 | 0x36 | 0x37 | 0x31 |  0xE5  |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | 0xE0 | 0x08 | 0xE2 | 0x33 | 0x2F |                                       | 0x30 | 0x2E | 0xE2 | 0xE7 | 0xE4 |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | ~L1  | ~L2  |       | ~L2  | ~L1  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | 0x4B |       | 0x4A |      |      |
     *                                 | 0x2A | 0x4C |------|       |------| 0x28 | 0x2C |
     *                                 |      |      | 0x4E |       | 0x4D |      |      |
     *                                 `--------------------'       `--------------------'
     *
     * Keymap: Layer 1
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  +L2   |  F1  |  F2  |  F3  |  F4  |  F5  |˘ ̑ ˚ |           |˘ ̑ · | PrtSc| NumLk|   /  |   *  |   -  |   L0   |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  Tab   |      | PgUp |  Up  | Vol+ |      | ˆ ˇ  |           |  / \ | ScrLk|   7  |   8  |   9  |  +   |        |
     * |--------+------+------+------+------+------|  *   |           |   /  |------+------+------+------+------+--------|
     * | ´` ¨   | Home | Left | Down |Right | End  |------|           |------| Pause|   4  |   5  |   6  |  =   |        |
     * |--------+------+------+------+------+------| RAlt |           | RAlt |------+------+------+------+------+--------|
     * | CapsLk |      | PgDn | Mute | Vol- |      |      |           |      |      |   1  |   2  |   3  | Enter| CapsLk |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | LCtrl| LGui | LAlt |  <(  |  {[  |                                       |   0  |  Del |  Crl |CjrEnt|      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | ~L1  | ~L2  |       | ~L2  | ~L1  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | PgUp |       | Home |      |      |
     *                                 | BkSp | Del  |------|       |------| Enter| Space|
     *                                 |      |      | PgDn |       | End  |      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(  // layer 1 : function and symbol keys
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F11,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN4,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             F12, F6,  F7,  F8,  F9,  F10, TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    KEYMAP(  // Layer3: default, leftled:none
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

