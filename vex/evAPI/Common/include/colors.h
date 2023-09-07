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

#include "vex_color.h"

//Custom colors

const color fieldGrey = color(60, 60, 60); //0x003C3C3C

//rgb.txt

const color vexClrAliceBlue                 = color(240, 248, 255); //0x00F0F8FF
const color vexClrAntiqueWhite              = color(250, 235, 215); //0x00FAEBD7
const color vexClrAqua                      = color(0, 255, 255);   //0x0000FFFF
const color vexClrAquamarine                = color(127, 255, 212); //0x007FFFD4
const color vexClrAzure                     = color(240, 255, 255); //0x00F0FFFF
const color vexClrBeige                     = color(245, 245, 220); //0x00F5F5DC
const color vexClrBisque                    = color(255, 228, 196); //0x00FFE4C4
const color vexClrBlack                     = color(0, 0, 0);       //0x00000000
const color vexClrBlanchedAlmond            = color(255, 235, 205); //0x00FFEBCD
const color vexClrBlue                      = color(0, 0, 255);     //0x000000FF
const color vexClrBlueViolet                = color(138, 43, 226);  //0x008A2BE2
const color vexClrBrown                     = color(165, 42, 42);   //0x00A52A2A
const color vexClrBurlyWood                 = color(222, 184, 135); //0x00DEB887
const color vexClrCadetBlue                 = color(95, 158, 160);  //0x005F9EA0
const color vexClrChartreuse                = color(127, 255, 0);   //0x007FFF00
const color vexClrChocolate                 = color(210, 105, 30);  //0x00D2691E
const color vexClrCoral                     = color(255, 127, 80);  //0x00FF7F50
const color vexClrCornflowerBlue            = color(100, 149, 237); //0x006495ED
const color vexClrCornsilk                  = color(255, 248, 220); //0x00FFF8DC
const color vexClrCrimson                   = color(220, 20, 60);   //0x00DC143C
const color vexClrCyan                      = color(0, 255, 255);   //0x0000FFFF
const color vexClrDarkBlue                  = color(0, 0, 139);     //0x0000008B
const color vexClrDarkCyan                  = color(0, 139, 139);   //0x00008B8B
const color vexClrDarkGoldenrod             = color(184, 134, 11);  //0x00B8860B
const color vexClrDarkGray                  = color(169, 169, 169); //0x00A9A9A9
const color vexClrDarkGreen                 = color(0, 100, 0);     //0x00006400
const color vexClrDarkKhaki                 = color(189, 183, 107); //0x00BDB76B
const color vexClrDarkMagenta               = color(139, 0, 139);   //0x008B008B
const color vexClrDarkOliveGreen            = color(85, 107, 47);   //0x00556B2F
const color vexClrDarkOrange                = color(255, 140, 0);   //0x00FF8C00
const color vexClrDarkOrchid                = color(153, 50, 204);  //0x009932CC
const color vexClrDarkRed                   = color(139, 0, 0);     //0x008B0000
const color vexClrDarkSalmon                = color(233, 150, 122); //0x00E9967A
const color vexClrDarkSeaGreen              = color(143, 188, 143); //0x008FBC8F
const color vexClrDarkSlateBlue             = color(72, 61, 139);   //0x00483D8B
const color vexClrDarkSlateGray             = color(47, 79, 79);    //0x002F4F4F
const color vexClrDarkTurquoise             = color(0, 206, 209);   //0x0000CED1
const color vexClrDarkViolet                = color(148, 0, 211);   //0x009400D3
const color vexClrDeepPink                  = color(255, 20, 147);  //0x00FF1493
const color vexClrDeepSkyBlue               = color(0, 191, 255);   //0x0000BFFF
const color vexClrDimGray                   = color(105, 105, 105); //0x00696969
const color vexClrDodgerBlue                = color(30, 144, 255);  //0x001E90FF
const color vexClrFireBrick                 = color(178, 34, 34);   //0x00B22222
const color vexClrFloralWhite               = color(255, 250, 240); //0x00FFFAF0
const color vexClrForestGreen               = color(34, 139, 34);   //0x00228B22
const color vexClrFuchsia                   = color(255, 0, 255);   //0x00FF00FF
const color vexClrGainsboro                 = color(220, 220, 220); //0x00DCDCDC
const color vexClrGhostWhite                = color(248, 248, 255); //0x00F8F8FF
const color vexClrGold                      = color(255, 215, 0);   //0x00FFD700
const color vexClrGoldenrod                 = color(218, 165, 32);  //0x00DAA520
const color vexClrGray                      = color(128, 128, 128); //0x00808080
const color vexClrGreen                     = color(0, 128, 0);     //0x00008000
const color vexClrGreenYellow               = color(173, 255, 47);  //0x00ADFF2F
const color vexClrHoneydew                  = color(240, 255, 240); //0x00F0FFF0
const color vexClrHotPink                   = color(255, 105, 180); //0x00FF69B4
const color vexClrIndianRed                 = color(205, 92, 92);   //0x00CD5C5C
const color vexClrIndigo                    = color(75, 0, 130);    //0x004B0082
const color vexClrIvory                     = color(255, 255, 240); //0x00FFFFF0
const color vexClrKhaki                     = color(240, 230, 140); //0x00F0E68C
const color vexClrLavender                  = color(230, 230, 250); //0x00E6E6FA
const color vexClrLavenderBlush             = color(255, 240, 245); //0x00FFF0F5
const color vexClrLawnGreen                 = color(124, 252, 0);   //0x007CFC00
const color vexClrLemonChiffon              = color(255, 250, 205); //0x00FFFACD
const color vexClrLightBlue                 = color(173, 216, 230); //0x00ADD8E6
const color vexClrLightCoral                = color(240, 128, 128); //0x00F08080
const color vexClrLightCyan                 = color(224, 255, 255); //0x00E0FFFF
const color vexClrLightGoldenrodYellow      = color(250, 250, 210); //0x00FAFAD2
const color vexClrLightGreen                = color(144, 238, 144); //0x0090EE90
const color vexClrLightGrey                 = color(211, 211, 211); //0x00D3D3D3
const color vexClrLightPink                 = color(255, 182, 193); //0x00FFB6C1
const color vexClrLightSalmon               = color(255, 160, 122); //0x00FFA07A
const color vexClrLightSeaGreen             = color(32, 178, 170);  //0x0020B2AA
const color vexClrLightSkyBlue              = color(135, 206, 250); //0x0087CEFA
const color vexClrLightSlateGray            = color(119, 136, 153); //0x00778899
const color vexClrLightSteelBlue            = color(176, 196, 222); //0x00B0C4DE
const color vexClrLightYellow               = color(255, 255, 224); //0x00FFFFE0
const color vexClrLime                      = color(0, 255, 0);     //0x0000FF00
const color vexClrLimeGreen                 = color(50, 205, 50);   //0x0032CD32
const color vexClrLinen                     = color(250, 240, 230); //0x00FAF0E6
const color vexClrMagenta                   = color(255, 0, 255);   //0x00FF00FF
const color vexClrMaroon                    = color(128, 0, 0);     //0x00800000
const color vexClrMediumAquamarine          = color(102, 205, 170); //0x0066CDAA
const color vexClrMediumBlue                = color(0, 0, 205);     //0x000000CD
const color vexClrMediumOrchid              = color(186, 85, 211);  //0x00BA55D3
const color vexClrMediumPurple              = color(147, 112, 219); //0x009370DB
const color vexClrMediumSeaGreen            = color(60, 179, 113);  //0x003CB371
const color vexClrMediumSlateBlue           = color(123, 104, 238); //0x007B68EE
const color vexClrMediumSpringGreen         = color(0, 250, 154);   //0x0000FA9A
const color vexClrMediumTurquoise           = color(72, 209, 204);  //0x0048D1CC
const color vexClrMediumVioletRed           = color(199, 21, 133);  //0x00C71585
const color vexClrMidnightBlue              = color(25, 25, 112);   //0x00191970
const color vexClrMintCream                 = color(245, 255, 250); //0x00F5FFFA
const color vexClrMistyRose                 = color(255, 228, 225); //0x00FFE4E1
const color vexClrMoccasin                  = color(255, 228, 181); //0x00FFE4B5
const color vexClrNavajoWhite               = color(255, 222, 173); //0x00FFDEAD
const color vexClrNavy                      = color(0, 0, 128);     //0x00000080
const color vexClrOldLace                   = color(253, 245, 230); //0x00FDF5E6
const color vexClrOlive                     = color(128, 128, 0);   //0x00808000
const color vexClrOliveDrab                 = color(107, 142, 35);  //0x006B8E23
const color vexClrOrange                    = color(255, 165, 0);   //0x00FFA500
const color vexClrOrangeRed                 = color(255, 69, 0);    //0x00FF4500
const color vexClrOrchid                    = color(218, 112, 214); //0x00DA70D6
const color vexClrPaleGoldenrod             = color(238, 232, 170); //0x00EEE8AA
const color vexClrPaleGreen                 = color(152, 251, 152); //0x0098FB98
const color vexClrPaleTurquoise             = color(175, 238, 238); //0x00AFEEEE
const color vexClrPaleVioletRed             = color(219, 112, 147); //0x00DB7093
const color vexClrPapayaWhip                = color(255, 239, 213); //0x00FFEFD5
const color vexClrPeachPuff                 = color(255, 239, 213); //0x00FFDAB9
const color vexClrPeru                      = color(205, 133, 63);  //0x00CD853F
const color vexClrPink                      = color(255, 192, 203); //0x00FFC0CB
const color vexClrPlum                      = color(221, 160, 221); //0x00DDA0DD
const color vexClrPowderBlue                = color(176, 224, 230); //0x00B0E0E6
const color vexClrPurple                    = color(128, 0, 128);   //0x00800080
const color vexClrRed                       = color(255, 0, 0);     //0x00FF0000
const color vexClrRosyBrown                 = color(188, 143, 143); //0x00BC8F8F
const color vexClrRoyalBlue                 = color(65, 105, 225);  //0x004169E1
const color vexClrSaddleBrown               = color(139, 69, 19);   //0x008B4513
const color vexClrSalmon                    = color(250, 128, 114); //0x00FA8072
const color vexClrSandyBrown                = color(244, 164, 96);  //0x00F4A460
const color vexClrSeaGreen                  = color(46, 139, 87);   //0x002E8B57
const color vexClrSeashell                  = color(255, 245, 238); //0x00FFF5EE
const color vexClrSienna                    = color(160, 82, 45);   //0x00A0522D
const color vexClrSilver                    = color(192, 192, 192); //0x00C0C0C0
const color vexClrSkyBlue                   = color(135, 206, 235); //0x0087CEEB
const color vexClrSlateBlue                 = color(106, 90, 205);  //0x006A5ACD
const color vexClrSlateGray                 = color(112, 128, 144); //0x00708090
const color vexClrSnow                      = color(255, 250, 250); //0x00FFFAFA
const color vexClrSpringGreen               = color(0, 255, 127);   //0x0000FF7F
const color vexClrSteelBlue                 = color(70, 130, 180);  //0x004682B4
const color vexClrTan                       = color(210, 180, 140); //0x00D2B48C
const color vexClrTeal                      = color(0, 128, 128);   //0x00008080
const color vexClrThistle                   = color(216, 191, 216); //0x00D8BFD8
const color vexClrTomato                    = color(255, 99, 71);   //0x00FF6347
const color vexClrTurquoise                 = color(64, 224, 208);  //0x0040E0D0
const color vexClrViolet                    = color(238, 130, 238); //0x00EE82EE
const color vexClrWheat                     = color(245, 222, 179); //0x00F5DEB3
const color vexClrWhite                     = color(255, 255, 255); //0x00FFFFFF
const color vexClrWhiteSmoke                = color(245, 245, 245); //0x00F5F5F5
const color vexClrYellow                    = color(255, 255, 0);   //0x00FFFF00
const color vexClrYellowGreen               = color(154, 205, 50);  //0x009ACD32

#endif // COLORS_H
