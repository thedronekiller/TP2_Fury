#pragma once
#include <SFML\Graphics.hpp>
#include "Constante.h"
using namespace sf;
class Wall:public RectangleShape
{
public:
	Wall(const int x, const int y);
	~Wall();
	void InitializeAttachedWall(int x, int y, const DIRECTION dir);
	const RectangleShape GetAttachedWall();
	const IntRect GetRectPivot();
	const IntRect GetRectWall();
private:
	DIRECTION direction;
	RectangleShape attachedWall;
	IntRect rectAttachedWall;
	IntRect rectPivot;
	const int taille_pivot = 15;
};

