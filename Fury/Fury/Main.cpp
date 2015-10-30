#define _USE_MATH_DEFINES
#include <vld.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Room.h"
#include "Character.h"

using namespace sf;
RenderWindow mainWin(VideoMode(LARGEUR, HAUTEUR, 32), "Fury");
View view(mainWin.getDefaultView());
Event event;
Room room;
Character* player;
Vector2f interfaceDeplacement; //Vecteur de déplacement du personnage
const float DIAGONALE = cos(M_PI_4);  //diagonale qui détermine une pure diagonale de pente 1

bool Init();
void GetInputs();
void Update();
void Draw();

void KeyboardMovement();

int main()
{
	if (!Init())
	{
		return EXIT_FAILURE;
	}

	while (mainWin.isOpen())
	{
		GetInputs();
		Update();
		Draw();
	}
	delete player;
	return EXIT_SUCCESS;
}
bool Init()
{
	if (!Character::ChargerTextures("Sprites\\perso.png"))
	{
		return false;
	}
	player = new Character(LARGEUR / 2, 100.0f, PLAYER_SPEED, 6, NOMBRE_ANIMATIONS, NOMBRE_FRAMES_IMMOBILE, NOMBRE_FRAMES_MOUVEMENT, &mainWin);
	player->AjustementsVisuels();

	//interface de déplacement à 0/0
	interfaceDeplacement.x = 0;
	interfaceDeplacement.y = 0;
	return true;
}

void GetInputs()
{
	while (mainWin.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			mainWin.close();
		}
	}
	KeyboardMovement();
}

void Update()
{
	//player->Deplacement(interfaceDeplacement.x, interfaceDeplacement.y, room.GetLimitWalls(),16, room.GetCenterWalls(), 8);
}

void Draw()
{
	mainWin.clear();
	room.Draw(&mainWin);
	mainWin.draw(*player);
	
	mainWin.display();
}

void KeyboardMovement()
{
	//Avec le clavier les directions sont franches
	//On teste les directions gauche / droite / neutre
	//Et pour chacune au dessus les direction haut / bas / neutre
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			interfaceDeplacement.x = -DIAGONALE;
			interfaceDeplacement.y = -DIAGONALE;
			player->AjustementsDuCadrant(NORTH_WEST);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			interfaceDeplacement.x = -DIAGONALE;
			interfaceDeplacement.y = DIAGONALE;
			player->AjustementsDuCadrant(SOUTH_WEST);
		}
		else
		{
			interfaceDeplacement.x = -1;
			interfaceDeplacement.y = 0;
			player->AjustementsDuCadrant(WEST);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			interfaceDeplacement.x = DIAGONALE;
			interfaceDeplacement.y = -DIAGONALE;
			player->AjustementsDuCadrant(NORTH_EAST);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			interfaceDeplacement.x = DIAGONALE;
			interfaceDeplacement.y = DIAGONALE;
			player->AjustementsDuCadrant(SOUTH_EAST);
		}
		else
		{
			interfaceDeplacement.x = 1;
			interfaceDeplacement.y = 0;
			player->AjustementsDuCadrant(EAST);
		}
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			interfaceDeplacement.x = 0;
			interfaceDeplacement.y = -1;
			player->AjustementsDuCadrant(NORTH);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			interfaceDeplacement.x = 0;
			interfaceDeplacement.y = 1;
			player->AjustementsDuCadrant(SOUTH);
		}
		else
		{
			interfaceDeplacement.x = 0;
			interfaceDeplacement.y = 0;
			player->AjustementsDuCadrant(NONE);
		}
	}
}