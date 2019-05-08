#include <SDL/SDL_image.h>
#include <assert.h>
#include <sprite.h>
#include <misc.h>
#include <constant.h>

struct bomb;
struct bomb* bomb_init();

struct bomb* bomb_create(int x, int y);

struct bomb* bomb_prepend( struct bomb* head, int x , int y);

void bomb_timer_update(struct bomb* bomb);
void bomb_display(struct bomb* bomb);

void bomb_free(struct bomb* bomb);

int bomb_get_x(struct bomb* bomb);

int bomb_get_y(struct bomb* bomb);

int bomb_get_bomb_type(struct bomb* bomb);
int bomb_get_timer(struct bomb* bomb);
