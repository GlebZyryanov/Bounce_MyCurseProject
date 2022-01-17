#pragma once
#include"SFML/Graphics.hpp"
using namespace sf;
void menu(RenderWindow& window) {
	Texture menuNewGame;
	Texture menuAboutProgram;
	Texture menuExit;
	Texture aboutWindowAboutProgram;
	menuNewGame.loadFromFile("C:/My_files/CloneBounceCurse/NewGame.png");
	menuAboutProgram.loadFromFile("C:/My_files/CloneBounceCurse/AboutProgram.png");
	menuExit.loadFromFile("C:/My_files/CloneBounceCurse/Exit.png");
	aboutWindowAboutProgram.loadFromFile("C:/My_files/CloneBounceCurse/WindowAboutProgram.png");

	Sprite menu1(menuNewGame);
	Sprite menu2(menuAboutProgram);
	Sprite menu3(menuExit);
	Sprite about(aboutWindowAboutProgram);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(50, 30);
	menu2.setPosition(50, 90);
	menu3.setPosition(50, 150);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu1.setColor(Color::Blue);
			menuNum = 1;
		}
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu2.setColor(Color::Blue);
			menuNum = 2;
		}
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu3.setColor(Color::Blue);
			menuNum = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				isMenu = false;
			}//åñëè íàæàëè ïåðâóþ êíîïêó, òî âûõîäèì èç ìåíþ 
			if (menuNum == 2) {
				window.draw(about);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}
			if (menuNum == 3) {
				window.close();
				isMenu = false;
			}

		}

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}

}