
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

int pwmOn2=0;
volatile char toggle2 = 0;

volatile uint8_t B1 = 0;
volatile uint8_t B2 = 0;
volatile uint8_t B3 = 0;

static inline void setup()
{
	toggle = 0;
	count = 0;
	TotalTime=60;
	lage = 0;
	grupp = 0;
	song = 0;
	number = 0;
	pwmOn = 0;

	B1 = 0;
	B2 = 0;
	B3 = 0;

	//output Player
	DDRD|=(1<<PIND5);//output
	DDRD|=(1<<PIND4);//output
	DDRD|=(1<<PIND3);//output
	DDRD|=(1<<PIND2);//output
	DDRD|=(1<<PIND1);//output
	DDRD|=(1<<PIND0);//output
	DDRA|=(1<<PINA0);//output
	DDRA|=(1<<PINA1);//output
	
	DDRB|=(1<<PIND6);//output


	DDRB |= (1 << PINB0)|(1 << PINB4)|(1 << PINB2)| (1 << PINB3) ; //LED pwm output
	PORTB &= ~ (1 << PINB4)|(1 << PINB2)| (1 << PINB3);	 //off
	
	DDRB |= (1 << PINB1); //Transistor output
	PORTB &= ~(1 << PINB1);	 //off

	//Reset pin as input
	DDRA &=~(1 << PINA2);//input
	PORTA  |=(1 << PINA2);
	

	

	//buttons interrupt inputs
	DDRB &=~(1 << PINB5)|(1 << PINB6)|(1 << PINB7);//input
	PORTB |=(1 << PINB5)|(1 << PINB6)|(1 << PINB7);
	
	

	IO0_high;
	IO1_high;
	IO2_high;
	IO3_high;
	IO4_high;
	IO5_high;
	IO6_high;
	IO7_high;
}

void  stop()
{
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

static inline void initTimer1(void)
{
	//DDRD |= (1 << PD5);     // LED on PD6
	//DDRD |=(1<<PD4);//output Led
	//PORTD |=(1<<PD4);//output Led

	OCR1A = 0x4000; // number to count to
	TCCR1A = 0;		// CTC mode
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
ISR(TIMER0_OVF_vect)
{

	//PORTB ^=(1<<PB4);
	//Test att tuggla led här
}


/////////////////MPC-4013-Volume Control//////////////////////////////

void increaseValue(){
}
void decreaseValue(){
}
void blink()
{

	for (int i = 0; i < 10; i)
	{
		PORTB ^= (1 << PINB2);
		_delay_ms(10);
		i++;
	}
	for (int i = 0; i < 10; i)
	{
		PORTB ^= (1 << PINB3);
		_delay_ms(10);
		i++;
	}
	for (int i = 0; i < 10; i)
	{
		PORTB ^= (1 << PINB4);
		_delay_ms(10);
		i++;
	}
}


void initPinChangeInterrupt4(void)
{
	GIMSK |= (1 << PCIE0);// | (1 << PCIE1)																			  /* set pin-change interrupt for D pins */
	PCMSK |= (1 << PCINT1) | (1 << PCINT5) | (1 << PCINT6) | (1 << PCINT7); /* set mask to look for PCINT13-15 */ // Behöver bara ha en Pin som interrupt
	//PCMSK1 |= (1 << PCINT10);
	//MCUCR |= (1<<ISC01)|(1<<ISC00);	//Set fire condition: Rising Edge
	sei(); /* set (global) interrupt enable bit */
}

void sleep(){
	if (TIFR & (1 << OCF1A))
	{  // count reached?
		TIFR |= (1 << OCF1A);   // clear flag
		// toggle LED
		
		count++;
		PORTB ^=(1<<PINB3);
		if(count==TotalTime)
		{
			count=0;
			stop();
			_delay_ms(5);												
			play_9; stop();
			_delay_ms(5);
			 TpowerOff();  // turn Power on DiyPlayer off 
			PORTB |=(1<<PINB2);
			PORTB |=(1<<PINB3);
			PORTB |=(1<<PINB4);
			_delay_ms(300);
			PORTB &=~(1<<PINB2);
			PORTB &=~(1<<PINB3);
			PORTB &=~(1<<PINB4);
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
void sleepLoop(){
	initTimer1();
	for (int i = 0; i < TotalTime; i++)
	{
		if (TIFR & (1 << OCF1A))
		{  // count reached?
			TIFR |= (1 << OCF1A);   // clear flag
			// toggle LED  blink();
			
			count++;
			PORTB ^=(1<<PINB3);
			if(count==TotalTime)
			{
				count=0;
				stop();
				_delay_ms(5);
				play_9; stop();
			_delay_ms(5);
			TpowerOff();  // turn Power on DiyPlayer off
				PORTB |=(1<<PINB2);
				PORTB |=(1<<PINB3);
				PORTB |=(1<<PINB4);
				_delay_ms(300);
				PORTB &=~(1<<PINB2);
				PORTB &=~(1<<PINB3);
				PORTB &=~(1<<PINB4);
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
void TpowerON()
{
	PORTB |=(1<<PINB1);
}
void TpowerOff()
{
	PORTB &=~(1<<PINB1);
}
void ledpwm()
{
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
	PORTB &= ~(1 << PINB2);
	PORTB &= ~(1 << PINB3);
	for (int loopar = 0; loopar < 10; loopar++)
	{
		for (int i = 0; i < 255; i++)
		{	 if (pwmOn !=0)
			{
				_delay_ms(20);
				OCR1B = i;
			}
			
		}
		for (int i = 255; i != 0; i--)
		{	 if (pwmOn !=0)
			{
				_delay_ms(20);
				OCR1B = i;
			}

		}

		for (int i = 0; i < 255; i++)
		{				    if (pwmOn !=0)
			{
				_delay_ms(20);

				OCR1A = i;
			}

		}
		for (int i = 255; i != 0; i--)
		{	 if (pwmOn !=0)
			{
				_delay_ms(20);

				OCR1A = i;
			}

		}

		for (int i = 0; i < 255; i++)
		{	 if (pwmOn !=0)
			{
				_delay_ms(20);

				OCR0A = i;
			}

		}
		for (int i = 255; i != 0; i--)
		{
			if (pwmOn !=0)
			{
				_delay_ms(20);
				OCR0A = i;
			}
		}
		
		sleep();
	}
}

void ledpwm_OFF()
{
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
	for (int i = 255; i != 0; i--)
	{
	
		 OCR1A = i;
		
	}

	
	for (int i = 255; i != 0; i--)
	{
	
		   OCR0A = i;
		
		
	}

	
	for (int i = 255; i != 0; i--)
	{
		
		 OCR1B = i;	
		
	}
	/**/	TCCR1B = (1 << CS10);
	
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
	PORTB &=~(1<<PINB2);
	PORTB &=~(1<<PINB3);
	PORTB &=~(1<<PINB4);
}

ISR(PCINT_B_vect)
{              /* Run every time button state changes */ // testa ISR(INT0_vect)
	count=0;
	//ledpwm_OFF();
	//setup();
	//initTimer1();
	//TpowerON();  // turn Power on DiyPlayer ON	
	//::::::::::::::::::::::::::::::::::::::::::::::::
	if (bit_is_clear(PINB, PINB5))
	{
		B1=0;
		
		lage++;
		if (lage == 1)
		{	_delay_ms(300); blink();
			play_1; stop();  // Natt bön
		}
		if (lage == 2)
		{	 _delay_ms(300);
			play_2; stop();	 // Morgon bön
		}
		if (lage == 3)
		{	_delay_ms(300);
			play_3; stop();	  //  sjunga
		}
		if (lage == 4)
		{	_delay_ms(300);
			play_4; stop();	  // leka
			
		}

		if (lage == 5)
		{	
			lage = 0;
			
			
			count=TotalTime - 5;
		}

	}
	//::::::::::::::::::::::::::::::::::::::::::::::::
	/**/
	if (bit_is_clear(PINB, PINB6)) //If PIND4 is low
	{
		B1++;  
		//**********Läge1************
		if (B1 == 1 && lage == 1)
		{_delay_ms(200); play_15; stop();}

		if (B1 == 2 && lage == 1)
		{_delay_ms(200); play_2; stop();}

		if (B1 == 3 && lage == 1)
		{_delay_ms(200); play_3; stop();}

		if (B1 == 4 && lage == 1)
		{_delay_ms(200);  play_4; stop(); B1=0;}
		//**********Läge2************
		if (B1 == 1 && lage == 2)
		{_delay_ms(200); play_5; stop();}

		if (B1 == 2 && lage == 2)
		{_delay_ms(200); play_6; stop();}

		if (B1 == 3 && lage == 2)
		{_delay_ms(200); play_7; stop();}

		if (B1 == 4 && lage == 2)
		{ _delay_ms(200); play_8; stop(); B1=0;}
		//**********Läge3************
		if (B1 == 1 && lage == 3)
		{_delay_ms(200); play_9; stop();}

		if (B1 == 2 && lage == 3)
		{_delay_ms(200); play_10; stop();}

		if (B1 == 3 && lage == 3)
		{_delay_ms(200); play_12; stop();}

		if (B1 == 4 && lage == 3)
		{ _delay_ms(200); play_13; stop();B1=0;}
		//**********Läge4************
		if (B1 == 1 && lage == 4)
		{_delay_ms(200); play_13; stop();}

		if (B1 == 2 && lage == 4)
		{_delay_ms(200); play_14; stop();}

		if (B1 == 3 && lage == 4)
		{_delay_ms(200); play_15; stop();}

		if (B1 == 4 && lage == 4)
		{ _delay_ms(200); play_16; stop();B1=0;}
	}
	//::::::::::::::::::::::::::::::::::::::::::::::::
	if (bit_is_clear(PINB, PINB7))
	{ 	  	led++;
		
		//seconds++; 	ledpwm_OFF(); return;
		if (led == 5)
		{	_delay_ms(5);
			//ledpwm_OFF();
			setup();   /**/
			led = 0;
			pwmOn = 0;
			stop();
			_delay_ms(5);
			play_9; stop();
			_delay_ms(1500);
			//POWER SAVE
			TpowerON();  // turn Power on DiyPlayer ON
			sleep_enable();
			sei();
			sleep_cpu();
			sleep_disable();
			
			
		}

		_delay_ms(300);
		if (bit_is_clear(PINB, PINB7))
		{	// led--;	led--;
			if (loud == 1 && bit_is_clear(PINB, PINB7))
			{
				blink();
				mcp4013_init_low();
				_delay_ms(500);
				loud = 0;	
			}
			
			if (loud == 0 && bit_is_clear(PINB, PINB7))
			{	 blink();
				mcp4013_init_high();
				_delay_ms(500);
				loud =1;	
			}
			//stop();
		}

		
	}
  
}

//******************************************************
int main(void)
{
	
	setup();
	TpowerOff();  // turn Power on DiyPlayer ON
	initTimer1();
	initPinChangeInterrupt4();
	mcp4013_init_high();
	//mcp4013_set(10);
	toggle = 1;
	
	while (1)
	{
		 			
		
		/*_delay_ms(2000); */	
		
		if (TIFR & (1 << OCF1A))
		{  // count reached?
		TIFR |= (1 << OCF1A);   // clear flag
		if (toggle)
		{           // toggle LED
		
		count++;
		PORTB ^=(1<<PINB2);	 PORTB ^=(1<<PINB3);  PORTB ^=(1<<PINB4);
		if(count==TotalTime)
		{		   
		count=0;
		stop();
		_delay_ms(5);
		play_9; stop();
		_delay_ms(500);
		 // turn Power on DiyPlayer off
		PORTB |=(1<<PINB2);
		PORTB |=(1<<PINB3);
		PORTB |=(1<<PINB4);
		_delay_ms(300);
		PORTB &=~(1<<PINB2);
		PORTB &=~(1<<PINB3);
		PORTB &=~(1<<PINB4);
		_delay_ms(5);
		//POWER SAVE
		// TpowerON();   turn Power on DiyPlayer ON
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();
		////////sleep_mode();
		}
		
		}
		}		/* */
		//****************************LEDs*******************************
		if (led == 1)
		{
		PORTB |= (1 << PB3);
		PORTB &= ~(1 << PB2);
		PORTB &= ~(1 << PB4);
		
		//sleepLoop();
		}
		if (led == 2)
		{
		PORTB |= (1 << PB2);
		PORTB &= ~(1 << PB3);
		PORTB &= ~(1 << PB4);
		//sleepLoop();
		}

		if (led == 3)
		{
		PORTB |= (1 << PB4);
		PORTB &= ~(1 << PB2);
		PORTB &= ~(1 << PB3);
		//sleepLoop();
		}
		
		if (led == 4)
		{	
			pwmOn = 1;
		ledpwm();
		sleep();
		}
	
		
		
		}
		}


		//		_delay_ms(200);     _delay_ms(40500);		  delay_ms(20200);		play_3;break;stop(); break;	play_1;	continue;stop();