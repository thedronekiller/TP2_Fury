#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"

using namespace sf;


	class Character : public Sprite
	{
	private:
		const int SPEED_ANIMATION = 10;  //Vitesse d'animation: on change de frame aux 10 soixantièmes de seconde
		static Texture texture;

		RenderWindow* renderWindow;	//Pointeur sur la fenêtre.  pratique pour connaitre sa taille entre autre
		float speed;  //Vitesse de déplacement du personnage

		int animator;  //Horloge d'animation de base
		int cadran;   //Niveau d'animation suivant un cadrant 0 est la direction gauche et on tourne suivant les aiguilles d'une montre

		int steadyAnimator;  //Animateur du cadran
		int steadyDirection; //Direction de l'animation du cadran
		bool isMobile;  //Détermine si le personnage bouge où s'il est immobile


		IntRect** intRectsSteady; //Tableau dynamique à deux dimensions pour des rectangles de dépoupage, pour les animations de "idle"  
		IntRect** intRectsMobile; //Tableau dynamique à deux dimensions pour des rectangles de dépoupage, pour les animations de mouvement 
		//ce sera un tableaau de taille déterminée plus tard car on ne connait pas encore le nombre de frames dans l'animation

		//Pour le découpage de la spriteSheet
		const int NBR_LEVEL;  //Total de lignes dans la spiteSheet
		const int NBR_ANIMS_STEADY;  //Nombre de frame d'animation pour le idle dans la spriteSheet.
		const int NBR_ANIMS_MOBILE;  //Nombre de frame d'animation pour le mouvement dans la spriteSheet.
		const int NBR_ANIMS;  //Nombre de frame d'animation au total dans la spriteSheet.

		IntRect rectPlayer;



		//Méthode récupéré gratis de même dans le corrigé d'Asteroid.   Si ça marche, pourquoi le refaire?
		float OtherSide(float positionDansAxe, const int tailleEcran, const int demiTailleVaisseau);

		const bool CheckWallCollisions(Wall* limitWalls[], const int nbLimitPivots, Wall* centerWalls[], const int nbCenterPivots);

	public:
		//Constructeur avec tous les attributs plus haut.  Utiliser un tableau de char pour le path évite d'inclure string et un string a un constructeur avec un tableau de char
		Character(const float posX, const float posY, const float speed, const int cadran, const int nbrNiveaux, const int nbrAnimsIdle, const int nbrAnimsMovement, RenderWindow* const renderWindow);
		~Character();

		static bool ChargerTextures(const char texturePath[]);
		void AjustementsVisuels(); //Méthode de "finalisation du constructeur"

		void AjustementsDuCadrant(int cadrant); //On détermine quel cadrant on fait face.
		void Deplacement(float axeX, float axeY,Wall* limitWalls[], const int nbLimitPivots, Wall* centerWalls[], const int nbCenterPivots);
	};


