//DUFOUR Arnaud 21505093
//CARBONNIER Nicolas 21404875
#ifndef TYPE
#define TYPE

#define TAILLEMAX 128
#define N 382
#define POSMAX 50
#define MAX 9999

struct station
{
	int S;
	struct station * suiv;
};
typedef struct station* L_STATION;

struct terminus
{
	char* ligne;
	int TD;
	int TF;
	struct terminus * suiv;
	char* TFN;
	char* TDN;
};
typedef struct terminus* L_TERMINUS;
#endif

