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
void Robot::MoveWarningBox()
{
	warningBox.left = getPosition().x - WARNING_BOX_OVERLAP;
	warningBox.top = getPosition().y - WARNING_BOX_OVERLAP;
	warningBox.height = movingAnimation[0][0].height + WARNING_BOX_OVERLAP * 2;
	warningBox.width = movingAnimation[0][0].width + WARNING_BOX_OVERLAP * 2;
}
void Robot::ActualizeDeplacement(sf::Vector2f destination)
{

}
void Robot::Deplacement()
{
	float angle = 0;
	switch (dir)
	{
	case SOUTH:
		angle = 0.5f * M_PI ;
		break;
	case SOUTH_WEST:
		angle = 0.75f * M_PI;
		break;
	case WEST:
		angle =  M_PI;
		break;
	case NORTH_WEST:
		angle = 1.25 * M_PI;
		break;
	case NORTH:
		angle = 1.5f * M_PI;
		break;
	case NORTH_EAST:
		angle = 1.75f * M_PI;
		break;
	case EAST:
		angle = 0;
		break;
	case SOUTH_EAST:
		angle = 0.25 * M_PI;
		break;
	default:
		angle = 0;
		break;
	}
	move(speed*cos(angle), speed * sin(angle));
	MoveWarningBox();
	if (animator++ % ANIM_SPEED == 0)
	{
		setTextureRect(movingAnimation[dir][(animator / ANIM_SPEED) % 4]);
	

	}
}