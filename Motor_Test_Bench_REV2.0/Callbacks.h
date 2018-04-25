/*
 * Callbacks.h
 *
 * Created: 22-09-16 11:24:22
 *  Author: Laurent Chevalier
 */ 


#ifndef CALLBACKS_H_
#define CALLBACKS_H_


// DEFINE
#define MAX_CALLBACKS 10
#define MAX_BUFFER 20
// PROTOTYPE DES FONCTIONS EXTERNES
//INITIALISATION DES CALLBACKS
void Callbacks_Init(void) ;
//ENREGISTRER DES FONCTIONS CALLBACKS LIEES AU TEMPS
// RETOURNE UN ID ASSOCIE A L’ENREGISTREMENT
unsigned char Callbacks_Record_Timer(void(*pt_Function)(void), unsigned int Time);
// RETIRER DES FONCTIONS CALLBACKS LIEES AU TEMPS, PREND L’ID DU CALLBACK
// COMME ARGUMENT
void Callbacks_Remove_Timer(unsigned char ID_CB) ;
//DEMARRAGE DE LA BOUCLE PRINCIPALE
void callbacks_Start(void) ;
// CALL BACK USART
void Callbacks_Record_USART(void(*pt_USART)(volatile char*));
// CALL BACK Button
//void Callbacks_Record_Button(void(*ptButton)(char));






#endif /* CALLBACKS_H_ */