#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Room.h"
#include "Projectile.h"

using namespace sf;


	class Character : public Sprite
	{
	private:
		const int SPEED_ANIMATION = 10;  //Vitesse d'animation: on change de frame aux 10 soixanti�mes de seconde
		static Texture texture;

		RenderWindow* renderWindow;	//Pointeur sur la fen�tre.  pratique pour connaitre sa taille entre autre
		float speed;  //Vitesse de d�placement du personnage

		int animator;  //Horloge d'animation de base
		int cadran;   //Niveau d'animation suivant un cadrant 0 est la direction gauche et on tourne suivant les aiguilles d'une montre

		int steadyAnimator;  //Animateur du cadran
		int steadyDirection; //Direction de l'animation du cadran
		bool isMobile;  //D�termine si le personnage bouge o� s'il est immobile


		IntRect** intRectsSteady; //Tableau dynamique � deux dimensions pour des rectangles de d�poupage, pour les animations de "idle"  
		IntRect** intRectsMobile; //Tableau dynamique � deux dimensions pour des rectangles de d�poupage, pour les animations de mouvement 
		//ce sera un tableaau de taille d�termin�e plus tard car on ne connait pas encore le nombre de frames dans l'animation

		//Pour le d�coupage de la spriteSheet
		const int NBR_LEVEL;  //Total de lignes dans la spiteSheet
		const int NBR_ANIMS_STEADY;  //Nombre de frame d'animation pour le idle dans la spriteSheet.
		const int NBR_ANIMS_MOBILE;  //Nombre de frame d'animation pour le mouvement dans la spriteSheet.
		const int NBR_ANIMS;  //Nombre de frame d'animation au total dans la spriteSheet.

		IntRect rectPlayer;
		CHAR_DIRECTION direction;
		Projectile projectiles[2];

		//M�thode r�cup�r� gratis de m�me dans le corrig� d'Asteroid.   Si �a marche, pourquoi le refaire?
		void OtherSide(const int screenWidth, const int screenHeight, const int demiTailleVaisseau);
		const bool CheckWallCollisions(Room* room);
		bool changeRoom;

	public:
		//Constructeur avec tous les attributs plus haut.  Utiliser un tableau de char pour le path �vite d'inclure string et un string a un constructeur avec un tableau de char
		Character(const float posX, const float posY, const float speed, const int cadran, const int nbrNiveaux, const int nbrAnimsIdle, const int nbrAnimsMovement, RenderWindow* const renderWindow);
		~Character();
		static bool ChargerTextures(const char texturePath[]);
		void AjustementsVisuels(); //M�thode de "finalisation du constructeur"

		void AjustementsDuCadrant(int cadrant); //On d�termine quel cadrant on fait face.
		void Deplacement(float axeX, float axeY, Room* room);
		void SetDirection(const CHAR_DIRECTION direction);
		const bool ChangedRoom();
		void SetChangedRoom(const bool changed);
		void Fire();
	};


