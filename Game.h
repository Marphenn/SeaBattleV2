#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Game {
protected:
	RenderWindow window;
	RectangleShape play, howToPlay;
	Text text_play, text_howToPlay, text_rules, text_name, text_other, text_next, text_winner, text_yourTurn,
		text_yourField, text_opponentField, text_backToMenu;
	Font font;
	bool isMenu;
	//bool isGame;
	bool myTurn;
	bool isWinner;

public:
	Game()
	{
		window.create(VideoMode(1200, 800), L"Морской бой");
		window.setFramerateLimit(60);
		window.setVerticalSyncEnabled(true);

		play.setSize(Vector2f(300.f, 100.f));
		play.setOutlineThickness(10.f);
		play.setOutlineColor(Color::Blue);
		play.setFillColor(Color::Black);
		play.setPosition(Vector2f(450.f, 250.f));

		howToPlay.setSize(Vector2f(300.f, 100.f));
		howToPlay.setOutlineThickness(10.f);
		howToPlay.setOutlineColor(Color::Blue);
		howToPlay.setFillColor(Color::Green);
		howToPlay.setPosition(Vector2f(450.f, 450.f));
		font.loadFromFile("Fonts/arial.ttf");

		text_name.setFont(font);
		text_name.setCharacterSize(65);
		text_name.setLetterSpacing(3.0);
		text_name.setString(L"Морской бой");
		text_name.setFillColor(Color::Black);
		text_name.setPosition(Vector2f(335.f, 50.f));

		text_play.setFont(font);
		text_play.setCharacterSize(50);
		text_play.setLetterSpacing(1.0);
		text_play.setString(L"Новая игра");
		text_play.setFillColor(Color::White);
		text_play.setPosition(Vector2f(465.f, 270.f));

		text_howToPlay.setFont(font);
		text_howToPlay.setCharacterSize(50);
		text_howToPlay.setLetterSpacing(3.0);
		text_howToPlay.setString(L"Правила игры");
		text_howToPlay.setFillColor(Color::White);
		text_howToPlay.setPosition(Vector2f(470.f, 470.f));

		text_rules.setFont(font);
		text_rules.setCharacterSize(20);
		text_rules.setLetterSpacing(1.0);
		text_rules.setString(L"Ваша задача - уничтожить все корабли соперника.\nВыбрав клетку, в которую вы хотите выстрелить, нажмите левой кнопкой мыши.\nЧтобы выйти в главное меню нажмите клавишу Escape.");
		text_rules.setFillColor(Color::Black);
		text_rules.setPosition(Vector2f(100.f, 100.f));

		text_other.setFont(font);
		text_other.setCharacterSize(20);
		text_other.setLetterSpacing(1.0);
		text_other.setString(L"Чтобы выбрать другую расстановку, нажмите D:");
		text_other.setFillColor(Color::Black);
		text_other.setPosition(Vector2f(600.f, 300.f));

		text_next.setFont(font);
		text_next.setCharacterSize(20);
		text_next.setLetterSpacing(1.0);
		text_next.setString(L"Чтобы продолжить, нажмите Enter:");
		text_next.setFillColor(Color::Black);
		text_next.setPosition(Vector2f(600.f, 350.f));

		text_winner.setFont(font);
		text_winner.setCharacterSize(50);
		text_winner.setLetterSpacing(1.0);
		text_winner.setFillColor(Color::Black);
		text_winner.setPosition(Vector2f(200.f, 120.f));

		text_yourTurn.setFont(font);
		text_yourTurn.setCharacterSize(20);
		text_yourTurn.setLetterSpacing(1.0);
		text_yourTurn.setFillColor(Color::Black);
		text_yourTurn.setString(L"Ваш ход...");
		text_yourTurn.setPosition(Vector2f(690.f, 700.f));

		text_yourField.setFont(font);
		text_yourField.setCharacterSize(20);
		text_yourField.setLetterSpacing(1.0);
		text_yourField.setFillColor(Color::Black);
		text_yourField.setString(L"Ваше поле");
		text_yourField.setPosition(Vector2f(220.f, 150.f));

		text_opponentField.setFont(font);
		text_opponentField.setCharacterSize(20);
		text_opponentField.setLetterSpacing(1.0);
		text_opponentField.setFillColor(Color::Black);
		text_opponentField.setString(L"Поле соперника");
		text_opponentField.setPosition(Vector2f(840.f, 150.f));

		text_backToMenu.setFont(font);
		text_backToMenu.setCharacterSize(20);
		text_backToMenu.setLetterSpacing(1.0);
		text_backToMenu.setFillColor(Color::Black);
		text_backToMenu.setString(L"Чтобы вернуться в меню, нажмите пробел");
		text_backToMenu.setPosition(Vector2f(470.f, 710.f));

		isMenu= true;
		myTurn = true;
		isWinner = false;
	}
	void menu();
	bool getMenuStatus();
};