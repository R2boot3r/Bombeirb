#include <SDL/SDL_image.h>
#include <assert.h>
#include <sprite.h>
#include <misc.h>
#include <constant.h>

struct bomb;
struct bomb* bomb_init();

struct bomb* bomb_create(int x, int y);

struct bomb* bombs_add_bomb( struct bomb* bombs, int x , int y);

void bomb_update(struct bomb* bombs);
void bomb_display(struct bomb* bombs);

void bomb_destruction(struct bomb* bombs, struct game* game);

int bombs_get_size(struct bomb *bombs);

/*void bomb_free(struct bomb* bomb);

int bomb_get_x(struct bomb* bomb);

int bomb_get_y(struct bomb* bomb);

int bomb_get_bomb_type(struct bomb* bomb);
int bomb_get_timer(struct bomb* bomb);
*/
