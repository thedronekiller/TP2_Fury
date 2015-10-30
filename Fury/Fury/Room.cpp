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
	for (int i = 0; i < NB_PIVOTS_CONTOUR; i++)
	{
		pivotsContour[i] = new Wall(x, y);
		if (i < 5 || (i>=10 && i<15))
		{
			if (i!= 2 && i!=12)
				pivotsContour[i]->InitializeAttachedWall(x + TAILLE_PIVOT, y, EAST);
		}
		else if (i >= 5 && i < 8)
		{
			pivotsContour[i]->InitializeAttachedWall(x, y - 220, NORTH);
			x = LARGEUR - COLONNE_POINTAGE_LARGEUR - TAILLE_PIVOT;
		}
		else if (i >= 8 && i < 10)
		{
			pivotsContour[i]->InitializeAttachedWall(x, y + TAILLE_PIVOT , SOUTH);
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
	x = 220-TAILLE_PIVOT;
	y = 220+TAILLE_PIVOT;
	int dir = 0;
	// Initialisation des pivots et murs centraux
	for (int j = 0; j < NB_PIVOTS_CENTRE; j++)
	{
		pivotsCentre[j] = new Wall(x, y);
		dir = rand() % 8;
		pivotsCentre[j]->InitializeAttachedWall(x + TAILLE_PIVOT, y, DIRECTION(dir));
		for (int i = 0; i < j; i++)
		{
			if (pivotsCentre[j]->GetRectWall().intersects(pivotsCentre[i]->GetRectWall()))
			{
				while (pivotsCentre[j]->GetRectWall().intersects(pivotsCentre[i]->GetRectWall()))
				{
					pivotsCentre[j]->InitializeAttachedWall(x, y, DIRECTION(rand()%8));
				}
			}
		}
		x += 220 + TAILLE_PIVOT;
		if (x+TAILLE_PIVOT >= LARGEUR - COLONNE_POINTAGE_LARGEUR - TAILLE_PIVOT)
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
