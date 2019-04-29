#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//#include <get_map_info.h>

int  STATIC_MAP_WIDTH = 12; // Il faudra par la suite modifier le nom de c 2 variables
int  STATIC_MAP_HEIGHT = 12;

// A refaire moi même
// fonction prise sur internet sur https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c
// Fonction qui permet de couper une chaine de caratère en plusieur morceaux renvoie un pointeur de pointeur


char** str_split(char* a_str, const char a_delim)
{
  char** result    = 0;
  size_t count     = 0;
  char* tmp        = a_str;
  char* last_comma = 0;
  char delim[2];
  delim[0] = a_delim;
  delim[1] = 0;

   //Count how many elements will be extracted.
  while (*tmp)
  {
    if (a_delim == *tmp)
    {
      count++;
      last_comma = tmp;
    }
    tmp++;
  }

   //Add space for trailing token.
  count += last_comma < (a_str + strlen(a_str) - 1);

   //Add space for terminating null string so caller
  //knows where the list of returned strings ends.
  count++;

  result = malloc(sizeof(char*) * count);

  if (result)
  {
    size_t idx  = 0;
    char* token = strtok(a_str, delim);

    while (token)
    {
      assert(idx < count);
      *(result + idx++) = strdup(token);
      token = strtok(0, delim);
    }
    assert(idx == count - 1);
    *(result + idx) = 0;
  }

  return result;
}


unsigned char chargement_carte(){
  unsigned char themap[STATIC_MAP_WIDTH * STATIC_MAP_HEIGHT];
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;

  FILE *file_to_read = fopen("../map/map_0","r");
  //FILE *file_to_write = fopen("../map/map_1", "w");



  if(file_to_read == NULL){
    printf("un fichier n'a pas voulue s'ouvrir! \n");

  }

  // https://riptutorial.com/c/example/8274/get-lines-from-a-file-using-getline--
  // récupération de ce code ici pas encore tout compris

  line_size = getline(&line_buf, &line_buf_size,file_to_read);

  //Boucle jusqu'a la fin du fichier
  while (line_size >= 0)
  {
    // incrémente la ligne
    line_count++;

    if (line_count != 1)
    {

      char** data_ligne;
      data_ligne = str_split(line_buf, ' ');
      int i;
      if (data_ligne)
      {
        for (i = 0; *(data_ligne + i); i++)
        {

          themap[i]=(atoi(*(data_ligne + i)));
          free(*(data_ligne + i));
        }
      }
      free(data_ligne);
    }

    else // récupération de STATIC_MAP_WIDTH, STATIC_MAP_HEIGHT a méliorer jusqu'a l'obtention du char :
    {
      char** dimension; // pointeur de pointeur sur les éléments de dimension voir si mettre null
      dimension = str_split(line_buf, ':'); // prise en compte qu'on att que 2 valeurs
      // rajouter un teste sur la longeur du pointeur pour voir qu'on att bien 2 chiffre et non plus  a faire
      STATIC_MAP_WIDTH = (atoi(*(dimension)));    //STATIC_MAP_WIDTH = (**(dimension)-'0'); Voir avec le prof pk ca marche pas
      STATIC_MAP_HEIGHT = (atoi(*(dimension+ 1)));   //STATIC_MAP_HEIGHT = (**(dimension+ 1)-'0');
      free(dimension);
    }





    // Show the line details
   //printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s\n", line_count,
      //  line_size, line_buf_size, line_buf);

     //Get the next line



    line_size = getline(&line_buf, &line_buf_size, file_to_read);
  }

  free(line_buf);
  line_buf = NULL;
  fclose(file_to_read);
  return themap;

}



/*
int main()
{
    char months[] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";
    char** tokens;

    printf("months=[%s]\n\n", months);

    tokens = str_split(months, ',');


    if (tokens)
    {
        int i;
        for (i = 0; *(tokens + i); i++)
        {
            printf("month=[%s]\n", *(tokens + i));
            free(*(tokens + i));
        }
        printf("\n");
        free(tokens);
    }

    return 0;
}
*/
