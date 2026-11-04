#include "game.h"
#include "game_config.h"
#include <iostream>
using namespace std;

Game::Game() : car(100.0f, 300.0f, 100.0f)
{
	window = nullptr;
	renderer = nullptr;

	SDL_SetMainReady();		// Call this before SDL_Init to avoid SDL overriding the main function -> Tell SDL2 not to replace the entry point.

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "SDL Initialization failed:" << SDL_GetError() << endl;
		return;
	}

	window = SDL_CreateWindow(
		"Car Racing Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		GameConfig::WINDOW_WIDTH,
		GameConfig::WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == nullptr)
	{
		cout << "Window creation failed: " << SDL_GetError() << endl;
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		cout << "SDL Renderer creation failed: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}
}

Game::~Game()
{
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}

void Game::handleEvents(float& directionX, float& directionY)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	directionX = 0.0f;
	directionY = 0.0f;

	if (keyboardState[SDL_SCANCODE_UP]) directionY = -1.0f; // Move up
	if (keyboardState[SDL_SCANCODE_DOWN]) directionY = 1.0f; // Move down
	if (keyboardState[SDL_SCANCODE_LEFT]) directionX = -1.0f; // Move left
	if (keyboardState[SDL_SCANCODE_RIGHT]) directionX = 1.0f; // Move right
}

void Game::update(float deltaTime, float directionX, float directionY)
{
	car.move(deltaTime, directionX, directionY);
	road.update(deltaTime);
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);
	road.render(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set draw color to red
	SDL_Rect carRect = { static_cast<int>(car.getX()), static_cast<int>(car.getY()), Vehicle::WIDTH, Vehicle::HEIGHT };
	SDL_RenderFillRect(renderer, &carRect); // Draw the car
	SDL_RenderPresent(renderer);
}

void Game::run()
{
	if (renderer == nullptr) return; // Ensure renderer is valid before proceeding

	isRunning = true;
	Uint32 lastTime = SDL_GetTicks();

	while (isRunning) // Game Loop
	{
		float directionX = 0.0f;
		float directionY = 0.0f;

		handleEvents(directionX, directionY);

		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds
		lastTime = currentTime;

		update(deltaTime, directionX, directionY);
		render();
		SDL_Delay(16); // Delay to cap the frame rate (approx. 60 FPS)
	}
}