/**
 * \file cesar.h
 * \brief Projet de Système
 * \author CARBONNIER Nicolas, SOTTAS Jean-Charles
 * 
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>

#define MAXBUF 512

/**
 * \struct info
 * \brief Information sur le fichier principal.
 *
 * Info est une structure d'information sur le contenu du fichier principal. 
 * Sauvegarde le nombre de lignes du fichier, et le contenu des lignes.
 */
struct info {
	int taille;      				/*!< Nombre de lignes */
	char ligne[MAXBUF][MAXBUF];		/*!< Contenu de la ligne */
	int taille_ligne[MAXBUF]; 	/*!< Nombre de caractères dans une ligne*/
};
typedef struct info INFO;
/**
 * \struct encodage
 * \brief Information sur les sous fichiers.
 *
 * Encodage est une structure d'information sur le contenu des sous fichiers. 
 * Sauvegarde un caractère, son encodage et le thread qui l'utilise.
 */
struct encodage {
	pthread_t ph;					/*!< Numéro du thread */
	int pas;						/*!< Nombre de décalage servant au codage ou au décodage */
	char caractere;					/*!< Caractère lu */
};
typedef struct encodage ENCODAGE;

/**
 * \fn INFO lire_fichier(char *fichier)
 * \brief Fonction qui lit un fichier
 * \return I 
 */
INFO lire_fichier(char *fichier)
{
	INFO I;
	int fichier_principal, i = 0, j = 0;
	char tmp;
	fichier_principal = open(fichier, O_RDONLY);
	if (fichier_principal == -1)
		exit(EXIT_FAILURE);
	while ((read(fichier_principal, &tmp, 1))==1) {
		if (tmp == 10) {
			I.ligne[i][j] = '\0';
			I.taille_ligne[i]=j;
			i++;
			j = 0;
		} else {
			I.ligne[i][j] = tmp;
			j++;
		}
	}
	I.ligne[i][j] = '\0';
	I.taille_ligne[i]=j;

	close(fichier_principal);
	I.taille = i;
	return I;
}
/**
 * \fn void ecrire_fichier(char buffer[], char fichier[])
 * \brief Fonction qui écrit dans un fichier
 * La fonction modifier le nom du fichier afin d'obtenir l'extention cryptée au nom du fichier.
 * Le fichier créé avec les mêmes droits et à la même adresse.
 * \return NULL 
 */
void ecrire_fichier(char buffer[], char fichier[])
{
	//modifier le nom du fichier pour avoir l'extention _cyphex
	struct stat src;
	stat(fichier, &src);
	int i, j, k, compt_ptvir = 0, compt_pt = 0, addr = 0;
	for (i = 0; fichier[i] != 0; i++) {
		if (fichier[i] == 47) {
			compt_ptvir++;
			compt_pt = 0;
			addr = i;
		}
		if (fichier[i] == 46) {
			compt_pt++;

		}
	}
	char extention[] = "_cypher";
	char new_fichier[MAXBUF]={0};
	if (addr != 0) {
		for (i = 0; i < addr; i++) {
			new_fichier[i] = fichier[i];
		}
	}
	if (compt_pt == 0) {
		for (i = addr; fichier[i] != 0; i++) {
			new_fichier[i] = fichier[i];
		}
		for (i = 0; extention[i] != 0; i++) {
			new_fichier[i] = extention[i];
		}
	} else {
		for (i = addr; fichier[i] != 46; i++) {
			new_fichier[i] = fichier[i];
		}
		k = i;
		for (j = 0; extention[j] != 0; j++) {
			new_fichier[i] = extention[j];
			i++;
		}
		for (j = k; fichier[j] != 0; j++) {
			new_fichier[i] = fichier[j];
			i++;
		}
	}
	int fc;
	fc = open(new_fichier, O_CREAT | O_WRONLY, src.st_mode);
	for (i = 0; buffer[i] != 0; i++) {
		write(fc, &buffer[i], 1);
	}
	close(fc);

}
/**
 * \fn void *encryptage(void *code)
 * \brief Processus employé, qui permet l'encryptage du mot avec le nombre de décalage
 * 
 * \return code 
 */
void *encryptage(void *code)
{
	int n;
	ENCODAGE *c = (ENCODAGE *) code;

	if ((c->caractere >= 65 && c->caractere <= 90)
	    || (c->caractere >= 97 && c->caractere <= 122)) {
		if (c->caractere >= 65 && c->caractere <= 90) {
			n = 0;
		} else {
			n = 1;
		}
		c->caractere =
		    (c->caractere - 65 - (n * 32) + c->pas + 26) % 26 + 65 +
		    (n * 32);
	}
	//printf("%c \n",c->caractere);
	pthread_exit(NULL);
}
/**
 * \fn void *decryptage(void *code)
 * \brief Processus employé, qui permet le décryptage du mot avec le nombre de décalage
 * 
 * \return code 
 */
void *decryptage(void *code)
{

	int n;
	ENCODAGE *c = (ENCODAGE *) code;

	if ((c->caractere >= 65 && c->caractere <= 90)
	    || (c->caractere >= 97 && c->caractere <= 122)) {
		if (c->caractere >= 65 && c->caractere <= 90) {
			n = 0;
		} else {
			n = 1;
		}
		c->caractere =
		    (c->caractere - 65 - (n * 32) - c->pas + 26) % 26 + 65 +
		    (n * 32);
	}
	pthread_exit(NULL);
}
/**
 * \fn void *encryptage(void *code)
 * \brief Processus chef d'équipe, qui ouvre le sous fichier et envoie 
 * 	au processus employé un mot du fichier, si le mot est à encrypter il
 * 	l'envoie à l'employé encrypter sinon à l'employé décrypter
 * \return retourne decoder si le message est à decoder ou retourne NULL s'il est à encrypter 
 */
char *chef_dequipe(char information[])
{
	char decoupe[3][MAXBUF] = {{0}};
	int i = 0, j = 0, k;
	for (k = 0; information[k] != '\0'; k++) {
		if (information[k] == ';') {
			j = 0;
			i++;
		} else {
			decoupe[i][j] = information[k];
			j++;
		}
	}
	int fichier_principal, cmpt = 0;
	fichier_principal = open(decoupe[0], O_RDONLY);
	ENCODAGE code[MAXBUF];
	for(i=0;i<MAXBUF;i++)
	{
		code[i].ph=0;
		code[i].caractere=0;
		code[i].pas=0;
	}
	if (fichier_principal == -1)
		EXIT_FAILURE;
	while (read(fichier_principal, &code[cmpt].caractere, 1)==1) {
		code[cmpt].pas = atoi(decoupe[1]);
		if (decoupe[2][0] == 100) {
			if(pthread_create(&code[cmpt].ph, NULL, &decryptage,(void *)&code[cmpt])==-1)
			exit(EXIT_FAILURE);
		} else {
			if(pthread_create(&code[cmpt].ph, NULL, &encryptage,(void *)&code[cmpt])==-1)
			exit(EXIT_FAILURE);
		}
		cmpt++;
	}
	close(fichier_principal);
	char *decoder =malloc((cmpt+1)*sizeof(char));
	for(i=0;i<cmpt+1;i++)
	{
		decoder[i] = 0; 
	}
	for (i = 0; i <= cmpt; i++) {
		 pthread_join(code[i].ph, NULL);
		decoder[i] = code[i].caractere;
	}
	if (decoupe[2][0] == 99) {
		ecrire_fichier(decoder, decoupe[0]);
		free(decoder);
	}
	else {
		return decoder;
	}

	return NULL;
}

/**
 * \fn main(int arg, char *argv[])
 * \brief Entrée du programme
 * 	
 * \return return 0 si succès sinon EXIT_FAILURE s'il y a une erreur
 */
int main(int arg, char *argv[])
{

	INFO I;
	int i;
	if (arg <= 1) {
		perror("nombre d'arguments");
		return EXIT_FAILURE;
	}
	I = lire_fichier(argv[1]);

	pid_t pid[I.taille];
	int tube1[I.taille][2];
	int tube2[I.taille][2];
	char chaine[MAXBUF]={0};
	char *motretour={0};
	for (i = 0; i < I.taille; i++) {
		pipe(tube1[i]);
		pipe(tube2[i]);
		pid[i] = fork();
		if (pid[i] == -1) {
			perror("Impossible de créer un fils ");
			return EXIT_FAILURE;
		} if (pid[i] == 0) {

			close(tube1[i][1]);close(tube2[i][0]);
			
			read(tube1[i][0], chaine, MAXBUF);
			motretour=chef_dequipe(chaine);
	
			if (motretour != NULL) {
				write(tube2[i][1], motretour,strlen(motretour));
			}else {
				char chainebase[] = "C";
				write(tube2[i][1], chainebase,2);
			}
			 free(motretour);
			
			close(tube1[i][0]);close(tube2[i][1]);
			
			exit(EXIT_SUCCESS) ;
		} else {
			close(tube1[i][0]);close(tube2[i][1]);
			write(tube1[i][1], I.ligne[i], I.taille_ligne[i]);
			close(tube1[i][1]);
		}
	}
	int fini;
	fini = 0;
	int j;
	char affiche[I.taille][MAXBUF];
	for(i=0;i<I.taille;i++){
		for(j=0;j<MAXBUF;j++){
		affiche [i][j]=0;
		}}
	while (!fini) {
		fini = 1;
		for (i = 0; i < I.taille; i++) {
			if (pid[i] > 0) {
				waitpid(pid[i], 0, WNOHANG); 
					read(tube2[i][0],affiche[i],MAXBUF);
					if(strcmp(affiche[i],"C"))
						printf("Le message en clair du fichier %d est : %s \n",i + 1, affiche[i]);
					pid[i] = 0;
					close(tube2[i][0]);
				
			} else {
				fini = 0;
			}
		}
	}
	return 0;
}
