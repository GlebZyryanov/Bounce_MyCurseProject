#pragma once
using System;
using System.Collections.Generic;
using System.Text;
using SFML.Graphics;
using SFML.Window;
using SFML.Audio;

namespace BounceCurseCSharp
{
	class MENU
	{
		public void menu(ref RenderWindow window)
		{
			Texture menuNewGame;
			Texture menuAboutProgram;
			Texture menuExit;
			Texture aboutWindowAboutProgram;
			menuNewGame = new Texture("C:/My_files/CloneBounceCurse/NewGame.png");
			menuAboutProgram = new Texture("C:/My_files/CloneBounceCurse/AboutProgram.png");
			menuExit = new Texture("C:/My_files/CloneBounceCurse/Exit.png");
			aboutWindowAboutProgram = new Texture("C:/My_files/CloneBounceCurse/WindowAboutProgram.png");

			Sprite menu1 = new Sprite(menuNewGame);
			Sprite menu2 = new Sprite(menuAboutProgram);
			Sprite menu3 = new Sprite(menuExit);
			Sprite about = new Sprite(aboutWindowAboutProgram);
			bool isMenu = true;
			int menuNum = 0;
			SFML.System.Vector2f vect2f = new SFML.System.Vector2f(50,30);
			menu1.Position = vect2f;
			vect2f = new SFML.System.Vector2f(50, 90);
			menu2.Position = vect2f;
			vect2f = new SFML.System.Vector2f(50, 150);
			menu3.Position = vect2f;

			while (isMenu)
			{
				Color mycol = new Color(255, 255, 255);
				menu1.Color = mycol;
				menu2.Color = mycol;
				menu3.Color = mycol;
				menuNum = 0;
				Color mycol2 = new Color(0, 181, 255);
				window.Clear(mycol2);
				IntRect intrect = new IntRect(100, 30, 300, 50);
				IntRect intrect2 = new IntRect(100, 90, 300, 50);
				IntRect intrect3 = new IntRect(100, 150, 300, 50);


				if (intrect.Contains(Mouse.GetPosition(window).X, Mouse.GetPosition(window).Y))
				{
					menu1.Color = mycol2;
					menuNum = 1;
				}
				if (intrect2.Contains(Mouse.GetPosition(window).X, Mouse.GetPosition(window).Y))
				{
					menu2.Color = mycol2;
					menuNum = 2;
				}
				if (intrect3.Contains(Mouse.GetPosition(window).X, Mouse.GetPosition(window).Y))
				{
					menu3.Color = mycol2;
					menuNum = 3;
				}

				if (Mouse.IsButtonPressed(Mouse.Button.Left))
				{
					if (menuNum == 1)
					{
						isMenu = false;


					}
					if (menuNum == 2)
					{
						window.Draw(about);
						window.Display();
						while (!Keyboard.IsKeyPressed(Keyboard.Key.Escape)) ;
					}
					if (menuNum == 3)
					{
						window.Close();
						isMenu = false;
					}

				}

				window.Draw(menu1);
				window.Draw(menu2);
				window.Draw(menu3);
				window.Display();
			}

		}
	};
}