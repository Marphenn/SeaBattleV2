#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Field.h"
#include "Player.h"

class Opponent : virtual protected Game
{
protected:
	Field field;
	Vector2i damagedTile;
	int horisontal;
	int left_or_up;
	int k_hits;
	int k_misses;
	int opponentShipTiles;
	int hit;

public:
	Opponent()
		: field(X2_START), horisontal(-1), opponentShipTiles(20), k_hits(0), k_misses(0), left_or_up(-1), hit(0)
	{
		field.load("Images/tiles1.jpg", sf::Vector2u(CELL_PX, CELL_PX));
		damagedTile.x = -1;
		damagedTile.y = -1;
	};

	//void firstShot();
	//void nextShot();

	Vector2i getClickedTile(Vector2i mousePosition);
	void playerChoose();

	friend class Player;
};
