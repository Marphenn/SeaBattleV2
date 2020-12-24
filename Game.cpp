#include "SFML/Graphics.hpp"
#include "Game.h"

using namespace sf;

void Game::menu()
{
	while (isMenu) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				exit(0);
			}
		}
		window.clear(Color::White);
		if (IntRect(440, 240, 300, 100).contains(Mouse::getPosition(window))) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				isMenu= false;
				//isGame = true;
				/*cout << state;*/
			}
		}
		if (IntRect(440, 440, 300, 100).contains(Mouse::getPosition(window))) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				window.draw(text_rules);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape)) {
					while (window.pollEvent(event)) {
						if (event.type == Event::Closed){
							window.close();
						}
					}
				}
				/*cout << state;*/
			}
		}
		window.draw(text_name);
		window.draw(play);
		window.draw(text_play);
		window.draw(howToPlay);
		window.draw(text_howToPlay);
		window.display();
	}
}

bool Game::getMenuStatus()
{
    return isMenu;
}
