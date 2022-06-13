#pragma once
#include "main.h"
#include "Vector2D.h"

class BaseGameEntity
{
public:
	BaseGameEntity(float x, float y, float r);
	Vector2D getPos() { return *pos; }
	float getRadius() { return m_r; }

	void draw(SDL_Renderer* renderer);
private:
	Vector2D* pos;
	float m_r;
};