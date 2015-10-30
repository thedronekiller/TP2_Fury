#include "Wall.h"

Wall::Wall(const int x, const int y)
{
	setPosition(x, y);
	setSize(Vector2f(taille_pivot, taille_pivot));
	setFillColor(Color::Blue);
	rectPivot = IntRect(x, y, taille_pivot, taille_pivot);
}


Wall::~Wall()
{
}

void Wall::InitializeAttachedWall(int x, int y, const DIRECTION dir)
{
	if (dir == NORTH || dir == NORTH_EAST )
		attachedWall.setSize(Vector2f(15, 220));
	else if (dir == SOUTH || dir == SOUTH_WEST)
	{
		attachedWall.setSize(Vector2f(15, 220));
	}
	else
		attachedWall.setSize(Vector2f(220, 15));
	attachedWall.setPosition(Vector2f(x, y));
	attachedWall.setFillColor(Color::Green);
	rectAttachedWall = IntRect(x, y, attachedWall.getSize().x, attachedWall.getSize().y);
}

const RectangleShape Wall::GetAttachedWall()
{
	return attachedWall;
}
const IntRect Wall::GetRectPivot()
{
	return rectPivot;
}

const IntRect Wall::GetRectWall()
{
	return rectAttachedWall;
}