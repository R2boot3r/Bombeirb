#include <SDL/SDL_image.h>
#include <assert.h>

#include <sprite.h>
#include <misc.h>
#include <constant.h>
#include <map.h>
#include <game.h> // a supprimer par la suite mettre tout un un fichier struture
#include <bomb.h>

// a mettre la creation de la bomb lors de l'apelle du clavier espace

// utilisation d'une chaine listée pour la gestion des bombes
struct bomb {
  int x,y;
  unsigned int timer;
	unsigned int time_init;
	enum bomb_type bomb_type;
	struct bomb * next;
};

struct bomb* bomb_init(){
	struct bomb* bomb = NULL;
	return bomb;
}
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
struct bomb* bomb_prepend( struct bomb* head, int x , int y){
	struct bomb* bomb = bomb_create(x,y,head);
	head = bomb;
	return head;
}

// Fonction qui permet de mettre le timer de la bomb a jour
void bomb_timer_update(struct bomb* bomb){ // a apeller avant bomb_update_ttl
	bomb->timer = SDL_GetTicks() - bomb->time_init;
}

// Fonction qui permet la mise a jour de l'état de chaque bombe
// et qui appelle bomb_timer_update pour chancune des bombes
void bomb_ttl_update_traverse(struct bomb* bomb)
{
  struct bomb* curseur = bomb;
	unsigned int time;
	while(curseur != NULL)
	{
    bomb_timer_update(curseur);
		time = curseur->timer;
		if((time >= 1000) && (time < 2000)){ // il ne sert a rien d'affecter la première image car cela est fait dans la boucle d'initialisation
			curseur->bomb_type = BOMB_TTL3;
		}
		else if((time >= 2000) && (time < 3000)){
			curseur->bomb_type = BOMB_TTL2;
		}
		else if((time >= 3000) && (time < 4000)){
			curseur->bomb_type = BOMB_TTL1;
		}
    else if((time >= 4000) && (time < 5000)){
		    curseur->bomb_type = BOMB_TTL0_EX;
	  }

		curseur = curseur->next;
	}
}


void bomb_display(struct bomb* bomb){ // ainsi que le renage qui sera aussi appeler et prit en paramètre par une autre fonction
  bomb = bomb_ttl_update_traverse();
    struct bomb* curseur = bomb;
    while(curseur != NULL){
      switch(curseur->bomb_type){ // on va pouvoir rajouter la suite ici des autres condition, on supprime la bombe

      default:
        window_display_image(sprite_get_bomb(curseur->bomb_type),curseur->x, curseur->y); // a appeler autres fonction pour la range
      }
      curseur = curseur->next;
    }
}










// Toutes les fonctions en rapport avec la récupération de données


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

int bomb_get_bomb_type(struct bomb* bomb){
  assert(bomb);
  return bomb->bomb_type;

}

int bomb_get_timer(struct bomb* bomb){
	assert(bomb);
	return bomb->timer;
}
