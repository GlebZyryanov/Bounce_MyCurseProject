#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>




float offsetX = 0, offsetY = 0;


const int H = 17;
const int W = 150;

sf::String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0",
"0                                                                                    w                                                               0",
"0                   w                                  w                   w                                                                         0",
"0                                      w                                       kk                                                                    0",
"0                                                                             k  k    k    k                                                         0",
"0                      c                                                      k      kkk  kkk  w                                                     0",
"0                                                                       r     k       k    k                                                         0",
"0                                                                      rr     k  k                                                                   0",
"0                                                                     rrr      kk                                                                    0",
"0               c    kckck                                           rrrr                                                                            0",
"0                                      t0                           rrrrr                                                                            0",
"0G                                     00              t0          rrrrrr            G                                                               0",
"0           d    g       d             00              00         rrrrrrr                                                                            0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};




class PLAYER {

public:

	float dx, dy;
	sf::FloatRect rect;
	bool onGround;
	sf::Sprite sprite;
	float currentFrame;
	

	PLAYER(sf::Texture& image)
	{
		sprite.setTexture(image);
		rect = sf::FloatRect(100, 180, 16, 16);
		
		dx=dy = 0.1;
		currentFrame = 0;
	}


	void update(float time)
	{

		rect.left += dx * time;
		Collision(0);


		if (!onGround) {
			dy = dy + 0.0005 * time;
		}
		rect.top += dy * time;
		onGround = false;
	  Collision(1);


		currentFrame += time * 0.005;
		if (currentFrame > 3) {
			currentFrame -= 3;
		}


		if (dx > 0) {
			sprite.setTextureRect(sf::IntRect(112 + 31 * int(currentFrame), 144, 16, 16));
		}
		if (dx < 0) {
			sprite.setTextureRect(sf::IntRect(112 + 31 * int(currentFrame) + 16, 144, -16, 16));
		}

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;
	}


	void Collision(int num)
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
				{
					if (dy > 0 && num == 1)
					{
						rect.top = i * 16 - rect.height;  dy = 0;   onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;   dy = 0;
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
					// TileMap[i][j]=' '; 
				}
			}
		

	}

};



class ENEMY
{

public:
	float dx, dy;
	sf::FloatRect rect;
	sf::Sprite sprite;
	float currentFrame;
	bool life;


	void set(sf::Texture& image, int x, int y)
	{
		sprite.setTexture(image);
		rect = sf::FloatRect(x, y, 16, 16);

		dx = 0.05;
		currentFrame = 0;
		life = true;
	}

	void update(float time)
	{
		rect.left += dx * time;

		Collision();


		currentFrame += time * 0.005;
		if (currentFrame > 2) currentFrame -= 2;

		sprite.setTextureRect(sf::IntRect(18 * int(currentFrame), 0, 16, 16));
		if (!life) sprite.setTextureRect(sf::IntRect(58, 0, 16, 16));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}


	void Collision()
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0'))
				{
					if (dx > 0)
					{
						rect.left = j * 16 - rect.width; dx *= -1;
					}
					else if (dx < 0)
					{
						rect.left = j * 16 + 16;  dx *= -1;
					}

				}
	}

};



int main()
{

	sf::RenderWindow window(sf::VideoMode(950, 450), "SFML works!");

	sf::Texture tileSet;
	tileSet.loadFromFile("Mario_Tileset.png");


	PLAYER Mario(tileSet);
	ENEMY  enemy;
	
	enemy.set(tileSet, 48 * 16, 13 * 16);
	ENEMY En;
	En.set(tileSet ,19 * 16, 13 * 16);


	sf::Sprite tile(tileSet);

	sf::SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	sf::Sound sound(buffer);

	sf::Music music;
	music.openFromFile("Horror-Music-Orchestra-Dark-Ambient-_www.hotplayer.ru_.ogg");
	music.play();

	sf::Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500;  // здесь регулируем скорость игры

		if (time > 20) {
			time = 20;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Mario.dx = -0.1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Mario.dx = 0.1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (Mario.onGround)
			{
				Mario.dy = -0.27;
				Mario.onGround = false;
				sound.play();
			}

		}


		Mario.update(time);
		enemy.update(time);
		En.update(time);


		if (Mario.rect.intersects(enemy.rect))
		{
			if (enemy.life) {
				if (Mario.dy > 0) {
					enemy.dx = 0; Mario.dy = -0.2; enemy.life = false;
				}
				else {
					Mario.sprite.setColor(sf::Color::Red);//добавить функцию гемовер?

				}
			}
		}
		if (Mario.rect.intersects(En.rect))
		{
			if (En.life) {
				if (Mario.dy > 0) {
					En.dx = 0; Mario.dy = -0.2; En.life = false;
				}
				else {
					Mario.sprite.setColor(sf::Color::Red);
				}
			}
		}


		if (Mario.rect.left > 200) {
			offsetX = Mario.rect.left - 200;
		}//смещение




		window.clear(sf::Color::Blue);

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'P') {
					tile.setTextureRect(sf::IntRect(143 - 16 * 3, 112, 16, 16));
				}

				if (TileMap[i][j] == 'k') {
					tile.setTextureRect(sf::IntRect(143, 112, 16, 16));
				}

				if (TileMap[i][j] == 'c') {
					tile.setTextureRect(sf::IntRect(143 - 16, 112, 16, 16));
				}

				if (TileMap[i][j] == 't') {
					tile.setTextureRect(sf::IntRect(0, 47, 32, 95 - 47));
				}

				if (TileMap[i][j] == 'g') {
					tile.setTextureRect(sf::IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));
				}

				if (TileMap[i][j] == 'G') {
					tile.setTextureRect(sf::IntRect(145, 222, 222 - 145, 255 - 222));
				}

				if (TileMap[i][j] == 'd') {
					tile.setTextureRect(sf::IntRect(0, 106, 74, 127 - 106));
				}

				if (TileMap[i][j] == 'w') {
					tile.setTextureRect(sf::IntRect(99, 224, 140 - 99, 255 - 224));
				}

				if (TileMap[i][j] == 'r') {
					tile.setTextureRect(sf::IntRect(143 - 32, 112, 16, 16));
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



		window.draw(Mario.sprite);
		window.draw(enemy.sprite);
		window.draw(En.sprite);

		window.display();
	}

	return 0;
}



