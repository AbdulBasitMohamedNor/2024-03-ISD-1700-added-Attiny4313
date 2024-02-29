/*
 * play_num.cpp
 *
 * Created: 2022-01-04 23:48:14
 *  Author: abuam
 */ 
#ifndef DiYplayer_functions1_H_
#define DiYplayer_functions1_H_

#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>


	#define IO0_high		PORTD|=(1<<PIND0); //
	#define IO1_high		PORTD|=(1<<PIND1); //
	#define IO2_high		PORTA|=(1<<PINA0);//
	#define IO3_high		PORTA|=(1<<PINA1);//
	#define IO4_high		PORTD|=(1<<PIND2); //knapp
	#define IO5_high		PORTD|=(1<<PIND3);//knapp
	#define IO6_high		PORTD|=(1<<PIND4);//knapp
	#define IO7_high		PORTD|=(1<<PIND5);//knapp
	
/*
	
	#define _UDPin_high		PORTB|=(1<<PINB0);//knapp
	#define _CSPin_high		PORTD|=(1<<PIND6);//knapp
	
	#define _UDPin_low		PORTB&=~(1<<PINB0);//knapp
	#define _CSPin_low		PORTD&=~(1<<PIND6);//knapp	
	

	
	#define _UDPin		PINB0//knapp
	#define _CSPin		PIND6//knapp	*/	

		

		
	//:::::Level Low:::::::::lower pin play::::se combination.
	#define IO0_low		PORTD&=~(1<<PD0); //
	#define IO1_low		PORTD&=~(1<<PD1); //
	#define IO2_low		PORTA&=~(1<<PA0);//
	#define IO3_low		PORTA&=~(1<<PA1);//
	#define IO4_low		PORTD&=~(1<<PD2); //
	#define IO5_low		PORTD&=~(1<<PD3);//
	#define IO6_low		PORTD&=~(1<<PD4);//
	#define IO7_low		PORTD&=~(1<<PD5);//
	
	

	#define play_1				IO0_low;IO1_high;IO2_high;IO3_high;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_2				IO0_high;IO1_low;IO2_high;IO3_high;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_3				IO0_low;IO1_low;IO2_high;IO3_high;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_4				IO0_high;IO1_high;IO2_low;IO3_high;IO4_high;IO5_high;IO6_high;IO7_high;

	#define play_5 				IO0_low;IO1_high;IO2_low;IO3_high;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_6				IO0_high;IO1_low;IO2_low;IO3_high;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_7				IO0_low;IO1_low;IO2_low;IO3_high;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_8				IO0_high;IO1_high;IO2_high;IO3_low;IO4_high;IO5_high;IO6_high;IO7_high;

	#define play_9 				IO0_low;IO1_high;IO2_high;IO3_low;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_10 			IO0_high;IO1_low;IO2_high;IO3_low;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_11 			IO0_low;IO1_low;IO2_high;IO3_low;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_12				IO0_high;IO1_high;IO2_low;IO3_low;IO4_high;IO5_high;IO6_high;IO7_high;

	#define play_13				IO0_low;IO1_high;IO2_low;IO3_low;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_14				IO0_high;IO1_low;IO2_low;IO3_low;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_15				IO0_low;IO1_low;IO2_low;IO3_low;IO4_high;IO5_high;IO6_high;IO7_high;
	#define play_16				IO0_high;IO1_high;IO2_high;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;
	//***********************************Oanvända i DiyMp3******************************************//
	#define play_17				IO0_low;IO1_high;IO2_high;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;

	#define play_18				IO0_high;IO1_low;IO2_high;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;
	#define play_19				IO0_low;IO1_low;IO2_high;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;
	#define play_20				IO0_high;IO1_high;IO2_low;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;
	#define play_21				IO0_low;IO1_high;IO2_low;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;

			//
 //IO7 IO6 IO5 IO4 IO3 IO2 IO1 IO0 Music playing
 //1 1 1 1 1 1 1 0 00001.mp3
 //1 1 1 1 1 1 0 1 00002.mp3
 //1 1 1 1 1 1 0 0 00003.mp3
 //1 1 1 1 1 0 1 1 00004.mp3
 //1 1 1 1 1 0 1 0 00005.mp3
 //1 1 1 1 1 0 0 1 00006.mp3
 //1 1 1 1 1 0 0 0 00007.mp3
 //1 1 1 1 0 1 1 1 00008.mp3
 //1 1 1 1 0 1 1 0 00008.mp3
 /*
static inline void initTimer1(void);
static inline void TMR0_init2( void );
static inline void initPinChangeInterrupt4(void);
	*/

#endif 										  