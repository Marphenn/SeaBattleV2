#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Field.h"
#include "Opponent.h"

class Player : virtual protected Game
{
protected:
	int playerShipTiles; 
	Field field;

public:
	Player()
		: field(X1_START), playerShipTiles(20)
	{
		field.load("Images/tiles1.jpg", sf::Vector2u(CELL_PX, CELL_PX));
	};

	//Vector2i getClickedTile(Vector2i mousePosition);

	void firstShot();
	void nextShot();

	//void playerChoose();
	
	friend class Opponent;
};