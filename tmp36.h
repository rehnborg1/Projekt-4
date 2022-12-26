/********************************************************************************
* tmp36.h: Inneh�ller drivrutiner f�r temperatursensor TMP36, som anv�nds f�r
*          m�tning samt utskrift av rumstemperaturen. Den analoga insignalen
*          fr�n TMP36 AD-omvandlas till en digital motsvarighet, som anv�nds
*          f�r att ber�kna aktuell temperatur. Utskrift sker till en seriell
*          terminal via USART.
********************************************************************************/
#ifndef TMP36_H_
#define TMP36_H_

#include "adc.h"
#include "serial.h"

/********************************************************************************
* tmp36: Strukt f�r implementering av temperatursensor TMP36, som anv�nds f�r
*        m�tning samt utskrift av rumstemperaturen. Vid avl�sning AD-omvandlas
*        den analoga insignalen till en digital motsvarighet. Utefter detta
*        v�rde ber�knas den analoga insp�nningen Uin via nedanst�ende formel:
*
*        Uin = ADC_result / ADC_MAX * Vcc,
*
*        d�r ADC_result �r den AD-omvandlade insignalen (0 - 1023),
*        ADC_MAX �r h�gsta m�jliga digitala signal (1023) och Vcc �r
*        mikrodatorns matningssp�nning (5 V).
*
*        Temperaturen T ber�knas utefter detta v�rde via nedanst�ende formel:
*
*        T = 100 * Uin - 50,
*
*        d�r Uin utg�r analog insp�nning avl�st fr�n temperatursensor TMP36.
********************************************************************************/
struct tmp36
{
	struct adc input; /* AD-omvandlare, omvandlar analog insignal fr�n TMP36. */
};

/********************************************************************************
* tmp36_init: Initierar pin ansluten till temperatursensor TMP36 f�r m�tning
*             samt utskrift av rumstemperaturen. Seriell �verf�ring initieras
*             ocks� med en baud rate (�verf�ringshastighet) p� 9600 kbps.
*
*             - self: Pekare till temperatursensorn som ska initieras.
*             - pin : Analog pin A0 - A5 som temperatursensorn �r ansluten till.
********************************************************************************/
static inline void tmp36_init(struct tmp36* self,
const uint8_t pin)
{
	adc_init(&self->input, pin);
	serial_init(9600);
	return;
}

/********************************************************************************
* tmp36_get_temperature: Returnerar aktuell rumstemperatur via avl�sning av
*                        angiven temperatursensor TMP36.
*
*                        - self: Pekare till temperatursensor TMP36.
********************************************************************************/
static inline double tmp36_get_temperature(const struct tmp36* self)
{
	const double voltage = adc_read(&self->input) / 1023.0 * 5;
	return 100 * voltage - 50;
}

/********************************************************************************
* tmp36_print_temperature: Skriver ut aktuell rumstemperatur avl�st av
*                          temperatursensor TMP36.
*
*                          - self: Pekare till temperatursensor TMP36.
********************************************************************************/
static inline void tmp36_print_temperature(const struct tmp36* self)
{
	serial_print_string("Temperature: ");
	serial_print_double(tmp36_get_temperature(self));
	serial_print_string(" degrees Celcius!\n");
	return;
}

#endif /* TMP36_H_ */