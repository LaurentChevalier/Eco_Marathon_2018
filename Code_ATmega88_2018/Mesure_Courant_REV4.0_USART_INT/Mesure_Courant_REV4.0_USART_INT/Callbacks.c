/*
 * Callbacks.c
 *
 * Created: 22-09-16 11:24:50
 *  Author: Laurent Chevalier
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#include "Callbacks.h"
#include "TIMERS.h"
#include "Main.h"
#include "USART.h"

// VARIABLES GLOBALES
unsigned char tmp_int; // pour l'interruption du timer
// VARIABLES POUR CALLBACKS TIMER
void (*My_CB[MAX_CALLBACKS])(void);
void (*My_CB_USART)(volatile char*);
void (*My_Button)(char);
unsigned int Time_CB[MAX_CALLBACKS];
unsigned int TICK_CB[MAX_CALLBACKS];

extern volatile unsigned char nombre_appuis_bouton;
volatile char buffer [MAX_BUFFER];
volatile unsigned char emplacement = 0;
volatile unsigned char USART_RECEPT = FALSE;
//char Button = NONE;
extern volatile int resultat_ADC;
volatile unsigned char adclow;
volatile unsigned char adchigh;
// DECLARATION DES FONCTIONS INTERNES


// CONTENU DES FONCTIONS EXTERNES
void Callbacks_Init(void)
{
	unsigned char i ;
	// INITIALISATION POUR VARIABLES CALLBACKS TIMER
	for (i = 0 ; i < MAX_CALLBACKS; i++)
	{
		My_CB[i] = 0;
		Time_CB[i] = 0; // Pas obligatoire
	}
	// INITIALISATION DU LCD
	// CONFIGURATION USART POUR INTERRUPTION RD
}
// ENREGISTREMENT CALLBACKS TIMER
unsigned char Callbacks_Record_Timer(void(*pt_Function)(void), unsigned int Time)
{
	unsigned int i = 0;
	while (My_CB[i] != 0 && i < MAX_CALLBACKS) i++;
	if (i < MAX_CALLBACKS)
	{
		My_CB[i] = pt_Function;
		Time_CB[i] = Time;
		TICK_CB[i]= 0;
		return i;
	}
	// IL N’Y A PLUS DE PLACE POUR ENREGISTRER UN CALLBACK
	else return 255;
}

//Création callback USART
void Callbacks_Record_USART(void(*pt_USART)(volatile char*))
{
	My_CB_USART = pt_USART;
}

//Callback BUTTON
/*void Callbacks_Record_Button(void(*ptButton)(char)){
	My_Button = ptButton;
}*/

// RETIRER FONCTION DE RAPPEL
void Callbacks_Remove_Timer(unsigned char ID_CB)
{
	if (ID_CB >= 0 && ID_CB < MAX_CALLBACKS);
	{
		My_CB[ID_CB] = 0;
		Time_CB[ID_CB] = 0;
	}
}

// BOUCLE PRINCIPALE DE L’OS
void callbacks_Start(void)
{
	unsigned char idx;
	// INITIALISATION DE TOUTES LES INTERRUPTIONS
	/* initialise Interruptions */

	sei();
	// CONFIGURATION TIMER
	TIMER0_Init_1ms() ;
	// BOUCLE INFINIE
	while (1)
	{

		// CHECK LES CONDITIONS POUR RAPPELER LES FONCTIONS LIEES AUTEMPS
		for (idx = 0 ; idx < MAX_CALLBACKS; idx++)
		{
			if (My_CB[idx])if (TICK_CB[idx] >= Time_CB[idx])
			{
				TICK_CB[idx] = 0;
				My_CB[idx]();
			}
		}

		if (USART_RECEPT==TRUE) //&& My_CB_USART) // à mettre en commentaire pour que ça fonctionne sur la carte
		{
			USART_RECEPT=FALSE;
			//My_CB_USART(buffer); // Fonctionne en simulation
			Affichage_usart(buffer); // à mettre pour que ça fonctionne avec la carte

		}
		//if(Button != NONE)
		//Button_work(Button);
	}
}
// CONTENU DES FONCTIONS INTERNES
// INTERRUPTIONS

// INTERRUPTION TIMER

//Interruption TIMER1
ISR(TIMER1_COMPA_vect)
{

	for ( tmp_int = 0 ; tmp_int < MAX_CALLBACKS; tmp_int++) TICK_CB[tmp_int]++;

}

// Interruption sur la reception en USART
ISR(USART_RX_vect)
{
	buffer[emplacement]=UDR0;

	if(buffer[emplacement]==0 ||buffer[emplacement]=='\r')
	{
		buffer[emplacement]= 0;
		USART_RECEPT=TRUE;
		emplacement=0;
		Usart_Tx('\r');
		Usart_Tx('>');
		Usart_String(buffer);
		Usart_Tx('\r');
	}
	/*else if(emplacement>=MAX_BUFFER)
	{
		emplacement=0;
	}*/
	else
	{
		emplacement++;
	}

}


// Interruption de fin de conversion

ISR (ADC_vect){

	adclow = ADCL ;
	adchigh = ADCH ;

	resultat_ADC = (adchigh << 8); // Décalage des bits présents dans ADCH de 8 vers la gauche
	resultat_ADC = resultat_ADC | (unsigned int)adclow; // ou bit à bit en entre resultat_ADC qui contient les 8 bits de MSB et ADCL qui contient les 8 bits de LSB

}
