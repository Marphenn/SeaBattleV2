#include "Player.h"

//Vector2i Player::getClickedTile(Vector2i mousePosition)
//{
//    Vector2i tile;
//    tile.x = (mousePosition.x - X1_START) / CELL_PX;
//    tile.y = (mousePosition.y - Y_START) / CELL_PX;
//    return tile;
//}

//void Player::playerChoose()
//{
//    Vector2i tilePos;
//    if (field.area.contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left) && myTurn)
//    {
//        tilePos = getClickedTile(Mouse::getPosition(window));
//        field.showTile(tilePos);
//        if (field.array[tilePos.y][tilePos.x] != DAMAGED) myTurn = false;
//        cout << "\nPLAYER SHIP TILES LEFT:" << Player::field.totalShipTiles;
//    }
//   
//}

void Player::firstShot()
{
	srand(time(0));
	int randX, randY;
	do
	{
		randX = (rand() % 10) + 1;
		randY = (rand() % 10) + 1;
		//cout << "\n" << randX << "\t" << randY;
	} while (Player::field.showTile(Vector2i(randX, randY)) == CLEAR);
	//cout << "\n" << randX << "\t" << randY;
	if (Player::field.array[randY][randX] == DAMAGED)
	{
		//damagedTile.x = randX;
		//damagedTile.y = randY;
		//hit = 1;
		myTurn = false;
	}
	else myTurn = true;
	cout << "\nOPPONENTS TILES SHIPS LEFT:" << Player::field.totalShipTiles;
}
