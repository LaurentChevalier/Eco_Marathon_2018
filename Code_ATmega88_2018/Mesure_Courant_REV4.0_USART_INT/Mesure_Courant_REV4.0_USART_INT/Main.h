// Main.h

#ifndef _main_h_
#define _main_h_

// DEFINE 

// Gestion registre par bit unique
#define sbiBF(port,bit)  (port |= (1<<bit))   //set bit in port
#define cbiBF(port,bit)  (port &= ~(1<<bit))  //clear bit in port


#define TRUE				1
#define FALSE				0

void hardware_Init(void) ;
void Affichage_usart(volatile char*);

#endif /* _main.h */
