#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
// choses qui reste a faire
// variable a entrée qui contient le nom des fichiers
// Fonction qui scan le dossier et qui renvoye toutes les map_set_cell_type
// modifications des STATIC_MAP_WIDTH STATIC_MAP_HEIGHT


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

unsigned char * chargement_carte(unsigned char* themap, char* chemin) { // fonction qui va lire un fichier et recupère les informations de la carte
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
    if(line_count == 0)
    {
      while((token2 = strsep(&token, ":")) != NULL && k <= 2) // permet de récuperer les deux dimensions de la carte
      {
        a[k] = atoi(token2);
        //printf("%d\n",a[k]);
        k++;
      }
      unsigned char *themap =  (unsigned char*)realloc(themap, a[0]*a[1]*sizeof(char)); //réallocation de la mémoire en fonction de la taille récuprer précedement
    }
    else{
   while((token2 = strsep(&token, " ")) != NULL ) //permet de récuperer un token qui contient les chiffres qui représente chaque élément de la carte
   {
      //printf("%s\n", token2);
      themap[l] = atoi(token2);
      l++;
    }
  }
  line_count++;
}

//free(token2); il y a un problème avec le free(token2) pk ?
free(token);
free(texte);


return themap;
}
