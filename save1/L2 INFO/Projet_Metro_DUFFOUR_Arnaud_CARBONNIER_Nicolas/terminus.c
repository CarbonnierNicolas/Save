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

//fichier de calcule et traitement de terminus

L_TERMINUS ADD_terminus(L_TERMINUS term,char* ligne,short position,char* noms) //ajout d'un terminus a la chaine.
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
		if(position > term->TF)
		{
			term->TF = position;
			term->TFN = noms;
		}
		return term;
	}
	term->suiv = ADD_terminus(term->suiv,ligne,position,noms);
	return term;
}

L_TERMINUS LT_initialize()
{
	return NULL;
}

L_TERMINUS CALCULE_terminus(char *lignes[383],short position[383],char* noms[383]) //calcule de tous les terminus.
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

void FREE_terminus(L_TERMINUS term) //liberation des terminus
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

char* RECHERCHE_terminusD(char* ligne,L_TERMINUS term)// recherche du premier terminus d'une ligne
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

char* RECHERCHE_terminusF(char* ligne,L_TERMINUS term)// recherche du dernier terminus d'une ligne
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


