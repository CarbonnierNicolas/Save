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

//fichier de calcule du plus court chemin.

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

int min(int distance[],int used[]) //recherche du sommet avec la plus petite distance relative non traité.
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

//focntion qui traite un sommet.
void utilise(int S,int distance_sommet[],int pere[],int used[],short** distance)
{
	int i;
	
	used[S] = 1;
	for(i = 0;i<N+1;i++)
	{
		if(distance[S][i]) // si il existe un chemin 
		{
			if((distance[S][i]+distance_sommet[S])<distance_sommet[i] || distance_sommet[i] == -1) //et qu'il est plus rapide et vers un sommet non traité
			{																					
				pere[i] = S;
				distance_sommet[i] = distance[S][i]+distance_sommet[S]; // on l'ajoute.
			}
		}
	}
}

//fonction principale
void times(int depart,short** distance,int distance_sommet[],int pere[])
{
	int used[383];
	int i,next;
	
	for(i = 0;i<N+1;i++) //initialisation des tableau
	{
		used[i] = 0;
		distance_sommet[i] = -1;
		pere[i] = -2;
	}
	
	distance_sommet[depart] = 0;
	pere[depart] = -1;
	
	while(somme(used) != N+1)
	{
		next = min(distance_sommet,used); //recherche du sommet suivant a traiter.
		utilise(next,distance_sommet,pere,used,distance); //traite du sommet.
	}
}

