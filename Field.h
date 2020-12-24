#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Game.h"

using namespace std;
using namespace sf;

#define CELL_PX 41
#define WIDTH_PX 410
#define HEIGHT_PX 410
#define ROWS_N 11
#define COL_N 11

#define X1_START 70
#define X2_START 680
#define Y_START 200

enum SHIPS
{
	CLEAR,
	EMPTY,// мимо или же окрестность корабля
	//NEAR=EMPTY,
	DAMAGED,
	SHIP,
	NEAR = -EMPTY,
	HIDE = -5
};

class Field : public sf::Drawable, public sf::Transformable // МОЖНО СДЕЛАТЬ ЭТОТ КЛАСС ОСНОВНЫМ КЛАССОМ ПОЛЯ (ПЕРЕИМЕНОВАТЬ В FIELD И ДОБАВИТЬ ОСТАЛЬНЫЕ ПЕРЕМЕННЫЕ: X,Y,...)
{
public:
	int** array;
	int totalShipTiles;
	const int x_start, rows{ 11 }, columns{ 11 }, y_start{ Y_START };
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	bool isClear;
	IntRect area;

public:
	Field(int X_start)
		: x_start(X_start), totalShipTiles(0), isClear(true), area(X_start + CELL_PX, Y_START + CELL_PX, WIDTH_PX, HEIGHT_PX)
	{
		srand(time(0));
		// Создаем массив для хранения строк
		// установка пустого поля
		array = new int* [rows];
		int numbers = 4, letters = 14; // 4-13 шкала цифр, 14-23 шкала букв
		for (int i = 0; i < rows; i++)
		{
			array[i] = new int[columns];
			for (int j = 0; j < columns; j++)
			{
				if (i == 0 && j > 0)
				{
					array[i][j] = letters++;
				}
				else if (j == 0 && i > 0)
				{
					array[i][j] = numbers++;
				}
				else array[i][j] = CLEAR;
			}
		}

	};

	bool load(const std::string& tileset, sf::Vector2u tileSize);
	Field* SetTile(int x, int y, int type);
	void Update();
	void randomFieldGenerate();
	void clearField();
	void hideAll();
	int showTile(Vector2i tilePosition);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}
};
