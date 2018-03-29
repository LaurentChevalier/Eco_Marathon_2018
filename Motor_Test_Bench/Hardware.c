/*
 * Hardware.c
 *
 * Created: 17-02-17 23:30:52
 *  Author: laurent
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include "Hardware.h"

void hardware_Init(void) {
	/* initialise Port Sortie */
	
	DDRD |=(1<<DDD1); //On initialise les bits 7 et 6 du DDRD à 1 pour les définir en output
	DDRB |=(1<<DDB3)|(1<<DDB4); // On initialise les bits 3 et 4 du DDRB en output (3 la led et 4 le relais)
	PORTB |=(1<<PB3)|(1<<PB4);
	// Configuration de l'interruption
	
	EICRA |= (1<<ISC01); //set bit ISC01 in EICRA // interruption sur flanc descendant de INTO
	EIMSK |= (1<<INT0); //set bit in port EIMSK // activation de l'interruption sur INT0
	
	DDRC = (0<<DDC0);
	
}