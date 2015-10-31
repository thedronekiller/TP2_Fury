#define _USE_MATH_DEFINES
#include "Robot.h"
#include <cmath>

sf::Texture Robot::texture;
Robot::Robot(sf::Vector2f position, const DIRECTION direction, const float speed) :dir(direction), speed(speed)
{
	dir = direction;
	this->speed = speed;
	setPosition(position);
}
Robot::Robot()
{

}

Robot::~Robot()
{
	for (int i = 0; i < NB_ANIM; i++)
	{
		delete[] movingAnimation;
	}
}
bool Robot::LoadTexture(const char texturePath[])
{
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}
	texture.setSmooth(true);
	
	return true;
}
void Robot::PrepareAnimation(const int nbAnimation, const int nbMovingFramePerDirection)
{
	setTexture(texture);
	NB_ANIM = nbAnimation;
	int nbCreatedRect = 0;
	int width = texture.getSize().x / nbAnimation;
	int height = texture.getSize().y / nbMovingFramePerDirection;

	movingAnimation = new sf::IntRect*[nbAnimation];
	for (int i = 0; i < nbAnimation; i++)
	{
		movingAnimation[i] = new sf::IntRect[nbMovingFramePerDirection];
		for (int j = 0; j < nbMovingFramePerDirection; j++)
		{
			movingAnimation[i][j].left = width * i;
			movingAnimation[i][j].top = height * j;
			movingAnimation[i][j].width = width;
			movingAnimation[i][j].height = height;
		}
	}

	setTextureRect(movingAnimation[dir][0]);
	setOrigin(movingAnimation[0][0].height / 2, movingAnimation[0][0].width / 2);
	MoveWarningBox();
		
}
void Robot::MoveWarningBox()
{
	warningBox.left = getPosition().x - WARNING_BOX_OVERLAP;
	warningBox.top = getPosition().y - WARNING_BOX_OVERLAP;
	warningBox.height = movingAnimation[0][0].height + WARNING_BOX_OVERLAP * 2;
	warningBox.width = movingAnimation[0][0].width + WARNING_BOX_OVERLAP * 2;
}
void Robot::ActualizeDeplacement(sf::Vector2f destination)
{
	movement = destination - getPosition();
	//Rendu à une certaine distance de la destination, on considère que l'on a atteint notre destination.
	if (abs(movement.x) > 1 || abs(movement.y) > 1)
	{


		float angle = atanf(abs(movement.y) / abs(movement.x));
		if (movement.x != 0)
		{
			//Le abs(movement.x) / movement.x retourne 1 ou -1 tout dépendant de la direction à prendre.
			movement.x = (abs(movement.x) / movement.x) * speed * cos(angle);
		}
		else
		{
			movement.x = speed * cos(angle);
		}
		if (movement.y != 0)
		{
			movement.y = (abs(movement.y) / movement.y) * speed * sin(angle);
		}
		else
		{
			movement.y = speed * cos(angle);
		}
		FindClosestDir();
	}
	else
	{
		movement.x = 0;
		movement.y = 0;
	}
}
void Robot::FindClosestDir()
{
	const float TOLERANCE = 0.2f;
	if (movement.y > TOLERANCE)
	{
		dir = DIRECTION::SOUTH;
		if (movement.x > TOLERANCE*2)
		{
			dir = DIRECTION::SOUTH_EAST;
		}
		else if (movement.x < -TOLERANCE * 2)
		{
			dir = DIRECTION::SOUTH_WEST;
		}
	}
	else if (movement.y < -TOLERANCE * 2)
	{
		dir = DIRECTION::NORTH;
		if (movement.x > TOLERANCE * 2)
		{
			dir = DIRECTION::NORTH_EAST;
		}
		else if (movement.x < -TOLERANCE * 2)
		{
			dir = DIRECTION::NORTH_WEST;
		}
	}
	else if (movement.x > TOLERANCE)
	{
		dir = DIRECTION::EAST;
	}
	else if (movement.x < -TOLERANCE)
	{
		dir = DIRECTION::WEST;
	}
	
}
void Robot::Deplacement()
{


	move(movement);
	MoveWarningBox();
	if (abs(movement.x) != 0 && abs(movement.y) != 0)
	{
		if (animator++ % ANIM_SPEED == 0)
		{
			setTextureRect(movingAnimation[dir][(animator / ANIM_SPEED) % 4]);
		}
	}

}