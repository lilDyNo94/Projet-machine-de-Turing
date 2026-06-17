#include "lib_turing.h"

// ==============================================================================
// TEST NUMERO 7 : MACHINE DE TURING COMPLETE (Saisie + Algorithme + Appui Long)
// ==============================================================================
#if (CURRENT_TEST == TEST_MACHINE_TURING)

#define TAILLE_ALPHABET 3

typedef enum { rien = 0, gauche = -1, droite = 1 } Deplacement;

struct action {
  int nv_char;
  Deplacement dep;
  int nv_etat;
};
typedef struct action Action;

struct etat {
    int final;
    Action transition[TAILLE_ALPHABET];
};
typedef struct etat Etat;

void action_create(Action *A, int a, Deplacement dep, int nv_etat) {
    if((a < TAILLE_ALPHABET) && (a >= 0)) {
        A->nv_char = a;
        A->dep = dep;
        A->nv_etat = nv_etat;
    }
}

// Variables globales du Test 7
Etat Etats_Turing[7];
int bande_turing[8] = {0,0,0,0,0,0,0,0}; // 0=Vide, 1=Vert(Bit 1), 2=Rouge(Bit 0)
int position_curseur = 0; 

// --- Config SPI ---
void SPI_Init(void) {
    SPI1STAT = 0; 
    TRISBbits.TRISB12 = 0; // MOSI 
    TRISBbits.TRISB13 = 0; // SCK 
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); 
    RPOR6bits.RP12R = 7; 
    RPOR6bits.RP13R = 8; 
    __builtin_write_OSCCONL(OSCCON | 0x40); 
    
    SPI1CON1bits.MSTEN = 1;   
    SPI1CON1bits.MODE16 = 0;  
    SPI1CON1bits.CKP = 0;     
    SPI1CON1bits.CKE = 1;     
    SPI1CON1bits.SMP = 0;     
    SPI1CON1bits.PPRE = 0b00;  
    SPI1CON1bits.SPRE = 0b111; 
    
    SPI1STATbits.SPIEN = 1;   
}

void SPI_Write(uint8_t data) {
    uint8_t donnee_recue;
    SPI1BUF = data;                     
    while(SPI1STATbits.SPIRBF == 0);    
    donnee_recue = SPI1BUF;             
}

// --- Dessin de l'ecran ---
void Matrix_Draw(int *bande, int curseur) {
    int i;
    MATRICE_CS_LAT = 0; 
    __delay_ms(1);
    SPI_Write(0x26);    
    __delay_ms(1);
    MATRICE_CS_LAT = 1; 
    
    __delay_ms(2); 
    MATRICE_CS_LAT = 0; 
    __delay_ms(1);      
    
    // Ligne 1 : Lecture du tableau de Turing
    for(i = 0; i < 8; i++) {
        if(bande[i] == 0)      SPI_Write(COULEUR_NOIR);
        else if(bande[i] == 1) SPI_Write(COULEUR_VERT);
        else if(bande[i] == 2) SPI_Write(COULEUR_ROUGE);
    }
    
    // Lignes 2 a 7 : Vides
    for(i = 8; i < 56; i++) {
        SPI_Write(COULEUR_NOIR); 
    }
    
    // Ligne 8 : Tete de lecture (Curseur Bleu)
    for(i = 56; i < 64; i++) {
        if((i - 56) == curseur) {
            SPI_Write(COULEUR_BLEU);
        } else {
            SPI_Write(COULEUR_NOIR);
        }
    }
    __delay_ms(1);      
    MATRICE_CS_LAT = 1; 
}

// ------- L'Algorithme d'addition ------
void Configurer_Algorithme_Addition(void) {
    
    // ETAT 0 
    Etats_Turing[0].final=0;
    action_create(&Etats_Turing[0].transition[2], 1, gauche, 1);     
    action_create(&Etats_Turing[0].transition[1], 2, gauche, 0); 
    action_create(&Etats_Turing[0].transition[0], 0, rien, 0);   

    // ETAT 1 
    Etats_Turing[1].final=0;
    action_create(&Etats_Turing[1].transition[2], 2, gauche, 1);   
    action_create(&Etats_Turing[1].transition[1], 1, gauche, 1); 
    action_create(&Etats_Turing[1].transition[0], 0, gauche, 2); 

    // ETAT 2 
    Etats_Turing[2].final=0;
    action_create(&Etats_Turing[2].transition[2], 1, droite, 3); 
    action_create(&Etats_Turing[2].transition[1], 2, gauche, 2); 
    action_create(&Etats_Turing[2].transition[0], 1, droite, 3); 

    // ETAT 3 
    Etats_Turing[3].final=0;
    action_create(&Etats_Turing[3].transition[2], 2, droite, 3);     
    action_create(&Etats_Turing[3].transition[1], 1, droite, 3); 
    action_create(&Etats_Turing[3].transition[0], 0, droite, 4); 

    // ETAT 4 
    Etats_Turing[4].final=0;
    action_create(&Etats_Turing[4].transition[2], 2, droite, 5);     
    action_create(&Etats_Turing[4].transition[1], 1, droite, 4); 
    action_create(&Etats_Turing[4].transition[0], 0, gauche, 0); 

    // ETAT 5 
    Etats_Turing[5].final=0;
    action_create(&Etats_Turing[5].transition[2], 2, droite, 5);    
    action_create(&Etats_Turing[5].transition[1], 1, droite, 5); 
    action_create(&Etats_Turing[5].transition[0], 0, gauche, 0); 
    
    // ETAT 6 
    Etats_Turing[6].final=1;
}

// --- Moteur de calcul ---
void Lancer_Calcul_Turing(void) {
    int etat_actuel = 0;
    int symbole_lu = 0;
    
    int a = 7;
    while((a >= 0) && (bande_turing[a] == 0)) {
        a--;
    }
    position_curseur = a; 
    
    while(Etats_Turing[etat_actuel].final != 1) {
        symbole_lu = bande_turing[position_curseur];
        
        bande_turing[position_curseur] = Etats_Turing[etat_actuel].transition[symbole_lu].nv_char;
        position_curseur += Etats_Turing[etat_actuel].transition[symbole_lu].dep;
        etat_actuel = Etats_Turing[etat_actuel].transition[symbole_lu].nv_etat;
        
        if(position_curseur < 0) position_curseur = 0;
        if(position_curseur > 7) position_curseur = 7;
        
        Matrix_Draw(bande_turing, position_curseur);
        __delay_ms(1500); 
    }
    
    Matrix_Draw(bande_turing, -1); 
    while(1); 
}

void Turing_Init(void) {
    AD1PCFG = 0xFFFF; 
    
    MATRICE_CS_TRIS = 0; 
    MATRICE_CS_LAT = 1; 
    SPI_Init(); 
    
    TRISAbits.TRISA0 = 1; 
    TRISAbits.TRISA1 = 1; 
    TRISAbits.TRISA4 = 1; 
    
    CNPU1bits.CN2PUE = 1;  
    CNPU1bits.CN3PUE = 1;  
    CNPU1bits.CN0PUE = 1;  
    
    Configurer_Algorithme_Addition();
    
    __delay_ms(3000); 
    Matrix_Draw(bande_turing, position_curseur);
}

void Turing_Task(void) {
    // Bouton DOWN (Droite)
    if (BTN_DOWN == 0) {
        if (position_curseur < 7) position_curseur++;
        else position_curseur = 0; 
        
        Matrix_Draw(bande_turing, position_curseur); 
        while(BTN_DOWN == 0); 
        __delay_ms(50); 
    }
    
    // Bouton UP (Gauche)
    else if (BTN_UP == 0) {
        if (position_curseur > 0) position_curseur--;
        else position_curseur = 7; 
        
        Matrix_Draw(bande_turing, position_curseur); 
        while(BTN_UP == 0); 
        __delay_ms(50); 
    }
    
    // Bouton SELECT (CLIC COURT = Couleur | APPUI LONG = Calcul)
    else if (BTN_SELECT == 0) {
        int temps_appui = 0;
        __delay_ms(50); // Anti-rebond
        
        while(BTN_SELECT == 0) {
            __delay_ms(50);
            temps_appui++;
            
            if (temps_appui > 20) {
                
                // --- BOUCLIER ANTI-PLANTAGE ---
                int bande_vide = 1;
                for(int k=0; k<8; k++) {
                    if(bande_turing[k] != 0) bande_vide = 0; 
                }
                
                if (bande_vide == 1) {

                    for(int clignote = 0; clignote < 3; clignote++) {
                        Matrix_Draw(bande_turing, -1); 
                        __delay_ms(150);
                        Matrix_Draw(bande_turing, position_curseur); 
                        __delay_ms(150);
                    }
                    while(BTN_SELECT == 0); 
                    return; 
                }
                // --------------------------------------------------------
                
                Matrix_Draw(bande_turing, -1); 
                __delay_ms(500);
                Lancer_Calcul_Turing(); 
            }
        }
        
        if(temps_appui > 0 && temps_appui <= 20) {
            if(bande_turing[position_curseur] == 0)      bande_turing[position_curseur] = 1;
            else if(bande_turing[position_curseur] == 1) bande_turing[position_curseur] = 2;
            else                                         bande_turing[position_curseur] = 0;
            
            Matrix_Draw(bande_turing, position_curseur); 
        }
        __delay_ms(50); 
    }
}
// ==============================================================================
// TEST NUMERO 4 : MATRICE SEULE (HISTORIQUE)
// ==============================================================================
#elif (CURRENT_TEST == TEST_MATRICE)

void SPI_Init(void) {
    SPI1STAT = 0; 
    TRISBbits.TRISB12 = 0; 
    TRISBbits.TRISB13 = 0; 
    __builtin_write_OSCCONL(OSCCON & 0xbf); 
    RPOR6bits.RP12R = 7; 
    RPOR6bits.RP13R = 8; 
    __builtin_write_OSCCONL(OSCCON | 0x40); 
    SPI1CON1bits.MSTEN = 1;   
    SPI1CON1bits.MODE16 = 0;  
    SPI1CON1bits.CKP = 0;     
    SPI1CON1bits.CKE = 1;     
    SPI1CON1bits.SMP = 0;     
    SPI1CON1bits.PPRE = 0b00;  
    SPI1CON1bits.SPRE = 0b111; 
    SPI1STATbits.SPIEN = 1;   
}

void SPI_Write(uint8_t data) {
    uint8_t donnee_recue;
    SPI1BUF = data;                     
    while(SPI1STATbits.SPIRBF == 0);    
    donnee_recue = SPI1BUF;             
}

void Matrix_Fill(uint8_t color) {
    int i;
    MATRICE_CS_LAT = 0; 
    __delay_ms(1);
    SPI_Write(0x26);    
    __delay_ms(1);
    MATRICE_CS_LAT = 1; 
    __delay_ms(2); 
    MATRICE_CS_LAT = 0; 
    __delay_ms(1);      
    for(i = 0; i < 64; i++) {
        SPI_Write(color); 
    }
    __delay_ms(1);      
    MATRICE_CS_LAT = 1; 
}

void Turing_Init(void) {
    AD1PCFG = 0xFFFF; 
    LED_TEST_TRIS = 0; 
    LedOn(); 
    MATRICE_CS_TRIS = 0; 
    MATRICE_CS_LAT = 1; 
    SPI_Init(); 
    __delay_ms(3000);
}

void Turing_Task(void) {
    Matrix_Fill(COULEUR_ROUGE);
    __delay_ms(1000);
    Matrix_Fill(COULEUR_VERT);
    __delay_ms(1000);
    Matrix_Fill(COULEUR_BLEU);
    __delay_ms(1000);
    Matrix_Fill(COULEUR_NOIR); 
    __delay_ms(1000);
}

// ==============================================================================
// TEST NUMERO 1 : BOUTONS SEULS (HISTORIQUE)
// ==============================================================================
#elif (CURRENT_TEST == TEST_BOUTONS)

void Turing_Init(void) {
    AD1PCFG = 0xFFFF; 
    TRISAbits.TRISA0 = 1; 
    TRISAbits.TRISA1 = 1; 
    TRISAbits.TRISA4 = 1; 
    TRISBbits.TRISB7 = 1; 
    LED_TEST_TRIS = 0; 
    LedOff(); 
    CNPU1bits.CN2PUE = 1;  
    CNPU1bits.CN3PUE = 1;  
    CNPU1bits.CN0PUE = 1;  
    CNPU2bits.CN23PUE = 1; 
}

void Turing_Task(void) {
    if (BTN_UP == 0 || BTN_DOWN == 0 || BTN_SELECT == 0 || BTN_START == 0) {
        LedOn(); 
    } else {
        LedOff(); 
    }
}

// ==============================================================================
// TEST NUMERO 5 : MATRICE + BOUTONS SANS CALCUL (HISTORIQUE)
// ==============================================================================
#elif (CURRENT_TEST == TEST_MATRICE_BOUTONS)

uint8_t bande_turing_test[8] = {0,0,0,0,0,0,0,0}; 
int position_curseur_test = 0;                    

void SPI_Init(void) {
    SPI1STAT = 0; 
    TRISBbits.TRISB12 = 0; 
    TRISBbits.TRISB13 = 0; 
    __builtin_write_OSCCONL(OSCCON & 0xbf); 
    RPOR6bits.RP12R = 7; 
    RPOR6bits.RP13R = 8; 
    __builtin_write_OSCCONL(OSCCON | 0x40); 
    SPI1CON1bits.MSTEN = 1;   
    SPI1CON1bits.MODE16 = 0;  
    SPI1CON1bits.CKP = 0;     
    SPI1CON1bits.CKE = 1;     
    SPI1CON1bits.SMP = 0;     
    SPI1CON1bits.PPRE = 0b00;  
    SPI1CON1bits.SPRE = 0b111; 
    SPI1STATbits.SPIEN = 1;   
}

void SPI_Write(uint8_t data) {
    uint8_t donnee_recue;
    SPI1BUF = data;                     
    while(SPI1STATbits.SPIRBF == 0);    
    donnee_recue = SPI1BUF;             
}

void Matrix_Draw(void) {
    int i;
    MATRICE_CS_LAT = 0; 
    __delay_ms(1);
    SPI_Write(0x26);    
    __delay_ms(1);
    MATRICE_CS_LAT = 1; 
    
    __delay_ms(2); 
    MATRICE_CS_LAT = 0; 
    __delay_ms(1);      
    
    for(i = 0; i < 8; i++) {
        SPI_Write(bande_turing_test[i]); 
    }
    for(i = 8; i < 56; i++) {
        SPI_Write(COULEUR_NOIR); 
    }
    for(i = 56; i < 64; i++) {
        if((i - 56) == position_curseur_test) {
            SPI_Write(COULEUR_BLEU);
        } else {
            SPI_Write(COULEUR_NOIR);
        }
    }
    __delay_ms(1);      
    MATRICE_CS_LAT = 1; 
}

void Turing_Init(void) {
    AD1PCFG = 0xFFFF; 
    MATRICE_CS_TRIS = 0; 
    MATRICE_CS_LAT = 1; 
    SPI_Init(); 
    TRISAbits.TRISA0 = 1; 
    TRISAbits.TRISA1 = 1; 
    TRISAbits.TRISA4 = 1; 
    CNPU1bits.CN2PUE = 1;  
    CNPU1bits.CN3PUE = 1;  
    CNPU1bits.CN0PUE = 1;  
    __delay_ms(3000);
    Matrix_Draw();
}

void Turing_Task(void) {
    if (BTN_DOWN == 0) {
        if (position_curseur_test < 7) position_curseur_test++;
        else position_curseur_test = 0; 
        Matrix_Draw(); 
        while(BTN_DOWN == 0); 
        __delay_ms(50); 
    }
    else if (BTN_UP == 0) {
        if (position_curseur_test > 0) position_curseur_test--;
        else position_curseur_test = 7; 
        Matrix_Draw(); 
        while(BTN_UP == 0); 
        __delay_ms(50); 
    }
    else if (BTN_SELECT == 0) {
        if(bande_turing_test[position_curseur_test] == COULEUR_NOIR) {
            bande_turing_test[position_curseur_test] = COULEUR_VERT;
        } 
        else if(bande_turing_test[position_curseur_test] == COULEUR_VERT) {
            bande_turing_test[position_curseur_test] = COULEUR_ROUGE;
        } 
        else {
            bande_turing_test[position_curseur_test] = COULEUR_NOIR;
        }
        Matrix_Draw(); 
        while(BTN_SELECT == 0); 
        __delay_ms(50); 
    }
}

#endif