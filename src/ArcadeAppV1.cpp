// ArcadeAppV1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SDL.h>
#include "Graphics/Color.h"
#undef main

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;

void SetPixel(SDL_Surface* noptrWindowSurface, uint32_t color, int x, int y);
size_t GetIndex(SDL_Surface* noptrWindowSurface, int row, int column);

int main(int argc, const char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "Error SDL_Init Failed" << std::endl;
		return 1;
	}

	SDL_Window* optrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if (optrWindow == nullptr)
	{
		std::cout << "Couldn't create window, error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Surface* noptrWindowSurface = SDL_GetWindowSurface(optrWindow);
	SDL_PixelFormat* pixelFormat = noptrWindowSurface->format;
	Color::InitColorFormat(pixelFormat);


	SetPixel(noptrWindowSurface, Color::Orange().GetPixelColor(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SDL_UpdateWindowSurface(optrWindow);

	SDL_Event sdlEvent;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}


	SDL_DestroyWindow(optrWindow);
	SDL_Quit();

	return 0;
}

void SetPixel(SDL_Surface* noptrWindowSurface, uint32_t color, int x, int y)
{
	SDL_LockSurface(noptrWindowSurface);

	uint32_t *pixels = (uint32_t*)noptrWindowSurface->pixels;

	size_t index = GetIndex(noptrWindowSurface, y, x);

	pixels[index] = color;

	SDL_UnlockSurface(noptrWindowSurface);
}


size_t GetIndex(SDL_Surface* noptrWindowSurface, int row, int column)
{
	return row * noptrWindowSurface->w + column;
}