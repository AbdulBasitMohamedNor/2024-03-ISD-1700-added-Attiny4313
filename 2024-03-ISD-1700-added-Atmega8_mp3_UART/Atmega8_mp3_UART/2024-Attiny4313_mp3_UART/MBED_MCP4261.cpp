#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
  
#include "MBED_MCP4261.h"

//=============================================================================
// Public functions
//=============================================================================


 #define SS PINB4
 char _command_byte;
int read(char address)
{
	_read( address);
}


void write(char address, int data)
{
	_write(address,  data);
}

void inc(bool number)
{
	if(number == '0')
	{
		_make_command_byte(CB_INCR, VW0_ADDR, 0);
		PORTB &= ~(1<<SS);    // enable 
		_spi_write(_command_byte);
		PORTB |= (1<<SS);     // disable
	}
	else
	{
		_make_command_byte(CB_INCR, VW1_ADDR, 0);
		PORTB &= ~(1<<SS);    // enable 
		_spi_write(_command_byte);
		PORTB |= (1<<SS);     // disable
	}
}

void dec(bool number)
{
	if(number == '0')
	{
		_make_command_byte(CB_DECR, VW0_ADDR, 0);
		PORTB &= ~(1<<SS);    // enable 
		_spi_write(_command_byte);
		PORTB |= (1<<SS);     // disable
	}
	else
	{
		_make_command_byte(CB_DECR, VW1_ADDR, 0);
		PORTB &= ~(1<<SS);    // enable 
		_spi_write(_command_byte);
		PORTB |= (1<<SS);     // disable
	}
}


int status()
{
	_read(STATUS_ADDR);
}


int tcon()
{
	_read(TCON_ADDR);
}


void tcon(int data)
{
	_write(TCON_ADDR,  data);
}


int wiper(bool number)
{
	if(number == '0')
	{
		_read(VW0_ADDR);
	}
	else
	{
		_read(VW1_ADDR);
	}
}


void wiper(bool number, int data)
{
	if(number == '0')
	{
		_write(VW0_ADDR,  data);
	}
	else
	{
		_write(VW1_ADDR,  data);
	}
}


int nvwiper(bool number)
{
	if(number == '0')
	{
		_read(NVW0_ADDR);
	}
	else
	{
		_read(NVW1_ADDR);
	}
}


void nvwiper(bool number, int data)
{
	if(number == '0')
	{
		_write(NVW0_ADDR, data);
	}
	else
	{
		_write(NVW1_ADDR, data);
	}
}

/*
void shdn(bool act)
{
	_nSHDN = ~act;
}


void wp(bool act)
{
	_nWP = ~act;
}
	*/
//=============================================================================
// Private functions
//=============================================================================

char _make_command_byte(int com, char address, int data)
{
	if(data > 0xff && data < 0x3FF)
	{
		_command_byte = address << 4;                   // add address to _commad_byte
		_command_byte = _command_byte | (data >> 8);    // add data to _commad_byte
		_command_byte = _command_byte | (com << 2);     // add com to _commad_byte
	}
	else
	{
		_command_byte = address << 4;                   // add address to _commad_byte
		_command_byte = _command_byte | (com << 2);     // add com to _commad_byte
	}
}

int _read(char address)
{
	int _response_msb;
	int _response_lsb;
	int _response;
	
	_response = 0;                                      // clear _response for old data
	_response_msb = 0;                                  // clear _response_msb for old data
	_response_lsb = 0;                                  // clear _response_lsb for old data
	
	_make_command_byte(CB_READ, address, 0);
	
	PORTB &= ~(1<<SS);    // enable 
	_spi_write(_command_byte);
	_spi_write(0xff);                                    // not important bit of the 16 bits
	//_response_msb = _spi_write();                        // get response
	//_response_lsb = _spi_write();                        // get response
	PORTB |= (1<<SS);     // disable
	
	_response = _response_msb << 8;
	_response = _response | _response_lsb;
	
	return _response;
}

void _write(char address, int data)
{
	_make_command_byte(CB_WRITE, address, data);
	int _send_data = data & 0xff;
	_command_byte = _command_byte | (data >> 8); 
	PORTB &= ~(1<<SS);    // enable 
	_spi_write(_command_byte);
	_spi_write(_send_data);
	PORTB |= (1<<SS);     // disable
}

unsigned char _spi_write(unsigned char val)
{
	USIDR = val;
	USISR = (1<<USIOIF);      // clear any pending
	do {
		USICR = (1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC);
	} while ((USISR & (1<<USIOIF)) == 0);
	return USIDR;
}