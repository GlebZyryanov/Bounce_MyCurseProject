#pragma once
#include<SFML/Graphics.hpp>
/*Переменные высота\щирина карты*/
const int H = 17;
const int W = 151;

sf::String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                w                                                       m       w                        Z                          0",
"0                                                                               w     m m   m                                                        0",
"0                    w                          w                                          mm                                                        0",
"0                                                                                        mm          t0                                              0",
"0                                                                                    t0               00                          t0          G      0",
"0                                      m                 m  m    m                   00               00    m m m m m m m         00     m m m       0",
"0                         m             m   m                           rPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0      m                                 m                     m       rrPPPPPPPPccccccPcccccPcPPPcPccPPPPcPcccccPcccccPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0      m              m m                m m m                        rrrPPPPPPPPccPPPcPcPPPcPcPPPcPcPcPPPcPcPPPPPcPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0      m             kckck                                m  m       rrrrPPPPPPPPccccccPcPPPcPcPPPcPcPPcPPcPcPPPPPcccccPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0      m                                t0                          rrrrrPPPPPPPPccPPPcPcPPPcPcPPPcPcPPPcPcPcPPPPPcPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0G                                     00              t0          rrrrrrPPPPPPPPccccccPcccccPcccccPcPPPPccPcccccPcccccPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"0           d    g  mmm     d          00      m  m    00         rrrrrrrPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP0",
};