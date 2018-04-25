//Projet Eco-Marathon-Banc_de_test_moteur
// Auteur: Laurent Chevalier 
// Année académique 2017-2018

// INCLUDE

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>


#include "Main.h"
#include "TIMERS.h"
#include "USART.h"
#include "Callbacks.h"
#include "ADC.h"
#include "Hardware.h"

//****************** fonction principale *****************
// VARIABLES GLOBALES
unsigned char ID_Envoi_USART;
unsigned char ID_Adc1s;
unsigned char ID_Adc2s;
unsigned char ID_Adc3s;
unsigned char ID_Interrupt_Speed;
volatile unsigned char nombre_appuis_bouton;
volatile int resultat_ADC;
volatile int Tension;
volatile int Courant_Moteur;
volatile int Couple_Moteur;
extern volatile int rpmcount;
int rpm = 0;
unsigned char etat;
unsigned char etat_center;
//char Button1 = NONE;
char String_Tension[5];
char Buffer[5];
char String_Courant_Moteur[5];
char String_RPM[5];
char String_Couple_Moteur[5];
char *Test_USART;
char trame2[16];
char i;



// FONCTIONS DONT ON PASSE LES ADRESSES A callbacks.c POUR QU’ELLES PUISSENT
// ÊTRE RAPPELEES TOUTES LES X MS
void Envoi_USART(void) ;
void Adc1s(void);
void Adc2s(void);
void Adc3s(void);
void Interrupt_Speed(void);

// FONCTION PRINCIPALE
int main(void)
{
	// INITIALISATION HARDWARE
	hardware_Init() ;
	// Configuration de l'usart
	USART_Init_9600();
	// Configuration de l'ADC
	Init_ADC();
	//INITIALISATION CALLBACKS
	Callbacks_Init() ;
	ID_Envoi_USART = Callbacks_Record_Timer(Envoi_USART, 1000) ; //(Mettre 1000 pour avoir 500ms) 
	ID_Adc1s = Callbacks_Record_Timer(Adc1s, 200);
	ID_Adc2s = Callbacks_Record_Timer(Adc2s, 200);
	ID_Adc3s = Callbacks_Record_Timer(Adc3s, 200);
	ID_Interrupt_Speed = Callbacks_Record_Timer(Interrupt_Speed, 2000);
	callbacks_Start();
	//INITIALISATION LCD
	Callbacks_Record_USART(Affichage_usart);
	// N’ARRIVE JAMAIS ICI
}
// CONTENU DES FONCTIONS CALLBACKS
void Envoi_USART(void)
{
	char mesures[21]; //33//13
	//strcpy(mesures,"U");
	strcat(mesures,String_Tension);
	//strcat(mesures,";IM");
	strcat(mesures,String_Courant_Moteur);//
	//strcat(mesures,";RPM");
	strcat(mesures,String_RPM);
	//strcat(mesures,";Nm");
	strcat(mesures,String_Couple_Moteur);
	//strcat(mesures,"\n");
	Usart_String(mesures);
	}


void Affichage_usart(volatile char *Trame)
{
	
}


void Adc1s(void)
{
	ADMUX = 0b01000001;//Attention logique inversée 
	ADCSRA |=(1<<ADSC);
	Tension = resultat_ADC;
	for(int i=0;i<5;i++){
		String_Tension[i]=0;
	}
	itoa(Tension, String_Tension, 10);
	if(Tension<10)
	{
		strcpy(Buffer,"000");
		strcat(Buffer,String_Tension);
		strcpy(String_Tension,Buffer);
	}
	else if(Tension>=10 && Tension<100)
	{
		strcpy(Buffer,"00");
		strcat(Buffer,String_Tension);
		strcpy(String_Tension,Buffer);
	}
	else if(Tension>=100 && Tension<1000)
	{
		strcpy(Buffer,"0");
		strcat(Buffer,String_Tension);
		strcpy(String_Tension,Buffer);
	}
	else
	{
		
	}
	
}
void Adc2s(void)
{
	ADMUX = 0b01000010;//Attention logique inversée (idem)
	ADCSRA |=(1<<ADSC);
	Courant_Moteur = resultat_ADC;
	for(int i=0;i<5;i++){
		String_Courant_Moteur[i]=0;
	}
	itoa(Courant_Moteur, String_Courant_Moteur, 10);
	if(Courant_Moteur<10)
	{
		strcpy(Buffer,"000");
		strcat(Buffer,String_Courant_Moteur);
		strcpy(String_Courant_Moteur,Buffer);
	}
	else if(Courant_Moteur>=10 && Courant_Moteur<100)
	{
		strcpy(Buffer,"00");
		strcat(Buffer,String_Courant_Moteur);
		strcpy(String_Courant_Moteur,Buffer);
	}
	else if(Courant_Moteur>=100 && Courant_Moteur<1000)
	{
		strcpy(Buffer,"0");
		strcat(Buffer,String_Courant_Moteur);
		strcpy(String_Courant_Moteur,Buffer);
	}
	else
	{
		
	}
}

void Adc3s(void)
{
	ADMUX = 0b01000000;//Attention logique inversée (idem)
	ADCSRA |=(1<<ADSC);
	Couple_Moteur = resultat_ADC;
	for(int i=0;i<5;i++){
		String_Couple_Moteur[i]=0;
	}
	itoa(Couple_Moteur, String_Couple_Moteur, 10);
	if(Couple_Moteur<10)
	{
		strcpy(Buffer,"000");
		strcat(Buffer,String_Couple_Moteur);
		strcpy(String_Couple_Moteur,Buffer);
	}
	else if(Couple_Moteur>=10 && Couple_Moteur<100)
	{
		strcpy(Buffer,"00");
		strcat(Buffer,String_Couple_Moteur);
		strcpy(String_Couple_Moteur,Buffer);
	}
	else if(Couple_Moteur>=100 && Couple_Moteur<1000)
	{
		strcpy(Buffer,"0");
		strcat(Buffer,String_Couple_Moteur);
		strcpy(String_Couple_Moteur,Buffer);
	}
	else
	{
		
	}
}

void Interrupt_Speed(void)
{
	//Desable interrupt int0
	EIMSK = (0<<INT0); //set bit in port EIMSK // désactivation de l'interruption sur INT0
	rpm = rpmcount * 15; /* Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use rpmcount * 30.*/
	for(int i=0;i<5;i++){
		String_RPM[i]=0;
	}
	itoa(rpm, String_RPM, 10);
	if(rpm<10)
	{
		strcpy(Buffer,"000");
		strcat(Buffer,String_RPM);
		strcpy(String_RPM,Buffer);
	}
	else if(rpm>=10 && rpm<100)
	{
		strcpy(Buffer,"00");
		strcat(Buffer,String_RPM);
		strcpy(String_RPM,Buffer);
	}
	else if(rpm>=100 && rpm<1000)
	{
		strcpy(Buffer,"0");
		strcat(Buffer,String_RPM);
		strcpy(String_RPM,Buffer);
	}
	else
	{
		
	}
	
	rpmcount = 0; // Restart the RPM counter
	EIMSK |= (1<<INT0); //set bit in port EIMSK // réactivation de l'interruption sur INT0
}