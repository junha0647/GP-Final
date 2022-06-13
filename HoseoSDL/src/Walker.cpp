#include "Walker.h"
#include "InputHandler.h"

#include <random>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> x(0, 600);
std::uniform_real_distribution<float> y(0, 400);
std::uniform_real_distribution<float> r(16, 32);

const int objNum = 5;

Walker::Walker()
{
	target = new Vector2D(0, 0);
	force = new Vector2D(1, 1);
	steering = new Vector2D(0, 0);

	m_vehicle = new Vehicle(0, 0);
	m_steeringbehavior = new SteeringBehavior(x(gen), y(gen));

	for (int i = 0; i < objNum; i++)
	{
		m_obstacles.push_back
		(new BaseGameEntity(x(gen), y(gen), r(gen)));
	}
}

void Walker::update()
{
	target = TheInputHandler::Instance()->getMousePosition();

	*steering = m_vehicle->Arrive(target);
	m_vehicle->applyForce(steering);
	m_vehicle->update();

	*force = m_steeringbehavior->Hide(m_vehicle, m_obstacles);
	m_steeringbehavior->applyForce(force);
	m_steeringbehavior->update();
}

void Walker::draw(SDL_Renderer* renderer)
{
	filledCircleRGBA(renderer,
		target->getX(), target->getY(),
		16,
		255, 0, 0, 255);

	m_vehicle->draw(renderer);
	m_steeringbehavior->draw(renderer);

	for (BaseGameEntity* obstacle : m_obstacles)
	{
		obstacle->draw(renderer);
	}
}