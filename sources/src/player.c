
/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
 //////////////// Bibliothèques ////////////////

#include <SDL/SDL_image.h>
#include <assert.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <map.h>

////////////////// Variables ////////////////////

struct player {
	int x, y, range;
	enum direction direction;
	int bombs;
	short level;
	int key;
	int heart;


}; //

////////////////// Fonctions ////////////////////


// Fonction qui initialise le player
struct player* player_init(int bombs, int heart) {
	struct player* player = malloc(sizeof(*player));
	if (!player)
		error("Memory error");

	player->direction = NORTH;
	player->bombs = bombs;
	player->level = 0;
	player->range = 2;
	player->key = 0;
	player->heart = heart;
	return player;
}

// Fonction qui initialise la position du player x, y
void player_set_position(struct player *player, int x, int y) {
	assert(player);
	player->x = x;
	player->y = y;
}

// Fonction qui déalloue la mémoire du pointeur player
void player_free(struct player* player) {
	assert(player);
	free(player);
}

// Fonction qui récupère position x
int player_get_x(struct player* player) {
	assert(player != NULL);
	return player->x;
}

// Fonction qui récupère position y
int player_get_y(struct player* player) {
	assert(player != NULL);
	return player->y;
}
//Fonction qui retourne le nombre de vie du player:
int player_get_nb_heart(struct player* player) {
	assert(player);
	return player->heart;
}
//fonction qui incrémente le nombre de vie
void player_inc_nb_heart(struct player* player) {
	assert(player);
	player->heart += 1;
}


//fonction qui décrémente le nombre de vie
void player_dec_nb_heart(struct player* player) {
	assert(player);
	player->heart -= 1;
}

// controle du range

int player_get_range_bomb(struct player* player) {
	assert(player);
	return player->range;
}
void player_inc_range_bomb(struct player* player) {
	assert(player);
	player->range += 1;
}

void player_dec_range_bomb(struct player* player) {
	assert(player);
	player->range -= 1;
}

//key control
int player_get_key_number(struct player* player) {
	assert(player);
	return player->key;
}

void player_inc_key_number(struct player* player) {
	assert(player);
	player->key += 1;
}

void player_dec_key_number(struct player* player) {
	assert(player);
	player->key -= 1;
}



// Fonction qui met la position du joeur
void player_set_current_way(struct player* player, enum direction way) {
	assert(player);
	player->direction = way;
}

// Fonction qui récupère le nombre de bombs
int player_get_nb_bomb(struct player* player) {
	assert(player);
	return player->bombs;
}

// Fonction qui incrémente le nombre de bombe
void player_inc_nb_bomb(struct player* player) {
	assert(player);
	player->bombs += 1;
}

// Fonction qui décrémente le nombre de bombe
void player_dec_nb_bomb(struct player* player) {
	assert(player);
	player->bombs -= 1;
}
// Fonction qui permet de récuprer les bonus
void player_move_case_bonus(struct player * player, struct map* map, int x, int y){
	switch (map_get_bonus_type(map,x,y)){
		case BONUS_LIFE:
		 map_set_cell_type(map, x, y, CELL_EMPTY);
		 player_inc_nb_heart(player);
		break;
		case BONUS_BOMB_NB_DEC:
			map_set_cell_type(map,x,y, CELL_EMPTY);
			player_dec_nb_bomb(player);
		break;
		case BONUS_BOMB_NB_INC:
			map_set_cell_type(map,x,y, CELL_EMPTY);
			player_inc_nb_bomb(player);
		break;
		case BONUS_BOMB_RANGE_DEC:
			map_set_cell_type(map,x,y, CELL_EMPTY);
			player_dec_range_bomb(player);
		break;
		case BONUS_BOMB_RANGE_INC:
			map_set_cell_type(map,x,y, CELL_EMPTY);
			player_inc_range_bomb(player);
		break;
	}
}



// Fonction qui permet de déplacer une boite (a comprésser après) j'aime pas du tout la logique de la fonction
void player_move_case_box(struct player* player, struct map* map, int x, int y){
	if (player->direction == NORTH  && map_get_cell_type(map,x,y-1)==CELL_EMPTY) {
		if(map_is_inside(map,x,y-1)){
			map_set_cell_type(map , x, y,CELL_EMPTY);
			map_set_cell_type(map , x, y-1,CELL_BOX);
			player->y--;
		}
	}
	if (player->direction == SOUTH  && map_get_cell_type(map,x,y+1)==CELL_EMPTY ){
			if(map_is_inside(map,x,y+1)){
		map_set_cell_type(map , x, y,CELL_EMPTY);
		map_set_cell_type(map , x, y+1,CELL_BOX);
		player->y++;
		}

	}
	if (player->direction == EAST  && map_get_cell_type(map,x+1,y)==CELL_EMPTY ){
			if(map_is_inside(map,x+1,y)){
		map_set_cell_type(map , x, y,CELL_EMPTY);
		map_set_cell_type(map , x+1, y,CELL_BOX);
		player->x++;
		}
	}
	if (player->direction == WEST && map_get_cell_type(map,x-1,y)==CELL_EMPTY  ){
		if(map_is_inside(map,x-1,y)){
		map_set_cell_type(map , x, y,CELL_EMPTY);
		map_set_cell_type(map , x-1, y,CELL_BOX);
		player->x--;
		}
	}
}

// Fonction qui permet d'agir en fonction du d'élément qui se trouve sous le joeur (de même pour box move c pas terrible)
int player_move_aux(struct player* player, struct map* map, int x, int y) {

	if (!map_is_inside(map, x, y))
		return 0;

	switch (map_get_cell_type(map, x, y)) {
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_BOX:
		player_move_case_box(player, map,x,y);
		return 0;
		break;

	case CELL_BONUS:
		player_move_case_bonus(player,map,x,y);

		return 1;
		break;

	case CELL_MONSTER:
		return 0;
		break;
	case CELL_KEY: // partie qui sert a ouvrir la porte lorsque le joeur a la clef
		map_set_cell_type(map, x, y, CELL_EMPTY);
		player_inc_key_number(player);
		map_open_door(map);
		return 1;
	case CELL_DOOR:
	// code a rajouter ici pour bien faire fonctionner la porte
		if (!door_is_closed(map)) // partie qui permet de changer de biveau et de voir si la porte est ouverte
		{
			player->level = player->level +1;
			player_dec_key_number(player);
		}
		return 0;
		break;
	default:
		break;
	}

	//Player has moved
	return 1;
}

// Fonction qui affecte la nouvelle position x,y grace a la direction
int player_move(struct player* player, struct map* map) {
	int x = player->x;
	int y = player->y;
	int move = 0;

	switch (player->direction) {
	case NORTH:
		if (player_move_aux(player, map, x, y - 1)) {
				player->y--;
				move = 1;
		}
		break;

	case SOUTH:
		if (player_move_aux(player, map, x, y + 1)) {
			player->y++;
			move = 1;
		}
		break;

	case WEST:
		if (player_move_aux(player, map, x - 1, y)) {
			player->x--;
			move = 1;
		}
		break;

	case EAST:
		if (player_move_aux(player, map, x + 1, y)) {
			player->x++;
			move = 1;
		}
		break;
	}
	return move;
}

// Fonction qui affiche la bonne image du player en fonction de son orientation
void player_display(struct player* player) {
	assert(player);
	window_display_image(sprite_get_player(player->direction),
			player->x * SIZE_BLOC, player->y * SIZE_BLOC);
}

int player_return_level(struct player* player){
	return player->level;
}

int player_return_range(struct player* player){
	return player->range;
}
