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


Copyright (c) 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>
Released under The MIT License (see "doc/licenses/MIT.md")
Project located at <https://github.com/benblazak/ergodox-firmware>

Most used files are located at
<https://github.com/benblazak/ergodox-firmware/tree/partial-rewrite/firmware/keyboard/ergodox/controller>

*/

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

void init_cx85(void);

#define LED_BRIGHTNESS_LO       31
#define LED_BRIGHTNESS_HI       255

inline void cx85_board_led_on(void)      { DDRD |=  (1<<6); PORTD |=  (1<<6); }

inline void cx85_board_led_off(void)     { DDRD &= ~(1<<6); PORTD &= ~(1<<6); }


inline void cx85_led_all_on(void)
{
    cx85_board_led_on();
}

inline void cx85_led_all_off(void)
{
    cx85_board_led_off();
}

inline void cx85_board_led_set(uint8_t n)    { DDRD = n; }

inline void cx85_led_all_set(uint8_t n)
{
    cx85_board_led_set(n);
}

