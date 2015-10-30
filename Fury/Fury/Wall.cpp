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

void Wall::InitializeAttachedWall(int x, int y, const DIRECTION dir, const bool limit)
{
	if (dir == NORTH || dir == NORTH_EAST)
	{
		attachedWall.setSize(Vector2f(15, 220));
		if (limit == false)
		{
			y -= 220;
		}
	}
	else if (dir == SOUTH || dir == SOUTH_WEST)
	{
		attachedWall.setSize(Vector2f(15, 220));
		if (limit == false)
		{
			y += TAILLE_PIVOT;
		}
	}
	else if (dir==EAST || dir == SOUTH_EAST)
	{
		if (limit==false)
			x += TAILLE_PIVOT;
		attachedWall.setSize(Vector2f(220, 15));
	}
	else if (dir == WEST | dir == NORTH_WEST)
	{
		attachedWall.setSize(Vector2f(220, 15));
		if(limit==false)
			x -= 220;
	}
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