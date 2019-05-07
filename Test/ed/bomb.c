#include <SDL/SDL_image.h>
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

#include <bomb.h>
#include <map.h>
#include <sprite.h>
#include <window.h>
#include <constant.h>
#include <game.h>
#include <player.h>
#include <monster.h>

struct bomb {
  int x,y;
  unsigned int timer;
	unsigned int time_init;
	enum bomb_type bomb_type;
	struct bomb * next;
};

struct bomb* bombs_init(){
	struct bomb* bombs = NULL;
	return bombs;
}


struct bomb* bomb_create(struct game* game, int x, int y){
	struct bomb* bomb;
	bomb = malloc(sizeof(struct bomb));

	bomb->x = x;
	bomb->y = y;
	bomb->bomb_type = BOMB_TTL4;
	bomb->next = NULL;
	return bomb;
}

struct bomb* bombs_add_bomb(struct bomb *bombs, int x, int y){

	struct bomb* bomb = bomb_create(game, x, y);
	bomb->next = bombs;
	bomb->time_init = SDL_GetTicks()
	return bomb;
}

void bomb_update(struct bomb *bombs){
	unsigned int time_live;
	while (bombs != NULL){
			time_live = SDL_GetTicks() - bombs->time_init;
			// time in milliseconds
			if(time_live <= 1000)
				bombs->bomb_type = BOMB_TTL3;
			else if((time_live > 1000) && (time_live <= 2000))
				bombs->bomb_type = BOMB_TTL2;
			else if((time_live > 2000) && (time_live <= 3000))
				bombs->->bomb_type = BOMB_TTL1;
			else if((time_live > 3000) && (time_live <= 4000))
				bombs->->bomb_type = BOMB_TTL0;
			bombs=bombs->next;
		}
}

void bomb_display(struct bomb* bombs) {

	bomb_update(bombs);
	struct bomb* temp_bomb = bombs;
	while (temp_bomb != NULL){

				window_display_image(sprite_get_bomb(temp_bomb->bomb_type),temp_bomb->x, temp_bomb->y);
		}
		temp_bomb=temp_bomb->next;
}



void bomb_destruction(struct bomb* bombs, struct game* game){
	// remove the last item from the bombs' list
	  if (bombs->next == NULL){
	    free(bombs);
	    game_set_bomb(game, NULL);
	  }
	  else{
		  struct bomb* temp = bombs;
		  struct bomb* before = bombs;
		  while (temp->next != NULL){
			before = temp;
			temp = temp->next;
		  }
		  before->next = NULL;
		  free(temp);
		  temp = NULL;
		  game_set_bomb(game, bombs);
	  }
}

//int bomb_get_state(struct bomb* bomb){
//	return (bomb->state);
//}

int bombs_get_size(struct bomb *bombs){
  if (bombs==NULL)
    return 0;
  int size=0;
  while (bombs!=NULL) {
    size++;
    bombs=bombs->next;
  }
  return size;
}
