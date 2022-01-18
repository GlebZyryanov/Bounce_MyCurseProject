using System;
using System.Collections.Generic;
using System.Text;
using SFML.Graphics;
using SFML.Window;
using SFML.Audio;


namespace BounceCurseCSharp
{
   
    class PLAYER
    {
        /*Переменные смещения экрана*/
        public  float offsetX = 0;
        public  float offsetY = 0;
		const int H = 17;
		const int W = 218;
		public String[] TileMap = {
	"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
	"0                                w                                                       m       w                        Z                                     w                 w      w                              0",
	"0                                                                               w     m m   m                                                   m     m                                                                 0",
	"0                    w                          w                                          mm                                                  kkk k  kkk       m        m  k        m     m         m                  0",
	"0                                                                                        mm          t0                                                       kkkk       kk   m     kkk    k       kkkk                 0",
	"0                                                                                    t0               00                          t0          G                      k        m                                         0",
	"0                                      m                 m  m    m                   00               00    m m m m m m m         00     m m m                                m                                         0",
	"0                         m             m   m                           rPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP  m mmmm                 m                                         0",
	"0      m                                 m                     m       rrPPPPPPPPccccccPcccccPcPPPcPccPPPPcPcccccPcccccPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP                        m                                         0",
	"0      m              m m                m m m                        rrrPPPPPPPPccPPPcPcPPPcPcPPPcPcPcPPPcPcPPPPPcPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP              m        m   m            m                        0",
	"0      m             kckck                                m  m       rrrrPPPPPPPPccccccPcPPPcPcPPPcPcPPcPPcPcPPPPPcccccPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP                                                                0",
	"0      m                                t0                          rrrrrPPPPPPPPccPPPcPcPPPcPcPPPcPcPPPcPcPcPPPPPcPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP            m                  m                  m            0",
	"0G                                     00              t0          rrrrrrPPPPPPPPccccccPcccccPcccccPcPPPPccPcccccPcccccPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP                mmmmmm mmmmmmmm mmmmmmmmm                     0",
	"0           d    g  mmm     d          00      m  m    00         rrrrrrrPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP          mmmmmmmmmmmmmmmmmmmmmm                             0",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
};
        public float dx;
        public float dy;
        public FloatRect rect;
        public bool onGround;
        public Sprite sprite;
        public float currentFrame;
        public bool life;
        public int Score;
        public int health;
        public static Texture tileSet = new Texture("C:/Users/zyrya/source/repos/BounceCurseCSharp/Mario_tileset.png");
        Sprite tile = new Sprite(tileSet);
        public 
        PLAYER(ref Texture  image)
        {
            sprite = new Sprite(image);
            rect = new FloatRect(80, 145, 16, 16);
            dy = dx = 0.1f;
            currentFrame = 0;
            Score = 0;
            life = false;
            health = 3;

        }
      


        public void Update(float time)
        {
            rect.Left += dx * time;
            Collision(0);
            if (!onGround)
            {
                dy = dy + 0.0005f * time;
            }
            rect.Top += dy * time;
            onGround = false;
            Collision(1);
            currentFrame += time * 0.005f;
            if (currentFrame > 3)
            {
                currentFrame -= 3;
            }

            if (dx == 0)
            {
                IntRect REC = new IntRect(112, 144, 16, 16);
                sprite = new Sprite(tileSet, REC);
            }
            if (dx > 0)
            {
                IntRect REC = new IntRect(112 + 31 *(int)(currentFrame), 144, 16, 16);
                sprite = new Sprite(tileSet, REC);
            }
            if (dx < 0)
            {
                IntRect REC = new IntRect(112 + 31 * (int)(currentFrame) + 16, 144, -16, 16);
                sprite = new Sprite(tileSet, REC);
            }
            if (dy > 0)
            {
                IntRect REC = new IntRect(230, 144, 16, 16);
                sprite = new Sprite(tileSet, REC);
            }
            if (dy > 0 && dx > 0)
            {
                IntRect REC = new IntRect(170 + 31 * (int)(currentFrame), 144, 16, 16);
                sprite = new Sprite(tileSet, REC);
            }
            if (dy > 0 && dx < 0)
            {
                IntRect REC = new IntRect(170 + 31 * (int)(currentFrame) + 16, 144, -16, 16);
                sprite = new Sprite(tileSet, REC);
            }
           
            
            /*Занулить скорость по x*/
            dx = 0;
            /*Смерть персонажа*/
            if (health < 0)
            {
                life = false;
                dx = 0;
                dy = 0;
            }
        }
		/*Обработка столкновений*/
		public void Collision(int num)
		{


			/*проход по карте*/
			for (int i = (int)rect.Top / 16; i < (rect.Top + rect.Height) / 16; i++)
			{
				for (int j = (int)rect.Left / 16; j < (rect.Left + rect.Width) / 16; j++)
				{
					/*Если персонаж столкнулся, с препятствием*/
					if ((TileMap[i][j] == 'P'))
					{
						/*проверяем в какую сторону двигался*/
						if (dy > 0 && num == 1)
						{
							/*Изменяем скорость и др.*/
							rect.Top = i * 16 - rect.Height;
							dy = 0;
							onGround = true;
						}
						if (dy < 0 && num == 1)
						{
							rect.Top = i * 16 + 16;
							dy = 0;

						}
						if (dx > 0 && num == 0)
						{
							rect.Left = j * 16 - rect.Width;
						}
						if (dx < 0 && num == 0)
						{
							rect.Left = j * 16 + 16;
						}
					}

					if (TileMap[i][j] == 'm')
					{
						//TileMap[i][j] = ' ';
						Score++;
					}
					if ((TileMap[i][j] == 'k'))
					{
						if (dy > 0 && num == 1)
						{
							rect.Top = i * 16 - rect.Height;
							dy = 0;
							onGround = true;
						}
						if (dy < 0 && num == 1)
						{
							rect.Top = i * 16 + 16;
							dy = 0;
						}
						if (dx > 0 && num == 0)
						{
							rect.Left = j * 16 - rect.Width;
						}
						if (dx < 0 && num == 0)
						{
							rect.Left = j * 16 + 16;
						}
					}
					if ((TileMap[i][j] == '0'))
					{
						if (dy > 0 && num == 1)
						{
							rect.Top = i * 16 - rect.Height;
							dy = 0;
							onGround = true;
						}
						if (dy < 0 && num == 1)
						{
							rect.Top = i * 16 + 16;
							dy = 0;
						}
						if (dx > 0 && num == 0)
						{
							rect.Left = j * 16 - rect.Width;
						}
						if (dx < 0 && num == 0)
						{
							rect.Left = j * 16 + 16;
						}
					}
					if ((TileMap[i][j] == 'r'))
					{
						if (dy > 0 && num == 1)
						{
							rect.Top = i * 16 - rect.Height;
							dy = 0;
							onGround = true;
						}
						if (dy < 0 && num == 1)
						{
							rect.Top = i * 16 + 16;
							dy = 0;
						}
						if (dx > 0 && num == 0)
						{
							rect.Left = j * 16 - rect.Width;
						}
						if (dx < 0 && num == 0)
						{
							rect.Left = j * 16 + 16;
						}
					}
					if ((TileMap[i][j] == 't'))
					{
						if (dy > 0 && num == 1)
						{
							rect.Top = i * 16 - rect.Height;
							dy = 0;
							onGround = true;
						}
						if (dy < 0 && num == 1)
						{
							rect.Top = i * 16 + 16;
							dy = 0;
						}
						if (dx > 0 && num == 0)
						{
							rect.Left = j * 16 - rect.Width;
						}
						if (dx < 0 && num == 0)
						{
							rect.Left = j * 16 + 16;
						}
					}
					if (TileMap[i][j] == 'c')
					{
						if (dy > 0 && num == 1)
						{

							rect.Top = i * 16 - rect.Height;
							dy = 0;
							onGround = true;
						}
						if (dy < 0 && num == 1)
						{
							rect.Top = i * 16 + 16;
							dy = 0;
						}
						if (dx > 0 && num == 0)
						{

							rect.Left = j * 16 - rect.Width;
						}
						if (dx < 0 && num == 0)
						{

							rect.Left = j * 16 + 16;
						}
					}
				}
			}
		}

	}
}
