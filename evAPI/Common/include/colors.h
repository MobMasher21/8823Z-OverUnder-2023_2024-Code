/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       colors.h                                                  */
/*    Author:       Jayden Liffick                                            */
/*    Created:      4 June 2023                                               */
/*    Description:  A conversion of all the colors in "v5_color.h" to use     */
/*                  the vex color class.                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef COLORS_H
#define COLORS_H

#include "evAPIBasicConfig.h"

namespace evAPI {
  //Custom colors
  
  const color fieldGrey = color(60, 60, 60); //0x3C3C3C
  
  //rgb.txt
  
  const color AliceBlue                 = color(240, 248, 255); //0xF0F8FF
  const color AntiqueWhite              = color(250, 235, 215); //0xFAEBD7
  const color Aqua                      = color(0, 255, 255);   //0x00FFFF
  const color Aquamarine                = color(127, 255, 212); //0x7FFFD4
  const color Azure                     = color(240, 255, 255); //0xF0FFFF
  const color Beige                     = color(245, 245, 220); //0xF5F5DC
  const color Bisque                    = color(255, 228, 196); //0xFFE4C4
  const color Black                     = color(0, 0, 0);       //0x000000
  const color BlanchedAlmond            = color(255, 235, 205); //0xFFEBCD
  const color Blue                      = color(0, 0, 255);     //0x0000FF
  const color BlueViolet                = color(138, 43, 226);  //0x8A2BE2
  const color Brown                     = color(165, 42, 42);   //0xA52A2A
  const color BurlyWood                 = color(222, 184, 135); //0xDEB887
  const color CadetBlue                 = color(95, 158, 160);  //0x5F9EA0
  const color Chartreuse                = color(127, 255, 0);   //0x7FFF00
  const color Chocolate                 = color(210, 105, 30);  //0xD2691E
  const color Coral                     = color(255, 127, 80);  //0xFF7F50
  const color CornflowerBlue            = color(100, 149, 237); //0x6495ED
  const color Cornsilk                  = color(255, 248, 220); //0xFFF8DC
  const color Crimson                   = color(220, 20, 60);   //0xDC143C
  const color Cyan                      = color(0, 255, 255);   //0x00FFFF
  const color DarkBlue                  = color(0, 0, 139);     //0x00008B
  const color DarkCyan                  = color(0, 139, 139);   //0x008B8B
  const color DarkGoldenrod             = color(184, 134, 11);  //0xB8860B
  const color DarkGray                  = color(169, 169, 169); //0xA9A9A9
  const color DarkGreen                 = color(0, 100, 0);     //0x006400
  const color DarkKhaki                 = color(189, 183, 107); //0xBDB76B
  const color DarkMagenta               = color(139, 0, 139);   //0x8B008B
  const color DarkOliveGreen            = color(85, 107, 47);   //0x556B2F
  const color DarkOrange                = color(255, 140, 0);   //0xFF8C00
  const color DarkOrchid                = color(153, 50, 204);  //0x9932CC
  const color DarkRed                   = color(139, 0, 0);     //0x8B0000
  const color DarkSalmon                = color(233, 150, 122); //0xE9967A
  const color DarkSeaGreen              = color(143, 188, 143); //0x8FBC8F
  const color DarkSlateBlue             = color(72, 61, 139);   //0x483D8B
  const color DarkSlateGray             = color(47, 79, 79);    //0x2F4F4F
  const color DarkTurquoise             = color(0, 206, 209);   //0x00CED1
  const color DarkViolet                = color(148, 0, 211);   //0x9400D3
  const color DeepPink                  = color(255, 20, 147);  //0xFF1493
  const color DeepSkyBlue               = color(0, 191, 255);   //0x00BFFF
  const color DimGray                   = color(105, 105, 105); //0x696969
  const color DodgerBlue                = color(30, 144, 255);  //0x1E90FF
  const color FireBrick                 = color(178, 34, 34);   //0xB22222
  const color FloralWhite               = color(255, 250, 240); //0xFFFAF0
  const color ForestGreen               = color(34, 139, 34);   //0x228B22
  const color Fuchsia                   = color(255, 0, 255);   //0xFF00FF
  const color Gainsboro                 = color(220, 220, 220); //0xDCDCDC
  const color GhostWhite                = color(248, 248, 255); //0xF8F8FF
  const color Gold                      = color(255, 215, 0);   //0xFFD700
  const color Goldenrod                 = color(218, 165, 32);  //0xDAA520
  const color Gray                      = color(128, 128, 128); //0x808080
  const color Green                     = color(0, 128, 0);     //0x008000
  const color GreenYellow               = color(173, 255, 47);  //0xADFF2F
  const color Honeydew                  = color(240, 255, 240); //0xF0FFF0
  const color HotPink                   = color(255, 105, 180); //0xFF69B4
  const color IndianRed                 = color(205, 92, 92);   //0xCD5C5C
  const color Indigo                    = color(75, 0, 130);    //0x4B0082
  const color Ivory                     = color(255, 255, 240); //0xFFFFF0
  const color Khaki                     = color(240, 230, 140); //0xF0E68C
  const color Lavender                  = color(230, 230, 250); //0xE6E6FA
  const color LavenderBlush             = color(255, 240, 245); //0xFFF0F5
  const color LawnGreen                 = color(124, 252, 0);   //0x7CFC00
  const color LemonChiffon              = color(255, 250, 205); //0xFFFACD
  const color LightBlue                 = color(173, 216, 230); //0xADD8E6
  const color LightCoral                = color(240, 128, 128); //0xF08080
  const color LightCyan                 = color(224, 255, 255); //0xE0FFFF
  const color LightGoldenrodYellow      = color(250, 250, 210); //0xFAFAD2
  const color LightGreen                = color(144, 238, 144); //0x90EE90
  const color LightGrey                 = color(211, 211, 211); //0xD3D3D3
  const color LightPink                 = color(255, 182, 193); //0xFFB6C1
  const color LightSalmon               = color(255, 160, 122); //0xFFA07A
  const color LightSeaGreen             = color(32, 178, 170);  //0x20B2AA
  const color LightSkyBlue              = color(135, 206, 250); //0x87CEFA
  const color LightSlateGray            = color(119, 136, 153); //0x778899
  const color LightSteelBlue            = color(176, 196, 222); //0xB0C4DE
  const color LightYellow               = color(255, 255, 224); //0xFFFFE0
  const color Lime                      = color(0, 255, 0);     //0x00FF00
  const color LimeGreen                 = color(50, 205, 50);   //0x32CD32
  const color Linen                     = color(250, 240, 230); //0xFAF0E6
  const color Magenta                   = color(255, 0, 255);   //0xFF00FF
  const color Maroon                    = color(128, 0, 0);     //0x800000
  const color MediumAquamarine          = color(102, 205, 170); //0x66CDAA
  const color MediumBlue                = color(0, 0, 205);     //0x0000CD
  const color MediumOrchid              = color(186, 85, 211);  //0xBA55D3
  const color MediumPurple              = color(147, 112, 219); //0x9370DB
  const color MediumSeaGreen            = color(60, 179, 113);  //0x3CB371
  const color MediumSlateBlue           = color(123, 104, 238); //0x7B68EE
  const color MediumSpringGreen         = color(0, 250, 154);   //0x00FA9A
  const color MediumTurquoise           = color(72, 209, 204);  //0x48D1CC
  const color MediumVioletRed           = color(199, 21, 133);  //0xC71585
  const color MidnightBlue              = color(25, 25, 112);   //0x191970
  const color MintCream                 = color(245, 255, 250); //0xF5FFFA
  const color MistyRose                 = color(255, 228, 225); //0xFFE4E1
  const color Moccasin                  = color(255, 228, 181); //0xFFE4B5
  const color NavajoWhite               = color(255, 222, 173); //0xFFDEAD
  const color Navy                      = color(0, 0, 128);     //0x000080
  const color OldLace                   = color(253, 245, 230); //0xFDF5E6
  const color Olive                     = color(128, 128, 0);   //0x808000
  const color OliveDrab                 = color(107, 142, 35);  //0x6B8E23
  const color Orange                    = color(255, 165, 0);   //0xFFA500
  const color OrangeRed                 = color(255, 69, 0);    //0xFF4500
  const color Orchid                    = color(218, 112, 214); //0xDA70D6
  const color PaleGoldenrod             = color(238, 232, 170); //0xEEE8AA
  const color PaleGreen                 = color(152, 251, 152); //0x98FB98
  const color PaleTurquoise             = color(175, 238, 238); //0xAFEEEE
  const color PaleVioletRed             = color(219, 112, 147); //0xDB7093
  const color PapayaWhip                = color(255, 239, 213); //0xFFEFD5
  const color PeachPuff                 = color(255, 239, 213); //0xFFDAB9
  const color Peru                      = color(205, 133, 63);  //0xCD853F
  const color Pink                      = color(255, 192, 203); //0xFFC0CB
  const color Plum                      = color(221, 160, 221); //0xDDA0DD
  const color PowderBlue                = color(176, 224, 230); //0xB0E0E6
  const color Purple                    = color(128, 0, 128);   //0x800080
  const color Red                       = color(255, 0, 0);     //0xFF0000
  const color RosyBrown                 = color(188, 143, 143); //0xBC8F8F
  const color RoyalBlue                 = color(65, 105, 225);  //0x4169E1
  const color SaddleBrown               = color(139, 69, 19);   //0x8B4513
  const color Salmon                    = color(250, 128, 114); //0xFA8072
  const color SandyBrown                = color(244, 164, 96);  //0xF4A460
  const color SeaGreen                  = color(46, 139, 87);   //0x2E8B57
  const color Seashell                  = color(255, 245, 238); //0xFFF5EE
  const color Sienna                    = color(160, 82, 45);   //0xA0522D
  const color Silver                    = color(192, 192, 192); //0xC0C0C0
  const color SkyBlue                   = color(135, 206, 235); //0x87CEEB
  const color SlateBlue                 = color(106, 90, 205);  //0x6A5ACD
  const color SlateGray                 = color(112, 128, 144); //0x708090
  const color Snow                      = color(255, 250, 250); //0xFFFAFA
  const color SpringGreen               = color(0, 255, 127);   //0x00FF7F
  const color SteelBlue                 = color(70, 130, 180);  //0x4682B4
  const color Tan                       = color(210, 180, 140); //0xD2B48C
  const color Teal                      = color(0, 128, 128);   //0x008080
  const color Thistle                   = color(216, 191, 216); //0xD8BFD8
  const color Tomato                    = color(255, 99, 71);   //0xFF6347
  const color Turquoise                 = color(64, 224, 208);  //0x40E0D0
  const color Violet                    = color(238, 130, 238); //0xEE82EE
  const color Wheat                     = color(245, 222, 179); //0xF5DEB3
  const color White                     = color(255, 255, 255); //0xFFFFFF
  const color WhiteSmoke                = color(245, 245, 245); //0xF5F5F5
  const color Yellow                    = color(255, 255, 0);   //0xFFFF00
  const color YellowGreen               = color(154, 205, 50);  //0x9ACD32
}

#endif // COLORS_H
