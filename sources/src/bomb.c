#include <SDL/SDL_image.h>
#include <assert.h>

#include <sprite.h>
#include <misc.h>
#include <constant.h>
#include <map.h>
#include <game.h>
#include <bomb.h>
// utilisation d'une chaine listée pour la gestion des bombes
struct bomb {
  int x,y;
  unsigned int timer;
	unsigned int time_init;
	enum bomb_type bomb_type;
	struct bomb * next;
};


// Documentation sur les listes chainées
//http://www.zentut.com/c-tutorial/c-linked-list/
// fonction qui crée une bombe spécifique
struct bomb* bomb_create(int x, int y, struct bomb* next) {
	struct bomb* bomb;
	bomb = malloc(sizeof(*bomb));
	if (!bomb) // a voir si on laisse cette partie
	{
		printf("Erreur lors de la creation de la struture bomb.\n");
		exit(0);
	}
	bomb->x = x;
	bomb->y = y;
	bomb->bomb_type = BOMB_TTL4;
	bomb->time_init = SDL_GetTicks();
	bomb->next = NULL;


	return bomb;
}

//fonction qui permet de crée la chaine de bombs
struct bomb* bomb_prepend( struct bomb* head,int x , int y){
	struct bomb* bomb = bomb_create(x,y,head);
	head = bomb;
	return head;
}


void bomb_timer_update(struct bomb* bomb){ // a apeller avant bomb_update_ttl
	bomb->timer = SDL_GetTicks() - bomb->time_init;
}


typedef void (*callback)(node* data);

void bomb_ttl_update_traverse(struct bomb* head,callback f)
{
	unsigned int time;
	struct curseur = head;
	while(curseur != NULL)
	{
		time = bomb->timer;
		if((time >= 1000) && (time < 2000)){ // il ne sert a rien d'affecter la première image car cela est fait dans la boucle d'initialisation
			bomb->bomb_type = BOMB_TTL3
		}
		else if((time >= 2000) && (time < 3000)){
			bomb->bomb_type = BOMB_TTL2
		}
		else if((time >= 3000) && (time < 4000)){
			bomb->bomb_type = BOMB_TTL1
		}
/*	else if((time >= 4000) && (time < 1000)){
		bomb->bomb_type = BOMB2
	}*/
		f(curseur);
		curseur = curseur->next
	}
}





void bomb_free(struct bomb* bomb) {
	assert(bomb);
	free(bomb);
}


int bomb_get_x(struct bomb* bomb) {
	assert(bomb != NULL);
	return bomb->x;
}

int bomb_get_y(struct bomb* bomb) {
	assert(bomb != NULL);
	return bomb->y;
}

int bomb_get_range(struct bomb* bomb){
	assert(bomb);
	return bomb->range;
}

int bomb_get_timer(struct bomb* bomb){
	assert(bomb);
	return bomb->timer;
}

void update_bomb_timer(struct bomb* bomb){
	assert(bomb);
	bomb->timer=SDL_GetTicks();
}

/*void bomb_display(struct bomb* bomb) {
	assert(bomb);
	window_display_image(sprite_get_bomb(bomb->bomb_type),
			bomb->x * SIZE_BLOC,bomb->y * SIZE_BLOC);
}*/
