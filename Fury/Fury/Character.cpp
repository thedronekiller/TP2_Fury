#include "Character.h"
#include <iostream>


Texture	Character::texture; //Initialisation de notre texture (appel du constructeur par dfaut)

Character::Character(const float posX, const float posY, const float vitesse, const int cadran, const int nbrNiveaux, const int nbrAnimsImmobile, const int nbrAnimsMovement, RenderWindow  * const renderWindow)
	: speed(vitesse), cadran(cadran), NBR_LEVEL(nbrNiveaux), NBR_ANIMS_STEADY(nbrAnimsImmobile), NBR_ANIMS_MOBILE(nbrAnimsMovement), NBR_ANIMS(nbrAnimsImmobile + nbrAnimsMovement), renderWindow(renderWindow), animator(0), steadyAnimator(0), steadyDirection(1), isMobile(false)
{
	setPosition(posX, posY);
	direction = NONE;
}

Character::~Character()
{
	//On commence par effacer chaque de tableau dans les tableau
	for (int i = 0; i < NBR_LEVEL; i++)
	{
		delete[] intRectsSteady[i];
		delete[] intRectsMobile[i];
	}

	//Puis on efface les tableaux extérieurs
	delete[] intRectsSteady;
	delete[] intRectsMobile;
}

bool Character::ChargerTextures(const char texturePath[])
{
	//Chargement du fichier de texture
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}
	texture.setSmooth(true);
	return true;
}

void Character::AjustementsVisuels()
{
	setTexture(texture);   //Placement de la texture dans le sprite

	intRectsSteady = new IntRect*[NBR_LEVEL];  //Tableaux de frames à deux dimensions dépendant du nombre d'animations
	intRectsMobile = new IntRect*[NBR_LEVEL];  //On a une série d'animation pour chaque direction


	//Pour chaque direction donc...
	for (int i = 0; i < NBR_LEVEL; i++)
	{
		intRectsSteady[i] = new IntRect[NBR_ANIMS_STEADY]; //On se fait des tableaux pour les niveaux individuelles
		intRectsMobile[i] = new IntRect[NBR_ANIMS_MOBILE];

		int largeur = texture.getSize().x / NBR_ANIMS; //On calcule la largeur et la hauteur à partir de la taille de la texture
		int hauteur = texture.getSize().y / NBR_LEVEL; //et des nombres d'animations

		//Taille et poistion de chacun des rectangles
		for (int j = 0; j < NBR_ANIMS_STEADY; j++)
		{
			intRectsSteady[i][j].left = largeur * j;
			intRectsSteady[i][j].top = hauteur * i;
			intRectsSteady[i][j].width = largeur;
			intRectsSteady[i][j].height = hauteur;
		}

		//Taille et poistion de chacun des rectangles
		for (int j = 0; j < NBR_ANIMS_MOBILE; j++)
		{
			intRectsMobile[i][j].left = largeur * (j + NBR_ANIMS_STEADY);
			intRectsMobile[i][j].top = hauteur * i;
			intRectsMobile[i][j].width = largeur;
			intRectsMobile[i][j].height = hauteur;
		}
	}

	//Le rectangle d'animation initial de notre texture est celui du personnage qui regarde vers le bas
	setTextureRect(intRectsSteady[cadran][0]);

	//L'origine est toujours le milieu de notre rectangle de texture.
	//Comme vu ci-haut, c'est la moitié du rectangle d'animation, pas de la texture entière
	//La première ligne de code peut faire, mais la seconde est mieux.
	//setOrigin((texture.getSize().x / NBR_ANIMS) / 2, (texture.getSize().y / NBR_MIVEAUX) / 2);

	//Comme tous les rectangles on la même taille, on prend le premier
	setOrigin(intRectsSteady[0][0].height / 2, intRectsSteady[0][0].width / 2);
	rectPlayer = IntRect(getPosition().x-20, getPosition().y-25, intRectsSteady[0][0].width/3.5, intRectsSteady[0][0].height/1.6);
}

void Character::AjustementsDuCadrant(int cadran)
{
	//Le cas -1 est si on arrête de bouger
	if (cadran == 8)
	{
		isMobile = false;
		animator = 0; //Pour à la fois changer et repartir l'animation (voir plus bas)
	}
	else if (cadran > -1)  //Pour toutes les autres directions
	{					   //Si c'est autre que -1, alors forcément on bouge.
		if (!isMobile)
		{
			isMobile = true;
			animator = 0;
		}

		this->cadran = cadran;
	}
}

void Character::Deplacement(float axeX, float axeY, Room* room)
{
	//Déplacement du personnage
	move(axeX * speed, axeY * speed);
	rectPlayer.left = getPosition().x - 20;
	rectPlayer.top = getPosition().y - 25;
	if (!CheckWallCollisions(room))
	{
		//Test pour la traverse des autres côtés de l'écran
		setPosition(OtherSide(getPosition().x, renderWindow->getSize().x, (texture.getSize().x / NBR_ANIMS) / 2), 
			OtherSide(getPosition().y, renderWindow->getSize().y, (texture.getSize().y / NBR_LEVEL) / 2));
		//Si on est mobile on joue les animations de course
		if (isMobile)
		{
			//On change de frame à chaque "temps d'animation"
			if (animator++ % SPEED_ANIMATION == 0)
			{
				//La division fait en sorte que la gauche du modulo est +1 de la fois précédente
				//Modulo le nombre d'animations de mouvement
				setTextureRect(intRectsMobile[cadran][(animator / SPEED_ANIMATION) % NBR_ANIMS_MOBILE]);
			}
		}
		else //Si on est immobile
		{
			//Idle(direction);
			//On change de frame à chaque "temps d'animation"
			if (animator++ % SPEED_ANIMATION == 0)
			{
				//Ici le principe est que l'animation fonctionne par frame 0-1-2-3-2-1-0-1......
				setTextureRect(intRectsSteady[cadran][steadyAnimator]);
				steadyAnimator += steadyDirection;

				if (steadyAnimator == 0 || steadyAnimator == (NBR_ANIMS_STEADY - 1))
				{
					steadyDirection *= -1;
				}
			}
		}
	}
	else
	{
		move(axeX * -speed, axeY * -speed);
		rectPlayer.left = getPosition().x - 20;
		rectPlayer.top = getPosition().y - 25;
	}

}

/// <summary>
/// Modifie un des axe du vaisseau s'il dépasse la limite de l'écran de plus
/// de la moitié de sa taille (donc au moment où il disparait de l'écran.
/// </summary>
/// <param name="position">La position de l'axe.</param>
/// <param name="tailleEcran">La taille de l'écran pour cet axe.</param>
/// <param name="demiTailleVaisseau">La taille de la moitié du vaisseau, du centre à son extrémité.</param>
/// <returns></returns>
float Character::OtherSide(float positionDansAxe, const int tailleEcran, const int demiTaillePersonnage)
{
	if (positionDansAxe > tailleEcran + demiTaillePersonnage)
	{
		positionDansAxe -= tailleEcran + demiTaillePersonnage * 2;
	}
	else if (positionDansAxe < -demiTaillePersonnage)
	{
		positionDansAxe += tailleEcran + demiTaillePersonnage * 2;
	}
	return positionDansAxe;
}

const bool Character::CheckWallCollisions(Room* room)
{
	for (int i = 0; i < 16; i++)
	{
		if (room->GetLimitPivots(i).intersects(rectPlayer) || room->GetLimitWalls(i).intersects(rectPlayer))
		{
			isMobile = false;
			cadran = 0;
			return true;
		}
	}
	if (isMobile)
	{
		for (int j = 0; j < 8; j++)
		{
			if (room->GetCenterPivots(j).intersects(rectPlayer) || room->GetCenterWalls(j).intersects(rectPlayer))
			{
				isMobile = false;
				cadran = 0;
				return true;
			}
		}
	}
	return false;
}

void Character::SetDirection(const DIRECTION direction) 
{
	this->direction = direction;
	if (direction == NONE)
		isMobile = false;
}
