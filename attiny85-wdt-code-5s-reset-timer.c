/*  Waits for pin change interrupt on ATtiny85. If this does not
 *  happen then the waspmote reboots.
 *  Created:	09-Jul-13 10:28:46 AM
 *  Author:	R.Aspey
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t watchdogCounter ;
volatile uint8_t powerRstCounter ;

void	 eventFlashLED(void)
{	// volatile uint8_t i;
	watchdogCounter = 0;
	/* for (i=0;i<10;i++)
		{	PORTB ^= 0x08;
			_delay_ms(50);
		} */
}

void	tristate(void)
{	DDRB = 0x00;	

	// Set all to inputs briefly
	
	_delay_ms(2000);
	DDRB  = 0xF8;
	PORTB = 0xFF;
	
}

void	Init(void)
{	PCMSK |= (1<<PCINT1);   
	
	// pin change mask: listen to portb bit 2
	
	PCMSK |= (1<<PCINT0);
	GIMSK |= (1<<PCIE);		
	
	// enable PCINT interrupt
	// sei();				
	// enable all interrupts
	// GIMSK = 0x20 ;		
	// _BV(PCINT0); // enable external int0
	// MCUCR = 0	 ;		
	// falling edge: int0
	
	sei();
}

ISR(PCINT0_vect)	// Pin change interrupt..
{	
	// eventFlashLED();
	
	watchdogCounter = 0;
	powerRstCounter = 0;
	MCUSR = 0x00;
}

int	main(void)
{	DDRB = 0xF8;
		
	watchdogCounter = 0;
	powerRstCounter = 0;
	Init();

	while(1)
		{   sei() ;
		if (++watchdogCounter > 5)
			{	PORTB  = 0x10 ;	
				// Was -0x08 ;
				watchdogCounter = 0;
			}
		else 
			{	PORTB = 0x18 ;	
				// Was -0x00 ;
			}
		if (++powerRstCounter > 60)
			{	PORTB  = 0x00;		
				// Reset both processor and power
				powerRstCounter = 0;
				tristate();
			}
		_delay_ms(1000) ;
		}
}

