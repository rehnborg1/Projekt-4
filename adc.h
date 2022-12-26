/********************************************************************************
* adc.h: Inneh�ller funktionalitet f�r enkel implementering av AD-omvandling
*        f�r analoga signaler via strukten adc. AD-omvandling sker via inl�sning
*        av signaler fr�n analoga pinnar A0 - A5 p�  Arduino Uno, vilket
*        motsvarar PORTC0 - PORTC5 p� ATmega328P.
*
*        Analoga insignaler mellan 0 - 5 V AD-omvandlas till digitala
*        motsvarigheter mellan 0 - 1023. Duty cycle kan anv�ndas f�r
*        PWM-generering och ber�knas enligt nedan:
*
*                       duty cycle = ADC_result / ADC_MAX,
*
*       d�r ADC_result �r resultat avl�st fr�n AD-omvandlaren OCH ADC_MAX
*       utg�r h�gsta m�jliga avl�sta v�rde, vilket �r 1023.0.
********************************************************************************/
#ifndef ADC_H_
#define ADC_H_

/* Inkluderingsdirektiv: */
#include "misc.h"

/* Makrodefinitioner: */
#define ADC_MAX 1023.0 /* H�gsta digitala v�rde vid AD-omvandling (motsvarar 5 V). */

/********************************************************************************
* adc: Strukt f�r implementering av AD-omvandlare, som m�jligg�r avl�sning
*      av insignaler fr�n analoga pinnar samt ber�kning av on- och off-tid f�r
*      PWM-generering (tiden som PWM-styrd utsignal ska vara h�g respektive l�g).
********************************************************************************/
struct adc
{
	uint8_t pin;         /* Analog pin som ska anv�ndas f�r avl�sning. */
	uint16_t pwm_on_us;  /* On-tid f�r PWM-generering i mikrosekunder. */
	uint16_t pwm_off_us; /* Off-tid f�r PWM-generering i mikrosekunder. */
};

/********************************************************************************
* adc_init: Initierar analog pin f�r avl�sning och AD-omvandling av insignaler,
*           som antingen kan anges som ett tal mellan 0 - 5 eller via konstanter
*           A0 - A5 (som motsvarar heltal 14 - 19).
*
*           - self: Pekare till analog pin som ska anv�ndas f�r AD-omvandling.
*           - pin : Analog pin som ska l�sas f�r AD-omvandling.
********************************************************************************/
void adc_init(struct adc* self,
const uint8_t pin);

/********************************************************************************
* adc_read: L�ser av en analog insignal och returnerar motsvarande digitala
*           motsvarighet mellan 0 - 1023.
*
*           - self: Pekare till analog pin vars insignal ska AD-omvandlas.
********************************************************************************/
uint16_t adc_read(const struct adc* self);

/********************************************************************************
* adc_duty_cycle: L�ser av en analog insignal och returnerar motsvarande
*                 duty cycle som ett flyttal mellan 0 - 1.
*
*                 - self: Pekare till analog pin vars insignal ska AD-omvandlas.
********************************************************************************/
double adc_duty_cycle(const struct adc* self);

/********************************************************************************
* adc_get_pwm_values: L�ser av en analog insignal och ber�knar on- och off-tid
*                     f�r PWM-generering, avrundat till n�rmaste heltal.
*
*                     - self         : Pekare till analog pin som ska l�sas av.
*                     - pwm_period_us: PWM-perioden (on-tid + off-tid) m�tt i
*                                      mikrosekunder (default = 10 000 us).
********************************************************************************/
void adc_get_pwm_values(struct adc* self,
uint16_t pwm_period_us);

#endif /* ADC_H_ */