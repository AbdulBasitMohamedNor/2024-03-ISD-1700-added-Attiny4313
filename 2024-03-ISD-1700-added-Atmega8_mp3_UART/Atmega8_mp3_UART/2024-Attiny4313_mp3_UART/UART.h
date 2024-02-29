#ifndef UART_H_
#define UART_H_
#define F_CPU 1000000UL
#define PRESCALL 16// 16 (U2X = 0) ��� 8 ���� �������� ������� (U2X = 1).
#define BAUD 9600 // ��������
#define MYUBRR F_CPU/PRESCALL/BAUD //BAUD-1 ������ �������� ��� �������� UBRR �� ��������... ( � ���� �� �����... ������� ���������)

void uart_init(uint16_t ubrr);
void uart_STOP(uint16_t ubrr);
void initUSART(uint16_t ubrr);
void uart_send_byte(uint8_t data);
void uart_send_str(uint8_t *s);
void uart_send_flashstr(const char *string);
void uart_send_int(uint16_t c);
void uart_send_numstr(uint16_t num);
void uart_send_entr();

uint8_t uart_read_byte(void);


void mp3_play_num(uint16_t num);
void mp3_play_next(void);
void stop(void);
void volumeIncrease(void);
void volumeDecrease(void);
void mp3_play_volume(uint16_t volume);


#endif /* UART_H_ */