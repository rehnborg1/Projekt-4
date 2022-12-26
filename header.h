/********************************************************************************
* header.h: Inneh�ller globala objekt och deklarationer f�r implementering av
*           det inbyggda systemet.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Inkluderingsdirektiv: */
#include "button.h"
#include "timer.h"
#include "tmp36.h"

/* Deklaration av globala objekt: */

 /* Tryckknapp. */
extern struct button b1;

/* Timerkretsar. */
extern struct timer t0, t1;

 /*Temperatursensor. */
extern struct tmp36 temp1; 

/********************************************************************************
* setup: Initierar det inbyggda systemet. Lysdioder initieras p� pin 8 - 9,
*        tryckknappar initieras med aktiverade PCI-avbrott p� pin 12 - 13
*        och samtliga timerkretsar konfigureras, d�r timer 0 s�tts till att
*        l�pa ut efter 300 ms (f�r att tempor�rt inaktivera PCI-avbrott p�
*        I/O-port B efter nedtryckning f�r att undvika multipla avbrott orsakat
*        av kontaktstudsar, medan timer 1 - 2 s�tts till att l�pa ut efter
*        100 ms (f�r blinkning via toggling av lysdioder).
********************************************************************************/
void setup(void);

#endif /* HEADER_H_ */