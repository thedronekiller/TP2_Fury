#pragma once
#include <SFML/Graphics.hpp>
class Projectile
{
private:
	sf::Vector2f position;
	int direction;
public:
	Projectile(sf::Vector2f position, int direction);
	~Projectile();
};
