#pragma once

#include "main.h"
#include "Vector2D.h"
#include "Vehicle.h"
#include "SteeringBehavior.h"
#include <vector>
#include "BaseGameEntity.h"

class Walker
{
public:
	Walker();
	void draw(SDL_Renderer* renderer);
	void update();

private:
	Vector2D* target;
	Vector2D* force;
	Vector2D* steering;

	Vehicle* m_vehicle;
	SteeringBehavior* m_steeringbehavior;

	std::vector<BaseGameEntity*> m_obstacles;
};