#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include"HandleEvents.h"

using namespace std;

void HandleEvents::events()
{
restart:
    bool isGame = false;
    bool isSet = false;
    float time;
    int winner = 0;

	Clock clock;
   
	clock.getElapsedTime().asSeconds();
	
    Opponent::field.randomFieldGenerate();

    bool isRestart = false;

    float freezeTime = 0;

	while (window.isOpen())
	{
        if (isMenu) menu();
        float time = clock.getElapsedTime().asMicroseconds(); // возвращает прошедшее время в микросекундах 
        clock.restart(); // перезагружает время(постоянно)
        time = time / 800; // скорость игры
        //cout << time << "\n";

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed /*|| !isGame*/) window.close();
            if (!isGame)
            {
                if (Keyboard::isKeyPressed(Keyboard::D))
                {
                    isSet = true;
                    Player::field.clearField();
                    Player::field.randomFieldGenerate();
                }
                if (Keyboard::isKeyPressed(Keyboard::Enter) && isSet)
                {
                    isGame = true;
                    Player::field.hideAll();
                    Opponent::field.hideAll();
                    //show(map_player.array);
                }
            }
            if (isGame && !isWinner)
            {
                if (Game::myTurn) playerChoose();
                else
                {
                    freezeTime += time;
                    if (freezeTime > 700)
                    {
                        firstShot();
                       /* if (hit==0) firstShot();
                        else if (hit == 1) nextShot();*/
                        freezeTime = 0;
                    }
                    
                }
                winner = checkWinner();
            }
            if (isWinner && Keyboard::isKeyPressed(Keyboard::Space))
            {
                isRestart = true;
                break;
            }
        }
        window.clear(Color::White);

        if (isRestart) break;

        window.draw(Player::field);

        if (!isGame)
        {
            window.draw(Game::text_other);
            if (isSet) window.draw(Game:: text_next);
        }
        else
        {
            if (Game::myTurn) Game::text_yourTurn.setString(L"Ваш ход...");
            else  Game::text_yourTurn.setString(L"Ход противника...");
            window.clear(Color::White);
            window.draw(Player::field);
            window.draw(Opponent::field);
            window.draw(Game::text_yourField);
            window.draw(Game::text_opponentField);
            window.draw(Game::text_yourTurn);
            if (isWinner)
            {
                window.clear(Color::White);
                window.draw(Player::field);
                window.draw(Opponent::field);
                //window.draw(Game::text_backToMenu);
                switch (winner)
                {
                case 1: Game::text_winner.setString(L"Вы победили!"); break;
                case -1: Game::text_winner.setString(L"Победил оппонент, не расстраивайтесь!"); break;
                default:Game::text_winner.setString(L"Что-то пошло не по плану"); break;
                }
                window.draw(Game::text_winner);
            }
        }

        window.display();
	}
    if (isRestart) goto restart;
}
