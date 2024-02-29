/*
 * ISD_1700_AVR4313.h
 *
 * Created: 2024-02-26 23:22:24
 *  Author: abuam
 */ 


#ifndef ISD_1700_AVR4313_H_
#define ISD_1700_AVR4313_H_

/*
* PinChangeInterrupt_Test1.cpp
*
* Created: 2021-07-28 20:10:51
* Author : abuam
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
#include <avr/sleep.h>


	

	#define uchar unsigned  char
	#define uint  unsigned  long
	
	//Setup SPI PINS.
	#define MO_1720_0  PORTB&=~(1<<PINB5)
	#define MO_1720_1  PORTB|=(1<<PINB5)

	#define MI_1720_0  PORTB&=~(1<<PINB6)
	#define MI_1720_1  PORTB|=(1<<PINB6)

	#define SCK_1720_0 PORTB&=~(1<<PINB7)
	#define SCK_1720_1 PORTB|=(1<<PINB7)

	#define SS_1720_0  PORTB&=~(1<<PINB0)
	#define SS_1720_1  PORTB|=(1<<PINB0)


	//opcodes
	#define PU	        0x01
	#define STOP	    0x02
	#define RESET	    0x03
	#define CLR_INT     0x04
	#define RD_STATUS   0x05
	#define RD_PLAY_PTR 0x06
	#define PD	        0x07
	#define RD_REC_PTR  0x08
	#define DEVID	    0x09
	#define PLAY	    0x40
	#define REC	        0x41
	#define ERASE	    0x42
	#define G_ERASE     0x43
	#define RD_APC	    0x44
	#define WR_APC1     0x45
	#define WR_APC2     0x65
	#define WR_NVCFG    0x46
	#define LD_NVCFG    0x47
	#define FWD	        0x48
	#define CHK_MEM     0x49
	#define EXTCLK	    0x4A
	#define SET_PLAY    0x80
	#define SET_REC     0x81
	#define SET_ERASE   0x82

 // audio list

 #define audio0  0x05B,0x084//
 #define audio1  0x088,0x090//
 #define audio2  0x092,0x09C //
 #define audio3  0x09F,0x0A7 //
 
 #define audio4  0x08A,0x08E//
 #define audio5  0x08F, 0x094 //
 #define audio6  0x095,0x09B//
 #define audio7  0x09C,0x0A2 //
 #define audio8  0x0A3,0x0A8 //
 #define audio9  0x0A9,0x0AF////

 #define audio10    0xFB,0x10A//251,266
 #define audio11  0x10B,0x120 //
 #define audio12    0x121,0x129 //
 #define audio13  0x130,0x148//
 #define audio14    329,364 //
 #define audio15  0x16D,0x181//
 #define audio16    0x182,0x194 //
 #define audio17  0x195,0x19B //
 #define audio18  0x19C,0x1E2//
 #define audio19  483,498//0x1E3,0x1F2
 #define audio20  499,543//0x1F3,0x21F subhana allah ahamdan lillah wallahu akbar


 #define audio21  544,561//0x0220,0x231  ja ska vi göra salat
 #define audio22  562,577 //0x0232,0x0241 la ilaha illa ALLAH
 #define audio23  578,635//0x0242,0x027B Iqra Iqra
 #define audio24  0X37D,0X3AE//0x027C,0x02AD assalatu wassalamu ala almustafa
 #define audio25  0x03AF,0x0495//0x02AE,0x0327 Wasalla rabbuna fi kulli hinin.
 //#define audio26  0x490,0x4BC//
 //#define audio27  0x4BD,0x4CE//
 //#define audio28  0x4CF,0x4DE//

void setup();

uint8_t  send_1720( uint8_t data);

void send_com(uchar com);

void stop(uchar start_address);

void set_play(uint16_t startAddr, uint16_t endAddr);



#endif /* ISD_1700_AVR4313_H_ */