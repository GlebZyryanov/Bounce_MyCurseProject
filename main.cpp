#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include"Map.h"
#include"Menu.h"
#include"ENEMYHorizont.h"
#include"ENEMYVertical.h"
#include"Offset.h"
#include"PLAYER.h"
int main()
{
	
	/*Загрузка шрифта*/
	sf::Font font;
	font.loadFromFile("C:/My_files/CloneBounceCurse/CyrilicOld.ttf");
	sf::Text text("", font, 20);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::Font fontGameOver;
	fontGameOver.loadFromFile("C:/My_files/CloneBounceCurse/CyrilicOld.ttf");
	sf::Text textGameOver("", font, 100);
	textGameOver.setFillColor(sf::Color::White);
	textGameOver.setStyle(sf::Text::Bold);

	/*Создание окна игры*/
	sf::RenderWindow window(sf::VideoMode(950, 272), "Bounce!");
	/*Вызов меню*/
	menu(window);
	/*Загрузка текстур*/
	sf::Texture tileSet;
	tileSet.loadFromFile("C:/My_files/CloneBounceCurse/Mario_tileset.png");
	sf::Texture tileSet2;
	tileSet2.loadFromFile("C:/My_files/CloneBounceCurse/TileSet2.png");
	/*Создание персонажа, врагов*/
	PLAYER Bounce(tileSet);
	ENEMYHorizont  enemy1;
	ENEMYHorizont enemy2;
	ENEMYHorizont enemy3;
	ENEMYVertical venemy;
	venemy.set(tileSet, 450, 100);
	enemy3.set(tileSet, 1500, 95);
	enemy1.set(tileSet, 1700, 95);
	enemy2.set(tileSet, 700, 208);
	/*Создание спрайтов*/
	sf::Sprite tile(tileSet);
	sf::Sprite tile2(tileSet2);
	/*Музыка*/
	sf::SoundBuffer buffer;
	buffer.loadFromFile("C:/My_files/CloneBounceCurse/Jump.ogg");
	sf::Sound sound(buffer);
	sf::Music music;
	music.openFromFile("C:/My_files/CloneBounceCurse/Game-Mario.ogg");
	music.play();

	sf::Clock clock;
	/*Рабочее окно*/
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		/*Обнуление таймера*/
		clock.restart();
		/*Регулировка скорости игры*/
		time = time / 700;

		if (time > 20) {
			time = 20;
		}

		/*Выход из окна*/
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		/*если персонаж жив*/
		if (Bounce.life) {

			/*Обработка клавиатуры*/
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				Bounce.dx = -0.07;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				Bounce.dx = 0.07;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				menu(window);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (Bounce.onGround)
				{
					Bounce.dy = -0.27;
					Bounce.onGround = false;
					sound.play();
				}

			}
		}

		/*Обновить обьекты*/
		Bounce.update(time);
		enemy1.update(time);
		enemy2.update(time);
		enemy3.update(time);
		venemy.update(time);

		/*Пересечение персонажа и врагов*/
		if (Bounce.life)
		{
			if (Bounce.rect.intersects(enemy1.rect))
			{
				if (enemy1.life) {
					if (Bounce.dy > 0) {
						Bounce.Score++;
						enemy1.dx = 0;
						Bounce.dy = -0.3;
						enemy1.life = false;
						if (Bounce.health <= 3)
						{
							Bounce.health += 1;
						}
					}
					else {
						Bounce.Score--;
						Bounce.health -= 1;
						if (enemy1.dx > 0)
						{
							Bounce.rect.left -= 35;
						}
						else {
							Bounce.rect.left += 35;
						}
						Bounce.sprite.setColor(sf::Color::Red);

					}
				}
			}
			if (Bounce.rect.intersects(enemy2.rect))
			{
				if (enemy2.life) {
					Bounce.Score++;
					if (Bounce.dy > 0) {
						enemy2.dx = 0;
						Bounce.dy = -0.3;
						enemy2.life = false;
						if (Bounce.health <= 3)
						{
							Bounce.health += 1;
						}
					}
					else {
						Bounce.Score--;
						Bounce.health -= 1;
						if (enemy2.dx > 0)
						{
							Bounce.rect.left -= 35;
						}
						else {
							Bounce.rect.left += 35;
						}
						Bounce.sprite.setColor(sf::Color::Red);
					}
				}
			}
			if (Bounce.rect.intersects(venemy.rect))
			{
				if (venemy.life) {
					if (Bounce.dy > 0)
					{
						if (Bounce.health <= 3)
						{
							Bounce.health += 1;
						}
						Bounce.Score++;
						venemy.dy = 0;
						Bounce.dy = -0.3;
						venemy.life = false;
					}
					else
					{
						Bounce.Score--;
						Bounce.health -= 1;
						if (enemy3.dx > 0)
						{
							Bounce.rect.left -= 35;
						}
						else {
							Bounce.rect.left += 35;
						}
						Bounce.sprite.setColor(sf::Color::Red);
					}
				}
			}
			if (Bounce.rect.intersects(enemy3.rect))
			{
				if (enemy3.life) {
					if (Bounce.dy > 0)
					{
						if (Bounce.health <= 3)
						{
							Bounce.health += 1;
						}
						Bounce.Score++;
						enemy3.dx = 0;
						Bounce.dy = -0.3;
						enemy3.life = false;
					}
					else {
						Bounce.health -= 1;
						Bounce.Score--;
						if (enemy3.dx > 0)
						{
							Bounce.rect.left -= 35;
						}
						else {
							Bounce.rect.left += 35;
						}
						Bounce.sprite.setColor(sf::Color::Red);
					}
				}
			}
		}

		if (Bounce.rect.left > 200 && Bounce.rect.left < 1600) {
			offsetX = Bounce.rect.left - 200;
		}

		/*Отрисовка карты*/
		window.clear(sf::Color::Blue);
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'Z') {
					continue;
				}
				if (TileMap[i][j] == 'P') {
					continue;
				}

				if (TileMap[i][j] == 'k') {
					continue;
				}

				if (TileMap[i][j] == 'c') {
					continue;
				}

				if (TileMap[i][j] == 't') {
					continue;
				}

				if (TileMap[i][j] == 'g') {
					continue;
				}

				if (TileMap[i][j] == 'G') {
					continue;
				}

				if (TileMap[i][j] == 'd') {
					continue;
				}

				if (TileMap[i][j] == 'w') {
					continue;
				}

				if (TileMap[i][j] == 'r') {
					continue;
				}

				if ((TileMap[i][j] == ' '))
				{
					continue;
				}
				if ((TileMap[i][j] == '0')) {
					continue;
				}
				if (TileMap[i][j] == 'm') {
					tile2.setTextureRect(sf::IntRect(84, 76, 8, 8));

				}

				tile2.setPosition(j * 16 - offsetX, i * 16 - offsetY);
				window.draw(tile2);
			}

		}
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'm') {
					continue;

				}
				if (TileMap[i][j] == 'Z') {
					tile.setTextureRect(sf::IntRect(95, 8, 109, 107));
				}
				if (TileMap[i][j] == 'P') {
					tile.setTextureRect(sf::IntRect(95, 112, 16, 16));
				}

				if (TileMap[i][j] == 'k') {
					tile.setTextureRect(sf::IntRect(143, 112, 16, 16));
				}

				if (TileMap[i][j] == 'c') {
					tile.setTextureRect(sf::IntRect(127, 112, 16, 16));
				}

				if (TileMap[i][j] == 't') {
					tile.setTextureRect(sf::IntRect(0, 47, 32, 48));
				}

				if (TileMap[i][j] == 'g') {
					tile.setTextureRect(sf::IntRect(0, 139, 48, 37));
				}

				if (TileMap[i][j] == 'G') {
					tile.setTextureRect(sf::IntRect(145, 222, 77, 33));
				}

				if (TileMap[i][j] == 'd') {
					tile.setTextureRect(sf::IntRect(0, 106, 74, 21));
				}

				if (TileMap[i][j] == 'w') {
					tile.setTextureRect(sf::IntRect(99, 224, 41, 255 - 224));
				}

				if (TileMap[i][j] == 'r') {
					tile.setTextureRect(sf::IntRect(111, 112, 16, 16));
				}

				if ((TileMap[i][j] == ' '))
				{
					continue;
				}
				if ((TileMap[i][j] == '0')) {
					continue;
				}

				tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
				window.draw(tile);

			}

		}
		window.draw(Bounce.sprite);
		window.draw(enemy1.sprite);

		if (venemy.life) {
			window.draw(venemy.sprite);
		}
		window.draw(enemy2.sprite);
		if (enemy3.life) {
			window.draw(enemy3.sprite);
		}
		/*Вывод надписи о сборе очков*/
		std::ostringstream ScoreString;
		ScoreString << Bounce.Score;
		text.setString("Всего очков:" + ScoreString.str());
		text.setPosition(10, 10);
		window.draw(text);
		/*Вывод кол\ва жизней*/
		std::ostringstream StringHealth;
		StringHealth << Bounce.health;
		text.setString("Здоровье:" + StringHealth.str());
		text.setPosition(10, 35);
		window.draw(text);
		/*Если здоровье меньше 0*/
		if (!Bounce.life) {
			textGameOver.setString("Игра Окончена");
			textGameOver.setPosition(150, 50);
			window.draw(textGameOver);

		}

		window.display();
	}

	return 0;
}

