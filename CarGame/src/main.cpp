#include "vehicle.h"
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
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
		1280,
		720,
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
		//car.move(0.016f); // Move the car with a delta time of 16 milliseconds (~60 FPS)
		car.move(deltaTime);

		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Set draw color to black
		SDL_RenderClear(renderer); // Clear the screen with the draw color

		SDL_Rect carRect = { static_cast<int>(car.getX()), static_cast<int>(car.getY()), 60, 30 };

		SDL_SetRenderDrawColor(renderer, 220, 40, 40, 255); // Set draw color to red
		SDL_RenderFillRect(renderer, &carRect); // Draw the car as a rectangle
		SDL_RenderPresent(renderer); // Present the rendered frame to the screen

		SDL_Delay(16); // Delay to simulate ~60 FPS)
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}