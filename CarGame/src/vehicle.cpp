#include <SDL.h>
#include <cmath>
#include "vehicle.h"
#include "game_config.h"

Vehicle::Vehicle(float x, float y, float speed) : x(x), y(y), speed(speed) {}

float Vehicle::getX() const 
{
	return x;
}

float Vehicle::getY() const
{
	return y;
}

float Vehicle::getSpeed() const
{
	return speed;
}

void Vehicle::setX(float newX) 
{
	x = newX;
}

void Vehicle::setY(float newY)
{
	y = newY;
}

void Vehicle::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

//void Vehicle::move(float deltaTime, const Uint8* keyboardState)
//{
//	// Assuming the vehicle moves in the positive x direction
//	//x += speed * deltaTime;
//
//	if (keyboardState[SDL_SCANCODE_UP])
//	{
//		y -= speed * deltaTime; // Move up
//	}
//	if (keyboardState[SDL_SCANCODE_DOWN])
//	{
//		y += speed * deltaTime; // Move down
//	}
//	if (keyboardState[SDL_SCANCODE_LEFT])
//	{
//		x -= speed * deltaTime; // Move left
//	}
//	if (keyboardState[SDL_SCANCODE_RIGHT])
//	{
//		x += speed * deltaTime; // Move right
//	}
//
//	if (x < 0) x = 0; // Prevent moving out of the left boundary
//	if (y < 0) y = 0; // Prevent moving out of the top boundary
//	if (x > GameConfig::WINDOW_WIDTH - WIDTH) x = GameConfig::WINDOW_WIDTH - WIDTH; // Prevent moving out of the right boundary (assuming vehicle width is 30)
//	if (y > GameConfig::WINDOW_HEIGHT - HEIGHT) y = GameConfig::WINDOW_HEIGHT - HEIGHT; // Prevent moving out of the bottom boundary (assuming vehicle height is 60)
//}

void Vehicle::move(float deltaTime, float directionX, float directionY)
{
	float length = std::sqrt(directionX * directionX + directionY * directionY);

	if (length > 0.0f)
	{
		directionX /= length;
		directionY /= length;
	}

	x += directionX * speed * deltaTime;
	y += directionY * speed * deltaTime;

	if (x < 0) x = 0; // Prevent moving out of the left boundary
	if (y < 0) y = 0; // Prevent moving out of the top boundary
	if (x > GameConfig::WINDOW_WIDTH - WIDTH) x = GameConfig::WINDOW_WIDTH - WIDTH; // Prevent moving out of the right boundary (assuming vehicle width is 30)
	if (y > GameConfig::WINDOW_HEIGHT - HEIGHT) y = GameConfig::WINDOW_HEIGHT - HEIGHT; // Prevent moving out of the bottom boundary (assuming vehicle height is 60)
}
