#define F_CPU 1000000UL
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
//#include "UART.h"
#include "mcp4013.h"
#include <stdbool.h>
#define VOL_WIPER_1_WRITE 0x10
#define VOL_WIPER_1_READ  0x1C
#define VOL_WIPER_1_INC   0x14
#define VOL_WIPER_1_DEC   0x18
#define NV_WIPER_0_WRITE 0x20
#define NV_WIPER_0_READ  0x2C
#define NV_WIPER_0_INC   0x24
#define NV_WIPER_0_DEC   0x28

void TpowerOff();
void TpowerON();
void ledpwm();
uint8_t lage = 0;
uint8_t tilt_Sensor = 0;
uint8_t magnet_change = 0;
uint8_t mode = 0;
uint8_t alarm = 0;
uint8_t number = 0;
uint8_t grupp = 0;
uint8_t song = 0;
uint8_t count = 0;
uint8_t TotalTime = 0;
uint8_t led = 0;
uint8_t count2;
uint8_t pwmOn;
char toggle = 0;
uint8_t loud = 1;
uint8_t seconds = 0;

int pwmOn2 = 0;
volatile char toggle2 = 0;

volatile uint8_t B1 = 0;
volatile uint8_t B2 = 0;
volatile uint8_t B3 = 0;

// Define the button pin
#define BUTTON_PIN PINB5

// Define the LED pin
#define LED_PIN PINB2

// Define the button states
#define BUTTON_RELEASED 0
#define BUTTON_PRESSED 1
#define BUTTON_LONG_PRESSED 3

// Define the button debounce delay in milliseconds
#define BUTTON_DEBOUNCE_DELAY 50

// Define the button press durations in milliseconds
#define BUTTON_SHORT_PRESS_DURATION 300
#define BUTTON_LONG_PRESS_DURATION 3000

// Define the LED PWM values
#define LED_PWM_OFF 0
#define LED_PWM_LOW 50
#define LED_PWM_MED 100
#define LED_PWM_HIGH 200

// Global variables
volatile uint8_t button_state = BUTTON_RELEASED;
volatile uint8_t button_press_count = 0;
static inline void setup() {
	toggle = 0;
	count = 0;
	mode = 0;
	TotalTime = 30;
	lage = 0;
	grupp = 0;
	song = 0;
	number = 0;
	pwmOn = 0;

	B1 = 0;
	B2 = 0;
	B3 = 0;

	//output Player
	DDRD |= (1 << PIND5); //output
	DDRD |= (1 << PIND4); //output
	DDRD |= (1 << PIND3); //output
	DDRD |= (1 << PIND2); //output
	DDRD |= (1 << PIND1); //output
	DDRD |= (1 << PIND0); //output
	DDRA |= (1 << PINA0); //output
	DDRA |= (1 << PINA1); //output

	DDRB |= (1 << PINB4); //LED pwm output
	PORTB &= ~(1 << PINB4); //off

	DDRB |= (1 << PINB7); //Transistor output
	PORTB &= ~(1 << PINB7); //off

	DDRB &= ~(1 << PINB2) | (1 << PINB3); //tilt input pin och MAGNET PIN:
	PORTB |= (1 << PINB2) | (1 << PINB3);

	//buttons interrupt inputs
	DDRB &= ~(1 << PINB5) | (1 << PINB6); //input
	PORTB |= (1 << PINB5) | (1 << PINB6);

	IO0_high;
	IO1_high;
	IO2_high;
	IO3_high;
	IO4_high;
	IO5_high;
	IO6_high;
	IO7_high;
}

void stop() {
	_delay_ms(200);
	IO0_high;
	IO1_high;
	IO2_high;
	IO3_high;
	IO4_high;
	IO5_high;
	IO6_high;
	IO7_high;
}

static inline void initTimer1(void) {
	//DDRD |= (1 << PD5);     // LED on PD6
	//DDRD |=(1<<PD4);//output Led
	//PORTD |=(1<<PD4);//output Led

	OCR1A = 0x4000; // number to count to
	TCCR1A = 0; // CTC mode
	// CTC mode, clk src = clk/8, start timer
	TCCR1B = (1 << WGM12) | (1 << CS11);

	// CTC mode, clk src = clk/64, start timer
	//TCCR1B |= (1 << CS11) | (1 << CS10);

	// CTC mode, clk src = clk/1024, start timer
	//TCCR1B |= (1 << CS12) | (1 << CS10);

	/* Disable interrupts */
	cli();
	/* Reset watchdog timer */
	wdt_reset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1 << WDRF);
	/* Turn off WDT */
	WDTCR = 0x00;
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}
ISR(TIMER0_OVF_vect) {

	//PORTB ^=(1<<PB4);
	//Test att tuggla led här
}

/////////////////MPC-4013-Volume Control//////////////////////////////

void increaseValue() {}
void decreaseValue() {}
void blink() {

	//for (int i = 0; i < 10; i) {
	//PORTB ^= (1 << PINB2);
	//_delay_ms(10);
	//i++;
	//}
	for (int i = 0; i < 10; i) {
		PORTB ^= (1 << PINB3);
		_delay_ms(10);
		i++;
	}
	for (int i = 0; i < 10; i) {
		PORTB ^= (1 << PINB4);
		_delay_ms(10);
		i++;
	}
}

void initPinChangeInterrupt4(void) {
	GIMSK |= (1 << PCIE0); // | (1 << PCIE1)???????????????????????????????????????????????????????????????????????????????????????????????????????????????  /* set pin-change interrupt for D pins */
	PCMSK |= (1 << PCINT1) | (1 << PCINT3) |(1 << PCINT5) | (1 << PCINT6); /*| (1 << PCINT7) set mask to look for PCINT13-15 */ // Behöver bara ha en Pin som interrupt
	//PCMSK1 |= (1 << PCINT10);
	//MCUCR |= (1<<ISC01)|(1<<ISC00);???//Set fire condition: Rising Edge
	sei(); /* set (global) interrupt enable bit */
}

void sleep() {
	if (TIFR & (1 << OCF1A)) { // count reached?
		TIFR |= (1 << OCF1A); // clear flag
		// toggle LED

		count++;
		PORTB ^= (1 << PINB3);
		if (count == TotalTime) {
			count = 0;
			stop();
			_delay_ms(5);
			play_9;
			stop();
			_delay_ms(5);
			TpowerOff(); // turn Power on DiyPlayer off
			//PORTB |= (1 << PINB2);
			PORTB |= (1 << PINB3);
			PORTB |= (1 << PINB4);
			_delay_ms(300);
			// PORTB &= ~(1 << PINB2);
			PORTB &= ~(1 << PINB3);
			PORTB &= ~(1 << PINB4);
			_delay_ms(5);
			//POWER SAVE
			sleep_enable();
			sei();
			sleep_cpu();
			sleep_disable();
			////////sleep_mode();
		}

	}
}
void sleepLoop() {
	initTimer1();
	for (int i = 0; i < TotalTime; i++) {
		if (TIFR & (1 << OCF1A)) { // count reached?
			TIFR |= (1 << OCF1A); // clear flag
			// toggle LED  blink();

			count++;
			PORTB ^= (1 << PINB3);
			if (count == TotalTime) {
				count = 0;
				stop();
				_delay_ms(5);
				play_9;
				stop();
				_delay_ms(5);
				TpowerOff(); // turn Power on DiyPlayer off
				// PORTB |= (1 << PINB2);
				PORTB |= (1 << PINB3);
				PORTB |= (1 << PINB4);
				_delay_ms(300);
				// PORTB &= ~(1 << PINB2);
				PORTB &= ~(1 << PINB3);
				PORTB &= ~(1 << PINB4);
				_delay_ms(5);
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
void TpowerON() {
	PORTB |= (1 << PINB7);
}
void TpowerOff() {
	PORTB &= ~(1 << PINB7);
}
void ledpwm() {
	// fast PWM mode
	// init timers as fast PWM
	TCCR0A = (1 << WGM00) | (1 << WGM01);
	TCCR1A = (1 << WGM10) | (1 << WGM12);
	// set prescaler to 1
	TCCR0B |= (1 << CS00);
	TCCR1B |= (1 << CS00);
	// set outputs to PWM
	TCCR0A |= (1 << COM0A1);
	TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << COM0B1);
	OCR1A = 0;
	OCR0A = 0;
	OCR1B = 0; // initial PWM pulse width
	// clock source = clock / 1 ; start PWM
	TCCR1B = (1 << CS10);
	PORTB &= ~(1 << PINB4);
	//PORTB &= ~(1 << PINB2);
	PORTB &= ~(1 << PINB3);
	for (int loopar = 0; loopar < 10; loopar++) {
		/*for (int i = 0; i < 255; i++)
		{????? if (pwmOn !=0)
		{
		_delay_ms(20);
		OCR1B = i;
		}
		
		}
		for (int i = 255; i != 0; i--)
		{????? if (pwmOn !=0)
		{
		_delay_ms(20);
		OCR1B = i;
		}

		} */

		for (int i = 0; i < 255; i++) {
			if (pwmOn != 0) {
				_delay_ms(20);

				OCR1A = i;
			}

		}
		for (int i = 255; i != 0; i--) {
			if (pwmOn != 0) {
				_delay_ms(20);

				OCR1A = i;
			}

		}

		for (int i = 0; i < 255; i++) {
			if (pwmOn != 0) {
				_delay_ms(20);

				OCR0A = i;
			}

		}
		for (int i = 255; i != 0; i--) {
			if (pwmOn != 0) {
				_delay_ms(20);
				OCR0A = i;
			}
		}

		sleep();
	}
}

void ledpwm_OFF() {
	// fast PWM mode
	// init timers as fast PWM
	TCCR0A = (1 << WGM00) | (1 << WGM01);
	TCCR1A = (1 << WGM10) | (1 << WGM12);
	// set prescaler to 1
	TCCR0B |= (1 << CS00);
	TCCR1B |= (1 << CS00);
	// set outputs to PWM
	TCCR0A |= (1 << COM0A1);
	TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << COM0B1);
	OCR1A = 0;
	OCR0A = 0;
	OCR1B = 0; // initial PWM pulse width
	// clock source = clock / 1 ; start PWM
	TCCR1B = (1 << CS10);

	// Turn off the timer
	TCCR1B &= 0xf8; // turn off timer 1;
	TCCR1A = 0; // disconnect the output pin
	TCCR0A = 0; // disconnect the output pin
	// Clear the count
	TCNT1 = 0;
	// Clear the pin

	pwmOn = 0;
	for (int i = 255; i != 0; i--) {

		OCR1A = i;

	}

	for (int i = 255; i != 0; i--) {

		OCR0A = i;

	}

	for (int i = 255; i != 0; i--) {

		OCR1B = i;

	}
	/**/
	TCCR1B = (1 << CS10);

	// Turn off the timer
	TCCR1B &= 0xf8; // turn off timer 1;
	TCCR1A = 0; // disconnect the output pin
	TCCR0A = 0; // disconnect the output pin
	// Clear the count
	TCNT1 = 0;
	OCR1A = 0;
	OCR0A = 0;
	OCR1B = 0; // initial PWM pulse width
	setup();
	//PORTB &= ~(1 << PINB2);
	PORTB &= ~(1 << PINB3);
	PORTB &= ~(1 << PINB4);
}

ISR(PCINT_B_vect) {
	TpowerON(); // turn Power on DiyPlayer ON


	if (alarm==1 && bit_is_set(PINB, PINB3))
	{
		_delay_ms(200);
		play_11; _delay_ms(300);//00005_Utgångs_Bönen
		stop();
	}


	//**********VÄNSTER DÖRR SKIFT************************
	if (tilt_Sensor == 0 && bit_is_clear(PINB, PINB6)) // bläddraren knapp 2
	{

		if (alarm == 0) {
			_delay_ms(200);
			play_6; //00005_Utgångs_Bönen
			stop();
			PORTB |= (1 << PINB6);
		}

		_delay_ms(500);
		if (bit_is_clear(PINB, PINB6)) {

			if (magnet_change == 0 && alarm == 0 && bit_is_clear(PINB, PINB6)) 	 // sätter på Larm
			{
				_delay_ms(3000);
				blink();
				_delay_ms(200);
				play_7;
				stop();
				blink();
				_delay_ms(1500);
				alarm = 1;
				return;
			}

			if (magnet_change == 1 && alarm == 1  && bit_is_clear(PINB, PINB6)) 		// stänger av Larm
			{
				_delay_ms(3000);
				blink();
				_delay_ms(200);
				play_3;
				stop();
				blink();
				_delay_ms(1500);
				alarm = 0;
				//count = 1; //Höger Dörr
				return;
			}

		}
	}
	//::::::::::::::::::::::::::::::::::::::::::::::::
	/**/
	if (tilt_Sensor == 0 && bit_is_clear(PINB, PINB5)) // bläddraren knapp 2
	{

		if (alarm == 0) {
			_delay_ms(200);
			play_5; //00005_Utgångs_Bönen
			stop();
			PORTB |= (1 << PINB5);
		}

		_delay_ms(500);
		if (bit_is_clear(PINB, PINB5)) {

			if (magnet_change == 1 && bit_is_clear(PINB, PINB5)) {
				_delay_ms(3000);
				blink();
				_delay_ms(200);
				play_7;
				stop();
				blink();
				_delay_ms(1500);
				alarm = 1;
				return;
			}

			if (magnet_change == 0 && bit_is_clear(PINB, PINB5)) {
				_delay_ms(3000);
				blink();
				_delay_ms(200);
				play_3;
				stop();
				blink();
				_delay_ms(1500);
				//mode = 1;
				//count = 1; //Höger Dörr
				return;
			}

		}

	}
	//**********VÄNSTER DÖRR SKIFT************************
	if (tilt_Sensor == 1 && bit_is_clear(PINB, PINB6)) // bläddraren knapp 2
	{
		if (alarm == 0) {
			_delay_ms(200);
			play_5; //00005/6_InUtgångs_Bönen
			stop();
			PORTB |= (1 << PINB6);
		}

		_delay_ms(500);
		if (bit_is_clear(PINB, PINB6)) {

			if (magnet_change == 1 && bit_is_clear(PINB, PINB6)) {
				_delay_ms(3000);
				blink();
				_delay_ms(200);
				play_7;
				stop();
				blink();
				_delay_ms(1500);
				alarm = 1;
				return;
			}

			if (magnet_change == 0 && bit_is_clear(PINB, PINB6)) {
				_delay_ms(3000);
				blink();
				_delay_ms(200);
				play_3;
				stop();
				blink();
				_delay_ms(1500);
				//mode = 1;
				//count = 1; //Höger Dörr
				return;
			}

		}
	}
	//::::::::::::::::::::::::::::::::::::::::::::::::
	/**/
	if (tilt_Sensor == 1 && bit_is_clear(PINB, PINB5)) // bläddraren knapp 2
	{

		if (alarm == 0) {
			_delay_ms(200);
			play_6; //00005_Utgångs_Bönen
			stop();
			PORTB |= (1 << PINB6);
		}

		_delay_ms(500);
		if (bit_is_clear(PINB, PINB5)) {

			if (magnet_change == 1 && bit_is_clear(PINB, PINB5)) {
				_delay_ms(3000);
				blink();
				_delay_ms(200);
				play_7;
				stop();
				blink();
				_delay_ms(1500);
				alarm = 1;
				return;
			}

			if (magnet_change == 0 && bit_is_clear(PINB, PINB5)) {
				_delay_ms(3000);
				blink();
				_delay_ms(200);
				play_3;
				stop();
				blink();
				_delay_ms(1500);
				//mode = 1;
				//count = 1; //Höger Dörr
				return;
			}

		}

	}

}

//******************************************************
int main(void) {

	setup();
	TpowerON(); //TpowerOff();     turn Power on DiyPlayer ON
	//initTimer1();
	initPinChangeInterrupt4();

	//_delay_ms(200);play_1;_delay_ms(1500);stop();
	//_delay_ms(200);play_2;_delay_ms(1500);stop();
	//_delay_ms(200);play_3;_delay_ms(1500);stop();
	//_delay_ms(200);play_4;_delay_ms(1500);stop();
	//_delay_ms(200);play_5;_delay_ms(1500);stop();
	//_delay_ms(200);play_6;_delay_ms(1500);stop();
	//_delay_ms(200);play_7;_delay_ms(1500);stop();
	//_delay_ms(200);play_8;_delay_ms(1500);stop();
	//_delay_ms(200);play_9;_delay_ms(1500);stop();
	//_delay_ms(200);play_10;_delay_ms(1500);stop();
	//_delay_ms(200);play_12;_delay_ms(1500);stop();
	//_delay_ms(200);play_13;_delay_ms(1500);stop();
	//_delay_ms(200);play_14;_delay_ms(1500);stop();
	//_delay_ms(200);play_15;_delay_ms(1500);stop();
	//_delay_ms(200);play_16;_delay_ms(1500);stop();
	//_delay_ms(200);play_17;_delay_ms(1500);stop();
	//_delay_ms(200);play_18;_delay_ms(1500);stop();
	//_delay_ms(200);play_19;_delay_ms(1500);stop();
	//_delay_ms(200);play_20;_delay_ms(1500);stop();

	//toggle = 1;
	// play_9; stop();  // Replace with "Hej Då" Sound  SSSS
	while (1) {

		//Metod för när man vänder på apparaten för H resp V dörr
		if (tilt_Sensor == 1 && bit_is_clear(PINB, PINB2)) {
			_delay_ms(200);
			play_1;					  //Höger Dörr
			_delay_ms(400);
			stop();
			tilt_Sensor = 0;
			count = 0;
		} // Vänster dörr
		_delay_ms(500);
		if (tilt_Sensor == 0 && bit_is_set(PINB, PINB2)) {
			_delay_ms(200);
			play_2;						//   Vänster Dörr
			_delay_ms(400);
			stop();
			tilt_Sensor = 1;
			count = 1;
		} // Höger Dörr
		_delay_ms(500);



	}

}

//??????????_delay_ms(200);     _delay_ms(40500);???????????  delay_ms(20200);????????????play_3;break;stop(); break;???play_1;?????continue;stop();