#pragma once
using System;
using System.Collections.Generic;
using System.Text;
using SFML.Graphics;
using SFML.Window;
using SFML.Audio;
namespace BounceCurseCSharp
{

    class Program
    {
        static void Main()
        {
			const int H = 17;
			const int W = 218;
			IntRect REC;
            /*Создание окна игры*/
            VideoMode mode = new VideoMode(950, 272);
            RenderWindow window = new RenderWindow(mode, "Bounce!");
            MENU m = new MENU();
            /*Вызов меню*/
            m.menu(ref window);
            /*Загрузка текстур*/
            Texture tileSet = new Texture("C:/My_files/CloneBounceCurse/Mario_tileset.png");

            Texture tileSet2 = new Texture("C:/My_files/CloneBounceCurse/TileSet2.png"); ;
            /*Создание персонажа, врагов*/
            PLAYER Bounce = new PLAYER(ref tileSet);
            ENEMYHorizont enemy1 = new ENEMYHorizont();
            ENEMYHorizont enemy2 = new ENEMYHorizont();
            ENEMYHorizont enemy3 = new ENEMYHorizont();
            ENEMYVertical venemy = new ENEMYVertical();
            venemy.set(ref tileSet, 2500, 100);
            enemy3.set(ref tileSet, 1500, 95);
            enemy1.set(ref tileSet, 1700, 95);
            enemy2.set(ref tileSet, 700, 208);
            /*Создание спрайтов*/
            Sprite tile = new Sprite(tileSet);
            Sprite tile2 = new Sprite(tileSet2);
            /*Музыка*/
            SoundBuffer buffer = new SoundBuffer("C:/My_files/CloneBounceCurse/Jump.ogg");
            Sound sound = new Sound(buffer);
            Music music = new Music("C:/My_files/CloneBounceCurse/Game-Mario.ogg");
            music.Play();
			Color mycolRED = new Color(255, 0, 0);
			Color mycolBlue = new Color(0, 181, 255);
			SFML.System.Clock clock = new SFML.System.Clock();
            /*Рабочее окно*/
            while (window.IsOpen)
            {
                float time = clock.ElapsedTime.AsMicroseconds();
                /*Обнуление таймера*/
                clock.Restart();
                /*Регулировка скорости игры*/
                time = time / 700;

                if (time > 20)
                {
                    time = 20;
                }
                if (Bounce.life)
                {
                    if (Keyboard.IsKeyPressed(Keyboard.Key.Left))
                    {
                        Bounce.dx = -0.07f;
                    }
                    if (Keyboard.IsKeyPressed(Keyboard.Key.Right))
                    {
                        Bounce.dx = 0.07f;
                    }
                    if (Keyboard.IsKeyPressed(Keyboard.Key.Tab))
                    {
                        m.menu(ref window);
                    }
                    if (Keyboard.IsKeyPressed(Keyboard.Key.Up))
                    {
                        if (Bounce.onGround)
                        {
                            Bounce.dy = -0.27F;
                            Bounce.onGround = false;
                            sound.Play();
                        }
                    }

                }
                /*Обновить обьекты*/
                Bounce.Update(time);
                enemy1.Update(time);
                enemy2.Update(time);
                enemy3.Update(time);
                venemy.Update(time);
				
				/*Пересечение персонажа и врагов*/
				if (Bounce.life)
					{
					if (Bounce.rect.Intersects(enemy1.rect))
					{
						if (enemy1.life)
						{
							if (Bounce.dy > 0)
							{
								Bounce.Score++;
								enemy1.dx = 0;
								Bounce.dy = -0.3F;
								enemy1.life = false;
								if (Bounce.health <= 3)
								{
									Bounce.health += 1;
								}
							}
							else
							{
								Bounce.Score--;
								Bounce.health -= 1;
								if (enemy1.dx > 0)
								{
									Bounce.rect.Left -= 35;
								}
								else
								{
									Bounce.rect.Left += 35;
								}
								Bounce.sprite.Color = mycolRED;

							}
						}
					}
					if (Bounce.rect.Intersects(enemy2.rect))
					{
						if (enemy2.life)
						{
							Bounce.Score++;
							if (Bounce.dy > 0)
							{
								enemy2.dx = 0;
								Bounce.dy = -0.3F;
								enemy2.life = false;
								if (Bounce.health <= 3)
								{
									Bounce.health += 1;
								}
							}
							else
							{
								Bounce.Score--;
								Bounce.health -= 1;
								if (enemy2.dx > 0)
								{
									Bounce.rect.Left -= 35;
								}
								else
								{
									Bounce.rect.Left += 35;
								}
								Bounce.sprite.Color = mycolRED;
							}
						}
					}
					if (Bounce.rect.Intersects(venemy.rect))
					{
						if (venemy.life)
						{
							if (Bounce.dy > 0)
							{
								if (Bounce.health <= 3)
								{
									Bounce.health += 1;
								}
								Bounce.Score++;
								venemy.dy = 0;
								Bounce.dy = -0.3F;
								venemy.life = false;
							}
							else
							{
								Bounce.Score--;
								Bounce.health -= 1;
								if (enemy3.dx > 0)
								{
									Bounce.rect.Left -= 35;
								}
								else
								{
									Bounce.rect.Left += 35;
								}
								Bounce.sprite.Color = mycolRED;
							}
						}
					}
					if (Bounce.rect.Intersects(enemy3.rect))
					{
						if (enemy3.life)
						{
							if (Bounce.dy > 0)
							{
								if (Bounce.health <= 3)
								{
									Bounce.health += 1;
								}
								Bounce.Score++;
								enemy3.dx = 0;
								Bounce.dy = -0.3F;
								enemy3.life = false;
							}
							else
							{
								Bounce.health -= 1;
								Bounce.Score--;
								if (enemy3.dx > 0)
								{
									Bounce.rect.Left -= 35;
								}
								else
								{
									Bounce.rect.Left += 35;
								}
								Bounce.sprite.Color = mycolRED;
							}
						}
					}
				}
				if (Bounce.rect.Left > 200 && Bounce.rect.Left < 2650)
				{
					Bounce.offsetX = Bounce.rect.Left - 200;
				}
				window.Clear(mycolBlue);

				for (int i = 0; i < H; i++)
				{
					for (int j = 0; j < W; j++)
					{
						if (Bounce.TileMap[i][j] == 'Z')
						{
							continue;
						}
						if (Bounce.TileMap[i][j] == 'P')
						{
							continue;
						}

						if (Bounce.TileMap[i][j] == 'k')
						{
							continue;
						}

						if (Bounce.TileMap[i][j] == 'c')
						{
							continue;
						}

						if (Bounce.TileMap[i][j] == 't')
						{
							continue;
						}

						if (Bounce.TileMap[i][j] == 'g')
						{
							continue;
						}

						if (Bounce.TileMap[i][j] == 'G')
						{
							continue;
						}

						if (Bounce.TileMap[i][j] == 'd')
						{
							continue;
						}

						if (Bounce.TileMap[i][j] == 'w')
						{
							continue;
						}

						if (Bounce.TileMap[i][j] == 'r')
						{
							continue;
						}

						if ((Bounce.TileMap[i][j] == ' '))
						{
							continue;
						}
						if ((Bounce.TileMap[i][j] == '0'))
						{
							continue;
						}
						if (Bounce.TileMap[i][j] == 'm')
						{
							REC = new IntRect(84, 76, 8, 8);
							tile2 = new Sprite(tileSet2, REC);
						}

						
						window.Draw(tile2);
					}

				}
				for (int i = 0; i < H; i++)
				{
					for (int j = 0; j < W; j++)
					{
						if (Bounce.TileMap[i][j] == 'm')
						{
							continue;

						}
						if (Bounce.TileMap[i][j] == 'Z')
						{
							REC = new IntRect(95, 8, 109, 107);
							tile = new Sprite(tileSet, REC);
							
						}
						if (Bounce.TileMap[i][j] == 'P')
						{
							REC = new IntRect(95, 112, 16, 16);
							tile = new Sprite(tileSet, REC);
							
						}

						if (Bounce.TileMap[i][j] == 'k')
						{
							REC = new IntRect(143, 112, 16, 16);
							tile = new Sprite(tileSet, REC);
							
						}

						if (Bounce.TileMap[i][j] == 'c')
						{
							REC = new IntRect(127, 112, 16, 16);
							tile = new Sprite(tileSet, REC);
							
						}

						if (Bounce.TileMap[i][j] == 't')
						{
							REC = new IntRect(0, 47, 32, 48);
							tile = new Sprite(tileSet, REC);
							
						}

						if (Bounce.TileMap[i][j] == 'g')
						{
							REC = new IntRect(0, 139, 48, 37);
							tile = new Sprite(tileSet, REC);
							
						}

						if (Bounce.TileMap[i][j] == 'G')
						{
							REC = new IntRect(145, 222, 77, 33);
							tile = new Sprite(tileSet, REC);
							
						}

						if (Bounce.TileMap[i][j] == 'd')
						{
							REC = new IntRect(0, 106, 74, 21);
							tile = new Sprite(tileSet, REC);
							
						}

						if (Bounce.TileMap[i][j] == 'w')
						{
							REC = new IntRect(99, 224, 41, 255 - 224);
							tile = new Sprite(tileSet, REC);
							
						}

						if (Bounce.TileMap[i][j] == 'r')
						{
							REC = new IntRect(111, 112, 16, 16);
							tile = new Sprite(tileSet, REC);
							
						}

						if ((Bounce.TileMap[i][j] == ' '))
						{
							continue;
						}
						if ((Bounce.TileMap[i][j] == '0'))
						{
							continue;
						}
						window.Draw(tile);
					}
					window.Draw(Bounce.sprite);
					window.Draw(enemy1.sprite);
					if (venemy.life)
					{
						window.Draw(venemy.sprite);
					}
					window.Draw(enemy2.sprite);
					if (enemy3.life)
					{
						window.Draw(enemy3.sprite);
					}
					

					window.Display();
				}
			}
        }
    }
}

 
    
