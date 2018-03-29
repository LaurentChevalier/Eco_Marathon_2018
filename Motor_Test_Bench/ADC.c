//FONCTIONS ADC


//INCLUDE

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Main.h"



//DECLARATION DES VARIABLES GLOGALES


//PROTOTYPE FONCTIONS INTERNES


//CONTENU FONCTIONS EXTERNES

void Init_ADC(void)
{
	ADMUX = 0b01000000; //on prend AVCC comme reference et justification à droite (mode 10bits) et ADC0 comme entrée
	ADCSRA = 0b10001100;  //freq à 1MHz/16==>62.500kHz et activation de l'interruption de fin de conversion
	ADCSRB = 0b00000000;

}


