#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Opponent.h"

class Judge : protected Player, protected Opponent
{
protected:
	int winner;

public:
	int checkWinner();
};