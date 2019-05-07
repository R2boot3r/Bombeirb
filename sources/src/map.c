/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
#include <SDL/SDL_image.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <map.h>
#include <constant.h>
#include <misc.h>
#include <sprite.h>
#include <window.h>
#include <get_map.h>
#include <string.h>
#include <unistd.h>

////////////////// Variables/Structures ////////////////////

//int  STATIC_MAP_WIDTH = 12; // Il faudra par la suite modifier le nom de c 2 variables
//int  STATIC_MAP_HEIGHT = 12;

struct map { //  une structure n'a pas besoin qu'on initialise les variables et pointeurs tt est null ou 0
	int width;
	int height;
	unsigned char* grid;
	int door_closed;
};

#define CELL(i,j) ( (i) + (j) * map->width)



////////////////// Fonctions ////////////////////


// Fonction qui crée une nouvelle map au debut du jeu
struct map* map_new(int width, int height) //
{
	assert(width > 0 && height > 0);

	struct map *map = malloc(sizeof *map); // reaction du pointeur mp sur la struture map
	if (map == NULL )
		error("map_new : malloc map failed");

	map->width = width;
	map->height = height;
	map->door_closed = 1;

	map->grid = malloc(height * width);
	if (map->grid == NULL) {
		error("map_new : malloc grid failed");
	}

	// Grid cleaning
	int i, j;
	for (i = 0; i < width; i++)
	  for (j = 0; j < height; j++)
	    map->grid[CELL(i,j)] = CELL_EMPTY;

	return map;
}

// Fonction qui permet de vérifier si le player est dans la map
int map_is_inside(struct map* map, int x, int y)
{
	assert(map);
	if (x<STATIC_MAP_WIDTH && x>=0 && y<STATIC_MAP_HEIGHT && y>=0)
	return 1;
	else return 0;
}

// Fonction qui libère le pointeur map
void map_free(struct map *map)
{
	if (map == NULL )
		return;
	free(map->grid);
	free(map);
}

// Fonction qui récupère la largeur de la map
int map_get_width(struct map* map)
{
	assert(map != NULL);
	return map->width;
}

// Fonction qui récupère la hauteur de la map
int map_get_height(struct map* map)
{
	assert(map);
	return map->height;
}

// A voir
enum cell_type map_get_cell_type(struct map* map, int x, int y)
{
	//assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)] & 0xf0;
}

// A voir
void map_set_cell_type(struct map* map, int x, int y, enum cell_type type)
{
	assert(map && map_is_inside(map, x, y));
	map->grid[CELL(x,y)] = type;
}

// Fonction qui modifie les bonus de bombs
void display_bonus(struct map* map, int x, int y, unsigned char type)
{
	// bonus is encoded with the 4 most significant bits
	switch (type & 0x0f) {
	case BONUS_BOMB_RANGE_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_INC), x, y);
		break;

	case BONUS_BOMB_RANGE_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_DEC), x, y);
		break;

	case BONUS_BOMB_NB_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_DEC), x, y);
		break;

	case BONUS_BOMB_NB_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_NB_INC), x, y);
		break;
	}
}

// Fonction qui  Affiche la bonne image de bomb

// Fonction qui affiche si la porte est ouverte ou non
void display_door(struct map* map, int x, int  y){
			if (map-> door_closed)
			window_display_image(sprite_get_door_closed() ,x ,y);
			else
			window_display_image(sprite_get_door_opened() ,x ,y);
}

// Fonction qui affiche le décor arbre ou roches ? ac compresser avec le reste ?
void display_scenery(struct map* map, int x, int  y, unsigned char type)
{
	switch (type & 0x0f) { // sub-types are encoded with the 4 less significant bits
	case SCENERY_STONE:
		window_display_image(sprite_get_stone(), x, y);
		break;

	case SCENERY_TREE:
		window_display_image(sprite_get_tree(), x, y);
		break;
	}
}
// Fonction ui affiche les éléments de la maps
void map_display(struct map* map)
{
	assert(map != NULL);
	assert(map->height > 0 && map->width > 0);

	int x, y;
	for (int i = 0; i < map->width; i++) {
	  for (int j = 0; j < map->height; j++) {
	    x = i * SIZE_BLOC;
	    y = j * SIZE_BLOC;

	    unsigned char type = map->grid[CELL(i,j)];

	    switch (type & 0xf0) {
		case CELL_SCENERY:
		  display_scenery(map, x, y, type);
		  break;
	    case CELL_BOX:
	      window_display_image(sprite_get_box(), x, y);
	      break;
	    case CELL_BONUS:
	      display_bonus(map, x, y, type);
	      break;
	    case CELL_KEY:
	      window_display_image(sprite_get_key(), x, y);
	      break;
	    case CELL_DOOR:
	      //pas de gestion du type de porte
	      display_door(map, x, y);
	      break;
	    case CELL_BOMB:
			break;
	    }
	  }
	}
}

// Fonction qu permet d'ouvrir une porte
void map_open_door(struct map* map){
	if (map->door_closed)
		map->door_closed = 0;
}

// Fonction qui regarde si la porte est fermé
int door_is_closed(struct map* map){
	if (map->door_closed)
		return 1;
	else
		return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////LECTURE DES CARTES////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

char* chemin = "./monde/monde1/map/map_monde1_0.txt";

// Fonction qui permet d'affecter une carte a la map
// A modifier faire eune seul fonction correcte pck la c pas top
// en entré metre la carte et en sortie tj la structure map element grid
struct map* map_get_static_1(void)
{
	struct map* map = map_new(STATIC_MAP_WIDTH, STATIC_MAP_HEIGHT);

	unsigned char * themap1 = malloc(10*sizeof(char));

	*themap1 = chargement_carte(themap1,chemin);

	for (int i = 0; i < STATIC_MAP_WIDTH * STATIC_MAP_HEIGHT; i++)
	{
		map->grid[i] = themap1[i];
	}
	return map;
}

struct map* map_get_static_2(void)
{
	struct map* map = map_new(STATIC_MAP_WIDTH, STATIC_MAP_HEIGHT);

	unsigned char * themap2 = malloc(10*sizeof(char));

	*themap2 = chargement_carte(themap2,chemin);


	for (int i = 0; i < STATIC_MAP_WIDTH * STATIC_MAP_HEIGHT; i++)
	{
		map->grid[i] = themap2[i];
	}
	return map;
}
