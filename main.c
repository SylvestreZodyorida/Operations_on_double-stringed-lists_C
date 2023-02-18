#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int choixMenu;
//author Sylvestre AHLONSOU  Github github.com/SylvestreZodyorida
typedef enum {
  false,
  true
}
bool_enum;

typedef void Object;


typedef struct CelluleDbl* PCelluleDbl;


typedef struct CelluleDbl {
    Object* valeur ;
    PCelluleDbl suivant;
    PCelluleDbl precedent;
}ListeDbl;



void creerListeDbl(PCelluleDbl l, int n){
    PCelluleDbl tete ;
    PCelluleDbl p;
    int i,donnee;
    //tete =malloc(sizeof(PCellule))
    gotoxy(0,5);printf("Veuillez saisir le premier element : ");
    scanf("%d",&donnee);

    tete=l;

    tete->valeur=donnee;
    tete->suivant=NULL;
    tete->precedent=NULL;

    for(i=2;i<=n;i++){
        p=malloc(sizeof(PCelluleDbl));
        printf("Veuillez saisir l element suivant : ");
        scanf("%d",&donnee);
        p->valeur=donnee;
        p->suivant=NULL;
        p->precedent=tete;
        tete->suivant=p;
        tete=p;

    }
}

void afficherlisteDbl(PCelluleDbl l){

    PCelluleDbl p;
    p=l;
    printf("\n******* Affichage de la liste******** \n \n");
    while(p!=NULL){

        printf("[ %d ] ",p->valeur);
        p=p->suivant;
    }
}

void ajouter_en_tete(PCelluleDbl * l){

    ListeDbl * b;
    int val;
    b=(ListeDbl *)malloc(sizeof(PCelluleDbl));
    gotoxy(0,3);printf("Saisissez la valeur de l element : ");
    scanf("%d",&val);

    b->suivant=NULL;
    b->precedent=NULL;
    b->valeur=val;
    b->suivant= * l ;

    if(*l!= NULL){
        (*l)->precedent=b;
        *l=b;
    }

}

void ajouter_en_queue(PCelluleDbl * l){

    ListeDbl * b;
    ListeDbl * q;
    int val;
    b=(ListeDbl *)malloc(sizeof(PCelluleDbl));
    gotoxy(0,3);printf("Saisissez la valeur de l element : ");
    scanf("%d",&val);

    b->suivant=NULL;
    b->precedent=NULL;
    b->valeur=val;
    q=l;
    if(*l == NULL){
          *l = q;

    }

    else{

        q=*l;


        while(q->suivant != NULL){
            q=q->suivant;
        }

        b->precedent=q;
        q->suivant=b;
    }

}



void trie_liste(PCelluleDbl * l){
    ListeDbl * b;
    ListeDbl * q;
    int temp;
    bool_enum permut =false ;

    do{

        b=*l;
        permut=true;

        while(b->suivant!=NULL){
            q=b->suivant;
            if(b->valeur > q->valeur){
                temp=b->valeur;
                b->valeur=q->valeur;
                q->valeur=temp;
                permut=false;
            }
            b=b->suivant;
        }
    }while(permut==false);

}

void supprimerElement(PCelluleDbl *l)
{
    ListeDbl * b;
    ListeDbl * prec;
    ListeDbl * suiv;
    bool_enum trouve =false ;
    int x;
    gotoxy(0,15);printf("Donnez la valeur de l element a supprimer :");
    scanf("%d",&x);

    b=*l;
    while (b != NULL && trouve ==false)
    {
        if (b->valeur == x)
        {
            trouve=true;
            prec=b->precedent;
            suiv=b->suivant;
            if(prec != NULL ){
                prec->suivant=suiv;
            }
            else{
                suiv->precedent=NULL;
                *l=suiv;

            }
            if(suiv!=NULL){
                suiv->precedent=prec;
            }
            else{
                prec->suivant=NULL;
            }

            free(b);

        }
        else{

            b = b->suivant;
        }
    }
}

void supprimerDoublons(PCelluleDbl *l){
    ListeDbl *actuB = *l;
    ListeDbl *suivB;

    if (actuB == NULL){
        return;
    }

    trie_liste(&actuB);

    while (actuB->suivant != NULL)
    {
        if (actuB->valeur == actuB->suivant->valeur)
        {
            suivB = actuB->suivant->suivant;
            free(actuB->suivant);
            actuB->suivant = suivB;
        }
        else
            actuB = actuB->suivant;}

}

void supprimerDernierElement(PCelluleDbl * l){

    ListeDbl * b;
    ListeDbl * prec;
    ListeDbl * suiv;
    bool_enum trouve =false ;

    b=*l;
    while (b != NULL && trouve ==false)
    {
        if (b->suivant == NULL)
        {
            trouve=true;
            prec=b->precedent;
            prec->suivant=NULL;
            free(b);

         }
        b = b->suivant;

    }

}

void fusionListes(PCelluleDbl * l,PCelluleDbl * l2){

    ListeDbl *b = *l2;


    while (b != NULL){

        PCelluleDbl maListeDbl3;
        maListeDbl3 = malloc(sizeof(PCelluleDbl));

        maListeDbl3->valeur=b->valeur;
        maListeDbl3->suivant=NULL;



        ListeDbl *c = *l;

        while (c->suivant != NULL){
            c = c->suivant;
        }

        c->suivant = maListeDbl3;
        maListeDbl3->precedent = c;
        b = b->suivant;
    }

    supprimerDoublons(l);
}

void inverserListe(PCelluleDbl  *l ){
    ListeDbl *b = *l;
    ListeDbl *c = NULL;

    while (b != NULL)
    {
        c = b->precedent;
        b->precedent = b->suivant;
        b->suivant = c;
        b = b->precedent;
    }

    if (c != NULL){

        *l= c->precedent;
    }


}

int tailleListe(PCelluleDbl  l){
    ListeDbl *p = l;
    int taille = 0;
    while(p != NULL ){
        taille=taille +1;
        p=p->suivant;
    }

    return taille ;

}

bool_enum siPalyndrome(PCelluleDbl  l){
    ListeDbl *b=l;
    ListeDbl *q = l;
    int nbr,i;
    bool_enum pal ;



    while(q->suivant!=NULL){

        q=q->suivant;
    }

    nbr = tailleListe(l) / 2;

    i=1;

    pal=true;
    while(i<= nbr && pal==true ){

        if(b->valeur != q->valeur){
            pal=false;
        }
        i=i+1;
        b=b->suivant;
        q=q->precedent;
    }
    return pal;
}
void gotoxy(int x, int y) {
    COORD c ;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void affichageMenu()
    {
int a =73;
        gotoxy(a,3);  printf("�������������������������������������������������Ŀ");
        gotoxy(a,4);  printf("�                Menu du programme                �");
        gotoxy(a,5);  printf("�������������������������������������������������Ĵ");
        gotoxy(a,6);  printf("� 1.Creer une liste chainee d'entier .            �");
        gotoxy(a,7);  printf("�������������������������������������������������Ĵ");
        gotoxy(a,8);  printf("� 2.Ajouter un element en tete de liste .         �");
        gotoxy(a,9);  printf("�������������������������������������������������Ĵ");
        gotoxy(a,10); printf("� 3.Ajouter un element en queue de liste .        �");
        gotoxy(a,11); printf("�������������������������������������������������Ĵ");
        gotoxy(a,12); printf("� 4.Trier une liste .                             �");
        gotoxy(a,13); printf("�������������������������������������������������Ĵ");
        gotoxy(a,14); printf("� 5.Supprimer un element donne de la liste .      �");
        gotoxy(a,15); printf("�������������������������������������������������Ĵ");
        gotoxy(a,16); printf("� 6.Supprimer les doublons de la liste .          �");
        gotoxy(a,17); printf("�������������������������������������������������Ĵ");
        gotoxy(a,18); printf("� 7.Supprimer le dernier element de la liste .    �");
        gotoxy(a,19); printf("�������������������������������������������������Ĵ");
        gotoxy(a,20); printf("� 8.Fusionner deux listes .                       �");
        gotoxy(a,21); printf("�������������������������������������������������Ĵ");
        gotoxy(a,22); printf("� 9.Inverser une liste .                          �");
        gotoxy(a,23); printf("�������������������������������������������������Ĵ");
        gotoxy(a,24); printf("� 10.Verifier si une liste est un palindrome .    �");
        gotoxy(a,25); printf("�������������������������������������������������Ĵ");
        gotoxy(a,26); printf("� 11.Quitter .                                    �");
        gotoxy(a,27); printf("�������������������������������������������������Ĵ");
        gotoxy(a,28); printf("� Votre choix :                                   �");
        gotoxy(a,29); printf("���������������������������������������������������");

        gotoxy(90,28); scanf("%d", &choixMenu);


   }

int main(){
    bool_enum existListe = false;
    bool_enum existListe2 = false;
    int nbr,nbr2;


    PCelluleDbl maListeDbl,maListeDbl2,maListeDbl3;
    maListeDbl = malloc(sizeof(PCelluleDbl));
    maListeDbl2 = malloc(sizeof(PCelluleDbl));
    maListeDbl3 = malloc(sizeof(PCelluleDbl));
    do{
        affichageMenu();

    }while(choixMenu < 1 || choixMenu > 11);

    do{
        switch(choixMenu)
          {
            case 1:

                gotoxy(0,3);printf("Votre liste contiendra combien d'element ? : ");
                scanf("%d",&nbr);
                creerListeDbl(maListeDbl,nbr);
                printf("\n SUCCES : Liste cree ! \n");
                existListe=true;
                afficherlisteDbl(maListeDbl);
                printf("\n \n");
                system("PAUSE");
                system("cls");

                break;
            case 2:

                if(existListe==false){
                    gotoxy(0,3);printf("ERROR : Ajout en tete impossible ! Creez d'abord une liste.\n");
                    system("PAUSE");
                    system("cls");
                }
                else{


                    ajouter_en_tete(&maListeDbl);
                    gotoxy(0,3);printf(" \n SUCCES : Ajout effectue !\n");
                    afficherlisteDbl(maListeDbl);
                    printf("\n \n");
                    system("PAUSE");
                    system("cls");
                }

                break;
            case 3:
                if(existListe==false){
                    gotoxy(0,3);printf("ERROR : Ajout en queue impossible ! Creez d'abord une liste.\n");
                    system("PAUSE");
                    system("cls");

                }
                else{


                    ajouter_en_queue(&maListeDbl);
                    gotoxy(0,3);printf(" \n SUCCES : Ajout effectue !\n");
                    afficherlisteDbl(maListeDbl);
                    printf("\n \n");
                    system("PAUSE");
                    system("cls");
                }
                break;
            case 4:
                if(existListe==false){
                    gotoxy(0,3);printf("ERROR : Trie impossible !Creez d abord une liste.\n");
                    system("PAUSE");
                    system("cls");

                }
                else{


                    trie_liste(&maListeDbl);
                    gotoxy(0,3);printf("\n SUCCES : Liste trie !\n");
                    afficherlisteDbl(maListeDbl);
                    printf("\n \n");
                    system("PAUSE");
                    system("cls");
                }
                break;
            case 5:
                if(existListe==false){
                    gotoxy(0,3);printf("ERROR : Suppression impossible !Creez d abord une liste.\n");
                    system("PAUSE");
                    system("cls");

                }
                else{

                    supprimerElement(&maListeDbl);
                    gotoxy(0,17); printf("\n SUCCES : Suppression effectue ! \n");
                    afficherlisteDbl(maListeDbl);
                    printf("\n \n");
                    system("PAUSE");
                    system("cls");
                }
                break;
            case 6:
                if(existListe==false){
                    gotoxy(0,3);printf("ERROR : Suppression impossible !Creez d abord une liste.\n");
                    system("PAUSE");
                    system("cls");

                }
                else{


                    supprimerDoublons(&maListeDbl);
                    gotoxy(0,17); printf("\n SUCCES : Suppression de doublons effectue ! \n");
                    afficherlisteDbl(maListeDbl);
                    printf("\n \n");
                    system("PAUSE");
                    system("cls");
                }
            case 7:
                if(existListe==false){
                    gotoxy(0,3);printf("ERROR : Suppression impossible !Creez d abord une liste.\n");
                    system("PAUSE");
                    system("cls");
                }
                else{

                    supprimerDernierElement(&maListeDbl);
                    gotoxy(0,17); printf("\n SUCCES : Suppression du dernier element effectue ! \n");
                    afficherlisteDbl(maListeDbl);
                    printf("\n \n");
                    system("PAUSE");
                    system("cls");
                }
                break;
            case 8:
                if(existListe==false){
                    gotoxy(0,3);printf("ERROR : Fusion de listes impossible!Creez d abord une premiere liste.\n");
                    system("PAUSE");
                    system("cls");

                }
                else{

                    if(existListe2==false){
                        gotoxy(0,3);printf("ERROR : Fusion de listes impossible!Creez la seconde liste.\n");
                        printf("Votre liste contiendra combien d'element ? : ");
                        scanf("%d",&nbr2);

                        creerListeDbl(maListeDbl2,nbr2);
                        existListe2=true;
                        afficherlisteDbl(maListeDbl2);
                        printf("\n \nLa fusion est maintenant possible \n\n");
                        system("PAUSE");
                        system("cls");


                        gotoxy(0,3);printf("Les deux listes a fusionner sont ci dessous :\n\n")  ;
                        afficherlisteDbl(maListeDbl);
                        printf("\n \n");
                        afficherlisteDbl(maListeDbl2);
                        printf("\n \n");
                        system("PAUSE");
                        fusionListes(&maListeDbl,&maListeDbl2);
                        printf(" \n SUCCES :Fusion effectuee ! \n");
                        afficherlisteDbl(maListeDbl);
                        printf("\n \n");
                        system("PAUSE");
                        system("cls");
                    }

                }
                break;
            case 9:
                if(existListe==false){
                    gotoxy(0,3);printf("ERROR : Inversion impossible !Creez d abord une liste.\n");
                    system("PAUSE");
                }
                else{
                        system("PAUSE");
                    inverserListe(&maListeDbl);
                    gotoxy(0,3); printf("\n SUCCES : Inversion effectuee ! \n");
                    afficherlisteDbl(maListeDbl);
                    printf("\n \n");
                    system("PAUSE");
                    system("cls");
                }
                break;
            case 10:


                if(existListe==false){
                    gotoxy(0,3);printf("ERROR : Verification impossible !Creez d abord une liste.\n");
                    system("PAUSE");
                    system("cls");
                }
                else{

                    if(maListeDbl != NULL){
                        if( siPalyndrome(maListeDbl)){
                            printf("\n");
                            gotoxy(0,3);printf("La liste est un palindrome !\n");
                            printf("\n \n");
                            system("PAUSE");
                            system("cls");

                        }
                        else{
                            printf("\n");
                            gotoxy(0,3);printf("La liste n est pas un palindrome !\n");
                            printf("\n \n");
                            system("PAUSE");
                            system("cls");
                        }
                    }
                }

                break;
            case 11:
                gotoxy(0,3);printf("Le programme va s'arreter !\n");
                return 0;

                break;

            default:

                break;
            }
        affichageMenu();

    }while(choixMenu != 11);

        return 0;
}
