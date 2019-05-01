#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <SDL/SDL.h>

// Fonction du thread
/*void* timer(void* arg)
{
  pthread_exit(0);
}*/




// fonction principale qui va permettre de lancer les timers
int main(int argc, char ** argv)
{
  	SDL_Event event; // structure qui permet de lire les événements du pc
  	while (SDL_PollEvent(&event)) { // SDL_PollEvent permet de lire les events dans la queue
  		switch (event.type){
  		case SDL_QUIT:
  			return 1;
  		case SDL_KEYDOWN:
  			switch (event.key.keysym.sym) {
  			case SDLK_SPACE:
         printf("appuit sur la touche espace");
  					// appuit sur la touche espace
  				break;
  			default:
  				break;
  			}
  		break;
  		}
  	}
  	return 0;

  return(0);

}
