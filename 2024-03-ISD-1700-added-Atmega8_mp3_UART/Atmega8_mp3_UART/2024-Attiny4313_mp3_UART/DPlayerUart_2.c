//#define F_CPU 1000000//7000000UL
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "USART.h"



static inline void setup()
{
	DDRD&=~(1<<PD6);//input
	PORTD|=(1<<PD6);//pull up
	DDRD&=~(1<<PD5);//input
	PORTD|=(1<<PD5);//pull up
	DDRD&=~(1<<PD4);//input
	PORTD|=(1<<PD4);//pull up
	DDRD&=~(1<<PD3);//input
	PORTD|=(1<<PD3);//pull up
	DDRD&=~(1<<PD2);//input
	PORTD|=(1<<PD2);//pull up
	//DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB4); //output
	//PORTB &= ~(1 << PB2);						  //off
	//PORTB &= ~(1 << PB3);						  //off
	//PORTB &= ~(1 << PB4);						  //off
}

void mp3_play_num(uint16_t num) {
	uint8_t CRC=0;
	uint8_t HIGH, LOW;
	LOW = (uint8_t)num; // 
	HIGH = num>>8; // 
	CRC = (uint8_t) (0xAA + 0x07 + 0x02 + HIGH + LOW); // PLAY CMD AA 02 00 AC
	transmitByte(0xAA); // 
	transmitByte(0x07); // 
	transmitByte(0x02); // 
	transmitByte(HIGH); // 
	transmitByte(LOW); // 
	transmitByte(CRC); // 
	
}
void mp3_send_byte(uint16_t num) {
	uint8_t CRC=0;
	uint8_t HIGH, LOW;
	LOW = (uint8_t)num; //
	HIGH = num>>8; //
	CRC = (uint8_t) (0xAA + 0x07 + 0x02 + HIGH + LOW); //
	uart_send_byte(0xAA); //
	uart_send_byte(0x07); //
	uart_send_byte(0x02); //
	uart_send_byte(HIGH); //
	uart_send_byte(LOW); //
	uart_send_byte(CRC); //
	
}


int main()
{

	setup();
	//uart_9600();
	initUSART();


    while(1)
    {
		//_________________________
		
        if(bit_is_clear(PIND,PD6))
        {		uint16_t number = 1;
	        uint8_t command[5] = {41, 41, 20, 30, 32, 20, 30, 30, 20, 41, 43};
	        command[4] = number >> 8;
	        command[5] = number & 0xff;
			transmitByte(command); 		

			_delay_ms(1000);//	
        }
		
		//__________________________
		
        if (bit_is_clear(PIND,PD5))
        {
			uint8_t command[5] = {41, 41, 20, 30, 32, 20, 30, 30, 20, 41, 43};
            uart_send_byte(command);
			 _delay_ms(5000);
        }
		
		//__________________________
		
        if (bit_is_clear(PIND,PD4))
        {
			uint8_t command[5] = {41, 41, 20, 30, 32, 20, 30, 30, 20, 41, 43};
			transmitByte(command);
	        _delay_ms(200);

        }
		
		//________volume__________________
		
		if (bit_is_clear(PIND,PD3))
		{

		
			_delay_ms(200);
		 }
		 //__________________________
		 
		 if (bit_is_clear(PIND,PD2))
	     {

			
			  _delay_ms(200);

		 //________________________________
		}


	}
}


 /* static void uart_9600(void)
   {
	   #define BAUD 115200
	   #include <util/setbaud.h>
	   UBRRH = 16;
	   UBRRL = 12;
	   #if USE_2X
	   UCSRA |= (1 << U2X);
	   #else
	   UCSRA &= ~(1 << U2X);
	   #endif
	   
	     UCSRB = (1 << TXEN) | (1 << RXEN);
	     UCSRC = (0 << USBS)|(1 << UCSZ1) | (1 << UCSZ0);   // 8 data bits, 1 stop bit 
   }
*/ 