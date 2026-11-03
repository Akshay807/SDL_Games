#pragma once
#include <SDL.h>
#include "vehicle.h"
#include "road.h"

class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Vehicle car;
	Road road;

public:
	Game::Game();
	~Game();

	void run();
};