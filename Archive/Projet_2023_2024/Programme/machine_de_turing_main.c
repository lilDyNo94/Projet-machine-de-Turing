/**
 * @file    machine_de _turing_main.c
 * @author 	Romain BROUARD
 * @date	2024/05
 * @brief 	main programm of the machine de turing project
 *  
 *
 */
#include "machine_de_turing_main.h"

/*--------------------------------------------------------------------------*/
/* PIC24FJ64GA002                                   						*/
/*--------------------------------------------------------------------------*/
#pragma config 	POSCMOD = NONE // 	Primary Oscillator Select (EC, XT, HS, NONE)
#pragma config	I2C1SEL = PRI	//	Alternate I2C1 Pin Mapping bit (PRI, SEC)
#pragma config  IOL1WAY = OFF
#pragma config  OSCIOFNC = ON
#pragma config	FCKSM = CSDCMD	//	Clock Switching and Monitor Selection (CSECME, CSECMD, CSDCMD)
#pragma config 	FNOSC = FRCPLL   // 	Oscillator Select (FRC, FRCPLL, PRI, PRIPLL, SOSC, LPRC, LPFRC, FRCDIV)
#pragma config  SOSCSEL = SOSC
#pragma config  WUTSEL = LEG
#pragma config  IESO = OFF
#pragma config	FWDTEN = OFF	//	Watchdog Timer Enable bits	
#pragma config	WINDIS = OFF	//	(ON, OFF)
#pragma config	FWPSA = PR32	//	WDT Prescaler bit (PR32, PR128)
#pragma config	WDTPS = PS2	//	Watchdog Timer Postscale Select bits
#pragma config	ICS = PGx1		//	ICD Pin Placement Select bits (PGx1, PGx2, PGx3)
#pragma config  BKBUG = OFF
#pragma config	GWRP = OFF          //	(ON, OFF)
#pragma config	GCP = OFF           //	(ON, OFF)
#pragma config  JTAGEN = OFF

/* Directives de compilation - Macros		*/

/* Déclarations des variables globales 	*/

/* Programme Principal			*/
int main(void){
    
    Initialiser();
    while(1) {
        MainTask();
    }
}
