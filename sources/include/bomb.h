#include <SDL/SDL_image.h>
#include <assert.h>
#include <sprite.h>
#include <misc.h>
#include <constant.h>

struct bomb;

struct bomb* bomb_new(int x, int y);

void bomb_free(struct bomb* bomb);
void update_time_bomb(struct bomb* bomb);
int bomb_get_x(struct bomb* bomb);
int bomb_get_y(struct bomb* bomb);
