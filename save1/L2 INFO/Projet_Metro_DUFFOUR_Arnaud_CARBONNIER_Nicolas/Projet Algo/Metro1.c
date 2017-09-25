/**
 * \file Metro1.c
 * \brief Projet d'Algo
 * \author DUFOUR Arnaud & CARBONNIER Nicolas
 * \version 1.0
 * \date 3 Mai 2017
 * 
 * Programme pour trouver le plus court chemin entre deux stations de métro parisien.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#define TAILLEMAX 128
#define N 382
#define POSMAX 50
#define MAX 9999

/**
 * \struct L_STATION
 * \brief Liste de station de métro
 * 
 * L_STATION est une liste de station de métro qui permet de contenir le trajet entre les deux stations de départ et d'arrivée.
 * Le dernier élément pointe sur NULL
 */
struct station
{
	int S;					/*!< Sommet de la station */
	struct station * suiv;	/*!< Pointeur sur la station suivante */
};
typedef struct station* L_STATION;

/**
 * \fn int somme(int Tab[])
 * \brief Fonction pour sommer les sommets afin de vérifier qu'on les as tous parcouru.
 * 
 * \param Tab[] tableau des éléments à sommer
 * \return s pour la somme des éléments
 */
int somme(int Tab[])
{
	int i;
	int s = 0;
	
	for(i = 0;i<383;i++)
	{
		s = s+Tab[i];
	}
	//~ printf("%d\n",s);
	return s;
}

/**
 * \fn L_STATION L_initialize()
 * \brief Fonction pour initialiser la liste de station.
 * 
 * \param Aucun
 * \return NULL pour l'initialisation
 */
L_STATION L_initialize()
{
	return NULL;
}


/**
 * \fn L_STATION ADD_station(L_STATION S,int s)
 * \brief Fonction pour ajouter une station a la liste et donc au trajet.
 * 
 * \param S la liste des stations déjà existente
 * \param s sommet/station à ajouter a la liste
 * \return
 */
L_STATION ADD_station(L_STATION S,int s)
{
	L_STATION new;
	new = malloc(sizeof(struct station));
	new->S = s;
	new->suiv = S;
	return new;
}

L_STATION CREAT_trajet(int pere[],int arrive)
{
	L_STATION trajet;
	trajet = L_initialize();
	while(arrive != -1)
	{
		trajet = ADD_station(trajet,arrive);
		arrive = pere[arrive];
	}
	return trajet;
}

int cherche_terminus(L_STATION trajet,short position[],char* lignes[])
{
	L_STATION Liste = trajet;
	int terminus = position[Liste->S];
	int sommet_terminus = Liste->S;
	int i;
	char ligne[TAILLEMAX];
	strcpy(ligne, lignes[Liste->S]);
	if(position[Liste->suiv->S]<terminus && ((strcmp(ligne,lignes[Liste->S]))==0))
	{
		for(i=0;i<=N;i++)
		{
			if(((strcmp(ligne,lignes[i]))==0) && position[i]<terminus)
			{
				terminus = position[i];
				sommet_terminus = i;
			}
		}
	}
	else
	{
		if(position[Liste->suiv->S]>terminus && ((strcmp(ligne,lignes[Liste->S]))==0))
		{
			for(i=0;i<=N;i++)
			{
				if(((strcmp(ligne,lignes[i]))==0) && position[i]>terminus)
				{
					terminus = position[i];
					sommet_terminus = i;
				}
			}
		}
	}	
	return sommet_terminus;
}

void AFFICHE_trajet(L_STATION trajet,char* noms[],char* lignes[],short** distance,short position[])
{
	L_STATION Liste = trajet;
	printf("Vous êtes à %s.\n",noms[Liste->S]);
	int terminus,terminus_prec;
	char ligne[TAILLEMAX];
	strcpy(ligne, lignes[Liste->S]);
	terminus = cherche_terminus(Liste,position,lignes);
	terminus_prec = terminus;
	printf("Prenez la ligne %s direction %s\n",ligne,noms[terminus]);
	int temps=0;
	while(Liste != NULL)
	{
		if((Liste->suiv)==NULL)
		{
			printf("Vous devriez arriver à %s dans %dmin et %ds.\n",noms[Liste->S],(temps/60),(temps%60));
			Liste = Liste->suiv;
		}
		else
		{
			terminus = cherche_terminus(Liste,position,lignes);
			temps = temps + distance[Liste->S][Liste->suiv->S];
			if((strcmp(ligne,lignes[Liste->S]))!=NULL && (terminus!=terminus_prec))
			{
				
				printf("À %s, prenez la ligne %s direction %s.\n",noms[Liste->S],lignes[Liste->S],noms[terminus]);
				Liste = Liste->suiv;
				strcpy(ligne, lignes[Liste->S]);
				terminus_prec = terminus;
			}
			else
			{
				Liste = Liste->suiv;
			}
		}
	}
}

void FREE_trajet(L_STATION trajet)
{
		if(trajet == NULL)
		{
			free(trajet);
		}
		else
		{
			FREE_trajet(trajet->suiv);
			free(trajet);
		}
}


int min(int distance[],int used[])
{
	int i = 0;
	int next;
	
	while(used[i] != 0)
	{
		i++;
	}
	
	next = i;
	i++;
	
	for(i;i<383;i++)
	{
		if(distance[i]!= -1 && (distance[i]<distance[next] || distance[next] == -1) && !used[i])
		{
			next = i;
		}
	}
	return next;
}

void utilise(int S,int distance_sommet[],int pere[],int used[],short** distance)
{
	int i;
	
	used[S] = 1;
	for(i = 0;i<N+1;i++)
	{
		if(distance[S][i])
		{
			if((distance[S][i]+distance_sommet[S])<distance_sommet[i] || distance_sommet[i] == -1)
			{
				pere[i] = S;
				distance_sommet[i] = distance[S][i]+distance_sommet[S];
			}
		}
	}
}
	
void times(int depart,short** distance,int distance_sommet[],int pere[])
{
	int used[383];
	int i,next;
	
	for(i = 0;i<N+1;i++)
	{
		used[i] = 0;
		distance_sommet[i] = -1;
		pere[i] = -2;
	}
	
	distance_sommet[depart] = 0;
	pere[depart] = -1;
	
	while(somme(used) != N+1)	///////////////////////////////////////
	{
		next = min(distance_sommet,used);
		utilise(next,distance_sommet,pere,used,distance);
	}
}

int main(int argc,char **argv)
{
	char *noms[383];								//Tableau pour stocker des chaines de caracteres, ici les noms des stations
	char *lignes[383];								//Tableau pour stocker des chaines de caracteres, ici les lignes des stations
	short** distance;								//Tableau pour stocker le temps entre deux sommets/stations
	if(argc != 3)
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
	char debut[TAILLEMAX];
	char fin[TAILLEMAX];
	strcpy(debut,argv[1]);
	strcpy(fin,argv[2]);
	int depart = -1;
	int arrive = -1;
	
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
	if(depart==-1)
	{
		perror("station de départ introuvable");
		exit(1);
	}
	if(arrive==-1)
	{
		perror("station d'arrivée introuvable");
		exit(1);
	}
	
	times(depart,distance,distance_sommet,pere);
	
	L_STATION trajet;
	trajet = CREAT_trajet(pere,arrive);
	AFFICHE_trajet(trajet,noms,lignes,distance,position);
	
	for(i=0; i<=382; i++)							//Libération de la mémoire
	{
		free(noms[i]);
		free(lignes[i]);
	}
	for(j = 0;j<=382;j++)
	{
		free(distance[j]);
	}
	free(distance);
	fclose(Fichier);
	exit(0);
}

