#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

float offsetX = 0;
float offsetY = 0;


const int H = 17;
const int W = 151;

sf::String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                w                                                               w                        Z                          0",
"0                                                                               w                                                                    0",
"0                    w                          w                                                                                                    0",
"0                                                                                                    t0                                              0",
"0                                                                                   t0               00                          t0          G       0",
"0                                                                                   00               00    m m m m m m m         00     m m m        0",
"0                         m                                             rPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0                                                             m        rrPPPPPPPPccccccPcccccPcPPPcPccPPPPcPcccccPcccccPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0                    m m                                              rrrPPPPPPPPccPPPcPcPPPcPcPPPcPcPcPPPcPcPPPPPcPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0                   kckck                                 m  m       rrrrPPPPPPPPccccccPcPPPcPcPPPcPcPPcPPcPcPPPPPcccccPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0                                      t0                           rrrrrPPPPPPPPccPPPcPcPPPcPcPPPcPcPPPcPcPcPPPPPcPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0G                                     00              t0          rrrrrrPPPPPPPPccccccPcccccPcccccPcPPPPccPcccccPcccccPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0           d    g  mmm     d          00      m  m    00         rrrrrrrPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
};



class PLAYER {

public:

	float dx;
	float dy;
	sf::FloatRect rect;
	bool onGround;
	sf::Sprite sprite;
	float currentFrame;
	int Score;
	PLAYER(sf::Texture& image)
	{
		sprite.setTexture(image);
		rect = sf::FloatRect(100, 180, 16, 16);

		dx = dy = 0.1;
		currentFrame = 0;
		Score = 0;
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

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;
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
						
						rect.top = i*16+rect.height;
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
				if ( (TileMap[i][j] == '0'))
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



int main()
{
	/*Загрузка шрифта*/
	sf::Font font;
	font.loadFromFile("CyrilicOld.ttf");
	sf::Text text("", font, 20);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	/*Создание окна игры*/
	sf::RenderWindow window(sf::VideoMode(950, 272), "Bounce!");


	sf::Texture tileSet;
	tileSet.loadFromFile("Mario_tileset.png");
	sf::Texture tileSet2;
	tileSet2.loadFromFile("TileSet2.png");
	PLAYER Bounce(tileSet);
	ENEMYHorizont  enemy1;
	ENEMYHorizont enemy2;
	ENEMYHorizont enemy3;
	ENEMYVertical venemy;
	venemy.set(tileSet, 450, 100);
	enemy3.set(tileSet, 1500, 95);
	enemy1.set(tileSet, 1700, 95);
	enemy2.set(tileSet, 700, 208);

	sf::Sprite tile(tileSet);
	sf::Sprite tile2(tileSet2);
	sf::SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	sf::Sound sound(buffer);

	sf::Music music;
	music.openFromFile("Game-Mario.ogg");
	music.play();
	

	sf::Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 700;  

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
			Bounce.dx = -0.08;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Bounce.dx = 0.08;
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


		Bounce.update(time);
		enemy1.update(time);
		enemy2.update(time);
		enemy3.update(time);
		venemy.update(time);

		if (Bounce.rect.intersects(enemy1.rect))
		{
			if (enemy1.life) {
				if (Bounce.dy > 0) {
					enemy1.dx = 0;
					Bounce.dy = -0.3; 
					enemy1.life = false;
					
				}
				else {
					Bounce.sprite.setColor(sf::Color::Red);

				}
			}
		}
		if (Bounce.rect.intersects(enemy2.rect))
		{
			if (enemy2.life) {
				if (Bounce.dy > 0) {
					enemy2.dx = 0;
					Bounce.dy = -0.3; 
					enemy2.life = false;
				}
				else {
					Bounce.sprite.setColor(sf::Color::Red);
				}
			}
		}
		if (Bounce.rect.intersects(venemy.rect))
		{
			if (venemy.life) {
				if (Bounce.dy > 0)
				{
					venemy.dy = 0;
					Bounce.dy = -0.3;
					venemy.life = false;
				}
				else
				{
					Bounce.sprite.setColor(sf::Color::Red);
				}
			}
		}
		if (Bounce.rect.intersects(enemy3.rect))
		{
			if (enemy3.life) {
				if (Bounce.dy > 0) {
					enemy3.dx = 0; 
					Bounce.dy = -0.3;
					enemy3.life = false;
				}
				else {
					Bounce.sprite.setColor(sf::Color::Red);
				}
			}
		}

		if (Bounce.rect.left > 200 && Bounce.rect.left<1600) {
			offsetX = Bounce.rect.left - 200;
		}

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
					tile2.setTextureRect(sf::IntRect(84,76,8,8));

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
		std::ostringstream ScoreString;
		ScoreString << Bounce.Score;
		text.setString("Всего очков:" + ScoreString.str());
		text.setPosition(10, 10);
		window.draw(text);
		
		window.display();
	}

	return 0;
}




