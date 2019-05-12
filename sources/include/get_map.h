#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>

char* chemin_monde;
char* chemin_map;

struct monde;

char *readFile(char *fileName); // fonction qui permet de recupérer l'ensemble des caratères des fichiers


unsigned char chargement_carte(unsigned char * themap, char* chemin); // fonction qui va lire un fichier et recupère les informations de la carte

struct monde* monde_new(void);

struct monde* chargement_monde(struct monde* monde , char* chemin);

struct monde* monde_init(void);

//void recuperation_nom_carte(char * chemin,char * nom_carte, int i);

//char* get_monde_nom_niveau(struct monde* monde);

int get_monde_nombre_carte(struct monde * monde);
 //
