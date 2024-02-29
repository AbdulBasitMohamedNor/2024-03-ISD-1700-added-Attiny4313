/*
 * MP3_PLAYER.h
 *
 * Created: 2021-11-06 20:46:57
 *  Author: abuam
 */ 

#include "UART.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>


#ifndef MP3_PLAYER_H_
#define MP3_PLAYER_H_


void mp3_play_num(uint16_t num);
void mp3_play_next(void);
void stop(void);
void volumeIncrease(void);
void volumeDecrease(void);
void mp3_play_volume(uint16_t volume);


#endif /* MP3_PLAYER_H_ */