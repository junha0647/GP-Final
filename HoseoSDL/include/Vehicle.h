#pragma once

#include "main.h"
#include "Vector2D.h"

class Vehicle
{
public:
	Vehicle(float x, float y);
	Vector2D Arrive(Vector2D* target);
	void applyForce(Vector2D* force);

	Vector2D rotate(float x, float y, float rad);

	Vector2D getPos() { return *pos; }
	Vector2D getVel() { return *vel; }
	float getMaxSpeed() { return maxSpeed; }

	void update();
	void draw(SDL_Renderer* renderer);

private:
	Vector2D* pos;
	Vector2D* vel;
	Vector2D* acc;
	float maxSpeed, maxForce, r;

	double radian;
	Vector2D* m_xy1;
	Vector2D* m_xy2;
	Vector2D* m_xy3;

	Vector2D* force;
};