/*PROGRAMME Carre Magique

Type Position=ENREGISTREMENT
		x : ENTIER
		y : ENTIER
FINENREGISTREMENT

CONSTANTE
	TAILLE<-25



PROCEDURE InitTab(VAR Tab:TABLEAU [1..5,1..5] de ENTIER)

	VAR
		cpt:ENTIER

	DEBUT
		POUR cpt de 1 à 5 FAIRE
			Tab[cpt,1]<-0
			Tab[cpt,2]<-0
			Tab[cpt,3]<-0
			Tab[cpt,4]<-0
			Tab[cpt,5]<-0
		FINPOUR
	FIN

FONCTION CaseVide(VAR Tab:TABLEAU [1..5,1..5] de ENTIER, jeton : position):BOOLEEN

	DEBUT
		SI Tab[jeton.x,jeton.y]=0 ALORS
			CaseVide<-VRAI
		SINON
			CaseVide<-FAUX
	FIN

PROCEDURE AvancerDr(VAR Tab:TABLEAU [1..5,1..5] de ENTIER, jeton:positon)

	DEBUT

		jeton.x<-jeton.x+1
		jeton.y<-jeton.y-1
		Corriger(Tab,jeton)

	FIN

PROCEDURE AvancerGa(VAR Tab:TABLEAU [1..5,1..5] de ENTIER, jeton:positon)

	DEBUT

		jeton.x<-jeton.x-1
		jeton.y<-jeton.y-1
		Corriger(Tab,jeton)
	FIN

PROCEDURE Corriger(VAR Tab:TABLEAU [1..5,1..5] de ENTIER, jeton:position)

	DEBUT

		SI jeton.x=6 ALORS
			jeton.x<-1
		SI jeton.y=0 ALORS
			jeton.y<-5
		SI jeton.x=0 ALORS
			jeton.x<-5

	FIN

PROCEDURE Placer(VAR Tab:TABLEAU [1..5,1..5] de ENTIER, jeton:position, compteur)

	DEBUT

		Tab[jeton.x,jeton.y]<-compteur

	FIN


PROCEDURE Avancer (VAR Tab:TABLEAU [1..5,1..5] de ENTIER, compteur : ENTIER, jeton:position)

	DEBUT

		AvancerDr(Tab, jeton)
		SI CaseVide(jeton)=VRAI ALORS
			Placer(Tab, jeton, compteur)
		SINON
			AvancerGa(Tab, jeton)
			Placer(Tab, jeton, compteur)
		FINSI
	FIN

PROCEDURE Afficher(VAR Tab:TABLEAU [1..5,1..5]de ENTIER)

	VAR
		Cpt:ENTIER

	DEBUT

		POUR Cpt de 1 à 5 FAIRE
			ECRIRE Tab[cpt,1]
			ECRIRE Tab[cpt,2]
			ECRIRE Tab[cpt,3]
			ECRIRE Tab[cpt,4]
			ECRIRE Tab[cpt,5]
		FINPOUR
	FIN



VAR

	jeton : position
	Tableau Tab[1..5, 1..5]: ENTIER
	compteur:ENTIER



DEBUT

	compteur<-2
	jeton.x<-3
	jeton.y<-2
	InitTab(Tab)
	Tab[jeton.x,jeton.y]<-1
	POUR compteur de 2 à TAILLE FAIRE
		Avancer(Tab, compteur, jeton)
	FINPOUR
	Afficher(Tab)
FIN. */

#include <stdio.h>
#include <stdlib.h>
#define TAILLE 25

typedef struct tJeton{

    int nX;
    int nY;

}tJeton;

//Prototypage

void initTab(int nTab[][5]);
void afficher(int nTab[][5]);
int caseVide(int nTab[][5], tJeton j);
tJeton corriger(tJeton j);
tJeton avancerDroite(tJeton j);
tJeton avancerGauche(tJeton j);
void placer(int nTab[][5], tJeton j, int nCpt);
tJeton avancer(int nTab[][5], tJeton j, int nCpt);

int main()
{
    int nTab[5][5];
    int nCpt=1,nCptJeu=2,i,j;
    tJeton pt1;
    initTab(nTab);
    nTab[1][2]=1;
    //afficher(nTab);   Permet de vérifier la fonction d'initialisation du tableau

    pt1.nX=0;
    pt1.nY=3;
    for (nCptJeu=2;nCptJeu<=TAILLE;nCptJeu++)
    {
        if(nCptJeu!=25)
        {
            nCpt = nCpt+1;
            pt1=avancer(nTab,pt1,nCpt);
            //printf("%d    %d   \n",nCpt,nCptJeu);
            //J'ai ecrit cette fonction car j'avais un probleme d'incrementation
            //et je voulais voir a quel moment cela se produisait
        }
        else
        {
            for(i=0;i<5;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(nTab[i][j]==0)
                    {
                        nTab[i][j]=nCpt+1;
                    }
                }
            }
        }
    }


    afficher(nTab);
    return 0;
}

/*-----------------------------------
 Descriptions : Initialisation du tableau, on remplace les valeurs par 0
 Entrées : Tableau à 2 dimensions, 5 par 5
 Sorties : Tableau 5 par 5 dont toutes les valeurs sont 0
-----------------------------------*/

void initTab(int nTab[][5])
{
    int i,j;

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            nTab[i][j]=0;
        }
    }
}

/*-----------------------------------
 Descriptions : Affiche les valeurs du tableau
 Entrées : Tableau a 3 dimensions
 Sorties : Affichage du tableau avec 5 elements par ligne sur 5 lignes
-----------------------------------*/

void afficher(int nTab[][5])
{
    int i,j;

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            printf("%d\t",nTab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*-----------------------------------
 Descriptions : Cette fonction teste la disponibilité de la case actuelle, elle renvoi 1 si c'est disponible
 Entrées : Tableau a 2 dimensions, 5 par 5 et un jeton qui a des coordonnes x et y
 Sorties : On connait la disponibilité de la case (1 = dispo || 0 = occupe)
-----------------------------------*/

int caseVide(int nTab[][5],tJeton j){

    int nValeur;

    if (nTab[j.nX][j.nY]==0){
        nValeur=1;
    }
    else{
        nValeur=0;
    }
    return nValeur;
}

/*-----------------------------------
 Descriptions : Cette fonction permet de ne pas sortir du tableau, quand on arrive à une extremite,
                le jeton est ramene de l'autre cote, comme si les bords du tableau se rejoignaient
 Entrées : La position du jeton grace a ses valeurs x et y
 Sorties : Si necessaire, le jeton est envoye de l'autre cote du tableau
-----------------------------------*/

tJeton corriger(tJeton j){

    if (j.nX>4 && j.nY>=0)
    {
        j.nX=0;
    }
    else if (j.nX>=0 && j.nY>4)
    {
        j.nY=0;
    }

    else if(j.nX<0 && j.nY>=0)
    {
        j.nX=4;
    }

    else if(j.nX>=0 && j.nY<0)
    {
        j.nY=4;
    }
    else if(j.nX>=0 && j.nY>=5)
    {
        j.nY=4;
    }

    return j;
}

/*-----------------------------------
 Descriptions : Cette fonction permet d'effectuer le deplacement diagonale droit, il donne +1 a Y et -1 a X
 Entrées : Coordonnes X et Y du jeton
 Sorties : Nouveaux coordonnes X et Y du jeton
-----------------------------------*/

tJeton avancerDroite(tJeton j){

    j.nX-=1;
    j.nY+=1;
    return corriger(j);
}

/*-----------------------------------
 Descriptions : Cette fonction permet d'effectuer le deplacement diagonale gauche, il donne -1 a Y et -1 a X
 Entrées : Coordonnes X et Y du jeton
 Sorties : Nouveaux coordonnes X et Y du jeton
-----------------------------------*/

tJeton avancerGauche(tJeton j){

    j.nX-=1;
    j.nY-=1;
    return corriger(j);
}

/*-----------------------------------
 Descriptions : Cette fonction permet d'ecraser la valeur actuelle du tableau pour la remplacer par celle voulue
 Entrées : tableau 2 dimensions, jeton et compteur pour ecraser la valeur du tableau
 Sorties : La valeur dans le tableau est ecrasee par la nouvelle
-----------------------------------*/

void placer(int nTab[][5],tJeton j,int nCpt)
{
    nTab[j.nX][j.nY]=nCpt;
}

/*-----------------------------------
 Descriptions : Cette fonction permet d'effectuer le deplacement vers la droite/gauche
 Entrées : Tableau 2 dims, coordonnes X et Y du jeton
 Sorties : Nouveaux coordonnes X et Y du jeton
-----------------------------------*/

tJeton avancer(int nTab[][5],tJeton j,int nCpt){


    if (caseVide(nTab,j)==1){
        placer(nTab, j, nCpt);
    }
    else{

        j=avancerGauche(j);
        placer(nTab, j, nCpt);
    }
    j=avancerDroite(j);
    return j;
}




