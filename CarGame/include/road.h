#pragma once
#include <SDL.h>

class Road
{
private:
	float roadOffset; // Offset for the road movement

public:
	Road();

	void update(float deltaTime);
	void render(SDL_Renderer* renderer) const;
};