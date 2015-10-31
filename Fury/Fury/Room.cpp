#include "Room.h"


Room::Room()
{
	srand(time(NULL));
	InitializeWalls();
}


Room::~Room()
{
	for (int i = 0; i < NB_PIVOTS_CONTOUR; i++)
		delete pivotsContour[i];
	for (int j = 0; j < NB_PIVOTS_CENTRE; j++)
		delete pivotsCentre[j];
}

void Room::InitializeWalls()
{
	//Initialisation des pivots et murs contours
	int x = 0;
	int y = 0;
	int row = 1;
	/*pivotsContour[0] = new Wall(x, y);
	pivotsContour[1] = new Wall(x, y);
	pivotsContour[2] = new Wall(x, y);
	pivotsContour[3] = new Wall(x, y);
	pivotsContour[4] = new Wall(x, y);
	pivotsContour[5] = new Wall(x, y);
	pivotsContour[6] = new Wall(x, y);
	pivotsContour[7] = new Wall(x, y);
	pivotsContour[8] = new Wall(x, y);
	pivotsContour[9] = new Wall(x, y);
	pivotsContour[10] = new Wall(x, y);
	pivotsContour[11] = new Wall(x, y);
	pivotsContour[12] = new Wall(x, y);
	pivotsContour[13] = new Wall(x, y);
	pivotsContour[14] = new Wall(x, y);
	pivotsContour[15] = new Wall(x, y);*/
	//8,10,11,13,14
	
	for (int i = 0; i < NB_PIVOTS_CONTOUR; i++)
	{
		pivotsContour[i] = new Wall(x, y);
		if (i < 5 || (i>=10 && i<15))
		{
			if (i!= 2 && i!=12)
				pivotsContour[i]->InitializeAttachedWall(x + TAILLE_PIVOT, y, EAST, true);
		}
		else if (i >= 5 && i < 8)
		{
			if (i!=6)
				pivotsContour[i]->InitializeAttachedWall(x, y+TAILLE_PIVOT, NORTH, true);
			else
				pivotsContour[i]->InitializeAttachedWall(x, y-220, NORTH, true);
			x = LARGEUR - COLONNE_POINTAGE_LARGEUR - TAILLE_PIVOT;
		}
		else if (i >= 8 && i < 10)
		{
			pivotsContour[i]->InitializeAttachedWall(x, y + TAILLE_PIVOT , SOUTH, true);
		}

		if (i == 5 || i==7 || i==9)
		{
			x = 0;
			y += 220 + TAILLE_PIVOT;
		}
		else if (i == 6 || i==8)
		{
			x = LARGEUR - COLONNE_POINTAGE_LARGEUR - TAILLE_PIVOT;
		}
		else 
		{
			x += 220 + TAILLE_PIVOT;
		}
	}
	// On set les "murs" des portes à une valeur par défaut
	pivotsContour[2]->InitializeAttachedWall(x, y + TAILLE_PIVOT, NONE, true);
	//pivotsContour[6]->InitializeAttachedWall(x, y + TAILLE_PIVOT, NONE, true);
	pivotsContour[7]->InitializeAttachedWall(x, y + TAILLE_PIVOT, NONE, true);
	//pivotsContour[8]->InitializeAttachedWall(0, 485, SOUTH, true);
	//pivotsContour[10]->InitializeAttachedWall(15, 705, EAST, true);
	//pivotsContour[11]->InitializeAttachedWall(205, 705, EAST, true);
	pivotsContour[12]->InitializeAttachedWall(x, y + TAILLE_PIVOT, NONE, true);
	//pivotsContour[13]->InitializeAttachedWall(720, 705, EAST, true);
	//pivotsContour[14]->InitializeAttachedWall(955, 705, EAST, true);

	x = 220+TAILLE_PIVOT;
	y = 220+TAILLE_PIVOT;
	int dir = 0;
	// Initialisation des pivots et murs centraux
	for (int j = 0; j < NB_PIVOTS_CENTRE; j++)
	{
		pivotsCentre[j] = new Wall(x, y);
		dir = rand() % 8;
		pivotsCentre[j]->InitializeAttachedWall(x, y, DIRECTION(dir), false);
		for (int i = 0; i < j; i++)
		{
			if (pivotsCentre[j]->GetRectWall().intersects(pivotsCentre[i]->GetRectWall()))
			{
				while (pivotsCentre[j]->GetRectWall().intersects(pivotsCentre[i]->GetRectWall()))
				{
					pivotsCentre[j]->InitializeAttachedWall(x, y, DIRECTION(rand()%8), false);
				}
			}
		}
		x += 220 + TAILLE_PIVOT;
		if (x+(TAILLE_PIVOT*2) >= LARGEUR - COLONNE_POINTAGE_LARGEUR - TAILLE_PIVOT)
		{
			x = 220+TAILLE_PIVOT;
			y += 220 + TAILLE_PIVOT;
		}
	}
}

void Room::Draw(RenderWindow* win)
{
	for (int i = 0; i < NB_PIVOTS_CENTRE; i++)
	{
		win->draw(*pivotsCentre[i]);
		win->draw(pivotsCentre[i]->GetAttachedWall());
	}
	for (int j = 0; j < NB_PIVOTS_CONTOUR; j++)
	{
		win->draw(*pivotsContour[j]);
		win->draw(pivotsContour[j]->GetAttachedWall());
	}
}

const IntRect Room::GetLimitWalls(const int index)
{
	return pivotsContour[index]->GetRectWall();
}

const IntRect Room::GetCenterWalls(const int index)
{
	return pivotsCentre[index]->GetRectWall();
}

const IntRect Room::GetLimitPivots(const int index)
{
	return pivotsContour[index]->GetRectPivot();
}
const IntRect Room::GetCenterPivots(const int index)
{
	return pivotsCentre[index]->GetRectPivot();
}
Wall** Room::GetAllLimitPivots()
{
	return pivotsContour;
}
Wall** Room::GetAllCenterPivots()
{
	return pivotsCentre;
}