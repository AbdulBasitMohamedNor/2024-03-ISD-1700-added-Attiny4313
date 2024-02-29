/*
 * CFile1.c
 *
 * Created: 2021-11-06 20:45:48
 *  Author: abuam
 */ 
#include "MP3_PLAYER.h"
#include <util/setbaud.h>
#include "UART.h"

void mp3_play_num(uint16_t num) {
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


void mp3_play_next() {
	uint8_t CRC=0;
	CRC = (uint8_t) (0xAA + 0x06 + 0x00 + 0xB0);//
	uart_send_byte(0xAA); //
	uart_send_byte(0x06); //
	uart_send_byte(0x00); //
	uart_send_byte(0xB0); //
	uart_send_byte(CRC);  //
}


void stop(void) {
	uint8_t CRC=0;
	CRC = (uint8_t) (0xaa, 0x04, 0x00, 0xae);
	uart_send_byte(0xAA); //
	uart_send_byte(0x04); //
	uart_send_byte(0x00); //
	uart_send_byte(0xae); //
	uart_send_byte(CRC); //
}

void volumeIncrease() {
	uint8_t CRC=0;
	CRC = (uint8_t) (0xaa, 0x14, 0x00, 0xbe);
	uart_send_byte(0xAA); //
	uart_send_byte(0x14); //
	uart_send_byte(0x00); //
	uart_send_byte(0xbe); //
	uart_send_byte(CRC); //
}

void volumeDecrease() {
	uint8_t CRC=0;
	CRC = (uint8_t) (0xaa, 0x15, 0x00, 0xbf);
	uart_send_byte(0xAA); //
	uart_send_byte(0x15); //
	uart_send_byte(0x00); //
	uart_send_byte(0xbf); //
	uart_send_byte(CRC); //
}

void mp3_play_volume(uint16_t volume) {
	uint8_t CRC=0;
	CRC = (uint8_t) (0xAA + 0x13 + 0x01 + volume);//
	uart_send_byte(0xAA); //
	uart_send_byte(0x13); //
	uart_send_byte(0x01); //
	uart_send_byte(volume); //
	uart_send_byte(CRC);  //
}