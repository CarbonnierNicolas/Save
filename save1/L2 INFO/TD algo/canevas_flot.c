#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct { //graphe représenté par une matrice d'adjacence
  	int nombre_sommet;
  	int ** capacite; //poids de l'arc, 0 quand il n'y a pas d'arcs
  	int ** flot;
} graphe;

//le sommet 0 est la source et le sommet 1 est le puit


void affiche_graphe(graphe G){
	int i,j;
	printf("Graphe avec %d sommets \n",G.nombre_sommet);
	for(i = 0; i<G.nombre_sommet; i++){
		printf("Voisins de %2d: ",i);
		for(j = 0; j < G.nombre_sommet; j++){
			if(G.capacite[i][j]) printf(" %2d: (%2d / %2d) ",j,G.flot[i][j],G.capacite[i][j]);
		}
		printf("\n");
	}
}


graphe init_graphe(int n){//créé un graphe dont tous les sommets sont isolés
	graphe G; int i;
	G.nombre_sommet = n;
	G.capacite = malloc(sizeof(int*)*n);
	G.flot = malloc(sizeof(int*)*n);
	for(i = 0; i<G.nombre_sommet; i++){
		G.capacite[i] = calloc(n,sizeof(int));
		G.flot[i] = calloc(n,sizeof(int));
	}
	return G;
}

void libere_graphe(graphe G){
	int i;
	for(i = 0; i<G.nombre_sommet; i++){
		free(G.capacite[i]);
		free(G.flot[i]);
	}
	free(G.flot);
	free(G.capacite);
}


graphe alea_graphe(int n, float p, int valeurmax){
	graphe G = init_graphe(n);	
	int i,j;
	for(i = 0; i < n; i++){
		for(j = 1; j < n; j++){
			if(rand()%1000 < p*1000 && i!=1 && !G.capacite[j][i] && i!=j) {
				G.capacite[i][j] = 1 + rand()%valeurmax;
			}
		}
	}
	return G;
}

void graphe_residuel(graphe G, graphe H){ //calcul du graphe résiduel (différence entre flot et capacité)
	for(int i=0; i < H.nombre_sommet; i++){
		for(int j = 0; j < H.nombre_sommet; j++){
			if(G.capacite[i][j]){
				H.capacite[i][j] = (G.capacite[i][j]-G.flot[i][j]);
				H.capacite[j][i] = G.flot[i][j];
			}
		}
	}	
}

int calcul_chemin(graphe G, int *pere){ 
	int sommet = 1;//on part du sommet d'arrivé et on remonte jusqu'au sommet de départ
	int min = 100;//valeur max
	printf("TEST\n");
	while(sommet)
	{
		if(min>G.capacite[pere[sommet]][sommet])
		{
			min=G.capacite[pere[sommet]][sommet];
		}
		sommet=pere[sommet];
	}
	sommet=1;
	while(sommet)
	{
		G.flot[pere[sommet]][sommet]=min;
		sommet=pere[sommet];
	}
	free(pere);
	return min;
}

int chemin_ameliorant(graphe G){//calcul un chemin améliorant dans le graphe résiduel, renvoie sa capacité
	int *pile = malloc(G.nombre_sommet*sizeof(int));
	int * pere = malloc(G.nombre_sommet*sizeof(int));
	//on initialise tous les père à -1 -> non marqué == père à -1 et marqué == père >=0
	for(int i=0; i<G.nombre_sommet;i++) pere[i] = -1;
	int taille_pile = 0;
	int sommet;
	pile[0] = 0; //le parcours commence du sommet 0 et s'arrête dès qu'on a trouvé le sommet 1
	pere[0] = 0;
	while(taille_pile >= 0){
		sommet=pile[taille_pile];
		taille_pile--;
		for(int j=0;j<G.nombre_sommet;j++)
		{
			if(G.capacite[sommet][j] && pere[j]==-1)
			{
				taille_pile++;
				pere[j]=sommet;
				pile[taille_pile]=j;
				if(j==1) return calcul_chemin(G,pere);
			}
		}
				

	}
	return 0;
}

void ameliore_flot(graphe G, graphe H){ //améliore le flot du graphe G en utilisant un chemin améliorant stocké dans H
	for(int i=0;i<G.nombre_sommet;i++)
	{
		for(int j=0;j<G.nombre_sommet;j++)
		{
			if(G.flot[i][j]) G.flot[i][j]+=H.flot[i][j];
			if(G.flot[j][i]) G.flot[j][i]-=H.flot[j][i];
		}
	}
}

int flot_max(graphe G){
	graphe H = init_graphe(G.nombre_sommet);
	graphe_residuel(G,H);
	while(chemin_ameliorant(H)){
		ameliore_flot(G,H);
		graphe_residuel(G,H);
		//affiche_graphe(G);
		//affiche_graphe(H);
	}
	int res = 0;
	for(int i = 0; i < G.nombre_sommet; i++) res += G.flot[0][i];
	libere_graphe(H);
	return res;
}

void coupe(graphe G){//affiche la coupe correspondant au flot calculé
	int* marquage = calloc(G.nombre_sommet,sizeof(int));
	int *pile = malloc(G.nombre_sommet*sizeof(int));
	int taille_pile = 0;
	int sommet;
	pile[0] = 0; //le parcours commence du sommet 0 et s'arrête dès qu'on a trouvé le sommet 1
	marquage[0] = 1;
	while(taille_pile >= 0){
		
	}
	
}


int main(){
	srand(time(NULL));
 	/* À décommenter au fur et à mesure pour tester votre programme */
	graphe A = alea_graphe(20,0.2,100);
	affiche_graphe(A);
	graphe B = init_graphe(A.nombre_sommet);
	graphe_residuel(A,B);
	affiche_graphe(B);
	printf("%d \n", chemin_ameliorant(B));
	affiche_graphe(B);
	flot_max(A);
	affiche_graphe(A);
	//coupe(A);
	libere_graphe(A);
}
