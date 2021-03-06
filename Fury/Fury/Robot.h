#pragma once
#include <SFML/Graphics.hpp>
#include "Constante.h"
#include "Wall.h"
class Robot: public sf::Sprite
{
private:
	DIRECTION dir;
	float speed;
	static sf::Texture texture;
	sf::IntRect warningBox;
	sf::IntRect** movingAnimation;
	int NB_ANIM = 0;
	int animator = 0;
	const int WARNING_BOX_OVERLAP = 5;
	const int ANIM_SPEED = 10;
	void MoveWarningBox();
	sf::Vector2f movement;
	void FindClosestDir();
	bool CheckWallCollisionWithWarning(Wall& wall);

public:
	Robot(sf::Vector2f position,const DIRECTION direction, const float speed);
	~Robot();
	static bool LoadTexture(const char texturePath[]);
	void PrepareAnimation(const int nbAnimation, const int nbMovingFramePerDirection);
	bool CheckRobotCollision(const Robot& otherRobot);
	void Deplacement();
	void ActualizeDeplacement(sf::Vector2f dest, Wall* walls);

};

