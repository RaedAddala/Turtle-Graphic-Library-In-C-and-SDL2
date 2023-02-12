#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include"TurtleMagic.hpp"
#include "GTurtle.hpp"


SDL_bool Init(void);
void Quit(void);
// Function called in the Init Function : 
void TurtleGraphicsInit(void);

GTurtle* Turtle = nullptr;
SDL_Window* Window = nullptr;
SDL_Renderer* Renderer = nullptr;

const int WINDOW_WIDTH  = 1280;
const int WINDOW_HEIGHT = 720;

int main(int argc, char* argv[])
{
	atexit(Quit);
	if (Init() == SDL_FALSE)exit(EXIT_FAILURE);
	SDL_bool KeepWorking = SDL_TRUE;
	SDL_Event event;
	while (KeepWorking)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					exit(EXIT_SUCCESS);
					break;
			}
		}
	}
	exit(EXIT_SUCCESS);
}

SDL_bool Init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		fprintf(stderr, "ERROR : INIT FAILED - %s", SDL_GetError());
		return SDL_FALSE;
	}
	if ( (Window = SDL_CreateWindow("Turtle Graphics",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED ,
					WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_FULLSCREEN))
		== nullptr)
	{
		fprintf(stderr, "ERROR : WINDOW CREATION FAILED - %s", SDL_GetError());
		return SDL_FALSE;
	}
	if ((Renderer = SDL_CreateRenderer(Window,-1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC))
		== nullptr)
	{
		fprintf(stderr, "ERROR : RENDERER CREATION FAILED - %s", SDL_GetError());
		return SDL_FALSE;
	}
	TurtleGraphicsInit();
	return SDL_TRUE;
}
void Quit(void)
{
	if(Renderer) SDL_DestroyRenderer(Renderer);
	if (Window) SDL_DestroyWindow(Window);
	if (Turtle) delete Turtle;

	SDL_Quit();
}


void TurtleGraphicsInit()
{
	Turtle = new GTurtle(static_cast<float>(WINDOW_WIDTH) / 2.0f, static_cast<float>(WINDOW_HEIGHT)/ 2.0f,2);
	// Background WHITE
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderClear(Renderer);
	Turtle->DrawModeOn();
	Turtle->setLength(75);
	Turtle->SetDrawColor({ 100,25,50,255 });
	TurtleDoMagic();
	// SHOW TO WINDOW
	SDL_RenderPresent(Renderer);
};
