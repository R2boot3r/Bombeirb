#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <stdbool.h>

#ifndef WIN32
    #include <sys/types.h> // problème sur la librairy si le système d'exploitation est windows
#endif

#define MAX_CHAR_NIVEAU 64
#define MAX_CHAR 100

char* chemin_monde = "../sources/monde/monde0_info";
 // a deplacer par la suivante
 // voir si on fzit pas une struture pour le chatgement des maps aussi
// liens des resssources qui m'ont été utiles pour cette librairy
//Pour la lecture de fichier et le type https://www.linuxquestions.org/questions/programming-9/how-to-know-the-file-extension-with-c-602471/



// choses qui reste a faire
// variable a entrée qui contient le nom des fichiers
// Fonction qui scan le dossier et qui renvoye toutes les map_set_cell_type
// modifications des STATIC_MAP_WIDTH STATIC_MAP_HEIGHT
// remettre les infos sur strsep
//-D_DEFAULT_SOURCE a mettre pour éviter les erreures de c voir https://stackoverflow.com/questions/26284110/strdup-confused-about-warnings-implicit-declaration-makes-pointer-with

struct monde {
	int nombre_carte;
	int level_debut;
	int ini_x, ini_y;
	char* nom_niveau;
};

bool ext_match(const char *name, const char *ext) // fonction qui renvoie true si un fichier a la bonne extension pas encore utiliser
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

unsigned char * chargement_carte(unsigned char* themap, char* chemin) { // fonction qui va lire un fichier et recupère les informations de la carte
  char* texte;
  char* token,* token2;
  int line_count = 0;
  int* a = (int *)calloc(2,sizeof(int));
  int l=0;
  texte = readFile(chemin);

  assert(texte != NULL);
 //faire ligne 1 = et bloucle pour la suite
  while ((token = strsep(&texte, "\n")) != NULL) // permet de recuperer un token (string) qui contient la partie gauche du caractère
  {
    if(line_count == 0)
    {
    	token2 = strsep(&token, ":"); // permet de récuperer la première ligne
    	a[0] = atoi(token2);
    	printf("%s",token2);
    	token2 = strsep(&token, ":");
    	a[1] = atoi(token2);
    	printf("%s",token2);
    	unsigned char *themap =  (unsigned char*)realloc(themap, a[0]*a[1]*sizeof(char)); //réallocation de la mémoire en fonction de la taille récuprer précedement
    }

    else{
   while((token2 = strsep(&token, " ")) != NULL ) //permet de récuperer un token qui contient les chiffres qui représente chaque élément de la carte
   {
      printf("%s\n", token2);
      themap[l] = atoi(token2);
      l++;
    }
  }
  line_count++;
}
return themap;
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
    int line_count = 0;
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

struct monde* monde_init(void){
  struct monde* monde = monde_new();
  monde = chargement_monde(monde,chemin_monde);
  return monde;
}

void print_struct(struct monde * monde){
  printf("%d ",monde->nombre_carte);
  printf("%d ",monde->level_debut);
  printf("%d ",monde->ini_x);
  printf("%d ",monde->ini_y);
  printf("%s\n",monde->nom_niveau);

}


// fonction qui modifie le tableauqui contient les liens
void nom_fichier(struct monde * monde, char * chemin_map, char arr[][MAX_CHAR]){ // voir themap pour amélioration
  for(int i=0; i< monde->nombre_carte ;i++){
    //char arr[i][]
    char chemin[MAX_CHAR];
    strcpy(chemin,chemin_map);
    char s[] = {'0' + i, '\0'}; // pas de problèmes on se limite a 8 niveau
    strcat(chemin,monde->nom_niveau);
    strcat(chemin,s);
    //printf("dfdf");
    strcpy(arr[i],chemin);

  }

}


/*


void main(){
  // voir ici pour ce qu'il faut https://stackoverflow.com/questions/14088804/how-to-return-matrix-2d-array-from-function-c/14088911
  // Il faudrait faire des teste sur la copy pour savoir d'ou viens la potentiel erreur

  char chemin_map[MAX_CHAR];
  char chemin_une_map[MAX_CHAR];
  strcpy(chemin_map,"../map/");


  struct monde* monde = monde_new();

  monde = chargement_monde(monde,chemin_monde);


  char  arr[monde->nombre_carte][MAX_CHAR];

  nom_fichier(monde,chemin_map,arr); // modifie array



}
*/
