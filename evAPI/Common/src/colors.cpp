/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       colors.cpp                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      6 Dec 2023                                                */
/*    Description:  A conversion of all the colors in "v5_color.h" to use     */
/*                  the vex color class.                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/colors.h"

namespace evAPI
{
  //Custom colors
  const vex::color fieldGrey = vex::color(60, 60, 60); //0x3C3C3C

  //rgb.txt

  const vex::color AliceBlue                 = vex::color(240, 248, 255); //0xF0F8FF
  const vex::color AntiqueWhite              = vex::color(250, 235, 215); //0xFAEBD7
  const vex::color Aqua                      = vex::color(0, 255, 255);   //0x00FFFF
  const vex::color Aquamarine                = vex::color(127, 255, 212); //0x7FFFD4
  const vex::color Azure                     = vex::color(240, 255, 255); //0xF0FFFF
  const vex::color Beige                     = vex::color(245, 245, 220); //0xF5F5DC
  const vex::color Bisque                    = vex::color(255, 228, 196); //0xFFE4C4
  const vex::color Black                     = vex::color(0, 0, 0);       //0x000000
  const vex::color BlanchedAlmond            = vex::color(255, 235, 205); //0xFFEBCD
  const vex::color Blue                      = vex::color(0, 0, 255);     //0x0000FF
  const vex::color BlueViolet                = vex::color(138, 43, 226);  //0x8A2BE2
  const vex::color Brown                     = vex::color(165, 42, 42);   //0xA52A2A
  const vex::color BurlyWood                 = vex::color(222, 184, 135); //0xDEB887
  const vex::color CadetBlue                 = vex::color(95, 158, 160);  //0x5F9EA0
  const vex::color Chartreuse                = vex::color(127, 255, 0);   //0x7FFF00
  const vex::color Chocolate                 = vex::color(210, 105, 30);  //0xD2691E
  const vex::color Coral                     = vex::color(255, 127, 80);  //0xFF7F50
  const vex::color CornflowerBlue            = vex::color(100, 149, 237); //0x6495ED
  const vex::color Cornsilk                  = vex::color(255, 248, 220); //0xFFF8DC
  const vex::color Crimson                   = vex::color(220, 20, 60);   //0xDC143C
  const vex::color Cyan                      = vex::color(0, 255, 255);   //0x00FFFF
  const vex::color DarkBlue                  = vex::color(0, 0, 139);     //0x00008B
  const vex::color DarkCyan                  = vex::color(0, 139, 139);   //0x008B8B
  const vex::color DarkGoldenrod             = vex::color(184, 134, 11);  //0xB8860B
  const vex::color DarkGray                  = vex::color(169, 169, 169); //0xA9A9A9
  const vex::color DarkGreen                 = vex::color(0, 100, 0);     //0x006400
  const vex::color DarkKhaki                 = vex::color(189, 183, 107); //0xBDB76B
  const vex::color DarkMagenta               = vex::color(139, 0, 139);   //0x8B008B
  const vex::color DarkOliveGreen            = vex::color(85, 107, 47);   //0x556B2F
  const vex::color DarkOrange                = vex::color(255, 140, 0);   //0xFF8C00
  const vex::color DarkOrchid                = vex::color(153, 50, 204);  //0x9932CC
  const vex::color DarkRed                   = vex::color(139, 0, 0);     //0x8B0000
  const vex::color DarkSalmon                = vex::color(233, 150, 122); //0xE9967A
  const vex::color DarkSeaGreen              = vex::color(143, 188, 143); //0x8FBC8F
  const vex::color DarkSlateBlue             = vex::color(72, 61, 139);   //0x483D8B
  const vex::color DarkSlateGray             = vex::color(47, 79, 79);    //0x2F4F4F
  const vex::color DarkTurquoise             = vex::color(0, 206, 209);   //0x00CED1
  const vex::color DarkViolet                = vex::color(148, 0, 211);   //0x9400D3
  const vex::color DeepPink                  = vex::color(255, 20, 147);  //0xFF1493
  const vex::color DeepSkyBlue               = vex::color(0, 191, 255);   //0x00BFFF
  const vex::color DimGray                   = vex::color(105, 105, 105); //0x696969
  const vex::color DodgerBlue                = vex::color(30, 144, 255);  //0x1E90FF
  const vex::color FireBrick                 = vex::color(178, 34, 34);   //0xB22222
  const vex::color FloralWhite               = vex::color(255, 250, 240); //0xFFFAF0
  const vex::color ForestGreen               = vex::color(34, 139, 34);   //0x228B22
  const vex::color Fuchsia                   = vex::color(255, 0, 255);   //0xFF00FF
  const vex::color Gainsboro                 = vex::color(220, 220, 220); //0xDCDCDC
  const vex::color GhostWhite                = vex::color(248, 248, 255); //0xF8F8FF
  const vex::color Gold                      = vex::color(255, 215, 0);   //0xFFD700
  const vex::color Goldenrod                 = vex::color(218, 165, 32);  //0xDAA520
  const vex::color Gray                      = vex::color(128, 128, 128); //0x808080
  const vex::color Green                     = vex::color(0, 128, 0);     //0x008000
  const vex::color GreenYellow               = vex::color(173, 255, 47);  //0xADFF2F
  const vex::color Honeydew                  = vex::color(240, 255, 240); //0xF0FFF0
  const vex::color HotPink                   = vex::color(255, 105, 180); //0xFF69B4
  const vex::color IndianRed                 = vex::color(205, 92, 92);   //0xCD5C5C
  const vex::color Indigo                    = vex::color(75, 0, 130);    //0x4B0082
  const vex::color Ivory                     = vex::color(255, 255, 240); //0xFFFFF0
  const vex::color Khaki                     = vex::color(240, 230, 140); //0xF0E68C
  const vex::color Lavender                  = vex::color(230, 230, 250); //0xE6E6FA
  const vex::color LavenderBlush             = vex::color(255, 240, 245); //0xFFF0F5
  const vex::color LawnGreen                 = vex::color(124, 252, 0);   //0x7CFC00
  const vex::color LemonChiffon              = vex::color(255, 250, 205); //0xFFFACD
  const vex::color LightBlue                 = vex::color(173, 216, 230); //0xADD8E6
  const vex::color LightCoral                = vex::color(240, 128, 128); //0xF08080
  const vex::color LightCyan                 = vex::color(224, 255, 255); //0xE0FFFF
  const vex::color LightGoldenrodYellow      = vex::color(250, 250, 210); //0xFAFAD2
  const vex::color LightGreen                = vex::color(144, 238, 144); //0x90EE90
  const vex::color LightGrey                 = vex::color(211, 211, 211); //0xD3D3D3
  const vex::color LightPink                 = vex::color(255, 182, 193); //0xFFB6C1
  const vex::color LightSalmon               = vex::color(255, 160, 122); //0xFFA07A
  const vex::color LightSeaGreen             = vex::color(32, 178, 170);  //0x20B2AA
  const vex::color LightSkyBlue              = vex::color(135, 206, 250); //0x87CEFA
  const vex::color LightSlateGray            = vex::color(119, 136, 153); //0x778899
  const vex::color LightSteelBlue            = vex::color(176, 196, 222); //0xB0C4DE
  const vex::color LightYellow               = vex::color(255, 255, 224); //0xFFFFE0
  const vex::color Lime                      = vex::color(0, 255, 0);     //0x00FF00
  const vex::color LimeGreen                 = vex::color(50, 205, 50);   //0x32CD32
  const vex::color Linen                     = vex::color(250, 240, 230); //0xFAF0E6
  const vex::color Magenta                   = vex::color(255, 0, 255);   //0xFF00FF
  const vex::color Maroon                    = vex::color(128, 0, 0);     //0x800000
  const vex::color MediumAquamarine          = vex::color(102, 205, 170); //0x66CDAA
  const vex::color MediumBlue                = vex::color(0, 0, 205);     //0x0000CD
  const vex::color MediumOrchid              = vex::color(186, 85, 211);  //0xBA55D3
  const vex::color MediumPurple              = vex::color(147, 112, 219); //0x9370DB
  const vex::color MediumSeaGreen            = vex::color(60, 179, 113);  //0x3CB371
  const vex::color MediumSlateBlue           = vex::color(123, 104, 238); //0x7B68EE
  const vex::color MediumSpringGreen         = vex::color(0, 250, 154);   //0x00FA9A
  const vex::color MediumTurquoise           = vex::color(72, 209, 204);  //0x48D1CC
  const vex::color MediumVioletRed           = vex::color(199, 21, 133);  //0xC71585
  const vex::color MidnightBlue              = vex::color(25, 25, 112);   //0x191970
  const vex::color MintCream                 = vex::color(245, 255, 250); //0xF5FFFA
  const vex::color MistyRose                 = vex::color(255, 228, 225); //0xFFE4E1
  const vex::color Moccasin                  = vex::color(255, 228, 181); //0xFFE4B5
  const vex::color NavajoWhite               = vex::color(255, 222, 173); //0xFFDEAD
  const vex::color Navy                      = vex::color(0, 0, 128);     //0x000080
  const vex::color OldLace                   = vex::color(253, 245, 230); //0xFDF5E6
  const vex::color Olive                     = vex::color(128, 128, 0);   //0x808000
  const vex::color OliveDrab                 = vex::color(107, 142, 35);  //0x6B8E23
  const vex::color Orange                    = vex::color(255, 165, 0);   //0xFFA500
  const vex::color OrangeRed                 = vex::color(255, 69, 0);    //0xFF4500
  const vex::color Orchid                    = vex::color(218, 112, 214); //0xDA70D6
  const vex::color PaleGoldenrod             = vex::color(238, 232, 170); //0xEEE8AA
  const vex::color PaleGreen                 = vex::color(152, 251, 152); //0x98FB98
  const vex::color PaleTurquoise             = vex::color(175, 238, 238); //0xAFEEEE
  const vex::color PaleVioletRed             = vex::color(219, 112, 147); //0xDB7093
  const vex::color PapayaWhip                = vex::color(255, 239, 213); //0xFFEFD5
  const vex::color PeachPuff                 = vex::color(255, 239, 213); //0xFFDAB9
  const vex::color Peru                      = vex::color(205, 133, 63);  //0xCD853F
  const vex::color Pink                      = vex::color(255, 192, 203); //0xFFC0CB
  const vex::color Plum                      = vex::color(221, 160, 221); //0xDDA0DD
  const vex::color PowderBlue                = vex::color(176, 224, 230); //0xB0E0E6
  const vex::color Purple                    = vex::color(128, 0, 128);   //0x800080
  const vex::color Red                       = vex::color(255, 0, 0);     //0xFF0000
  const vex::color RosyBrown                 = vex::color(188, 143, 143); //0xBC8F8F
  const vex::color RoyalBlue                 = vex::color(65, 105, 225);  //0x4169E1
  const vex::color SaddleBrown               = vex::color(139, 69, 19);   //0x8B4513
  const vex::color Salmon                    = vex::color(250, 128, 114); //0xFA8072
  const vex::color SandyBrown                = vex::color(244, 164, 96);  //0xF4A460
  const vex::color SeaGreen                  = vex::color(46, 139, 87);   //0x2E8B57
  const vex::color Seashell                  = vex::color(255, 245, 238); //0xFFF5EE
  const vex::color Sienna                    = vex::color(160, 82, 45);   //0xA0522D
  const vex::color Silver                    = vex::color(192, 192, 192); //0xC0C0C0
  const vex::color SkyBlue                   = vex::color(135, 206, 235); //0x87CEEB
  const vex::color SlateBlue                 = vex::color(106, 90, 205);  //0x6A5ACD
  const vex::color SlateGray                 = vex::color(112, 128, 144); //0x708090
  const vex::color Snow                      = vex::color(255, 250, 250); //0xFFFAFA
  const vex::color SpringGreen               = vex::color(0, 255, 127);   //0x00FF7F
  const vex::color SteelBlue                 = vex::color(70, 130, 180);  //0x4682B4
  const vex::color Tan                       = vex::color(210, 180, 140); //0xD2B48C
  const vex::color Teal                      = vex::color(0, 128, 128);   //0x008080
  const vex::color Thistle                   = vex::color(216, 191, 216); //0xD8BFD8
  const vex::color Tomato                    = vex::color(255, 99, 71);   //0xFF6347
  const vex::color Turquoise                 = vex::color(64, 224, 208);  //0x40E0D0
  const vex::color Violet                    = vex::color(238, 130, 238); //0xEE82EE
  const vex::color Wheat                     = vex::color(245, 222, 179); //0xF5DEB3
  const vex::color White                     = vex::color(255, 255, 255); //0xFFFFFF
  const vex::color WhiteSmoke                = vex::color(245, 245, 245); //0xF5F5F5
  const vex::color Yellow                    = vex::color(255, 255, 0);   //0xFFFF00
  const vex::color YellowGreen               = vex::color(154, 205, 50);  //0x9ACD32
}