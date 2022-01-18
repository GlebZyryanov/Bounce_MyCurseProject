using System;
using System.Collections.Generic;
using System.Text;
using SFML.Graphics;
using SFML.Window;
using SFML.Audio;

namespace BounceCurseCSharp
{
	class ENEMYHorizont
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
		public FloatRect rect;
		IntRect REC;
		public Sprite sprite;
		public float currentFrame;
		public bool life;

		public static Texture tileSet = new Texture("C:/Users/zyrya/source/repos/BounceCurseCSharp/Mario_tileset.png");
		Sprite tile = new Sprite(tileSet);
		public void set(ref Texture image, int x, int y)
		{
			sprite = new Sprite(image);
			rect = new FloatRect(x, y, 16, 16);
		}


		public void Update(float time)
		{
			rect.Left += dx * time;
			Collision();

			currentFrame += time * 0.005f;
			if (currentFrame > 2)
			{
				currentFrame -= 2;
			}
			REC = new IntRect(36 * (int)(currentFrame), 0, 16, 16);
			sprite = new Sprite(tileSet, REC);
			if (!life)
			{
				REC = new IntRect(58, 0, 16, 16);
				sprite = new Sprite(tileSet, REC);
			}
		}
		/*Обработка столкновений*/
		public void Collision()
		{



			for (int i = (int)rect.Top / 16; i < (rect.Top + rect.Height) / 16; i++)
			{
				for (int j = (int)rect.Left / 16; j < (rect.Left + rect.Width) / 16; j++)
				{

					if ((TileMap[i][j] == 'P'))
					{
						if (dx > 0)
						{
							/*Изменяем скорость и др.*/
							rect.Top = i * 16 - rect.Height;
							dx *= -1;
						}

					}



					if ((TileMap[i][j] == '0'))
					{
						if (dx > 0)
						{
							rect.Top = i * 16 - rect.Height;
							dx *= -1;

						}

					}


				}

			}
		}
	}


}