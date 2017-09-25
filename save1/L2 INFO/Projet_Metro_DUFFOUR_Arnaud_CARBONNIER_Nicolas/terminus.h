//DUFOUR Arnaud 21505093
//CARBONNIER Nicolas 21404875
#include "types.h"

L_TERMINUS CALCULE_terminus(char *lignes[383],short position[383],char* noms[383]);

void FREE_terminus(L_TERMINUS term);

char* RECHERCHE_terminusD(char* ligne,L_TERMINUS term);

char* RECHERCHE_terminusF(char* ligne,L_TERMINUS term);
