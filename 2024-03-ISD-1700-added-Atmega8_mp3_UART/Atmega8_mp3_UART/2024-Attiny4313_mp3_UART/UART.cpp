#include "main.h"
#include "UART.h"
#include <util/setbaud.h>
//настройка уарт 8 бит данных, проверка четности откл., 1 стоп бит.
void uart_init(uint16_t ubrr) {
	UBRRH = (uint8_t)(ubrr>>8);
	UBRRL = (uint8_t)ubrr;

	UCSRB |= (1<<TXEN); //
	UCSRB |= (1<<RXEN); // 

UCSRC |= (1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0); // 

}
void uart_STOP(uint16_t ubrr) {

	UCSRB  &= ~(1<<TXEN); //
	UCSRB  &= ~(1<<RXEN); //

	UCSRC  &= ~ (1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0); //
}
//UCSRC = 0b10000110;


void  initUSART(uint16_t ubrr)
{                                /* requires BAUD */
	//UBRRH = UBRRH_VALUE;                        /* defined in setbaud.h */
	//UBRRL = UBRRL_VALUE;
	// --------- настройка скорости ака BAUD RATE ---------------------
	UBRRH = (uint8_t)(ubrr>>8);
	UBRRL = (uint8_t)ubrr;
	//-----------------------------------------------------------------

	// UBRRH = 0;                        /* defined in setbaud.h */
	// UBRRL =8;
	
	#if USE_2X
	UCSRA |= (1 << U2X);
	#else
	UCSRA &= ~(1 << U2X);
	#endif
	/* Enable USART transmitter/receiver */
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC = (0 << USBS)|(1 << UCSZ1) | (1 << UCSZ0);   /* 8 data bits, 1 stop bit */
}



// отправка байта
void uart_send_byte(uint8_t data) {
	while (!(UCSRA & (1 << UDRE))); // Ожидание освобождения буфера отправки
	UDR = data; // записывает байт в буфер, отправка начинается автоматически.
}


// Отправка строки
void uart_send_str(uint8_t *s) {
	while (*s != 0) uart_send_byte(*s++);
}


// отправка строки из флэш памяти
void uart_send_flashstr(const char *string)
{
	while (pgm_read_byte(string)!='\0')
	{
		uart_send_byte(pgm_read_byte(string));
		string++;
	}
}


// Отправка числа от 0000 до 9999
void uart_send_int(uint16_t c)
{
	uint8_t temp;
	c=c%10000;
	temp=c/100;
	uart_send_byte(temp/10+'0');
	uart_send_byte(temp%10+'0');
	temp=c%100;
	uart_send_byte(temp/10+'0');
	uart_send_byte(temp%10+'0');
}

// отправка числа int от 0 до 65535
void uart_send_numstr(uint16_t num) {
	char str[10];
	utoa(num, str, 10);
	uart_send_str((uint8_t*)str);
}


// перевод каретки на новую строку
void uart_send_entr() {
	uart_send_byte(0x0d);
}

//	Получение байта
uint8_t uart_read_byte(void) {
	while(!(UCSRA&(1<<RXC)))	//	Устанавливается, когда регистр свободен
	{}
	return UDR;
}


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



void STOP_UART_PLAY(void) {
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

