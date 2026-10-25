#pragma once

class Vehicle
{
private:
	float x;
	float y;
	float speed;

public:
	Vehicle(float x, float y, float speed);

	//Public Getter and Setter methods for x, y, and speed
	float getX() const;
	float getY() const;
	float getSpeed() const;

	void setX(float newX);
	void setY(float newY);
	void setSpeed(float newSpeed);

	void move(float deltaTime);
};