#pragma once

#include "Vector2D.h"
#include "Vehicle.h"
#include <vector>
#include "BaseGameEntity.h"

class SteeringBehavior
{
public:
	SteeringBehavior(float x, float y);
	Vector2D Flee(Vector2D* TargetPos);
	Vector2D Evade(Vehicle* pursuer);
	Vector2D Arrive(Vector2D* target);
	Vector2D Hide(Vehicle* hunter,
		const std::vector<BaseGameEntity*>& obstacles);
	Vector2D* GetHidingPosition(const Vector2D& posOb,
		const double radiusOb,
		const Vector2D& posHunter);
	void applyForce(Vector2D* force);
	Vector2D rotate(float x, float y, float rad);
	void edges();

	void update();
	void draw(SDL_Renderer* renderer);

private:
	Vector2D* pos;
	float maxSpeed;
	Vector2D* DesiredVelocity;

	Vector2D* ToPursuer;
	Vector2D* value;

	Vector2D* force;
	Vector2D* vel;

	float MaxDouble;
	Vector2D* tmp;
	Vector2D* BestHidingSpot;
	float MaxFloat;

	Vector2D* ToOb;

	Vector2D* acc;
	float side;
	double radian;
	Vector2D* m_xy1;
	Vector2D* m_xy2;
	Vector2D* m_xy3;
};