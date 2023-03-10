#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "RKS-16.hpp"

class Emulator {
    public:
        inline void init(const char*, int, int, int, int);
        void start();

    private:
        SDL_Window* window;
        SDL_Event event;
        bool quit = false;
};

void Emulator::init(const char *windowName, int xPos, int yPos, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow(windowName, xPos, yPos, width, height, 0);
}

void Emulator::start() {
    while (!quit) {
        SDL_WaitEvent(&event);
 
        switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
        }
    }
 
    SDL_Quit();
}
 
// int main() {
//     bool quit = false;
//     SDL_Event event;
 
//     SDL_Init(SDL_INIT_VIDEO);
 
//     SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
 
//     while (!quit)
//     {
//         SDL_WaitEvent(&event);
 
//         switch (event.type) {
// 			case SDL_QUIT:
// 				quit = true;
// 				break;
//         }
//     }
 
//     SDL_Quit();
 
//     return 0;
// }