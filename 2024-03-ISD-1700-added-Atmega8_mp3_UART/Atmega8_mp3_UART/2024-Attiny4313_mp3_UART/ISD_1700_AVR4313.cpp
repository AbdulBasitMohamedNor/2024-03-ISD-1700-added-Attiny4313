/*
 * ISD_1700_AVR4313.cpp
 *
 * Created: 2024-02-26 23:04:24
 *  Author: abuam
 */ 



#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include "ISD_1700_AVR4313.h"
#include <inttypes.h>



void setup()
{
	DDRB|=(1<<PINB7)|(1<<PINB5)|(1<<PINB0);
	PORTB|=(1<<PINB6)|(1<<PINB0); //pull high

	DDRB&=~(1<<PINB6)|(1<<PINB1);//inputs/
	PORTB|=(1<<PINB6)|(1<<PINB1);//pull up

	DDRD&=~(1<<PIND0)|(1<<PIND1)|(1<<PIND2)|(1<<PIND3)|(1<<PIND4)|(1<<PIND5)|(1<<PIND6);//input PIND3-PIND5 are PCINT13 PCINT14  PCINT15 interrupt pins
	PORTD|=(1<<PIND0)|(1<<PIND1)|(1<<PIND2)|(1<<PIND3)|(1<<PIND4)|(1<<PIND5)|(1<<PIND6);//pull up
	
		DDRB |= (1 << PINB4); //LED pwm output
		PORTB &= ~(1 << PINB4); //off

		DDRB |= (1 << PINB7); //Transistor output
		PORTB &= ~(1 << PINB7); //off

		DDRB &= ~(1 << PINB2) | (1 << PINB3); //tilt input pin och MAGNET PIN:
		PORTB |= (1 << PINB2) | (1 << PINB3);

		//buttons interrupt inputs
		DDRB &= ~(1 << PINB5) | (1 << PINB6); //input
		PORTB |= (1 << PINB5) | (1 << PINB6);
	


    
}



uint8_t  send_1720( uint8_t data)
{
	uint16_t i;
	SCK_1720_1;
	SS_1720_0;
	_delay_ms(5);
	for(i=8; i>0; i--)
	{
		SCK_1720_0;
		if((data&0x01)==1)
		{
			MO_1720_1;

		}
		else
		{
			MO_1720_0;
		}
		data=data>>1;

		if(PINB6)
		{
			data=data|0x80;
		}
		SCK_1720_1;
		
		_delay_ms(3);
		
	}
	
	MO_1720_0;
	// return(data);
}

void send_com(uchar com)
{
	SS_1720_0;
	send_1720(com);
	send_1720(0x00);
	SS_1720_1;

}

void stop(uchar start_address)
{
	send_com(PU);
	_delay_ms(5);
	SS_1720_0;                     //
	send_1720(0x02);               // 0x90
	send_1720(0x00);               //0x00)
	send_1720(start_address);      //    S7~S0)
	send_1720(0x00);               //  00000 s10~s8)

	SS_1720_1;
	_delay_ms(5);
	MO_1720_0;
	_delay_ms(5);
	MI_1720_0;

}

void set_play(uint16_t startAddr, uint16_t endAddr)
{
	uint8_t data[2] = {0xFF,0xFF};


	send_com(PU);
	_delay_ms(5);
	SS_1720_0;
	data[0] = send_1720(0x80);
	data[1] = send_1720(0);
	data[0] = send_1720( (uint8_t)(startAddr & 0xFF) );
	data[1] = send_1720( (uint8_t)(startAddr>>8) );
	data[0] = send_1720( (uint8_t)(endAddr & 0xFF) );
	data[1] = send_1720( (uint8_t)(endAddr>>8) );
	data[0] = send_1720(0);
	SS_1720_1;
	_delay_ms(5);
	MO_1720_0;
	_delay_ms(5);
	MI_1720_0;
}





	// _______________________________________________________________________
	// disable further INT0 until next sleep
	// GIMSK &= ~(1<<PCIE2); //disable further INT0 until next sleep
	//från https://www.avrfreaks.net/forum/power-down-wakeup-external-interrupts
	// http://www.auldies.cz/avr/ATtiny4313_pins.jpg //PinOuts
	// https://ww1.microchip.com/downloads/en/DeviceDoc/doc8246.pdf // DataBlad


/*
	int main()
	{
		setup();
		char toggle = 0;
		
		DDRB|=(1<<PINB2)|(1<<PINB3)|(1<<PINB4);
		PORTB &=~(1<<PINB2);
		PORTB &=~(1<<PINB3);
		PORTB &=~(1<<PINB4);
		initTimer1();
		GIMSK |= (1 << PCIE2); // set pin-change interrupt for D pins
		PCMSK2 |= (1 << PCINT14)|(1 << PCINT15)|(1 << PCINT16);
		sei();

		send_com(PD);
		_delay_ms(100);
		
		
		while(1)
		{

			
			//PORTB ^=(1<<PINB4);
			if (TIFR & (1 << OCF1A)) {  // count reached?
				TIFR |= (1 << OCF1A);   // clear flag
				if (toggle) {           // toggle LED
					toggle = 0;
					
					
					count++;
					PORTB ^=(1<<PINB2);
					if(count==30){
						count=0;
						stop(STOP);
						_delay_ms(5);
						set_play(audio10);
						_delay_ms(5);
						PORTB &=~(1<<PINB2);
						PORTB &=~(1<<PINB3);
						PORTB &=~(1<<PINB4);
						_delay_ms(5);
						send_com(PD);
						//POWER SAVE
						sleep_enable();
						sei();
						sleep_cpu();
						sleep_disable();
						////////sleep_mode();
					}
					
				}
				
			}
		}

	}
	*/


