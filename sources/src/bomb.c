#include <SDL/SDL_image.h>
#include <assert.h>
#include <sprite.h>
#include <misc.h>
#include <constant.h>


struct bomb {
	int range;
  int x,y;
  int timer;
	int time_ini;
	// mettre le type de bomb ttl
	enum bomb_type bomb_type;
};




struct bomb* bomb_new(int x, int y) { // a modifier avec le truc d'avant
	struct bomb* bomb;
	bomb = malloc(sizeof(*bomb));
	if (!bomb)
		error("Erreur d'initialisation de la structure");
	bomb->x = x;
	bomb->y = y;
	bomb->time_ini = SDL_GetTicks();
	return bomb;
}


void bomb_free(struct bomb* bomb) { // libération de la struture
	assert(bomb);
	free(bomb);
}

void update_time_bomb(struct bomb* bomb){
	bomb->timer = SDL_GetTicks()- bomb->time_ini;
}


int bomb_get_x(struct bomb* bomb) { // recupération de la position x
	assert(bomb != NULL);
	return bomb->x;
}

int bomb_get_y(struct bomb* bomb) { // recupération de la position y
	assert(bomb != NULL);
	return bomb->y;
}


//Fonction global que j'apelle en entier dans le game ou main a avoir




/*void bomb_display(struct bomb* bomb) {
	assert(bomb);
	window_display_image(sprite_get_bomb(bomb->bomb_type),
			bomb->x * SIZE_BLOC,bomb->y * SIZE_BLOC);
}*/
