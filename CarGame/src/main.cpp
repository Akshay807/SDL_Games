#define SDL_MAIN_HANDLED
#include "game.h"

using namespace std;

int main() {
	Game game;
	game.run();

	return 0;
}
	

	//Vehicle car(100.0f, 300.0f, 100.0f); // Initial position (100, 300) and speed 100 units per second)

	//

	//Uint32 lastTime = SDL_GetTicks();
	//

	//

	//	Uint32 currentTime = SDL_GetTicks();
	//	float deltaTime = (currentTime - lastTime) / 1000.0f;
	//	lastTime = currentTime;

	//	roadOffset += 200.0f * deltaTime;
	//	if (roadOffset >= GameConfig::DASH_HEIGHT + GameConfig::DASH_GAP)
	//	{
	//		roadOffset -= GameConfig::DASH_HEIGHT + GameConfig::DASH_GAP;
	//	}


	//	car.move(deltaTime, directionX, directionY);
	
	//	
	//	// Car Rendering
	//	SDL_Rect carRect = { static_cast<int>(car.getX()), static_cast<int>(car.getY()), Vehicle::WIDTH, Vehicle::HEIGHT };

	//	
	//}

	//SDL_DestroyWindow(window);
	//SDL_Quit();
	//return 0;