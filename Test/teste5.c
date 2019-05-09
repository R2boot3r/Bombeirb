#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <stdbool.h>

void main(){
  int range = 1;
  for(int i = -(range); i<= range;i++){
    for(int j = -(range);j<= range; j++){
      //if(i != x && j != y){
        printf("%d ",i);
        printf("%d\n",j);
      //}
    }
  }
}
