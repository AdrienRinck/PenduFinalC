#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLEMOT 11
#define TAILLEMAX 10
#define TAILLEMINI 3

//PROTOTYPE
void TourDeJeu(int compteurdefaite,int compteur,char Lettre,char MotFin[],char MotADeviner[],int vie);
void input(char MotADeviner[]);
int setPv(int vie,char MotADeviner[]);
void setMotFin(char MotADeviner[],char MotFin[]);
void verifInput(char MotADeviner[],char MotFin[],char Lettre);
int PerteDeVie(char MotADeviner[],int compteurdefaite,char Lettre,int vie);
int AugmentCompteur(char MotADeviner[],int compteurdefaite,char Lettre,int vie);
void AfficheMot(char MotADeviner[],char MotFin[]);
int VerifReussite(char MotADeviner[],char MotFin[],int compteur);

int main()
{
    int vie=0;
    char MotADeviner[TAILLEMOT];
    char MotFin[TAILLEMOT];
    char Lettre;
    int compteurdefaite=0;
    int compteur=0;
    int reponse=1;

    //Boucle entière du jeu pour pouvoir rejouer
    do{
        fflush(stdin);
        input(MotADeviner);
        vie=setPv(vie,MotADeviner);
        printf("LE MOT A DEVINER EST : %s  \n",MotADeviner);
        system("pause");
        system("cls");
        setMotFin(MotADeviner,MotFin);
        TourDeJeu(compteurdefaite,compteur,Lettre,MotFin,MotADeviner,vie);
        printf("ENTREZ 1 POUR REJOUER ET 0 POUR QUITTER\n");
        scanf("%d",&reponse);
        system("cls");
    }while(reponse!=0);
    printf("AU REVOIR :)\n");
    system("pause");
    return 0;
}

//Procedure de tour de jeu, boucle do while
void TourDeJeu(int compteurdefaite,int compteur,char Lettre,char MotFin[],char MotADeviner[],int vie)
{
    do{
        compteurdefaite=0;  //réinitialisation de mes compteur à chaque bouclage
        compteur=0;
        fflush(stdin);

        printf("MOT FAIT %d -> ENTREZ UNE LETTRE - IL VOUS RESTE %d VIE :\n",strlen(MotADeviner),vie); //Saisie de la lettre joué
        scanf("%c",&Lettre);
        Lettre = tolower(Lettre);

        verifInput(MotADeviner,MotFin,Lettre);
        AugmentCompteur(MotADeviner,compteurdefaite,Lettre,vie);
        compteurdefaite=AugmentCompteur(MotADeviner,compteurdefaite,Lettre,vie);
        vie=PerteDeVie(MotADeviner,compteurdefaite,Lettre,vie);
        AfficheMot(MotADeviner,MotFin);
        compteur=VerifReussite(MotADeviner,MotFin,compteur);

    }while(compteur!=strlen(MotADeviner) &&  vie!=0); //Condition de sortie de la boucle
    if (vie==0){                                        //Test de fin victoire/defaite
        printf("PAS DE CHANCE, C'EST PERDU :/\n");
    }
    else{
        printf("VOUS AVEZ GAGNE :D\n");
    }
}



// Fonction d'initialisation du mot à deviner
void input(char MotADeviner[])
{
    int i=0;
    do{
        printf("ENTREZ LE MOT A DEVINER (3-10 LETTRES):\n");
        scanf("%s",MotADeviner);
    }while(strlen(MotADeviner)>TAILLEMAX || strlen(MotADeviner)<TAILLEMINI);

    for(i=0; MotADeviner[i]; i++){                  //initialisation en minuscule pour éviter la casse
        MotADeviner[i] = tolower(MotADeviner[i]);
    }
}


int setPv(int vie,char MotADeviner[])
{
    //Switch pour set la vie en fonction de la taille du mot
    switch (strlen(MotADeviner)){
        case 3 : vie=2; break;
        case 4 : vie=3; break;
        case 5 : vie=3; break;
        case 6 : vie=4; break;
        case 7 : vie=5; break;
        case 8 : vie=5; break;
        case 9 : vie=6; break;
        case 10 : vie=6; break;
        }
    return vie;
}


// Initialisation du mot de fin
void setMotFin(char MotADeviner[],char MotFin[])
{
    int i=0;
    for (i=0;i<strlen(MotADeviner);i++){
            MotFin[i]='_';
    }
    MotFin[i]='\0';
}


//Verification de l'input
void verifInput(char MotADeviner[],char MotFin[],char Lettre)
{
    int i=0;
    for (i=0;i<=strlen(MotADeviner);i++){
        if (Lettre==MotADeviner[i]){
            MotFin[i]=Lettre;
        }else if (MotFin[i]=='_'){
            MotFin[i]='_';
        }
    }
}


//Calcul de perte de vie si toute les lettres sont fausses
//compteurdefaite=longeurMotADeviner alors perte de vie
int PerteDeVie(char MotADeviner[],int compteurdefaite,char Lettre,int vie)
{
    int i=0;
    if (compteurdefaite==strlen(MotADeviner)+1){
        vie--;
        printf("FAUX !\n");
    }else {
        printf("BIEN VU !\n");
        }
    return vie;
}
int AugmentCompteur(char MotADeviner[],int compteurdefaite,char Lettre,int vie)
{
    int i=0;
    for (i=0;i<=strlen(MotADeviner);i++){
        if (Lettre!=MotADeviner[i]){
            compteurdefaite++;
        }
    }
    return compteurdefaite;
}


//Affichage a l'utilisateur de sa chaine
void AfficheMot(char MotADeviner[],char MotFin[])
{
    int i=0;
    for (i=0;i<strlen(MotADeviner);i++){
        putchar(MotFin[i]);
    }
    fflush(stdin);
    putchar('\n');
}

//Verification de réussite
int VerifReussite(char MotADeviner[],char MotFin[],int compteur)
{
    int i=0;
    for (i=0;i<strlen(MotADeviner);i++){
        if (MotADeviner[i]==MotFin[i]){
            compteur++;
        }
    }
    return compteur;
}
