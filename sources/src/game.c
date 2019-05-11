/******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
 //////////////// Bibliothèques ////////////////

#include <assert.h>
#include <time.h>
#include <game.h>
#include <misc.h>
#include <bomb.h>
#include <get_map.h>

////////////////// Variables ////////////////////

struct game {
	struct map** maps;       // the game's map
	short levels;        // nb maps of the game
	struct player* player;
	struct bomb * bomb;
	struct monde * monde;
}; // struture du game


////////////////// Fonctions ////////////////////



// Fonction qui crée une nouvelle game
struct game* game_new(void) {
	sprite_load(); // load sprites into process memory

	struct game* game = malloc(sizeof(*game));
	game->monde = monde_init();
	game->maps = malloc(sizeof(struct game));
	printf("%s",get_monde_nom_niveau(game->monde));
	printf("zdsddssdfsd");
	printf("zdsddssdfsd");
	printf("zdsddssdfsd");


	/*for(int i = 0; i<2;i++){
		game->maps[i] = map_get_dynamique(game->monde,i);
	}
	*/
	game->maps[1] = map_get_static_2();
	game->levels = 2;
	game->nb_monster=2;
	//game->level = 0;
  for(int i=0; i<game->nb_monster; i++){
		game->monsters[i] = monster_init();
	}
	game->player = player_init(3,3);
	// Set default location of the player
	player_set_position(game->player, 1, 0);
	//Set default location of monsters
	monster_set_position(game->monsters[0],6,6);
	monster_set_position(game->monsters[1],7,6);

	return game;

}

// initialisation du jeu

// Fonction qui libère toutes les variables de game ATT voir pour maps
void game_free(struct game* game) {
	assert(game);
	for(int i=0; i<game->nb_monster; i++){
		monster_free(game->monsters[i]);
	}
	player_free(game->player);
	for (int i = 0; i < game->levels; i++)
		map_free(game->maps[i]);
}


// Fonction qui prend la structure de la map et renvoie celle du player
struct player* game_get_player(struct game* game) {
	assert(game);
	return game->player;
}

//fonction qui permet de faire bouger les monstres sur la maps
void monsters_move_level(struct game* game, int monster_time){
	struct player* player= game_get_player(game);
	short level = player_return_level(player) +1;
	printf("%d\n" ,level);
	if (SDL_GetTicks()-monster_time>(1000)){
		monsters_move(game);
		monster_time=SDL_GetTicks();
	}
}

void monsters_move(struct game* game){
	struct map* map = game_get_current_map(game);
	for (int i = 0; i<game->nb_monster; i++){
		monster_move(game->monsters[i],map);
	}
}


// Fonction qui permet de selectionner la bonne carte en fonction du level
struct map* game_get_current_map(struct game* game) {
	assert(game);

	struct player* player = game_get_player(game);

	return game->maps[player_return_level(player)];
}



// Fonction qui affiche la bannière
void game_banner_display(struct game* game) {
	assert(game);

	struct map* map = game_get_current_map(game);

	int y = (map_get_height(map)) * SIZE_BLOC;
	for (int i = 0; i < map_get_width(map); i++)
		window_display_image(sprite_get_banner_line(), i * SIZE_BLOC, y);

	int white_bloc = ((map_get_width(map) * SIZE_BLOC) - 6 * SIZE_BLOC) / 4;
	int x = white_bloc;
	y = (map_get_height(map) * SIZE_BLOC) + LINE_HEIGHT;
	window_display_image(sprite_get_banner_life(), x, y);

	x = white_bloc + SIZE_BLOC;
	window_display_image(
		sprite_get_number(player_get_nb_hurt(game_get_player(game))), x, y);

	x = 2 * white_bloc + SIZE_BLOC;
	window_display_image(sprite_get_banner_bomb(), x, y);

	x = 2 * white_bloc + 2 * SIZE_BLOC;
	window_display_image(
			sprite_get_number(player_get_nb_bomb(game_get_player(game))), x, y);

	x = 3 * white_bloc + 2 * SIZE_BLOC;
	window_display_image(sprite_get_banner_range(), x, y);

	x = 3 * white_bloc + 3 * SIZE_BLOC;
	window_display_image(
		sprite_get_number(player_get_range_bomb(game_get_player(game))), x, y);

	x = 5 * white_bloc + 2 * SIZE_BLOC;
	window_display_image(sprite_get_key(),x,y);

	x = 5 * white_bloc + 3 * SIZE_BLOC;
	window_display_image(
		sprite_get_number(player_get_key_number(game_get_player(game))), x, y);

}

// Fonction Principale d'affichage
void game_display(struct game* game) {
	assert(game);
	window_clear();
	game_banner_display(game);
	map_display(game_get_current_map(game));
	for(int i=0; i<game->nb_monster; i++){
		monster_display(game->monsters[i]); //the monsters have to be displayed after the map.
	}
	player_display(game->player);
	bomb_display(game->bomb,game_get_current_map(game),player_return_range(game->player));
	//update_time_bomb(bomb1);

	window_refresh();
}




// Fonction qui detecte les touches et agit en fonction
static short input_keyboard(struct game* game, int timer) { // recupère les entrées clavier et agit en fonction !! comprend pas encore toutes les actions
	SDL_Event event; // structure qui permet de lire les événements du pc
	struct player* player = game_get_player(game); // récupère les infos du player
	struct map* map = game_get_current_map(game);	// récupère les infos de la map
	int i = player_get_x(game->player);
	int j = player_get_y(game->player);
	while (SDL_PollEvent(&event)) { // SDL_PollEvent permet de lire les events dans la queueet agit en fonction
		switch (event.type){
		case SDL_QUIT:
			return 1;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				return 1;
			case SDLK_UP:
				player_set_current_way(player, NORTH);
				player_move(player, map);
				break;
			case SDLK_DOWN:
				player_set_current_way(player, SOUTH);
				player_move(player, map);
				break;
			case SDLK_RIGHT:
				player_set_current_way(player, EAST);
				player_move(player, map);
				break;
			case SDLK_LEFT:
				player_set_current_way(player, WEST);
				player_move(player, map);
				break;
			case SDLK_SPACE:
					if (player_get_nb_bomb(player)>0){
						game->bomb = bomb_prepend(game->bomb,i,j);
						//printf("j'appuie sur espace\n");
					}
				break;

			case SDLK_j:

				break;
			case SDLK_k:

				break;
			default:
				break;
			}
		break;
		}
	}
	return 0;
}



// Fonction ????
int game_update(struct game* game, int timer) {
	if (input_keyboard(game, timer))
		return 1; // exit game

	return 0;
}
