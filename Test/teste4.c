#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    int x = 8;
    char s[] = {'0' + x, '\0'};
    printf("%s",s);
  }
