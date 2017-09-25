/**
 * \file Metro1.c
 * \brief Projet d'Algo
 * \author DUFOUR Arnaud & CARBONNIER Nicolas
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
 * \struct L_TERMINUS
 * \brief Structure 
 * 
 * L_TERMINUS contient les terminus de la ligne.
 */
struct terminus
{
	char* ligne;			/*!< Ligne du terminus */
	int TD;					/*!< Sommet du terminus de début de ligne */
	int TF;					/*!< Sommet du terminus de fin de ligne */
	struct terminus * suiv;	/*!< Pointeur sur le terminus suivant */
	char* TFN;				/*!< Nom du terminus de début de ligne */
	char* TDN;				/*!< Nom du terminus de fin de ligne */
};
typedef struct terminus* L_TERMINUS;

/**
 * \fn int somme(int Tab[])
 * \brief Fonction pour sommer les sommets
 * 
 * \return s
 */
int somme(int Tab[])
{
	int i;
	int s = 0;
	
	for(i = 0;i<383;i++)
	{
		s = s+Tab[i];
	}
	return s;
}

/**
 * \fn L_STATION LS_initialize()
 * \brief Fonction pour initialiser la liste de station.
 * 
 * \return NULL
 */
L_STATION LS_initialize()
{
	return NULL;
}

/**
 * \fn L_TERMINUS LT_initialize()
 * \brief Fonction pour initialiser la liste de terminus.
 * 
 * \return NULL
 */
L_TERMINUS LT_initialize()
{
	return NULL;
}

/**
 * \fn L_STATION ADD_station(L_STATION S,int s)
 * \brief Fonction pour ajouter une station a la liste et donc au trajet.
 * 
 * \return new pour la nouvelle liste implémenter de la nouvelle station.
 */
L_STATION ADD_station(L_STATION S,int s)
{
	L_STATION new;
	new = malloc(sizeof(struct station));
	new->S = s;
	new->suiv = S;
	return new;
}

/**
 * \fn L_STATION CREAT_trajet(int pere[],int arrive)
 * \brief Fonction qui va creer un trajet le plus court grace à un tableau des peres.
 * 
 * \return le trajet créé
 */
L_STATION CREAT_trajet(int pere[],int arrive)
{
	L_STATION trajet;
	trajet = LS_initialize();
	while(arrive != -1)
	{
		trajet = ADD_station(trajet,arrive);
		arrive = pere[arrive];
	}
	return trajet;
}

/**
 * \fn char* RECHERCHE_terminusD(char* ligne,L_TERMINUS term)
 * \brief Fonction de recherche du terminus de début de ligne.
 * 
 * \return le terminus de début de ligne.
 */
char* RECHERCHE_terminusD(char* ligne,L_TERMINUS term)
{
	if(!(strcmp(ligne,term->ligne)))
	{
		return term->TDN;
	}
	else
	{
		return RECHERCHE_terminusD(ligne,term->suiv);
	}
}

/**
 * \fn char* RECHERCHE_terminusF(char* ligne,L_TERMINUS term)
 * \brief Fonction de recherche du terminus de fin de ligne.
 * 
 * \return le terminus de fin de ligne.
 */
char* RECHERCHE_terminusF(char* ligne,L_TERMINUS term)
{
	if(!(strcmp(ligne,term->ligne)))
	{
		return term->TFN;
	}
	else
	{
		return RECHERCHE_terminusF(ligne,term->suiv);
	}
}

/**
 * \fn void AFFICHE_trajet(L_STATION trajet,char* noms[],char* lignes[],short** distance,L_TERMINUS term)
 * \brief Fonction d'affichage du détail du trajet.
 */
void AFFICHE_trajet(L_STATION trajet,char* noms[],char* lignes[],short** distance,L_TERMINUS term)
{
	//~ while(Liste != NULL)
	//~ {
		//~ if((Liste->suiv)==NULL)
		//~ {
			//~ printf("Vous devriez arriver à %s dans %dmin et %ds.\n",noms[Liste->S],(temps/60),(temps%60));
			//~ Liste = Liste->suiv;
		//~ }
		//~ else
		//~ {
			//~ if((strcmp(ligne,lignes[Liste->S]))!=NULL)
			//~ {
				//~ printf("À %s, prenez la ligne %s.\n",noms[Liste->S],lignes[Liste->S]);
				//~ Liste = Liste->suiv;
				//~ strcpy(ligne, lignes[Liste->S]);
			//~ }
			//~ else
			//~ {
				//~ Liste = Liste->suiv;
			//~ }
		//~ }
	//~ }
	
	int temps=0;
	printf("Vous êtes à %s sur la ligne %s.\n",noms[trajet->S],lignes[trajet->S]);
	if(strcmp(lignes[trajet->S],lignes[trajet->suiv->S]))
	{
		printf("dirigez vous vers la ligne %s de la station %s.\n",lignes[trajet->S],noms[trajet->S]);
		trajet = trajet->suiv;
		printf("suivez la ligne %s direction %s.\n",lignes[trajet->S],RECHERCHE_terminusD(lignes[trajet->S],term));
	}
	else
	{
		if(trajet->S > trajet->suiv->S)
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
	
	while(trajet->suiv != NULL)
	{
		temps = temps + distance[trajet->S][trajet->suiv->S];
		if(strcmp(lignes[trajet->S],lignes[trajet->suiv->S]))
		{
			printf("arretez vous a la station %s.\n",noms[trajet->S]);
			printf("dirigez vous vers la ligne %s.\n",lignes[trajet->suiv->S]);
			trajet = trajet->suiv;
			if(trajet->suiv != NULL)
			{
				if(trajet->S > trajet->suiv->S)
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

/**
 * \fn void FREE_trajet(L_STATION trajet)
 * \brief Fonction pour free la liste des stations du trajet.
 */
void FREE_trajet(L_STATION trajet)
{
		if(trajet->suiv == NULL)
		{
			free(trajet);
		}
		else
		{
			FREE_trajet(trajet->suiv);
			free(trajet);
		}
}

/**
 * \fn void FREE_terminus(L_TERMINUS term)
 * \brief Fonction pour free la liste des terminus.
 */
void FREE_terminus(L_TERMINUS term)
{
		if(term->suiv == NULL)
		{
			free(term);
		}
		else
		{
			FREE_terminus(term->suiv);
			free(term);
		}
}

/**
 * \fn int min(int distance[],int used[])
 * \brief Fonction
 * 
 * \return 
 */
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

/**
 * \fn void utilise(int S,int distance_sommet[],int pere[],int used[],short** distance)
 * \brief Fonction
 */
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

/**
 * \fn void times(int depart,short** distance,int distance_sommet[],int pere[])
 * \brief Fonction
 */
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
	
	while(somme(used) != N+1)
	{
		next = min(distance_sommet,used);
		utilise(next,distance_sommet,pere,used,distance);
	}
}

/**
 * \fn L_TERMINUS ADD_terminus(L_TERMINUS term,char* ligne,short position,char* noms)
 * \brief Fonction pour ajouter un terminus.
 * 
 * La fonction compare les position du sommet passer en argument et celui présent deja dans la structure L_TERMINUS.
 * 
 * \return term
 */
L_TERMINUS ADD_terminus(L_TERMINUS term,char* ligne,short position,char* noms)
{
	if(term == NULL)
	{
		term = malloc(sizeof(struct terminus));
		term->suiv = NULL;
		term->TD = 1;
		term->TF = position;
		term->ligne = ligne;
		term->TFN = noms;
		if(term->TF == 1)
		{
			term->TDN = noms;
		}
		else
		{
			term->TDN = "";
		} 
		return term;
	}
	if(!(strcmp(term->ligne,ligne)))
	{
		if(position == 1)
		{
			term->TDN = noms;
		}
		else if(position > term->TF)
		{
			term->TF = position;
			term->TFN = noms;
		}
		return term;
	}
	term->suiv = ADD_terminus(term->suiv,ligne,position,noms);
	return term;
}

/**
 * \fn L_TERMINUS CALCULE_terminus(char *lignes[383],short position[383],char* noms[383])
 * \brief Fonction pour calculer les terminus des lignes.
 * 
 * \return term
 */
L_TERMINUS CALCULE_terminus(char *lignes[383],short position[383],char* noms[383])
{
	L_TERMINUS term;
	int i;
	
	term = LT_initialize();
	
	for(i = 0;i<=N;i++)
	{
		term = ADD_terminus(term,lignes[i],position[i],noms[i]);
	}
	return term;
}

/**
 * \fn int main(int argc,char **argv)
 * \brief Entrée du programme
 * 
 * \return 0 si succes sinon 1 si échec
 */
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
	
	if(argv[1][2] == 'm')
	{
	strcpy(debut,argv[2]);
	strcpy(fin,argv[3]);
	}
	if(argv[1][2] == 'b')
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
	//~ if(argv[1][2] == 'm')
	//~ {
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
	//~ }
	//~ printf("Vous partez de %s pour arrivez à %s\n\n",noms[depart],noms[arrive]);
	
	times(depart,distance,distance_sommet,pere);
	
	L_STATION trajet;
	L_TERMINUS term;
	trajet = CREAT_trajet(pere,arrive);	
	term = CALCULE_terminus(lignes,position,noms);
	AFFICHE_trajet(trajet,noms,lignes,distance,term);

	
	
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

