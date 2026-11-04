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

	bool isRunning;

	void update(float deltaTime, float directionX, float directionY);
	void handleEvents(float& directionX, float& directionY);
	void render();

public:
	Game::Game();
	~Game();

	void run();
};