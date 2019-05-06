/*#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <dirent.h>

int main(void)
{
    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(".");

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);

    closedir(dr);
    return 0;
}



bool ext_match(const char *name, const char *ext) // fonction qui renvoie true si un fichier a la bonne extension
// rajout de static devant inline voir https://www.geeksforgeeks.org/inline-function-in-c/
{
	size_t nl = strlen(name), el = strlen(ext);
	return nl >= el && !strcmp(name + nl - el, ext);
}

void main(){
	char *a= "texte.txt";
	const char* b = "txt2" ;
	bool x = ext_match(a,b);
	printf("%d\n",x);

}
*/
