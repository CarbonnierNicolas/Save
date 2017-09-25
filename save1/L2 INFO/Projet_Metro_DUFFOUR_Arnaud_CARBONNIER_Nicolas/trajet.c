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

//fichier de cration du tajet selon le plus cours chemin.

L_STATION LS_initialize()
{
	return NULL;
}

void FREE_trajet(L_STATION trajet)//liberation du tajet
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

L_STATION ADD_station(L_STATION S,int s)//ajout d'une station au trajet
{
	L_STATION new;
	new = malloc(sizeof(struct station));
	new->S = s;
	new->suiv = S;
	return new;
}

L_STATION CREAT_trajet(int pere[],int arrive)// creation du trajet.
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
