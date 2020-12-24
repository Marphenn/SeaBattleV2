#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Field.h"

bool Field:: load(const std::string& tileset, sf::Vector2u tileSize)
{
	// load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
    {
        cout << "COULDN'T LOAD TEXTURE. ERROR.";
        exit(-1);
        //return false;
    }
		

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(columns * rows * 4);

	//this->Update();


	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < rows; i++)
	{
        if (i == rows)
        {
            cout << "OUT OF THE ARRAY'S BOUNDRIES!";
            exit(-2);
        }
		for (unsigned int j = 0; j < columns; j++)
		{
			// get the current tile number
			int tileNumber = array[j][i];

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * columns) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(x_start + i * tileSize.x, Y_START + j * tileSize.y);
			quad[1].position = sf::Vector2f(x_start + (i + 1) * tileSize.x, Y_START + j * tileSize.y);
			quad[2].position = sf::Vector2f(x_start + (i + 1) * tileSize.x, Y_START + (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(x_start + i * tileSize.x, Y_START + (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
	return true;
}

Field* Field:: SetTile(int x, int y, int type)
{
	this->array[x - 1][y - 1] = type;
	return this;
};

void Field:: Update(/*float time, sf::Vector2u tileSize*/)
{
	sf::Vector2u tileSize(CELL_PX, CELL_PX);
	for (unsigned int i = 1; i < ROWS_N; ++i)
		for (unsigned int j = 1; j < COL_N; ++j)
		{
			// get the current tile number
			int tileNumber = array[j][i];
			if (tileNumber < 0) tileNumber = 0;

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * ROWS_N) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(x_start + i * tileSize.x, Y_START + j * tileSize.y);
			quad[1].position = sf::Vector2f(x_start + (i + 1) * tileSize.x, Y_START + j * tileSize.y);
			quad[2].position = sf::Vector2f(x_start + (i + 1) * tileSize.x, Y_START + (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(x_start + i * tileSize.x, Y_START + (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
}

void fillNearShip(int** array, int let_start, int let_end, int num_start, int num_end) // заполнение окрестности корабля
{
	if ((let_start - 1) > 0)
	{
		if ((num_start - 1) > 0) array[num_start - 1][let_start - 1] = NEAR;
		if ((num_end + 1) < ROWS_N) array[num_end + 1][let_start - 1] = NEAR;
		for (int i = num_start; i <= num_end; i++) array[i][let_start - 1] = NEAR;
	}
	if ((let_end + 1) < COL_N)
	{
		if ((num_start - 1) > 0) array[num_start - 1][let_end + 1] = NEAR;
		if ((num_end + 1) < ROWS_N) array[num_end + 1][let_end + 1] = NEAR;
		for (int i = num_start; i <= num_end; i++) array[i][let_end + 1] = NEAR;
	}
	if (num_start - 1 > 0)
		for (int i = let_start; i <= let_end; i++) array[num_start - 1][i] = NEAR;
	if (num_end + 1 < ROWS_N)
		for (int i = let_start; i <= let_end; i++) array[num_end + 1][i] = NEAR;
}

void Field::randomFieldGenerate()
{
    srand(time(0));
    totalShipTiles = 0;
    int randLet = 0, randNum = 0, numShips = 0;
    bool isHorisontal = true; // горизонтально/вертикально (по умолчанию - горизонтально)
    //bool isSet = false; // установлен ли корабль
    for (int type = 4; type > 0; type--) // 4 типа кораблей
    {
        switch (type)
        {
        case 4: numShips = 1; break;
        case 3: numShips = 2; break;
        case 2: numShips = 3; break;
        case 1: numShips = 4; break;
        }
        for (int j = 0; j < numShips; j++)
        {
            for (bool isSet = false; isSet == false; )
            {
                randLet = 1 + rand() % (COL_N - 1);
                randNum = 1 + rand() % (ROWS_N - 1);
                isHorisontal = rand() % 2;
                int k = 0;
                if (array[randNum][randLet] == CLEAR)
                {
                    while (isSet == false && k < 2)
                    {
                        if (isHorisontal && !isSet)
                        {
                            switch (type)
                            {
                            case 4:
                                if ((randLet + 2) < COL_N && (randLet - 1) > 0)
                                {
                                    if (array[randNum][randLet - 1] == CLEAR && array[randNum][randLet + 1] == CLEAR && array[randNum][randLet + 2] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum][randLet - 1] = SHIP; array[randNum][randLet + 1] = SHIP; array[randNum][randLet + 2] = SHIP; // заполнение клеток корабля
                                        isSet = true;
                                        fillNearShip(array, randLet - 1, randLet + 2, randNum, randNum);
                                        break;
                                    }
                                }
                                if ((randLet + 1) < COL_N && (randLet - 2) > 0)
                                {
                                    if (array[randNum][randLet + 1] == CLEAR && array[randNum][randLet - 1] == CLEAR && array[randNum][randLet - 2] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum][randLet + 1] = SHIP; array[randNum][randLet - 1] = SHIP; array[randNum][randLet - 2] = SHIP;
                                        isSet = true;
                                        fillNearShip(array, randLet - 2, randLet + 1, randNum, randNum);
                                        break;
                                    }
                                }
                                if ((randLet - 3) > 0)
                                {
                                    if (array[randNum][randLet - 1] == CLEAR && array[randNum][randLet - 2] == CLEAR && array[randNum][randLet - 3] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum][randLet - 1] = SHIP; array[randNum][randLet - 2] = SHIP; array[randNum][randLet - 3] = SHIP;
                                        isSet = true;
                                        fillNearShip(array, randLet - 3, randLet, randNum, randNum);
                                        break;
                                    }
                                }
                                if ((randLet + 3) < COL_N)
                                {
                                    if (array[randNum][randLet + 1] == CLEAR && array[randNum][randLet + 2] == CLEAR && array[randNum][randLet + 3] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum][randLet + 1] = SHIP; array[randNum][randLet + 2] = SHIP; array[randNum][randLet + 3] = SHIP;
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet + 3, randNum, randNum);
                                        break;
                                    }
                                }
                                else { break; }
                            case 3:
                                if ((randLet + 1) < COL_N && (randLet - 1) > 0)
                                {
                                    if (array[randNum][randLet + 1] == CLEAR && array[randNum][randLet - 1] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum][randLet + 1] = SHIP; array[randNum][randLet - 1] = SHIP;
                                        isSet = true;
                                        fillNearShip(array, randLet - 1, randLet + 1, randNum, randNum);
                                        break;
                                    }
                                }
                                if ((randLet - 2) > 0)
                                {
                                    if (array[randNum][randLet - 1] == CLEAR && array[randNum][randLet - 2] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum][randLet - 1] = SHIP; array[randNum][randLet - 2] = SHIP;
                                        isSet = true;
                                        fillNearShip(array, randLet - 2, randLet, randNum, randNum);
                                        break;
                                    }
                                }
                                if ((randLet + 2) < COL_N)
                                {
                                    if (array[randNum][randLet + 1] == CLEAR && array[randNum][randLet + 2] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum][randLet + 1] = SHIP; array[randNum][randLet + 2] = SHIP;
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet + 2, randNum, randNum);
                                        break;
                                    }
                                }
                                else { break; }
                            case 2:
                                if ((randLet + 1) < COL_N)
                                {
                                    if (array[randNum][randLet + 1] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum][randLet + 1] = SHIP;
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet + 1, randNum, randNum);
                                        break;
                                    }
                                }
                                if ((randLet - 1) > 0)
                                {
                                    if (array[randNum][randLet - 1] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum][randLet - 1] = SHIP;
                                        isSet = true;
                                        fillNearShip(array, randLet - 1, randLet, randNum, randNum);
                                        break;
                                    }
                                }
                                else { break; }
                            case 1: array[randNum][randLet] = SHIP;
                                isSet = true;
                                fillNearShip(array, randLet, randLet, randNum, randNum);
                                break;
                            }
                            k++;
                            if (!isSet) isHorisontal = false;
                        }
                        if (!isHorisontal && !isSet)
                        {
                            switch (type)
                            {
                            case 4:
                                if ((randNum - 1) > 0 && (randNum + 2) < ROWS_N)
                                {
                                    if (array[randNum - 1][randLet] == CLEAR && array[randNum + 1][randLet] == CLEAR && array[randNum + 2][randLet] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum - 1][randLet] = SHIP; array[randNum + 1][randLet] = SHIP; array[randNum + 2][randLet] = SHIP; // заполнение клеток корабля
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet, randNum - 1, randNum + 2);
                                        break;
                                    }
                                }
                                if ((randNum - 2) > 0 && (randNum + 1) < ROWS_N)
                                {
                                    if (array[randNum - 1][randLet] == CLEAR && array[randNum - 2][randLet] == CLEAR && array[randNum + 1][randLet] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum - 1][randLet] = SHIP; array[randNum - 2][randLet] = SHIP; array[randNum + 1][randLet] = SHIP; // заполнение клеток корабля
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet, randNum - 2, randNum + 1);
                                        break;
                                    }
                                }
                                if ((randNum + 3) < ROWS_N)
                                {
                                    if (array[randNum + 1][randLet] == CLEAR && array[randNum + 2][randLet] == CLEAR && array[randNum + 3][randLet] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum + 1][randLet] = SHIP; array[randNum + 2][randLet] = SHIP; array[randNum + 3][randLet] = SHIP; // заполнение клеток корабля
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet, randNum, randNum + 3);
                                        break;
                                    }
                                }
                                if ((randNum - 3) < ROWS_N)
                                {
                                    if (array[randNum - 1][randLet] == CLEAR && array[randNum - 2][randLet] == CLEAR && array[randNum - 3][randLet] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum - 1][randLet] = SHIP; array[randNum - 2][randLet] = SHIP; array[randNum - 3][randLet] = SHIP; // заполнение клеток корабля
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet, randNum - 3, randNum);
                                        break;
                                    }
                                }
                                else { break; }
                            case 3:
                                if ((randNum - 1) > 0 && (randNum + 1) < ROWS_N)
                                {
                                    if (array[randNum - 1][randLet] == CLEAR && array[randNum + 1][randLet] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum - 1][randLet] = SHIP; array[randNum + 1][randLet] = SHIP; // заполнение клеток корабля
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet, randNum - 1, randNum + 1);
                                        break;
                                    }
                                }
                                if ((randNum + 2) < ROWS_N)
                                {
                                    if (array[randNum + 1][randLet] == CLEAR && array[randNum + 2][randLet] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum + 1][randLet] = SHIP; array[randNum + 2][randLet] = SHIP; // заполнение клеток корабля
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet, randNum, randNum + 2);
                                        break;
                                    }
                                }
                                if ((randNum - 2) > 0)
                                {
                                    if (array[randNum - 1][randLet] == CLEAR && array[randNum - 2][randLet] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum - 1][randLet] = SHIP; array[randNum - 2][randLet] = SHIP; // заполнение клеток корабля
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet, randNum - 2, randNum);
                                        break;
                                    }
                                }
                                else { break; }
                            case 2:
                                if ((randNum + 1) < ROWS_N)
                                {
                                    if (array[randNum + 1][randLet] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum + 1][randLet] = SHIP; // заполнение клеток корабля
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet, randNum, randNum + 1);
                                        break;
                                    }
                                }
                                if ((randNum - 1) > 0)
                                {
                                    if (array[randNum - 1][randLet] == CLEAR)
                                    {
                                        array[randNum][randLet] = SHIP; array[randNum - 1][randLet] = SHIP;
                                        isSet = true;
                                        fillNearShip(array, randLet, randLet, randNum - 1, randNum);
                                        break;
                                    }
                                }
                                break;
                            case 1: array[randNum][randLet] = SHIP;
                                isSet = true;
                                fillNearShip(array, randLet, randLet, randNum, randNum);
                                break;
                            }
                            k++;
                            if (!isSet) isHorisontal = true;
                        }
                        //else j--;
                    }
                    //else j--;
                }
                if (isSet)
                {
                    //totalShipTiles += type;
                    cout << "size: " << type << "position: X " << randLet << " Y: " << randNum;
                    if (isHorisontal) cout << " HORISONTAL\n";
                    else cout << " VERTICAL\n";
                }
            }
            totalShipTiles += type;
        }
    }
    isClear = false;
    cout << "\TOTAL: " << totalShipTiles << "\n";
    this->Update();
}

void Field::clearField()
{
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
}

void Field::hideAll()
{
    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < columns; j++)
        {
            array[i][j] += HIDE;
        }
    }
    this->Update();
}

int Field::showTile(Vector2i tilePosition) // открыть клетку после нажатия
{
    if (array[tilePosition.y][tilePosition.x] < 0)
    {
        array[tilePosition.y][tilePosition.x] -= HIDE;
        if (array[tilePosition.y][tilePosition.x] == NEAR) array[tilePosition.y][tilePosition.x] = EMPTY;
        else if (array[tilePosition.y][tilePosition.x] == CLEAR) array[tilePosition.y][tilePosition.x] = EMPTY;
        else if (array[tilePosition.y][tilePosition.x] == SHIP)
        {
            array[tilePosition.y][tilePosition.x] = DAMAGED;
            totalShipTiles--;
        }
        this->Update();
        cout << "\n" << totalShipTiles;
        return array[tilePosition.y][tilePosition.x];
    }
    else return 0;
}