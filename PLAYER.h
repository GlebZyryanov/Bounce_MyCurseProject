/*Класс Игрока*/
#include<SFML/Graphics.hpp>
#include"Offset.h"
#include"Map.h"
class PLAYER {

public:
	/*Изменение скорости по x,y*/
	float dx;
	float dy;
	/*класс sf::FloatRect*/
	/*позволяет работать с объектами как с прямоугольниками*/
	sf::FloatRect rect;
	/*Переменная-флаг,персонаж на земле или нет*/
	bool onGround;
	/*sf::Sprite-это класс для рисования, который позволяет легко отображать текстуру на объекте рендеринга.*/
	sf::Sprite sprite;
	/*Текущий кадр*/
	float currentFrame;
	/*Опыт, жизнь, здоровье*/
	int Score;
	bool life;
	int health;
	/*Конструктор - инициализация переменных*/
	PLAYER(sf::Texture& image)
	{
		sprite.setTexture(image);
		rect = sf::FloatRect(80, 145, 16, 16);

		dx = dy = 0.1;
		currentFrame = 0;
		Score = 0;
		life = true;
		health = 3;
	}

	/*Обновление характеристик*/
	void update(float time)
	{
		/*смещение по x*/
		rect.left += dx * time;

		Collision(0);

		if (!onGround) {
			dy = dy + 0.0005 * time;
		}
		/*смещение по y*/
		rect.top += dy * time;
		onGround = false;
		Collision(1);

		/*Смена текущего кадра анимации*/
		currentFrame += time * 0.005;
		if (currentFrame > 3) {
			currentFrame -= 3;
		}

		//проигрывание анимаций
		if (dx == 0) {
			sprite.setTextureRect(sf::IntRect(112, 144, 16, 16));
		}
		if (dx > 0) {
			sprite.setTextureRect(sf::IntRect(112 + 31 * int(currentFrame), 144, 16, 16));
		}
		if (dx < 0) {
			sprite.setTextureRect(sf::IntRect(112 + 31 * int(currentFrame) + 16, 144, -16, 16));
		}
		if (dy > 0) {
			sprite.setTextureRect(sf::IntRect(230, 144, 16, 16));
		}
		if (dy > 0 && dx > 0) {
			sprite.setTextureRect(sf::IntRect(170 + 31 * int(currentFrame), 144, 16, 16));
		}
		if (dy > 0 && dx < 0) {
			sprite.setTextureRect(sf::IntRect(170 + 31 * int(currentFrame) + 16, 144, -16, 16));
		}
		/*Установка позиции персонажа*/
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		/*Занулить скорость по x*/
		dx = 0;
		/*Смерть персонажа*/
		if (health < 0) {
			life = false;
			dx = 0;
			dy = 0;
		}
	}

	/*Обработка столкновений*/
	void Collision(int num)
	{


		/*проход по карте*/
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++) {
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				/*Если персонаж столкнулся, с препятствием*/
				if ((TileMap[i][j] == 'P'))
				{
					/*проверяем в какую сторону двигался*/
					if (dy > 0 && num == 1)
					{
						/*Изменяем скорость и др.*/
						rect.top = i * 16 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;
						dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 16 + 16;
					}
				}
		
				if (TileMap[i][j] == 'm') {
					TileMap[i][j] = ' ';
					Score++;
				}
				if ((TileMap[i][j] == 'k')) {
					if (dy > 0 && num == 1)
					{
						rect.top = i * 16 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;
						dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 16 + 16;
					}
				}
				if ((TileMap[i][j] == '0')) {
					if (dy > 0 && num == 1)
					{
						rect.top = i * 16 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;
						dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 16 + 16;
					}
				}
				if ((TileMap[i][j] == 'r')) {
					if (dy > 0 && num == 1)
					{
						rect.top = i * 16 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;
						dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 16 + 16;
					}
				}
				if ((TileMap[i][j] == 't')) {
					if (dy > 0 && num == 1)
					{
						rect.top = i * 16 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;
						dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 16 + 16;
					}
				}
				if (TileMap[i][j] == 'c') {
					if (dy > 0 && num == 1)
					{

						rect.top = i * 16 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;
						dy = 0;
					}
					if (dx > 0 && num == 0)
					{

						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{

						rect.left = j * 16 + 16;
					}
				}
			}
		}
	}
};

