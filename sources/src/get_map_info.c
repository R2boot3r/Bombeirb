#include <stdio.h>
#include <stdlib.h>
#include <get_map_info.h>


void teste(){



  FILE *file_to_read = fopen("../map/map_0","r");
  FILE *file_to_write = fopen("../map/map_1", "w");

  if(file_to_read == NULL || file_to_write == NULL){
    printf("un fichier n'a pas voulue s'ouvrir! \n");
    
  }
  char c;
  while ((c=fgetc(file_to_read)) != EOF){
    fputc(c, file_to_write);
  }
  fclose(file_to_read);
  fclose(file_to_write);
}
