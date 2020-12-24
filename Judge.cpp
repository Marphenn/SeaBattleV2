#include <iostream>
#include "Judge.h"

using namespace std;

int Judge::checkWinner()
{
	if (Opponent::field.totalShipTiles == 0)
	{
		Game::isWinner = true;
		return 1;
	}
	if (Player::field.totalShipTiles == 0)
	{
		Game::isWinner = true;
		return -1;
	}
	return 0;
}
