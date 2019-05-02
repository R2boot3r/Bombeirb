#include <stdbool.h>
#include <string.h>

inline bool ext_match(const char *name, const char *ext) // fonction qui renvoie true si un fichier a la bonne extension
{
	size_t nl = strlen(name), el = strlen(ext);
	return nl >= el && !strcmp(name + nl - el, ext);
}

void main()
