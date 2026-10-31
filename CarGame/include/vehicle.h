#pragma once
#include <SDL.h>

class Vehicle
{
private:
	float x;
	float y;
	float speed;

public:
	static constexpr int WIDTH = 30;  // Width of the vehicle
	static constexpr int HEIGHT = 60; // Height of the vehicle

	Vehicle(float x, float y, float speed);

	//Public Getter and Setter methods for x, y, and speed
	float getX() const;
	float getY() const;
	float getSpeed() const;

	void setX(float newX);
	void setY(float newY);
	void setSpeed(float newSpeed);

	//void move(float deltaTime, const Uint8* keyboardState);
	void move(float deltaTime, float directionX, float directionY);
};