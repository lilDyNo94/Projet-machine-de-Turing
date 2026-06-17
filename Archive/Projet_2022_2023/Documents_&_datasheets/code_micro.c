/**
 * @file        Maching de Turing addition
 * @author      LAZOUZI Jihane  
 * @date        
 * @brief        
 */
#ifndef FCY
#define FCY 400000UL
#endif

#include <libpic30.h>
#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#define TAILLE_ALPHABET 3
#define LONG_BANDE 8

// Configuration des bits du PIC
// Configuration Bits
#pragma config POSCMOD = NONE    // Primary Oscillator Select (Primary Oscillator Disabled)
#pragma config I2C1SEL = PRI    // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF    // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = OFF    // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD   // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCDIV   // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config SOSCSEL = SOSC   // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG     // Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = OFF       // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)


#pragma config WINDIS = OFF     // Watchdog Timer Window Select bits (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF     // Watchdog Timer Enable bits (Watchdog Timer is disabled)
#pragma config ICS = PGx2       // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF       // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF        // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF     // JTAG Port Enable (JTAG port is disabled)


#define CS LATBbits.LATB15 // Définition de la broche CS utilisée (CS est sur RB15)
//#define add PORTBbits.RB10
//#define sous PORTBbits.RB11
#define chang  PORTBbits.RB9
//#define divi PORTBbits.RB3
//#define run PORTBbits.RB4
#define dep_g  PORTBbits.RB7
#define dep_d PORTBbits.RB8


void HardwareInit(void)
{
    // Configuration du SPI

    
    TRISBbits.TRISB15 = 0; // Configurer RB15 (CS) en tant que sortie
    TRISBbits.TRISB14 = 0; // Configurer RB14 (SCLK) en tant que sortie
    TRISBbits.TRISB13 = 0; // Configurer RB13 (MOSI) en tant que sortie
    //TRISBbits.TRISB4 = 1; // Configurer RB0 (button) en tant qu'entrée
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB8 = 1; // Configurer RB0 (button) en tant qu'entrée
    //TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB9 = 1;
    //TRISBbits.TRISB11 = 0;
    RPOR7bits.RP14R= 0x08;
    RPOR7bits.RP15R= 0x09;
    RPOR6bits.RP13R= 0x07;
    SPI1CON1 = 0x0019; // Initialiser le contrôleur SPI, Master mode
    SPI1CON1bits.MSTEN = 1;         // 1 master mode 0 slave mode
    SPI1CON1bits.MODE16 = 0;        // pour word 1 pour bit 0
    //SPI1CON1bits.DISSDO = 1;
    SPI1STATbits.SPIEN = 1; // Activer le module SPI
}


///// Definition des structures de donnees //////////

typedef enum{
  rien=0,
  gauche=-1,
  droite=1,
} Deplacement;

struct action {
  int nv_char;
  Deplacement dep;
  int nv_etat;
};
typedef struct action Action;

struct etat{
    int final;
    Action transition[TAILLE_ALPHABET];
    
};
typedef struct etat Etat;


// Creation d'une action qui
    // - ecrit le caractere "a" dans la position actuelle
    //  de la tete de lecture de la bande ("pos_tete_lecture")
    // - deplace la tete de lecture à "pos_tete_lecture + dep"
    // - change l'etat actel au "nv_etat"

void action_create(Action *A ,int a, Deplacement dep, int nv_etat){

    if(( a<TAILLE_ALPHABET)&&(a>=0)){
        A->nv_char=a;
        A->dep=dep;
        A->nv_etat=nv_etat;
        
    }//else printf("caractere non accepte \n");

}


// Affecte l'action "act" au caractere "alphabet" de "etat_actuel"
// Si ( "etat_actuel" & caractere lu de la bande ("pos_tete_lecture") = "alphabet")
// => l'action "act"

// Fonction qui fait l'action pour un etat et un caractere lu de la bande
// (selon les definitions precedentes)




int etat_chang(Etat * Etats, int pos_tete_lecture, int num_etat_deb,int *bande){
    int rouge[8]={0};
        int vert[8]={0};
        int blanc[8]={0};
        
    int i=0;
    int a=0;
    int k=0;
    while(Etats[i].final!=1){
        a= *(bande+pos_tete_lecture);
        *(bande+pos_tete_lecture)=Etats[i].transition[a].nv_char;
        pos_tete_lecture += Etats[i].transition[a].dep;
        i=Etats[i].transition[a].nv_etat;
        k=0;
            for(k=0; k<8; k++){
                if(bande[k]==0){
                    blanc[k]=1;
                    rouge[k]=0;
                    vert[k]=0;
                }else if (bande[k]==1){
                    blanc[k]=0;
                    rouge[k]=0;
                    vert[k]=1;
                } else{
                    blanc[k]=0;
                    rouge[k]=1;
                    vert[k]=0;
                }
            }
        affiche(rouge, vert, blanc, pos_tete_lecture+56);
            __delay_ms(2000);

        
    }
        k=0;
            for(k=0; k<8; k++){
                if(bande[k]==0){
                    blanc[k]=1;
                    rouge[k]=0;
                    vert[k]=0;
                }else if (bande[k]==1){
                    blanc[k]=0;
                    rouge[k]=0;
                    vert[k]=1;
                } else{// if (bande[z]==2){
                    blanc[k]=0;
                    rouge[k]=1;
                    vert[k]=0;
                }
            }
            affiche(rouge, vert, blanc, 111);//pos_tete_lecture+56);
            __delay_ms(100);
            while(1);
        
    return 4;
}

/////// Liste pour stocker les etats definis  ////////////

////////// fonction d'addition predefinie ///////////


void addition(Etat *Etats){
    
    ///// definition des etats ( un par un )   /////////
    Etats[0].final=0;
    action_create(&Etats[0].transition[2], 1, gauche, 1);      // nv_char, dep, nv_etat
    action_create(&Etats[0].transition[1], 2, gauche, 0);
    action_create(&Etats[0].transition[0], 0, rien, 0);

    Etats[1].final=0;
    action_create(&Etats[1].transition[2],2, gauche, 1);    
    action_create(&Etats[1].transition[1],1, gauche, 1);
    action_create(&Etats[1].transition[0],0, gauche, 2);

    Etats[2].final=0;
    action_create(&Etats[2].transition[2],1, gauche, 2);    
    action_create(&Etats[2].transition[1],2, droite, 3);
    action_create(&Etats[2].transition[0],2, droite, 3);

    Etats[3].final=0;
    action_create(&Etats[3].transition[2],2, droite, 3);      
    action_create(&Etats[3].transition[1],1, droite, 3);
    action_create(&Etats[3].transition[0],0, droite, 4);

    Etats[4].final=0;
    action_create(&Etats[4].transition[2],2, droite, 5);      
    action_create(&Etats[4].transition[1],1, droite, 4);
    action_create(&Etats[4].transition[0],0, rien, 6);

    Etats[5].final=0;
    action_create(&Etats[5].transition[2], 2, droite, 5);      
    action_create(&Etats[5].transition[1],1, droite, 5);
    action_create(&Etats[5].transition[0], 0, gauche, 0);

    
    Etats[6].final=1;
  
}
/*
void soustraction(Etat *Etats){
    
//    int nb_alphab=3;    
//    int nb_etats=6;
//    Action actions[nb_alphab];
//    int depl=0, etatN=0, charN=0;
    
    Etats[0].final=0;
    action_create(&Etats[0].transition[2], 1, gauche, 1);      // nv_char, dep, nv_etat
    action_create(&Etats[0].transition[1], 2, gauche, 0);
    action_create(&Etats[0].transition[0], 0, rien, 0);

    Etats[1].final=0;
    action_create(&Etats[1].transition[2],2, gauche, 1);    
    action_create(&Etats[1].transition[1],1, gauche, 1);
    action_create(&Etats[1].transition[0],0, gauche, 2);

    Etats[2].final=0;
    action_create(&Etats[2].transition[2],1, droite, 3);    
    action_create(&Etats[2].transition[1],2, gauche, 2);
    action_create(&Etats[2].transition[0],2, droite, 3);

    Etats[3].final=0;
    action_create(&Etats[3].transition[2],2, droite, 3);      
    action_create(&Etats[3].transition[1],1, droite, 3);
    action_create(&Etats[3].transition[0],0, droite, 4);

    Etats[4].final=0;
    action_create(&Etats[4].transition[2],2, droite, 5);      
    action_create(&Etats[4].transition[1],1, droite, 4);
    action_create(&Etats[4].transition[0],0, rien, 6);

    Etats[5].final=0;
    action_create(&Etats[5].transition[2], 2, droite, 5);      
    action_create(&Etats[5].transition[1],1, droite, 5);
    action_create(&Etats[5].transition[0], 0, gauche, 0);

    Etats[6].final=1;
  
}*/
void affiche(int rouge[8], int vert[8], int blanc[8], int bleu ){
    int j=0;
    __delay_ms(0.5);
    CS = 0;
    __delay_ms(0.5);
    while (SPI1STATbits.SPITBF);
    while(j<8){
        if(rouge[j]==1){
            SPI1BUF = 0xE0;
            while (SPI1STATbits.SPITBF);
            j++;
        }else{
            SPI1BUF = 0x00;
            while (SPI1STATbits.SPITBF);
            j++;
        }
    }
    while(j<16){
        if(vert[j-8]==1){
            SPI1BUF = 0x1C;
            while (SPI1STATbits.SPITBF);
            j++;
        }else{
            SPI1BUF = 0x00;
            while (SPI1STATbits.SPITBF);
            j++;
        }
    }
    while(j<24){
        if(blanc[j-16]==1){
            SPI1BUF = 0xFF;
            while (SPI1STATbits.SPITBF);
            j++;
        }else{
            SPI1BUF = 0x00;
            while (SPI1STATbits.SPITBF);
            j++;
        }
    }
    while(j<56){
        
        SPI1BUF = 0x00;
        while (SPI1STATbits.SPITBF);
        j++;
    }
    while(j<64){
        if(bleu==j){
            SPI1BUF = 0x03;
            while (SPI1STATbits.SPITBF);
            j++;
        }else{
            SPI1BUF = 0x00;
            while (SPI1STATbits.SPITBF);
            j++;
        }
    }
    __delay_ms(0.5);
    CS=1;
    __delay_ms(0.5);
    
}
Etat Etats[7];
int main(void)
{
    HardwareInit(); // Initialise le matériel, y compris la SPI
    int a=0,y=0, k=0;
    int bande[LONG_BANDE]={0};
    int pos_tete_lecture=0;
    addition(&Etats);
    int blanc[8]={0};
    int vert[8]={0};
    int rouge[8]={0};
    y=0;
    for(y=0;y<8; y++){
        blanc[y]=1;
    }
    affiche(rouge,vert,blanc,pos_tete_lecture+56);
    __delay_ms(10);
    int cp=0;
    while(1){
        if (dep_g==1){
            if (pos_tete_lecture==LONG_BANDE-1){
                pos_tete_lecture=0;
            }else pos_tete_lecture++;
            affiche(rouge, vert, blanc,pos_tete_lecture+56);
            while(dep_g);
            cp++;
        }
    
        else if (dep_d==1){
            if (pos_tete_lecture==0){
                pos_tete_lecture=LONG_BANDE-1;
            }else pos_tete_lecture--;
            while(dep_d);
            affiche(rouge, vert, blanc, pos_tete_lecture+56);
            cp++;
        }else
        if(chang==1){
            if(blanc[pos_tete_lecture]==1){
                blanc[pos_tete_lecture]=0;
                vert[pos_tete_lecture]=1;
                bande[pos_tete_lecture]=1;
            }else if(vert[pos_tete_lecture]==1){
                vert[pos_tete_lecture]=0;
                rouge[pos_tete_lecture]=1;
                bande[pos_tete_lecture]=2;
            }else if(rouge[pos_tete_lecture]==1){
                rouge[pos_tete_lecture]=0;
                blanc[pos_tete_lecture]=1;
                bande[pos_tete_lecture]=0;
            }
            
            affiche(rouge, vert, blanc,pos_tete_lecture+56);
            while(chang);
            cp++;
            
        }
        if(cp==50){
            a=7;
            while((a>=0)&&(bande[a]==0)){
                a--;
            }
            pos_tete_lecture=a;
            int res=etat_chang(Etats, pos_tete_lecture , 0 ,&bande);
            
            __delay_ms(0.5);
            cp=0;
        }
    }

    
   return 0;
}