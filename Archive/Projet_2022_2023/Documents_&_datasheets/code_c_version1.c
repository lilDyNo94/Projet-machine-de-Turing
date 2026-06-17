#include <stdio.h>
#include <stdlib.h>
#define TAILLE_ALPHABET 7
#define LONG_BANDE 16

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
    int numero;
    Action transition[TAILLE_ALPHABET];
};
typedef struct etat Etat;

struct list_etat{
    Etat etat;
    struct list_etat * next;
};
typedef struct list_etat Etats;


//////////// Initialisation de la structure etat ///////////

Etat init_etat(int num){
    Etat E;
    E.numero=num;
    for( int i=0; i<TAILLE_ALPHABET; i++){
        E.transition[i].nv_char=0;
        E.transition[i].dep=0;
        E.transition[i].nv_etat=0;
    }
    return E;
}


// Creation d'une action qui 
    // - ecrit le caractere "a" dans la position actuelle 
    //  de la tete de lecture de la bande ("pos_tete_lecture")
    // - deplace la tete de lecture à "pos_tete_lecture + dep"
    // - change l'etat actel au "nv_etat"
    
Action action_create(int a, Deplacement dep, int nv_etat){
    Action A;
    if(( a<TAILLE_ALPHABET)&&(a>=0)){
        A.nv_char=a;
        A.dep=dep;
        A.nv_etat=nv_etat;
        
    }else printf("caractere non accepte \n");
    return A;
}


// Affecte l'action "act" au caractere "alphabet" de "etat_actuel"
// Si ( "etat_actuel" & caractere lu de la bande ("pos_tete_lecture") = "alphabet")
// => l'action "act"

void actions_def (Action act, Etat* etat_actuel,int alphabet){
    etat_actuel->transition[alphabet]=act;
}


// Fonction qui fait l'action pour un etat et un caractere lu de la bande 
// (selon les definitions precedentes)


        //////////  version reccursive //////////

int etat_chang_reccur(Etats * list, int pos_tete_lecture, int num_etat_deb,int bande[LONG_BANDE], int etat_accept){

    Etats * parc=list;
    while(((parc->etat).numero!=num_etat_deb)&&(parc->next!=NULL)){
        parc=parc->next;
    }
    int a= bande[pos_tete_lecture];
    bande[pos_tete_lecture]=parc->etat.transition[a].nv_char;
    pos_tete_lecture+=parc->etat.transition[a].dep;
    if((a==bande[pos_tete_lecture])&&(parc->etat.transition[a].dep==0)&&(parc->etat.numero==etat_accept)){
        return 1;
    }
    else{
        etat_chang_reccur(list,pos_tete_lecture,parc->etat.transition[a].nv_etat, bande,etat_accept);
    }
}


    ////////////// version iterative ////////////
    
int etat_chang(Etats * list, int pos_tete_lecture, int num_etat_deb,int bande[LONG_BANDE],int etat_accept){

    Etats * parc=list;
    int a=0;
    
    while(!((a==bande[pos_tete_lecture])&&(parc->etat.transition[a].dep==0)&&(parc->etat.numero==etat_accept))){
        parc=list;
        while(((parc->etat).numero!=num_etat_deb)&&(parc->next!=NULL)){
            parc=parc->next;
        }    
        a= bande[pos_tete_lecture];
        bande[pos_tete_lecture]=parc->etat.transition[a].nv_char;
        pos_tete_lecture+=parc->etat.transition[a].dep;
        num_etat_deb=parc->etat.transition[a].nv_etat;
    }
    return 4;
}


/////// Liste pour stocker les etats definis  ////////////

void ajouter_etat( Etats* list, Etat  etat1){
    Etats *parc=list;
    while (parc->next!=NULL){
        parc=parc->next;
    }
    parc->next=malloc(sizeof(Etats));
    parc->next->etat=etat1;
    parc->next->next=NULL;
}


////////// fonction d'addition predefinie ///////////

Etats addition(){
    
    int nb_alphab=3;    
    // avec 0 le caractere nul led jaune, 1->0 (binaire) Led verte et  et 2->1(binaire) led rouge 
    int nb_etats=6;
    // nombre d'etats necessaire pour la definition de la fonction addition
    Action actions[nb_alphab];
    Etats premier_etat;
    premier_etat.next=NULL;
    Etat e[nb_etats];
    int depl=0, etatN=0, charN=0;
    
    ///// definition des etats ( un par un )   /////////
    
    e[0]=init_etat(0);
    actions[0]=action_create(1, gauche, 1);      // nv_char, dep, nv_etat
    actions_def(actions[0], &e[0], 2);          // definir action[0] pour char 0(alphabet) de l'etat e[0]

    actions[1]=action_create(2, gauche, 0);
    actions_def(actions[1], &e[0], 1);
    
    actions[2]=action_create(0, rien, 0);
    actions_def(actions[2], &e[0], 0);
    
    premier_etat.etat=e[0];


    e[1]=init_etat(1);  
    
    actions[0]=action_create(2, gauche, 1);    
    actions_def(actions[0], &e[1], 2);                   

    
    actions[1]=action_create(1, gauche, 1);
    actions_def(actions[1], &e[1], 1);
    
    actions[2]=action_create(0, gauche, 2);
    actions_def(actions[2], &e[1], 0);
    
    ajouter_etat(&premier_etat, e[1]);
    
    e[2]=init_etat(2);  
    
    actions[0]=action_create(1, gauche, 2);     
    actions_def(actions[0], &e[2], 2);                  
    
    actions[1]=action_create(2, droite, 3);
    actions_def(actions[1], &e[2], 1);
    
    actions[2]=action_create(2, droite, 3);
    actions_def(actions[2], &e[2], 0);
    
    ajouter_etat(&premier_etat, e[2]);
    
    e[3]=init_etat(3);   
    actions[0]=action_create(2, droite, 3);      
    actions_def(actions[0], &e[3], 2);
    
    actions[1]=action_create(1, droite, 3);
    actions_def(actions[1], &e[3], 1);
    
    actions[2]=action_create(0, droite, 4);
    actions_def(actions[2], &e[3], 0);
    
    ajouter_etat(&premier_etat, e[3]);
    
    e[4]=init_etat(4);   
    actions[0]=action_create(2, droite, 5);      
    actions_def(actions[0], &e[4], 2);                     
    
    actions[1]=action_create(1, droite, 4);
    actions_def(actions[1], &e[4], 1);
    
    actions[2]=action_create(0, rien, 4);
    actions_def(actions[2], &e[4], 0);
    
    ajouter_etat(&premier_etat, e[4]);
    
    e[5]=init_etat(5);   
    
    actions[0]=action_create(2, droite, 5);      
    actions_def(actions[0], &e[5], 2);                    
    
    actions[1]=action_create(1, droite, 5);
    actions_def(actions[1], &e[5], 1);
    
    actions[2]=action_create(0, gauche, 0);
    actions_def(actions[2], &e[5], 0);
    
    ajouter_etat(&premier_etat, e[5]);
    
   
    return premier_etat;
}

int main(){
    
    int led[TAILLE_ALPHABET+1][LONG_BANDE]; 
    int bande[LONG_BANDE]={0};
    int pos_tete_lecture=0;           
    int n=0, m=0, o=0;
    
    printf("saisie des elements de la bande\n");
    for( int k=0; k<LONG_BANDE; k++){
        scanf("%d",&bande[k]);
    }
    printf("\n");
    
    printf("position de tete de lecture\n");
    scanf("%d", &pos_tete_lecture);
    printf("\n");
    
    printf("etat accept\n");        // pour la fonction addition l'etat4 
    scanf("%d", &o);
    printf("\n");

    Etats premier_etat;
    premier_etat= addition();
    Etats *p=&premier_etat;
    
    //////////////////////  Affichage des etats ////////////////
    
    /*                      
    while(p!=NULL){
        for( int i=0; i<TAILLE_ALPHABET; i++){
            printf(" etat %d char %d nv char %d nv etat %d dep %d \n", p->etat.numero,i,p->etat.transition[i].nv_char, p->etat.transition[i].nv_etat, p->etat.transition[i].dep);    
        }
        p=p->next;
    }
    */
    
    
    //int res=etat_chang(&premier_etat, pos_tete_lecture , 0 , bande,o);
    int res=etat_chang_reccur(&premier_etat, pos_tete_lecture , 0 , bande,o);
    
    ////////////   Affichage du resultat (la bande)     //////////////
    
    for(int i=0; i<LONG_BANDE; i++){
        printf(" le caractere a la position %d de la bande est %d \n", i, bande[i]);
    }

    return 0;
}