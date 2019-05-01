#include <stdio.h>

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>



char *readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL) return NULL; //could not open file
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

unsigned char * chargement_carte(unsigned char * themap) {
  char* test;
  char *token, *token2;
  //char themap[];
  int k = 0;
  int line_count = 0;
  int* a = (int *)calloc(2,sizeof(int));
  int l=0;
  test = readFile("./map/map_0");


  assert(test != NULL);

  while ((token = strsep(&test, "\n")) != NULL)
  {
    if(line_count == 0)
    {
      while((token2 = strsep(&token, ":")) != NULL && k <= 2)
      {
        a[k] = atoi(token2);
        printf("%d\n",a[k]);
        k++;

      }
      unsigned char *themap =  (unsigned char*)realloc(themap, a[0]*a[1]*sizeof(char));

    }
    else{


   while((token2 = strsep(&token, " ")) != NULL )
   {

      printf("%s\n", token2);
    /*  int a = atoi(token2);
      printf("%c", a);*/
      themap[l] = atoi(token2);
      //printf("#\n");
      l++;
    }

  }


    line_count++;
  //}
}
/*if(a[0]*a[1] == l){
  printf("il y a un problème de dimension sur la carte");*/



for (int i = 0; i<144; i++){
  printf("%d\n",themap[i]);
}
return themap;
}
