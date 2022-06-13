#include "SteeringBehavior.h"
#include <math.h>

const int WIDTH = 600;
const int HEIGHT = 400;

SteeringBehavior::SteeringBehavior(float x, float y)
{
	pos = new Vector2D(x, y);
	maxSpeed = 6;
	DesiredVelocity = new Vector2D(0, 0);

	ToPursuer = new Vector2D(0, 0);
	value = new Vector2D(0, 0);

	force = new Vector2D(0, 0);
	vel = new Vector2D(0, 0);

	MaxDouble = 100;
	tmp = new Vector2D(0, 0);
	BestHidingSpot = new Vector2D(0, 0);
	MaxFloat = 100;

	ToOb = new Vector2D(0, 0);

	acc = new Vector2D(0, 0);
	side = 16;
	radian = 0;
	m_xy1 = new Vector2D(0, 0);
	m_xy2 = new Vector2D(0, 0);
	m_xy3 = new Vector2D(0, 0);
}

Vector2D SteeringBehavior::Flee(Vector2D* TargetPos)
{
	*DesiredVelocity = *pos - *TargetPos;
	DesiredVelocity->normalize();
	*DesiredVelocity *= maxSpeed;
	*DesiredVelocity -= *vel;

	return *DesiredVelocity;
}

Vector2D SteeringBehavior::Evade(Vehicle* pursuer)
{
	*ToPursuer = pursuer->getPos() - *pos;

	const double ThreatRange = 100.0f;
	if (ToPursuer->length() * ToPursuer->length() > ThreatRange * ThreatRange)
	{
		return Vector2D(0, 0);
	}

	double LookAheadTime = ToPursuer->length() / (maxSpeed + pursuer->getMaxSpeed());
	*value = pursuer->getPos() + pursuer->getVel() * LookAheadTime;

	return Flee(value);
}

Vector2D SteeringBehavior::Arrive(Vector2D* target)
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

Vector2D SteeringBehavior::Hide(Vehicle* hunter,
	const std::vector<BaseGameEntity*>& obstacles)
{
	double DistToClosest = MaxDouble;

	std::vector<BaseGameEntity*>::const_iterator curOb = obstacles.begin();
	std::vector<BaseGameEntity*>::const_iterator closest;

	while (curOb != obstacles.end())
	{
		Vector2D* HidingSpot = GetHidingPosition((*curOb)->getPos(),
			(*curOb)->getRadius(),
			hunter->getPos());

		*tmp = *HidingSpot - *pos;
		double dist = tmp->length();

		if (dist < DistToClosest)
		{
			DistToClosest = dist;

			*BestHidingSpot = *HidingSpot;

			closest = curOb;
		}

		++curOb;
	}

	if (DistToClosest == MaxFloat)
	{
		return Evade(hunter);
	}

	return Arrive(BestHidingSpot);
}

Vector2D* SteeringBehavior::GetHidingPosition(const Vector2D& posOb,
	const double radiusOb,
	const Vector2D& posHunter)
{
	const double DistanceFromBoundary = 30.0f;
	double DistAway = radiusOb + DistanceFromBoundary;

	*ToOb = posOb - posHunter;
	ToOb->normalize();
	*ToOb *= DistAway;
	*ToOb += posOb;

	return ToOb;
}

void SteeringBehavior::applyForce(Vector2D* force)
{
	*acc += *force;
}

Vector2D SteeringBehavior::rotate(float x, float y, float rad)
{
	Vector2D tmp(0, 0);
	tmp.setX(cos(rad) * x - sin(rad) * y);
	tmp.setY(sin(rad) * x + cos(rad) * y);
	return tmp;
}

void SteeringBehavior::edges()
{
	if (pos->getX() > WIDTH + side)
	{
		pos->setX(-side);
	}
	else if (pos->getX() < -side)
	{
		pos->setX(WIDTH + side);
	}

	if (pos->getY() > HEIGHT + side)
	{
		pos->setY(-side);
	}
	else if (pos->getY() < -side)
	{
		pos->setY(HEIGHT + side);
	}
}

void SteeringBehavior::update()
{
	edges();

	*vel += *acc;
	vel->limit(maxSpeed);
	*pos += *vel;
	*acc *= 0;

	radian = atan2(vel->getY(), vel->getX());
	*m_xy1 = rotate(-side, -side / 2, radian);
	*m_xy2 = rotate(-side, side / 2, radian);
	*m_xy3 = rotate(side, 0, radian);
}

void SteeringBehavior::draw(SDL_Renderer* renderer)
{
	filledTrigonRGBA(renderer,
		m_xy1->getX() + pos->getX(), m_xy1->getY() + pos->getY(),
		m_xy2->getX() + pos->getX(), m_xy2->getY() + pos->getY(),
		m_xy3->getX() + pos->getX(), m_xy3->getY() + pos->getY(),
		255, 255, 255, 255);
}