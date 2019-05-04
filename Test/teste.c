#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <dirent.h>

#define MAX_CHAR_NIVEAU 64

struct monde {
	int nombre_carte;
	int level_debut;
	int ini_x, ini_y;
	char* nom_niveau;
};



 bool ext_match(const char *name, const char *ext) // fonction qui renvoie true si un fichier a la bonne extension
{
	size_t nl = strlen(name), el = strlen(ext);
	return nl >= el && !strcmp(name + nl - el, ext);
}


char* readFile(char *fileName) { // fonction qui permet de recupérer l'ensemble des caratères des fichiers
    FILE* file = fopen(fileName, "r");
    char* code;
    size_t n = 0;
    int c;

    if (file == NULL) return NULL; //teste si il y a bien un fichier
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);

    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }

    code[n] = '\0';
    fclose(file);
    return code;
}


struct monde* monde_new(void) //
{
	struct monde *monde = malloc(sizeof( *monde)); // reaction du pointeur mp sur la struture map
	//if (monde == NULL )
		//error("monde : malloc map failed");
	monde->nom_niveau = malloc(MAX_CHAR_NIVEAU);
	//if (monde == NULL) {
		//error("map_new : malloc grid failed");
	return monde;
	}

struct monde* chargement_monde(struct monde* monde , char* chemin) { // fonction qui va lire un fichier et recupère les informations de la carte
  char* texte;
  char* token,* token2;
  int k = 0;
  int line_count = 0;
  int* a = (int *)calloc(2,sizeof(int));
  int l=0;
  texte = readFile(chemin);

  assert(texte != NULL);

  while ((token = strsep(&texte, "\n")) != NULL) // permet de recuperer un token (string) qui contient la partie gauche du caractère
  {
		//printf("%s\n",token);
    if(line_count == 0)
    {
			monde->nombre_carte = atoi(token);
			//printf("%d\n",monde->nombre_carte);
      }
    if(line_count == 1){ // A voir si scanf() fscanf sscanf n'est pas mieux faire la même sur l'autre
			token2 = strsep(&token, ":"); // voir si les atoi servent vraiment bien
			monde->level_debut = atoi(token2);
			//printf("%s\n",token2);
			token2 = strsep(&token,":");
			monde->ini_x = atoi(token2);
			//printf("%s\n",token2);
			token2 = strsep(&token2,",");
			monde->ini_y = atoi(token2);

			//printf("%s\n",token2);
			token2 = strsep(&token2,",");

			//printf("%s\n",token2);
    }
    if(line_count == 2){
			monde->nom_niveau = token;
    }
  //printf("%d\n",line_count);
  line_count++;
}
  return monde;
}

void main()
{
  char* chemin = "../sources/monde/monde1/monde1_info";
	struct monde* monde = chargement_monde(monde_new(),chemin);
}
