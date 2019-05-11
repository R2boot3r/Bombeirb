/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
#ifndef PLAYER_H_
#define PLAYER_H_

#include <map.h>
#include <constant.h>

struct player;

// Creates a new player with a given number of available bombs
struct player* player_init(int bomb_number, int hurt);
void   player_free(struct player* player);

// Set the position of the player
void player_set_position(struct player *player, int x, int y);

// Returns the current position of the player
int player_get_x(struct player* player);
int player_get_y(struct player* player);

// Set the direction of the next move of the player
void player_set_current_way(struct player * player, enum direction direction);

// Set, Increase, Decrease the number of bomb that player can put
int  player_get_nb_bomb(struct player * player);
void player_inc_nb_bomb(struct player * player);
void player_dec_nb_bomb(struct player * player);

// Set, Increase, Decrease the number of hurt that player has:
int  player_get_nb_hurt(struct player * player);
void player_inc_nb_hurt(struct player * player);
void player_dec_nb_hurt(struct player * player);

// Set, Increase, Decrease the range of bomb that player put:
int  player_get_range_bomb(struct player * player);
void player_inc_range_bomb(struct player * player);
void player_dec_range_bomb(struct player * player);

// Set, Increase, Decrease the number of key that player has:
int  player_get_key_number(struct player * player);
void player_inc_key_number(struct player * player);
void player_dec_key_number(struct player * player);










// Move gestion the player according to the current direction
int player_move(struct player* player, struct map* map);
void player_move_case_box(struct player* player, struct map* map, int x, int y);
int player_move_case_Door(struct player* player, struct map* map, int x, int y);
void player_move_case_bonus(struct player * player, struct map* map, int x, int y);


// Display the player on the screen
void player_display(struct player* player);

int player_return_level(struct player* player);
int player_return_range(struct player* player);

#endif /* PLAYER_H_ */
