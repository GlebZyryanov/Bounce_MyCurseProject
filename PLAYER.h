/*����� ������*/
#include<SFML/Graphics.hpp>
#include"Offset.h"
#include"Map.h"
class PLAYER {

public:
	/*��������� �������� �� x,y*/
	float dx;
	float dy;
	/*����� sf::FloatRect*/
	/*��������� �������� � ��������� ��� � ����������������*/
	sf::FloatRect rect;
	/*����������-����,�������� �� ����� ��� ���*/
	bool onGround;
	/*sf::Sprite-��� ����� ��� ���������, ������� ��������� ����� ���������� �������� �� ������� ����������.*/
	sf::Sprite sprite;
	/*������� ����*/
	float currentFrame;
	/*����, �����, ��������*/
	int Score;
	bool life;
	int health;
	/*����������� - ������������� ����������*/
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

	/*���������� �������������*/
	void update(float time)
	{
		/*�������� �� x*/
		rect.left += dx * time;

		Collision(0);

		if (!onGround) {
			dy = dy + 0.0005 * time;
		}
		/*�������� �� y*/
		rect.top += dy * time;
		onGround = false;
		Collision(1);

		/*����� �������� ����� ��������*/
		currentFrame += time * 0.005;
		if (currentFrame > 3) {
			currentFrame -= 3;
		}

		//������������ ��������
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
		/*��������� ������� ���������*/
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		/*�������� �������� �� x*/
		dx = 0;
		/*������ ���������*/
		if (health < 0) {
			life = false;
			dx = 0;
			dy = 0;
		}
	}

	/*��������� ������������*/
	void Collision(int num)
	{


		/*������ �� �����*/
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++) {
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				/*���� �������� ����������, � ������������*/
				if ((TileMap[i][j] == 'P'))
				{
					/*��������� � ����� ������� ��������*/
					if (dy > 0 && num == 1)
					{
						/*�������� �������� � ��.*/
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

