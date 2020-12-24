#include <iostream>
#include <ctime>
#include "Opponent.h"

using namespace std;

//void Opponent::firstShot()
//{
//	srand(time(0));
//	int randX, randY;
//	do
//	{
//		randX = (rand() % 10) + 1;
//		randY = (rand() % 10) + 1;
//		//cout << "\n" << randX << "\t" << randY;
//	} while (Opponent::field.showTile(Vector2i(randX, randY)) == CLEAR);
//	//cout << "\n" << randX << "\t" << randY;
//	if (Opponent::field.array[randY][randX] == DAMAGED)
//	{
//		damagedTile.x = randX;
//		damagedTile.y = randY;
//		hit = 1;
//		myTurn = false;
//	}
//	else myTurn = true;
//	cout << "\nOPPONENTS TILES SHIPS LEFT:" << Opponent::field.totalShipTiles;
//}

//void Opponent::nextShot()
//{
//	srand(time(0));
//
//	if (horisontal==-1)
//	{
//		k_misses = 0;
//		k_hits = 0;
//		horisontal = rand() % 2;
//		left_or_up = rand() % 2;
//	}
//	int check = k_misses;
//
//		if (horisontal)
//		{
//			if (left_or_up==1)
//			{
//				if (damagedTile.x - 1 > 0)
//				{
//					if (field.showTile(Vector2i(damagedTile.y, damagedTile.x - 1)) == DAMAGED)
//					{
//						damagedTile.x = damagedTile.x - 1;
//						hit = true;
//						//k++;
//					}
//					else if (field.showTile(Vector2i(damagedTile.y, damagedTile.x - 1)) == EMPTY)
//					{
//						myTurn = true;
//						left_or_up = 0;
//						damagedTile.x = damagedTile.x - k_hits;
//						k_misses++;
//						//k++;
//					}
//				}
//				else left_or_up = 0;
//			}
//			else if(left_or_up==0)
//			{
//				if (damagedTile.x + 1 < COL_N)
//				{
//					if (field.showTile(Vector2i(damagedTile.y, damagedTile.x + 1)) == DAMAGED)
//					{
//						damagedTile.x = damagedTile.x + 1;
//						hit = true;
//						//k++;
//					}
//					else if (field.showTile(Vector2i(damagedTile.y, damagedTile.x + 1)) == EMPTY)
//					{
//						myTurn = true;
//						left_or_up = 1;
//						damagedTile.x = damagedTile.x - k_hits;
//						k_misses++;
//						//k++;
//					}
//				}
//				else left_or_up = 1;
//			}
//		}
//		else
//		{
//			if (left_or_up==1)
//			{
//				if (damagedTile.y - 1 > 0)
//				{
//					if (field.showTile(Vector2i(damagedTile.y - 1, damagedTile.x)) == DAMAGED)
//					{
//						damagedTile.y--;
//						hit = true;
//						//k++;
//					}
//					else if (field.showTile(Vector2i(damagedTile.y - 1, damagedTile.x)) == EMPTY)
//					{
//						myTurn = true;
//						left_or_up = 0;
//						damagedTile.y-=k_hits;
//						k_misses++;
//						//k++;
//					}
//				}
//				else left_or_up = 0;
//			}
//			else if(left_or_up==0)
//			{
//				if (damagedTile.y + 1 < ROWS_N)
//				{
//					if (field.showTile(Vector2i(damagedTile.y + 1, damagedTile.x)) == DAMAGED)
//					{
//						damagedTile.y++;
//						hit = true;
//						//k++;
//					}
//					else if (field.showTile(Vector2i(damagedTile.y + 1, damagedTile.x)) == EMPTY)
//					{
//						myTurn = true;
//						left_or_up = 1;
//						damagedTile.y -= k_hits;
//						k_misses++;
//						//k++;
//					}
//				}
//				else left_or_up = 1;
//			}
//		}
//		if (!hit)
//		{
//			if(check!=k_misses) myTurn = true;
//		}
//		else k_hits++;
//
//		if (k_misses == 4 || (k_misses == 2 && horisontal >= 0))
//		{
//			hit = 0;
//			horisontal = -1;
//			damagedTile.x = -1;
//			damagedTile.y = -1;
//			myTurn = true;
//		}
//}

Vector2i Opponent::getClickedTile(Vector2i mousePosition)
{
	Vector2i tile;
	tile.x = (mousePosition.x - X2_START) / CELL_PX;
	tile.y = (mousePosition.y - Y_START) / CELL_PX;
	return tile;
}

void Opponent::playerChoose()
{
	Vector2i tilePos;
	if (field.area.contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left) && myTurn)
	{
		tilePos = getClickedTile(Mouse::getPosition(window));
		field.showTile(tilePos);
		if (field.array[tilePos.y][tilePos.x] != DAMAGED) myTurn = false;
		cout << "\nPLAYER SHIP TILES LEFT:" << Opponent::field.totalShipTiles;
	}

}