#include "Vehicle.h"
#include <iostream>
#include <math.h>

Vehicle::Vehicle(float x, float y)
{
	pos = new Vector2D(x, y);
	vel = new Vector2D(0, 0);
	acc = new Vector2D(0, 0);
	maxSpeed = 6;
	maxForce = 0.4f;
	r = 16;

	radian = 0;
	m_xy1 = new Vector2D(0, 0);
	m_xy2 = new Vector2D(0, 0);
	m_xy3 = new Vector2D(0, 0);

	force = new Vector2D(0, 0);
}

Vector2D Vehicle::Arrive(Vector2D* target)
{
	*force = *target - *pos;
	double dist = force->length();
	if (dist > 0)
	{
		const double dt = 0.3f;
		double speed = dist / (50 * dt);
		speed = std::min(speed, (double)maxSpeed);
		*force *= speed / dist;
		Vector2D dv = *force;

		return dv - *vel;
	}

	return Vector2D(0, 0);
}

void Vehicle::applyForce(Vector2D* force)
{
	*acc += *force;
}

Vector2D Vehicle::rotate(float x, float y, float rad)
{
	Vector2D tmp(0, 0);
	tmp.setX(cos(rad) * x - sin(rad) * y);
	tmp.setY(sin(rad) * x + cos(rad) * y);
	return tmp;
}

void Vehicle::update()
{
	*vel += *acc;
	vel->limit(maxSpeed);
	*pos += *vel;
	*acc *= 0;

	radian = atan2(vel->getY(), vel->getX());
	*m_xy1 = rotate(-r, -r / 2, radian);
	*m_xy2 = rotate(-r, r / 2, radian);
	*m_xy3 = rotate(r, 0, radian);
}

void Vehicle::draw(SDL_Renderer* renderer)
{
	filledTrigonRGBA(renderer,
		m_xy1->getX() + pos->getX(), m_xy1->getY() + pos->getY(),
		m_xy2->getX() + pos->getX(), m_xy2->getY() + pos->getY(),
		m_xy3->getX() + pos->getX(), m_xy3->getY() + pos->getY(),
		255, 255, 255, 255);
}