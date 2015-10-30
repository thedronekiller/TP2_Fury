#pragma once
#include "Wall.h"
#include <SFML\Graphics.hpp>
#include <random>
#include <ctime>
using namespace sf;
using namespace std;
class Room
{
public:
	Room();
	~Room();
	void InitializeWalls();
	void Draw(RenderWindow* win);
	Wall* GetLimitWalls();
	Wall* GetCenterWalls();
private:
	Wall* pivotsContour[NB_PIVOTS_CONTOUR];
	Wall* pivotsCentre[NB_PIVOTS_CENTRE];
};

