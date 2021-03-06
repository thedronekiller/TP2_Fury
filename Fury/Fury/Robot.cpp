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
bool Robot::CheckWallCollisionWithWarning(Wall& wall)
{
	bool isColliding = false;
	//int a = wall.GetAttachedWall().getPosition().x;
	//int b = wall.GetAttachedWall().getPosition().y;
	//sf::IntRect wallRect(wall.getPosition().x, wall.getPosition().y,wall.getSize().x, wall.getSize().y);
	sf::IntRect rect(wall.GetRectWall());
	if (wall.GetRectWall().intersects(warningBox))
	{
		isColliding = true;
	}

	return isColliding;
}
bool Robot::CheckRobotCollision(const Robot& otherRobot)
{
	bool isColliding = false;
	if (warningBox.intersects(otherRobot.warningBox))
	{
	

		isColliding = true;
	}
	return isColliding;
}
void Robot::MoveWarningBox()
{
	warningBox.left = getPosition().x;
	warningBox.top = getPosition().y;
	warningBox.height = movingAnimation[0][0].height;
	warningBox.width = movingAnimation[0][0].width;
}
void Robot::ActualizeDeplacement(sf::Vector2f destination, Wall* walls)
{
	movement = destination - getPosition();
	//Rendu � une certaine distance de la destination, on consid�re que l'on a atteint notre destination.
	if (abs(movement.x) > 1 && abs(movement.y) > 1)
	{
		float angle = atanf(movement.y / movement.x);
		
		//Le abs(movement.x) / movement.x retourne 1 ou -1 tout d�pendant de la direction � prendre.
		movement.x = (abs(movement.x) / movement.x) * speed * cos(angle);
		movement.y = (abs(movement.x) / movement.x) * speed * sin(angle);
		FindClosestDir();
		for (int i = 0; i < NB_PIVOTS_CENTRE; i++)
		{
			CheckWallCollisionWithWarning(walls[i]);
		}
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
