#include <SDL2/SDL.h>
 
int main() {
    bool quit = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
 
    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
        }
    }
 
    SDL_Quit();
 
    return 0;
}