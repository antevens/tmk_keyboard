/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "ergodox.h"
#include "i2cmaster.h"
#ifdef DEBUG_MATRIX_FREQ
#include  "timer.h"
#endif

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(uint8_t row);
static void init_cols(void);
static void unselect_rows();
static void select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;

uint8_t led_left            = (1<<2 | 1<<1 | 1<<0);
uint8_t led_right           = (1<<2 | 1<<1 | 1<<0);
uint8_t led_side            = 0;
uint8_t led_counter         = 0;
uint8_t led_counter_max     = 10;

#ifdef DEBUG_MATRIX_FREQ
uint32_t matrix_timer;
uint32_t matrix_scan_count;
#endif

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    // initialize row and col
    init_ergodox();
    mcp23018_status = 1;
    ergodox_blink_all_leds();
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

#ifdef DEBUG_MATRIX_FREQ
    matrix_timer = timer_read32();
    matrix_scan_count = 0;
#endif
}

uint8_t matrix_scan(void)
{
#ifdef DEBUG_MATRIX_FREQ
    matrix_scan_count++;

    uint32_t timer_now = timer_read32();
    if (TIMER_DIFF_32(timer_now, matrix_timer)>1000) {
        phex(led_right);
        print("/");
        phex(led_right<<4);
        print(":");
        phex(led_left);
        print("/");
        phex(led_left<<4);
        print(":");
        pdec(led_counter_max);
        print(", ");

        print("matrix scan frequency: ");
        pdec(matrix_scan_count);
        print("\n");

        matrix_timer = timer_now;
        matrix_scan_count = 0;
    }
#endif

#ifdef KEYMAP_CUB
    if (led_counter == 0) {
        led_counter = led_counter_max;

        if (led_side) {
            led_side = 0;

            DDRB  |=  (1<<7 | 1<<6 | 1<<5 | 1<<4);
            PORTB &= ~(1<<7 | 1<<6 | 1<<5 | 1<<4);
            PORTB |=  (led_left<<4);
        } else {
            led_side = 1;

            DDRB  |=  (1<<7 | 1<<6 | 1<<5 | 1<<4);
            PORTB &= ~(1<<6 | 1<<5 | 1<<4);
            PORTB |=  ((1<<7 | 1<<6 | 1<<5 | 1<<4)^(led_right<<4));
        }
    } else {
        led_counter--;
    }
#endif

#ifdef KEYMAP_CUB1
    // on many registers - ok
    if (led_counter == 0) {
        led_counter = led_counter_max;

        if (led_side) {
            led_side = 0;

            uint32_t led;
            if (led_left & (1<<1)) { led = 1; } else { led = 0; }
            // led D7 - output; high/low output
            DDRD  |=  (1<<7);
            PORTD &= ~(1<<7);
            PORTD |=  (led<<7);

            DDRB  |=  (1<<6 | 1<<5 | 1<<4);
            PORTB &= ~(1<<6 | 1<<5 | 1<<4);
            PORTB |=  (led_left<<4);

            // gnd C7 - output; low output
            DDRC  |=  (1<<7);
            PORTC &= ~(1<<7);
        } else {
            led_side = 1;

            uint32_t led;
            if (led_right & (1<<1)) { led = 1; } else { led = 0; }
            // led D7 - output; low/high output
            DDRD  |=  (1<<7);
            PORTD &= ~(1<<7);
            PORTD |=  ((1^led)<<7);

            DDRB  |=  (1<<6 | 1<<5 | 1<<4);
            PORTB &= ~(1<<6 | 1<<5 | 1<<4);
            PORTB |=  ((1<<6 | 1<<5 | 1<<4)^(led_right<<4));

            // gnd C7 - output; high output
            DDRC  |=  (1<<7);
            PORTC |=  (1<<7);
        }

        _delay_ms(5);
    } else {
        led_counter--;
    }

        // on
        //DDRB |=  (1<<5); PORTB |=  (1<<5);
        //DDRB |=  (1<<6); PORTB |=  (1<<6);
        //DDRB |=  (1<<7); PORTB |=  (1<<7);
        //
        // off
        //DDRB &= ~(1<<5); PORTB &= ~(1<<5);
        //DDRB &= ~(1<<6); PORTB &= ~(1<<6);
        //DDRB &= ~(1<<7); PORTB &= ~(1<<7);
        //

        // D7 - led
        // C7 - Gnd

        //uint32_t led;
        //if (led_left & (1<<0)) {
        //    led = 1;
        //} else {
        //    led = 0;
        //}

        // 1
        // led - output; high/low output
        // DDRD  |=  (1<<7);
        // PORTD &= ~(1<<7);
        // PORTD |=  (led<<7);
        // gnd - output; high output
        // DDRC  |=  (1<<7);
        // PORTC |=  (1<<7);

        // 2
        // led - output; high/low output
        // DDRD  |=  (1<<7);
        // PORTD &= ~(1<<7);
        // PORTD |=  (led<<7);
        // gnd - output; low output
        // DDRC  |=  (1<<7);
        // PORTC &= ~(1<<7);

        // 3
        // led - output; high/low output
        // DDRD  |=  (1<<7);
        // PORTD &= ~(1<<7);
        // PORTD |=  (led<<7);
        // gnd - input; pull-up
        // DDRC  &= ~(1<<7);
        // PORTC |=  (1<<7);

        // 4
        // led - output; high/low output
        // DDRD  |=  (1<<7);
        // PORTD &= ~(1<<7);
        // PORTD |=  (led<<7);
        // gnd - input; normal
        // DDRC  &= ~(1<<7);
        // PORTC &= ~(1<<7);
#endif

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        matrix_row_t cols = read_cols(i);
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 *
 * Teensy
 * col: 0   1   2   3   4   5
 * pin: F0  F1  F4  F5  F6  F7
 *
 * MCP23018
 * col: 0   1   2   3   4   5
 * pin: B5  B4  B3  B2  B1  B0
 */
static void  init_cols(void)
{
    // init on mcp23018
    // not needed, already done as part of init_mcp23018()

    // init on teensy
    // Input with pull-up(DDR:0, PORT:1)
    DDRF  &= ~(1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<1 | 1<<0);
    PORTF |=  (1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<1 | 1<<0);
}

static matrix_row_t read_cols(uint8_t row)
{
    if (row < 7) {
        if (mcp23018_status) { // if there was an error
            return 0;
        } else {
            uint8_t data = 0;
            mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOB);             if (mcp23018_status) goto out;
            mcp23018_status = i2c_start(I2C_ADDR_READ);     if (mcp23018_status) goto out;
            data = i2c_readNak();
            data = ~data;
        out:
            i2c_stop();
            return data;
        }
    } else {
        _delay_us(30);  // without this wait read unstable value.
        // read from teensy
        return
            (PINF&(1<<0) ? 0 : (1<<0)) |
            (PINF&(1<<1) ? 0 : (1<<1)) |
            (PINF&(1<<4) ? 0 : (1<<2)) |
            (PINF&(1<<5) ? 0 : (1<<3)) |
            (PINF&(1<<6) ? 0 : (1<<4)) |
            (PINF&(1<<7) ? 0 : (1<<5)) ;
    }
}

/* Row pin configuration
 *
 * Teensy
 * row: 7   8   9   10  11  12  13
 * pin: B0  B1  B2  B3  D2  D3  C6
 *
 * MCP23018
 * row: 0   1   2   3   4   5   6
 * pin: A0  A1  A2  A3  A4  A5  A6
 */
static void unselect_rows(void)
{
    // unselect on mcp23018
    if (mcp23018_status) { // if there was an error
        // do nothing
    } else {
        // set all rows hi-Z : 1
        mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(GPIOA);             if (mcp23018_status) goto out;
        mcp23018_status = i2c_write( 0xFF
                              & ~(ergodox_left_led_3<<LEFT_LED_3_SHIFT)
                          );                            if (mcp23018_status) goto out;
    out:
        i2c_stop();
    }

    // unselect on teensy
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3);
    PORTB &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3);
    DDRD  &= ~(1<<2 | 1<<3);
    PORTD &= ~(1<<2 | 1<<3);
    DDRC  &= ~(1<<6);
    PORTC &= ~(1<<6);
}

static void select_row(uint8_t row)
{
    if (row < 7) {
        // select on mcp23018
        if (mcp23018_status) { // if there was an error
            // do nothing
        } else {
            // set active row low  : 0
            // set other rows hi-Z : 1
            mcp23018_status = i2c_start(I2C_ADDR_WRITE);        if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOA);                 if (mcp23018_status) goto out;
            mcp23018_status = i2c_write( 0xFF & ~(1<<row)
                                  & ~(ergodox_left_led_3<<LEFT_LED_3_SHIFT)
                              );                                if (mcp23018_status) goto out;
        out:
            i2c_stop();
        }
    } else {
        // select on teensy
        // Output low(DDR:1, PORT:0) to select
        switch (row) {
            case 7:
                DDRB  |= (1<<0);
                PORTB &= ~(1<<0);
                break;
            case 8:
                DDRB  |= (1<<1);
                PORTB &= ~(1<<1);
                break;
            case 9:
                DDRB  |= (1<<2);
                PORTB &= ~(1<<2);
                break;
            case 10:
                DDRB  |= (1<<3);
                PORTB &= ~(1<<3);
                break;
            case 11:
                DDRD  |= (1<<2);
                PORTD &= ~(1<<3);
                break;
            case 12:
                DDRD  |= (1<<3);
                PORTD &= ~(1<<3);
                break;
            case 13:
                DDRC  |= (1<<6);
                PORTC &= ~(1<<6);
                break;
        }
    }
}

