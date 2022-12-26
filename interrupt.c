/********************************************************************************
interrupts.c: Definerar avbrott för knapp och timerkretsar.
********************************************************************************/
#include "header.h"

/********************************************************************************
ISR (PCINT0_vect): Avbrott för knapp samt rebounce.
********************************************************************************/
ISR (PCINT0_vect)
{
	disable_pin_change_interrupt(IO_PORTB);		/* Inaktiverar PCI avbrott på kanppens io-port 
												  för skydd mot rebounce. */
	
	timer_enable_interrupt(&t0);				/* Startar timerkrets för rebounce. */
	
	if (button_is_pressed(&b1))
	{
		tmp36_print_temperature(&temp1);		/* Skriver temperaturen. */
		
		timer_reset_counter(&t1);				/* Startar om tiden i timern som skriver ut temperaturen. */
		
	}
	
	return;
}


/********************************************************************************
ISR (TIMER0_OVF_vect): Avbrott för timern för rebounce
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	timer_count(&t0);							/* Räknar upp timern. */
	
	if (timer_elapsed(&t0))						/* Kollar om timern har löpt ut. */
	{
		enable_pin_change_interrupt(IO_PORTB);	/* Återställer avbrott för knappen. */
		
		timer_disable_interrupt(&t0);			/* Stänger av avbrotten för timern. */
	}
	
	return;
}

/********************************************************************************
ISR (TIMER1_COMPA_vect): Avbrott för timern för utskrift av temperatur
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	timer_count(&t1);						/* Räknar upp timern.*/
	
	if (timer_elapsed(&t1))					/* Kollar om timern löpt ut. */
	{
		tmp36_print_temperature(&temp1);	/* Skriver ut temperaturen. */
	}
	
	return;
}