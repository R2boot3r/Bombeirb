#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>


bool is_file(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}




  int main() {
    char cwd[300];
    DIR *d;
    struct dirent *dir;
    d = opendir("../sources/monde/monde1");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
          if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Current working dir: %s\n", cwd);
          } else {
            perror("getcwd() error");
            return 1;
          }
            printf("%s\n", dir->d_name);
            //printf("%d\n", is_dir(dir->d_name));
            printf("%d\n", is_dir("map"));
            //printf("%d\n", is_file(dir->d_name));
            //printf("%d\n", is_file("../sources/monde/monde1/map/map_monde1_1.txt"));
        }
        closedir(d);
    }
    return(0);
}
