#include "vehicle.h"

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

void Vehicle::move(float deltaTime)
{
	// Assuming the vehicle moves in the positive x direction
	x += speed * deltaTime;
}