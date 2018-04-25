//FONCTIONS USART


//INCLUDE
#include "USART.h"
#include "Main.h"
#include "TIMERS.h"

#include <avr/io.h>
#include <avr/interrupt.h>


//DECLARATION DES VARIABLES GLOGALES
int i=0;
//PROTOTYPE FONCTIONS INTERNES


//CONTENU FONCTIONS EXTERNES

void Usart_Tx(char data)
{
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0=data;
		

}



void Usart_String(char datastr[])
{

	int i=0;
	while(datastr[i]!=0){
		
		Usart_Tx(datastr[i]);
		i++;
	}

	
}

void USART_Init_9600(void)
{
	
	UBRR0L=0b00001100; //Baudrate = 9600bps
	UBRR0H=0b00000000;
	UCSR0A = 0b00100010; //receiver is ready to receive data, double speed
	UCSR0B = 0b10011000; //Activation de l'émetteur et activation de l'interruption sur la reception USART
	UCSR0C = 0b00000110; //Mode asynchrone, pas de bit de parité, 1 bit de stop, 8 bits de données
}


//CONTENU FONCTIONS INTERNES
