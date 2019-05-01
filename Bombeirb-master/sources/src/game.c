/******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
 //////////////// Bibliothèques ////////////////

#include <assert.h>
#include <time.h>
#include <game.h>
#include <misc.h>


////////////////// Variables ////////////////////

struct game {
	struct map** maps;       // the game's map
	short levels;        // nb maps of the game
	struct player* player;
}; // struture du game

////////////////// Fonctions ////////////////////

// Fonction qui crée une nouvelle game
struct game* game_new(void) {
	sprite_load(); // load sprites into process memory

	struct game* game = malloc(sizeof(*game));
	game->maps = malloc(sizeof(struct game));
	game->maps[0] = map_get_static_1();
	game->maps[1] = map_get_static_2();
	game->levels = 2;
	//game->level = 0;

	game->player = player_init(3);
	// Set default location of the player
	player_set_position(game->player, 1, 0);

	return game;

}

// initialisation du jeu

// Fonction qui libère toutes les variables de game ATT voir pour maps
void game_free(struct game* game) {
	assert(game);

	player_free(game->player);
	for (int i = 0; i < game->levels; i++)
		map_free(game->maps[i]);
}


// Fonction qui prend la structure de la map et renvoie celle du player
struct player* game_get_player(struct game* game) {
	assert(game);
	return game->player;
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
	window_display_image(sprite_get_number(7), x, y);

	x = 2 * white_bloc + 2 * SIZE_BLOC;
	window_display_image(sprite_get_banner_bomb(), x, y);

	x = 2 * white_bloc + 3 * SIZE_BLOC;
	window_display_image(
			sprite_get_number(player_get_nb_bomb(game_get_player(game))), x, y);

	x = 3 * white_bloc + 4 * SIZE_BLOC;
	window_display_image(sprite_get_banner_range(), x, y);

	x = 3 * white_bloc + 5 * SIZE_BLOC;
	window_display_image(sprite_get_number(3), x, y);
}

// Fonction Principale d'affichage
void game_display(struct game* game) {
	assert(game);

	window_clear();
	game_banner_display(game);
	map_display(game_get_current_map(game));
	player_display(game->player);

	window_refresh();
}




// Fonction qui detecte les touches et agit en fonction
static short input_keyboard(struct game* game, int timer) { // recupère les entrées clavier et agit en fonction !! comprend pas encore toutes les actions
	SDL_Event event; // structure qui permet de lire les événements du pc
	struct player* player = game_get_player(game); // récupère les infos du player
	struct map* map = game_get_current_map(game);	// récupère les infos de la map
	int x, y;
	for (int i = 0; i < 12; i++) {
	  for (int j = 0; j < 12; j++) {
	    x = i * SIZE_BLOC;
	    y = j * SIZE_BLOC;
		}
	}
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
						timer = SDL_GetTicks();
						player_drop_bomb(player, map,timer,i,j);
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


// Fonction qui permet de changer de map
/*void map_change(struct game* game, int x) {
	if(x == 1){
		game->maps[0] = map_get_static_1();
		printf(map_get_static_1());
	}
	if (x == 0){
		game->maps[0] = map_get_static_2();
	}

}*/
