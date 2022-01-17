/*Враг, движется по вертикали*/
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Map.h"
#include"Offset.h"
class ENEMYVertical
{
public:
	float  dy;
	sf::FloatRect rect;
	sf::Sprite sprite;
	float currentFrame;
	bool life;
	void set(sf::Texture& image, unsigned long int x, unsigned long int y)
	{
		sprite.setTexture(image);
		rect = sf::FloatRect(x, y, 16, 16);

		dy = -0.1;
		currentFrame = 0;
		life = true;
	}
	void Collision()
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++) {
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++) {
				if ((TileMap[i][j] == '0'))
				{
					if (dy < 0)
					{

						rect.top = i * 16 + rect.height;
						dy *= -1;
					}

				}
				if ((TileMap[i][j] == 'P'))
				{
					if (dy > 0)
					{

						rect.top = i * 16 - rect.height;
						dy *= -1;
					}

				}
			}
		}
	}
	void update(float time)
	{
		rect.top += dy * time;
		Collision();

		currentFrame += time * 0.001;
		if (currentFrame > 2) {
			currentFrame -= 2;
		}
		sprite.setTextureRect(sf::IntRect(36 * int(currentFrame), 0, 16, 16));
		if (!life) {
			sprite.setTextureRect(sf::IntRect(58, 0, 16, 16));

		}
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}
};