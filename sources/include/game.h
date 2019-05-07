/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
#ifndef GAME_H_
#define GAME_H_

#include <player.h>
#include <map.h>
#include <window.h>
#include <sprite.h>
#include <bomb.h>
// Abstract data type
struct game;

// Create a new game
struct game* game_new();

// Free a game
void game_free(struct game* game);

// Return the player of the current game
struct player* game_get_player(struct game* game);

// Return the current map
struct map* game_get_current_map(struct game* game);

// Display the game on the screen
void game_display(struct game* game);

// update
int game_update(struct game* game, int timer);

// Fonction qui permet de changer de map
void map_change(struct game* game, int x);

void game_set_bomb(struct game * game, struct bomb * bombs);

#endif /* GAME_H_ */
