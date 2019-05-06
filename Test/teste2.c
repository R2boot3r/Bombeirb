#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>

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


int main(void)

{
    DIR *d;
    struct dirent *dir;
    d = opendir("../sources/monde/monde1/map");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
            printf("%d\n", is_dir(dir->d_name));
            printf("%d\n", is_file(dir->d_name));
        }
        closedir(d);
    }
    return(0);
}
