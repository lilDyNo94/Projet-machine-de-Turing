#ifndef LIB_TURING_H
#define LIB_TURING_H

#ifndef FCY
#define FCY 4000000UL // Frequence de travail a 4 MHz
#endif

#include <xc.h>
#include <libpic30.h> 
#include <stdint.h>

// ---------------------------------------------------------
// DEFINITION DES TESTS DU PROJET 
// ---------------------------------------------------------
#define TEST_BOUTONS            1
#define TEST_COMMUTATEUR        2
#define TEST_LCD                3
#define TEST_MATRICE            4   
#define TEST_MATRICE_BOUTONS    5   
#define TEST_MACHINE_TURING     7   

// =========================================================
// CHOIX DU TEST A EXECUTER
// =========================================================
#define CURRENT_TEST    TEST_MACHINE_TURING

// ---------------------------------------------------------
// MAPPAGE MATERIEL
// ---------------------------------------------------------

// Mappage de la broche CS (Pin 26)
#define MATRICE_CS_LAT      LATBbits.LATB14
#define MATRICE_CS_TRIS     TRISBbits.TRISB14

// Mappage de la LED 
#define LED_TEST_LAT        LATBbits.LATB4
#define LED_TEST_TRIS       TRISBbits.TRISB4
#define LedOn()             {LED_TEST_LAT = 1;}
#define LedOff()            {LED_TEST_LAT = 0;}

// Mappage des boutons
#define BTN_UP              PORTAbits.RA0
#define BTN_DOWN            PORTAbits.RA1
#define BTN_SELECT          PORTAbits.RA4
#define BTN_START           PORTBbits.RB7

// Codes des couleurs (Format RGB332 - 1 Octet)
#define COULEUR_NOIR        0x00
#define COULEUR_ROUGE       0xE0 // Pour le bit '0'
#define COULEUR_VERT        0x1C // Pour le bit '1'
#define COULEUR_BLEU        0x03 // Pour le curseur
#define COULEUR_BLANC       0xFF 

// Prototypes des fonctions communes
void Turing_Init(void);
void Turing_Task(void);

// Prototypes specifiques aux differents tests
#if (CURRENT_TEST == TEST_MATRICE)
void SPI_Init(void);
void SPI_Write(uint8_t data);
void Matrix_Fill(uint8_t color);
#elif (CURRENT_TEST == TEST_MATRICE_BOUTONS)
void SPI_Init(void);
void SPI_Write(uint8_t data);
void Matrix_Draw(void);
#elif (CURRENT_TEST == TEST_MACHINE_TURING)
void SPI_Init(void);
void SPI_Write(uint8_t data);
void Matrix_Draw(int *bande, int curseur);
#endif

#endif /* LIB_TURING_H */