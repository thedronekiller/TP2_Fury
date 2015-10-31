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
	const IntRect GetLimitWalls(const int index);
	const IntRect GetLimitPivots(const int index);
	const IntRect GetCenterWalls(const int index);
	const IntRect GetCenterPivots(const int index);
	Wall** GetAllLimitPivots();
	Wall** GetAllCenterPivots();
private:
	Wall* pivotsContour[NB_PIVOTS_CONTOUR];
	Wall* pivotsCentre[NB_PIVOTS_CENTRE];
};

