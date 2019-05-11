#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <stdbool.h>

void main(){
  int x = 4;
  int range = 2;
for(int i = (x-1); i>=(x-range); i--){
  printf("%d",i);
}
}
