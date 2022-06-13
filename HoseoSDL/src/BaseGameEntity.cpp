#include "BaseGameEntity.h"

BaseGameEntity::BaseGameEntity(float x, float y, float r)
{
	pos = new Vector2D(x, y);
	m_r = r;
}

void BaseGameEntity::draw(SDL_Renderer* renderer)
{
	filledCircleRGBA(renderer,
		pos->getX(), pos->getY(),
		m_r,
		128, 128, 128, 192);
}