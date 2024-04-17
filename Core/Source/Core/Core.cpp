#include "Core.h"

#include <iostream>

#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <SDL_Image.h>



void PrintHelloWorld()
{
	std::cout << "Hello World!\n";

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (result < 0) 
    {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("sdl3 hello world", 800, 600, 0);
    if (window == NULL) 
    {
        SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) 
    {
        SDL_Log("SDL_CreateRenderer: %s", SDL_GetError());
        return;
    }

    SDL_Log("SDL3 initialized");

    SDL_Event event;
    int quit = 0;
    while (!quit) 
    {
        while (SDL_PollEvent(&event)) 
        {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                SDL_Log("SDL3 event quit");
                quit = 1;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) 
                {
                    SDL_Log("SDL3 ESC key quit");
                    quit = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, 0xff);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    SDL_Log("SDL3 shutdown");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}