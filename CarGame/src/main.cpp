#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "vehicle.h"
#include "game_config.h"
#include <iostream>

using namespace std;

int main() {

	SDL_SetMainReady();		// Call this before SDL_Init to avoid SDL overriding the main function -> Tell SDL2 not to replace the entry point.
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "SDL Initialization failed:" << SDL_GetError() << endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
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
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		cout << "SDL Renderer creation failed: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	Vehicle car(100.0f, 300.0f, 100.0f); // Initial position (100, 300) and speed 100 units per second)

	bool isRunning = true;
	SDL_Event event;

	Uint32 lastTime = SDL_GetTicks();
	float roadOffset = 0.0f;

	while (isRunning) // Game Loop
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}

		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		roadOffset += 200.0f * deltaTime;
		if (roadOffset >= GameConfig::DASH_HEIGHT + GameConfig::DASH_GAP)
		{
			roadOffset -= GameConfig::DASH_HEIGHT + GameConfig::DASH_GAP;
		}

		const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);
		
		float directionX = 0.0f;
		float directionY = 0.0f;

		if (keyboardState[SDL_SCANCODE_UP]) directionY = -1.0f; // Move up
		if (keyboardState[SDL_SCANCODE_DOWN]) directionY = 1.0f; // Move down
		if (keyboardState[SDL_SCANCODE_LEFT]) directionX = -1.0f; // Move left
		if (keyboardState[SDL_SCANCODE_RIGHT]) directionX = 1.0f; // Move right

		car.move(deltaTime, directionX, directionY);

		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Set draw color to black
		SDL_RenderClear(renderer); // Clear the screen with the draw 
		
		//Road Surface
		SDL_Rect roadRect = { GameConfig::ROAD_X, 0, GameConfig::ROAD_WIDTH, GameConfig::WINDOW_HEIGHT };
		SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
		SDL_RenderFillRect(renderer, &roadRect); // Draw the road as a rectangle

		// Road Boundaries
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set draw color to white
		SDL_RenderDrawLine(renderer, GameConfig::ROAD_X, 0, GameConfig::ROAD_X, GameConfig::WINDOW_HEIGHT); // Left boundary
		SDL_RenderDrawLine(renderer, GameConfig::ROAD_X + GameConfig::ROAD_WIDTH, 0, GameConfig::ROAD_X + GameConfig::ROAD_WIDTH, GameConfig::WINDOW_HEIGHT); // Right Boundary

		// Lane Divider + Road Movement
		int laneDividerX = GameConfig::ROAD_X + GameConfig::LANE_WIDTH;
		int patternHeight = GameConfig::DASH_HEIGHT + GameConfig::DASH_GAP;
		for (int y = -patternHeight; y < GameConfig::WINDOW_HEIGHT; y += patternHeight)
		{
			int dashY = y + static_cast<int>(roadOffset);
			SDL_RenderDrawLine(renderer, laneDividerX, dashY, laneDividerX, dashY + GameConfig::DASH_HEIGHT);
		}
		
		// Car Rendering
		SDL_Rect carRect = { static_cast<int>(car.getX()), static_cast<int>(car.getY()), Vehicle::WIDTH, Vehicle::HEIGHT };

		SDL_SetRenderDrawColor(renderer, 220, 40, 40, 255); // Set draw color to red
		SDL_RenderFillRect(renderer, &carRect); // Draw the car as a rectangle
		SDL_RenderPresent(renderer); // Present the rendered frame to the screen

		SDL_Delay(16); // Delay to simulate ~60 FPS)
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}