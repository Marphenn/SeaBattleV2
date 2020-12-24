#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Game.h"
#include "HandleEvents.h"

using namespace std;

int main()
{
	HandleEvents game;
	game.events();

	cout << "\nFinished correctly";
	return 0;
}