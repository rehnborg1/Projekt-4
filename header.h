/********************************************************************************
* header.h: Innehåller globala objekt och deklarationer för implementering av
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
* setup: Initierar det inbyggda systemet. Lysdioder initieras på pin 8 - 9,
*        tryckknappar initieras med aktiverade PCI-avbrott på pin 12 - 13
*        och samtliga timerkretsar konfigureras, där timer 0 sätts till att
*        löpa ut efter 300 ms (för att temporärt inaktivera PCI-avbrott på
*        I/O-port B efter nedtryckning för att undvika multipla avbrott orsakat
*        av kontaktstudsar, medan timer 1 - 2 sätts till att löpa ut efter
*        100 ms (för blinkning via toggling av lysdioder).
********************************************************************************/
void setup(void);

#endif /* HEADER_H_ */