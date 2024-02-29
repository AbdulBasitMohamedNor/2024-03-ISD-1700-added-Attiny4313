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


	#define IO0_high		PORTD|=(1<<PD0); //
	#define IO1_high		PORTD|=(1<<PD1); //
	#define IO2_high		PORTA|=(1<<PA1);//
	#define IO3_high		PORTA|=(1<<PA0);//
	#define IO4_high		PORTD|=(1<<PD2); //knapp
	#define IO5_high		PORTD|=(1<<PD3);//knapp
	#define IO6_high		PORTD|=(1<<PD4);//knapp
	#define IO7_high		PORTD|=(1<<PD5);//knapp
	
	

		
	//:::::Level Low:::::::::lower pin play::::se combination.
	#define IO0_low		PORTD&=~(1<<PD0); //
	#define IO1_low		PORTD&=~(1<<PD1); //
	#define IO2_low		PORTA&=~(1<<PA1);//
	#define IO3_low		PORTA&=~(1<<PA0);//
	#define IO4_low		PORTD&=~(1<<PD2); //knapp
	#define IO5_low		PORTD&=~(1<<PD3);//knapp
	#define IO6_low		PORTD&=~(1<<PD4);//knapp
	#define IO7_low		PORTD&=~(1<<PD5);//knapp
	
	

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
	#define play_17				IO0_low;IO1_high;IO2_high;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;

	#define play_18				IO0_high;IO1_low;IO2_high;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;
	#define play_19				IO0_low;IO1_low;IO2_high;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;
	#define play_20				IO0_high;IO1_high;IO2_low;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;
	#define play_21				IO0_low;IO1_high;IO2_low;IO3_high;IO4_low;IO5_high;IO6_high;IO7_high;




#endif 										  