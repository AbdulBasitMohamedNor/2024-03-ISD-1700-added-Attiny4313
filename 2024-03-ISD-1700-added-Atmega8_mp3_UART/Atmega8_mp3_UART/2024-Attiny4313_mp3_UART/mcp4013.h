/*
 * TWI 4-digit 7-segment display
 * (C) 2011 Akafugu
 *
 * This program is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 */

#ifndef MCP4013_h
#define MCP4013_h

#include <avr/io.h>

#define CS_DDR  DDRD
#define CS_PORT PORTD
#define CS_BIT  PIND6

#define U_D_DDR  DDRB
#define U_D_PORT PORTB
#define U_D_BIT  PINB0

void mcp4013_init(void);
void mcp4013_init_low(void);
void mcp4013_init_high(void);
void mcp4013_inc(void);
void mcp4013_dec(void);
void mcp4013_set(uint8_t);

#endif // MCP4013_h