//DUFOUR Arnaud 21505093
//CARBONNIER Nicolas 21404875
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#include "types.h"
#include "terminus.h"
#include "trajet.h"
#include "chemin.h"


// fonction d'affichage
void AFFICHE_trajet(L_STATION trajet,char* noms[],char* lignes[],short** distance,L_TERMINUS term,short position[383])
{
	int temps=0;
	printf("Vous êtes à %s sur la ligne %s.\n",noms[trajet->S],lignes[trajet->S]);
	if(strcmp(lignes[trajet->S],lignes[trajet->suiv->S])) //un test si changement de ligne des le depart.
	{
		printf("dirigez vous vers la ligne %s de la station %s.\n",lignes[trajet->S],noms[trajet->S]);
		trajet = trajet->suiv;
		if(position[trajet->S] > position[trajet->suiv->S])	//puis continuation sur la ligne
		{
			printf("suivez la ligne %s direction %s.\n",lignes[trajet->S],RECHERCHE_terminusD(lignes[trajet->S],term));
		}
		else
		{
			printf("suivez la ligne %s direction %s.\n",lignes[trajet->S],RECHERCHE_terminusF(lignes[trajet->S],term));
		}
	} 
	else //ou depart classique sur la ligne
	{
		if(position[trajet->S] > position[trajet->suiv->S])
		{
			printf("suivez la ligne %s direction %s.\n",lignes[trajet->S],RECHERCHE_terminusD(lignes[trajet->S],term));
		}
		else
		{
			printf("suivez la ligne %s direction %s.\n",lignes[trajet->S],RECHERCHE_terminusF(lignes[trajet->S],term));
		}
		temps = temps + distance[trajet->S][trajet->suiv->S];
		trajet = trajet->suiv;
	}
	
	while(trajet->suiv != NULL) //enfin une boucle qui repettent un suivit de lignes et des changements de lignes.
	{
		temps = temps + distance[trajet->S][trajet->suiv->S];
		if(strcmp(lignes[trajet->S],lignes[trajet->suiv->S]))
		{
			printf("arretez vous a la station %s.\n",noms[trajet->S]);
			printf("dirigez vous vers la ligne %s.\n",lignes[trajet->suiv->S]);
			trajet = trajet->suiv;
			if(trajet->suiv != NULL)
			{
				if(position[trajet->S] > position[trajet->suiv->S])
				{
				printf("suivez la ligne %s direction %s.\n",lignes[trajet->S],RECHERCHE_terminusD(lignes[trajet->S],term));
				}
				else
				{
				printf("suivez la ligne %s direction %s.\n",lignes[trajet->S],RECHERCHE_terminusF(lignes[trajet->S],term));
				}
			}
		}
		else
		{
			trajet = trajet->suiv;
		}
	}
	printf("arretez vous a %s.\nVous etes arrivé.\nVous devriez y être en %dmin et %ds\n",noms[trajet->S],(temps/60),(temps%60));
}


int main(int argc,char **argv)
{
	short** distance;								//Tableau pour stocker le temps entre deux sommets/stations
	char *noms[383];								//Tableau pour stocker des chaines de caracteres, ici les noms des stations
	char *lignes[383];								//Tableau pour stocker des chaines de caracteres, ici les lignes des stations
	if(argc != 4)
	{
		printf("too few arguments\n");
		exit(1);
	}
	int j,q;
	distance = malloc((N+1) * sizeof(short*));
	for(j = 0;j<=N;j++)								//Initialisation du tableau des temps entre les stations
	{
		distance[j] = malloc((N+1) * sizeof(short));
		*distance[j] = 0;
	}
	short position[383]; 
	int distance_sommet[383];
	int pere[383];
	int depart;
	int arrive;
	char debut[TAILLEMAX];
	char fin[TAILLEMAX];
	
	if(!(strcmp(argv[1],"-nm")))
	{
	strcpy(debut,argv[2]);
	strcpy(fin,argv[3]);
	}
	if(!(strcmp(argv[1],"-nb")))
	{
		depart = atoi(argv[2]);
		arrive = atoi(argv[3]);
	}
	
	FILE* Fichier = fopen("metro.txt", "r");		//Ouverture du fichier où sont stocker toutes les infos
	if(Fichier == NULL)								//Verification de l'ouverture
	{
		perror("cannot open file");
		exit(1);
	}
	
	int b;
	short f;
	char c[TAILLEMAX];								//Chaine de caractere
	char d[TAILLEMAX];								//Chaine de caractere
	char a, e;
	int i,smt1,smt2;
	short temps;
	int x;
	
	for(i=0; i<=1730; i++)							//Lecture du fichier
	{
		fscanf(Fichier, "%c %d %s %hd %s",&a, &b, &c, &f, &d);
		if(a == 'V')
		{
			x=i/2;
			noms[x] = malloc(strlen(d)+1);
			strcpy(noms[x], d);						//Stocke les noms de chaque sommets/stations dans un tableau de chaine de caractere
			lignes[x] = malloc(strlen(c)+1);
			strcpy(lignes[x], c);					//Stocke les lignes de metro de chaque sommets/stations dans un tableau de chaine de caractere
			position[x]=f;
			//~ printf("%2d	%2d	nom : %2s	ligne : %2s	position : %2d\n",i, x, noms[x], lignes[x], position[x]);
		}
		else
		{
			if(a == 'E')
			{
				smt1=b;
				smt2=atoi(c);
				temps=f;
				distance[smt1][smt2] = temps;		//Stocke le temps entre deux sommets/stations
				distance[smt2][smt1] = temps;		//Stocke le temps entre deux sommets/stations
				//~ printf("i = %d	%d	et	%d	temps : %d secondes\n",i,smt1,smt2, temps);
			}
		}	
	}
	
	/*Stations avec sens*/
	distance[198][36] = MAX;
	distance[52][198] = MAX;
	distance[201][52] = MAX;
	distance[198][259] = MAX;
	distance[259][196] = MAX;
	distance[196][373] = MAX;
	distance[373][201] = MAX;
	distance[373][145] = MAX;
	distance[248][34] = MAX;
	distance[34][92] = MAX;
	distance[92][280] = MAX;
	distance[280][34] = MAX;
	distance[280][248] = MAX;
	
	//~ printf("nom : %s	ligne : %s position : %d\n", noms[0], lignes[0], position[0]);
	if(!(strcmp(argv[1],"-nm")))
	{
		for(j=0;j<=N;j++)
		{
			if(!(strcmp(debut,noms[j])))
			{
				depart = j;
			}
			if(!(strcmp(fin,noms[j])))
			{
				arrive = j;
			}
		}
	}
	//~ printf("Vous partez de %s pour arrivez à %s\n\n",noms[depart],noms[arrive]);
	
	times(depart,distance,distance_sommet,pere);
	
	L_STATION trajet;
	L_TERMINUS term;
	trajet = CREAT_trajet(pere,arrive);	
	term = CALCULE_terminus(lignes,position,noms);
	AFFICHE_trajet(trajet,noms,lignes,distance,term,position);
	
	for(i=0; i<=382; i++)							//Libération de la mémoire
	{
		free(noms[i]);
		free(lignes[i]);
	}
	FREE_trajet(trajet);
	FREE_terminus(term);
	for(j = 0;j<=382;j++)
	{
		free(distance[j]);
	}
	free(distance);
	fclose(Fichier);
	exit(0);
}

