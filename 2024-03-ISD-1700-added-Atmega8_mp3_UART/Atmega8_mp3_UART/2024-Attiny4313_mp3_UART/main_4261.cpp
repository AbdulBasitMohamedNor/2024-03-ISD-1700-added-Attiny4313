//#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "DiYplayer_functions1.h"
#include "UART.h"
//#include "mcp413.h"
//#include "MCP4261.h"
//#include "mcp4013.h"
//#include "MCP40xx.h"

//PIN connections:
//ATTINY2313	MCP4261
//VCC		    Vdd
//PB7(USCK)	    SCK
//PB6(MISO/DO)	SDI
//PB5(MOSI/DI)	SDO
//PB4(OC1B)	    CS
//GND		    Vss

 
 #define VOL_WIPER_1_WRITE 0x10
 #define VOL_WIPER_1_READ  0x1C
 #define VOL_WIPER_1_INC   0x14
 #define VOL_WIPER_1_DEC   0x18
 #define NV_WIPER_0_WRITE 0x20
 #define NV_WIPER_0_READ  0x2C
 #define NV_WIPER_0_INC   0x24
 #define NV_WIPER_0_DEC   0x28

#ifndef F_CPU
#define F_CPU 8000000UL //#define F_CPU 1000000UL
#endif

#define USCK PINB7
#define DO PINB6
#define DI PINB5
#define SS PINB4

void spi_init(void)
{
	PORTB |= (1<<DO)|(1<<SS);       // pull-up i.e. disabled
	DDRB = (1<<USCK)|(1<<DI)|(1<<SS);
	USICR = (1<<USIWM0)|(1<<USICS1)|(1<<USICLK);
}

void select_CS(char on)
{
	if (on)
	PORTB &= ~(1<<SS);    // enable Slave
	else
	PORTB |= (1<<SS);     // disable slave
}

unsigned char spi(unsigned char val)
{
	USIDR = val;
	USISR = (1<<USIOIF);      // clear any pending
	do {
		USICR = (1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC);
	} while ((USISR & (1<<USIOIF)) == 0);
	return USIDR;
}


void delay_ms(uint8_t ms) {
	uint16_t delay_count = F_CPU / 17500;
	volatile uint16_t i;

	while (ms != 0) {
		for (i=0; i != delay_count; i++);
		ms--;
	}
}

void mcp_write(uint8_t potaddr,uint8_t datlo)
{
	uint8_t dathi;
	dathi=0x0;

	select_CS(1);
	spi(potaddr | dathi);
	spi(datlo);
	select_CS(0);
}

int main(void)
{
	unsigned char j,i,gotByte,pot;
	spi_init();

	while (1) {
		for (i=0;i<256;i++)
		//i=50;//a constant works fine. ex: 50->~1kohms
		{
			gotByte=(unsigned char)i;
			
			mcp_write(NV_WIPER_0_WRITE,gotByte);
			delay_ms(1000);
		}
		for (j=0;j>256;j--)
		//i=50;//a constant works fine. ex: 50->~1kohms
		{
			gotByte=(unsigned char)j;
			
			mcp_write(NV_WIPER_0_WRITE,gotByte);
			delay_ms(1000);
		}
	}
	return 0;
}