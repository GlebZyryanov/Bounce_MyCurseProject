/*Враг по горизонтали*/
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Map.h"
#include"Offset.h"
class ENEMYHorizont
{

public:
	float dx;
	sf::FloatRect rect;
	sf::Sprite sprite;
	float currentFrame;
	bool life;

	void set(sf::Texture& image, unsigned long int x, unsigned long int y)
	{
		sprite.setTexture(image);
		rect = sf::FloatRect(x, y, 16, 16);

		dx = 0.1;
		currentFrame = 0;
		life = true;
	}

	void update(float time)
	{
		rect.left += dx * time;

		Collision();

		currentFrame += time * 0.005;
		if (currentFrame > 2) {
			currentFrame -= 2;
		}
		sprite.setTextureRect(sf::IntRect(18 * int(currentFrame), 0, 16, 16));
		if (!life) {
			sprite.setTextureRect(sf::IntRect(58, 0, 16, 16));

		}
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	void Collision()
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++) {
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
				if ((TileMap[i][j] == '0'))
				{
					if (dx > 0)
					{
						rect.left = j * 16 - rect.width;
						dx *= -1;
					}
					else if (dx < 0)
					{
						rect.left = j * 16 + 16;
						dx *= -1;
					}

				}
		}
	}

};