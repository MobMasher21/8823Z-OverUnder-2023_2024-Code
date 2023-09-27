/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       colors.h                                                  */
/*    Author:       Jayden Liffick                                            */
/*    Created:      4 June 2023                                               */
/*    Description:  Redefines all the colors in "v5_color.h" so they use the  */
/*                  vex color class.                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef COLORS_H
#define COLORS_H

#include "vex_color.h"
#include "evAPISettings.h"

//Custom colors
const color fieldGrey = color(60, 60, 60);                //0x003C3C3C
const color vexDisplayBackgroundDark = color(21, 23, 26); //0x15171a

#if REDEFINE_COLORS
  #undef ClrAliceBlue            
  #undef ClrAntiqueWhite         
  #undef ClrAqua                 
  #undef ClrAquamarine           
  #undef ClrAzure                
  #undef ClrBeige                
  #undef ClrBisque               
  #undef ClrBlack                
  #undef ClrBlanchedAlmond       
  #undef ClrBlue                 
  #undef ClrBlueViolet           
  #undef ClrBrown                
  #undef ClrBurlyWood            
  #undef ClrCadetBlue            
  #undef ClrChartreuse           
  #undef ClrChocolate            
  #undef ClrCoral                
  #undef ClrCornflowerBlue       
  #undef ClrCornsilk             
  #undef ClrCrimson              
  #undef ClrCyan                 
  #undef ClrDarkBlue             
  #undef ClrDarkCyan             
  #undef ClrDarkGoldenrod        
  #undef ClrDarkGray             
  #undef ClrDarkGreen            
  #undef ClrDarkKhaki            
  #undef ClrDarkMagenta          
  #undef ClrDarkOliveGreen       
  #undef ClrDarkOrange           
  #undef ClrDarkOrchid           
  #undef ClrDarkRed              
  #undef ClrDarkSalmon           
  #undef ClrDarkSeaGreen         
  #undef ClrDarkSlateBlue        
  #undef ClrDarkSlateGray        
  #undef ClrDarkTurquoise        
  #undef ClrDarkViolet           
  #undef ClrDeepPink             
  #undef ClrDeepSkyBlue          
  #undef ClrDimGray              
  #undef ClrDodgerBlue           
  #undef ClrFireBrick            
  #undef ClrFloralWhite          
  #undef ClrForestGreen          
  #undef ClrFuchsia              
  #undef ClrGainsboro            
  #undef ClrGhostWhite           
  #undef ClrGold                 
  #undef ClrGoldenrod            
  #undef ClrGray                 
  #undef ClrGreen                
  #undef ClrGreenYellow          
  #undef ClrHoneydew             
  #undef ClrHotPink              
  #undef ClrIndianRed            
  #undef ClrIndigo               
  #undef ClrIvory                
  #undef ClrKhaki                
  #undef ClrLavender             
  #undef ClrLavenderBlush        
  #undef ClrLawnGreen            
  #undef ClrLemonChiffon         
  #undef ClrLightBlue            
  #undef ClrLightCoral           
  #undef ClrLightCyan            
  #undef ClrLightGoldenrodYellow 
  #undef ClrLightGreen           
  #undef ClrLightGrey            
  #undef ClrLightPink            
  #undef ClrLightSalmon          
  #undef ClrLightSeaGreen        
  #undef ClrLightSkyBlue         
  #undef ClrLightSlateGray       
  #undef ClrLightSteelBlue       
  #undef ClrLightYellow          
  #undef ClrLime                 
  #undef ClrLimeGreen            
  #undef ClrLinen                
  #undef ClrMagenta              
  #undef ClrMaroon               
  #undef ClrMediumAquamarine     
  #undef ClrMediumBlue           
  #undef ClrMediumOrchid         
  #undef ClrMediumPurple         
  #undef ClrMediumSeaGreen       
  #undef ClrMediumSlateBlue      
  #undef ClrMediumSpringGreen    
  #undef ClrMediumTurquoise      
  #undef ClrMediumVioletRed      
  #undef ClrMidnightBlue         
  #undef ClrMintCream            
  #undef ClrMistyRose            
  #undef ClrMoccasin             
  #undef ClrNavajoWhite          
  #undef ClrNavy                 
  #undef ClrOldLace              
  #undef ClrOlive                
  #undef ClrOliveDrab            
  #undef ClrOrange               
  #undef ClrOrangeRed            
  #undef ClrOrchid               
  #undef ClrPaleGoldenrod        
  #undef ClrPaleGreen            
  #undef ClrPaleTurquoise        
  #undef ClrPaleVioletRed        
  #undef ClrPapayaWhip           
  #undef ClrPeachPuff            
  #undef ClrPeru                 
  #undef ClrPink                 
  #undef ClrPlum                 
  #undef ClrPowderBlue           
  #undef ClrPurple               
  #undef ClrRed                  
  #undef ClrRosyBrown            
  #undef ClrRoyalBlue            
  #undef ClrSaddleBrown          
  #undef ClrSalmon               
  #undef ClrSandyBrown           
  #undef ClrSeaGreen             
  #undef ClrSeashell             
  #undef ClrSienna               
  #undef ClrSilver               
  #undef ClrSkyBlue              
  #undef ClrSlateBlue            
  #undef ClrSlateGray            
  #undef ClrSnow                 
  #undef ClrSpringGreen          
  #undef ClrSteelBlue            
  #undef ClrTan                  
  #undef ClrTeal                 
  #undef ClrThistle              
  #undef ClrTomato               
  #undef ClrTurquoise            
  #undef ClrViolet               
  #undef ClrWheat                
  #undef ClrWhite                
  #undef ClrWhiteSmoke           
  #undef ClrYellow               
  #undef ClrYellowGreen          

  //rgb.txt

  const color ClrAliceBlue                 = color(240, 248, 255); //0xF0F8FF
  const color ClrAntiqueWhite              = color(250, 235, 215); //0xFAEBD7
  const color ClrAqua                      = color(0, 255, 255);   //0x00FFFF
  const color ClrAquamarine                = color(127, 255, 212); //0x7FFFD4
  const color ClrAzure                     = color(240, 255, 255); //0xF0FFFF
  const color ClrBeige                     = color(245, 245, 220); //0xF5F5DC
  const color ClrBisque                    = color(255, 228, 196); //0xFFE4C4
  const color ClrBlack                     = color(0, 0, 0);       //0x000000
  const color ClrBlanchedAlmond            = color(255, 235, 205); //0xFFEBCD
  const color ClrBlue                      = color(0, 0, 255);     //0x0000FF
  const color ClrBlueViolet                = color(138, 43, 226);  //0x8A2BE2
  const color ClrBrown                     = color(165, 42, 42);   //0xA52A2A
  const color ClrBurlyWood                 = color(222, 184, 135); //0xDEB887
  const color ClrCadetBlue                 = color(95, 158, 160);  //0x5F9EA0
  const color ClrChartreuse                = color(127, 255, 0);   //0x7FFF00
  const color ClrChocolate                 = color(210, 105, 30);  //0xD2691E
  const color ClrCoral                     = color(255, 127, 80);  //0xFF7F50
  const color ClrCornflowerBlue            = color(100, 149, 237); //0x6495ED
  const color ClrCornsilk                  = color(255, 248, 220); //0xFFF8DC
  const color ClrCrimson                   = color(220, 20, 60);   //0xDC143C
  const color ClrCyan                      = color(0, 255, 255);   //0x00FFFF
  const color ClrDarkBlue                  = color(0, 0, 139);     //0x00008B
  const color ClrDarkCyan                  = color(0, 139, 139);   //0x008B8B
  const color ClrDarkGoldenrod             = color(184, 134, 11);  //0xB8860B
  const color ClrDarkGray                  = color(169, 169, 169); //0xA9A9A9
  const color ClrDarkGreen                 = color(0, 100, 0);     //0x006400
  const color ClrDarkKhaki                 = color(189, 183, 107); //0xBDB76B
  const color ClrDarkMagenta               = color(139, 0, 139);   //0x8B008B
  const color ClrDarkOliveGreen            = color(85, 107, 47);   //0x556B2F
  const color ClrDarkOrange                = color(255, 140, 0);   //0xFF8C00
  const color ClrDarkOrchid                = color(153, 50, 204);  //0x9932CC
  const color ClrDarkRed                   = color(139, 0, 0);     //0x8B0000
  const color ClrDarkSalmon                = color(233, 150, 122); //0xE9967A
  const color ClrDarkSeaGreen              = color(143, 188, 143); //0x8FBC8F
  const color ClrDarkSlateBlue             = color(72, 61, 139);   //0x483D8B
  const color ClrDarkSlateGray             = color(47, 79, 79);    //0x2F4F4F
  const color ClrDarkTurquoise             = color(0, 206, 209);   //0x00CED1
  const color ClrDarkViolet                = color(148, 0, 211);   //0x9400D3
  const color ClrDeepPink                  = color(255, 20, 147);  //0xFF1493
  const color ClrDeepSkyBlue               = color(0, 191, 255);   //0x00BFFF
  const color ClrDimGray                   = color(105, 105, 105); //0x696969
  const color ClrDodgerBlue                = color(30, 144, 255);  //0x1E90FF
  const color ClrFireBrick                 = color(178, 34, 34);   //0xB22222
  const color ClrFloralWhite               = color(255, 250, 240); //0xFFFAF0
  const color ClrForestGreen               = color(34, 139, 34);   //0x228B22
  const color ClrFuchsia                   = color(255, 0, 255);   //0xFF00FF
  const color ClrGainsboro                 = color(220, 220, 220); //0xDCDCDC
  const color ClrGhostWhite                = color(248, 248, 255); //0xF8F8FF
  const color ClrGold                      = color(255, 215, 0);   //0xFFD700
  const color ClrGoldenrod                 = color(218, 165, 32);  //0xDAA520
  const color ClrGray                      = color(128, 128, 128); //0x808080
  const color ClrGreen                     = color(0, 128, 0);     //0x008000
  const color ClrGreenYellow               = color(173, 255, 47);  //0xADFF2F
  const color ClrHoneydew                  = color(240, 255, 240); //0xF0FFF0
  const color ClrHotPink                   = color(255, 105, 180); //0xFF69B4
  const color ClrIndianRed                 = color(205, 92, 92);   //0xCD5C5C
  const color ClrIndigo                    = color(75, 0, 130);    //0x4B0082
  const color ClrIvory                     = color(255, 255, 240); //0xFFFFF0
  const color ClrKhaki                     = color(240, 230, 140); //0xF0E68C
  const color ClrLavender                  = color(230, 230, 250); //0xE6E6FA
  const color ClrLavenderBlush             = color(255, 240, 245); //0xFFF0F5
  const color ClrLawnGreen                 = color(124, 252, 0);   //0x7CFC00
  const color ClrLemonChiffon              = color(255, 250, 205); //0xFFFACD
  const color ClrLightBlue                 = color(173, 216, 230); //0xADD8E6
  const color ClrLightCoral                = color(240, 128, 128); //0xF08080
  const color ClrLightCyan                 = color(224, 255, 255); //0xE0FFFF
  const color ClrLightGoldenrodYellow      = color(250, 250, 210); //0xFAFAD2
  const color ClrLightGreen                = color(144, 238, 144); //0x90EE90
  const color ClrLightGrey                 = color(211, 211, 211); //0xD3D3D3
  const color ClrLightPink                 = color(255, 182, 193); //0xFFB6C1
  const color ClrLightSalmon               = color(255, 160, 122); //0xFFA07A
  const color ClrLightSeaGreen             = color(32, 178, 170);  //0x20B2AA
  const color ClrLightSkyBlue              = color(135, 206, 250); //0x87CEFA
  const color ClrLightSlateGray            = color(119, 136, 153); //0x778899
  const color ClrLightSteelBlue            = color(176, 196, 222); //0xB0C4DE
  const color ClrLightYellow               = color(255, 255, 224); //0xFFFFE0
  const color ClrLime                      = color(0, 255, 0);     //0x00FF00
  const color ClrLimeGreen                 = color(50, 205, 50);   //0x32CD32
  const color ClrLinen                     = color(250, 240, 230); //0xFAF0E6
  const color ClrMagenta                   = color(255, 0, 255);   //0xFF00FF
  const color ClrMaroon                    = color(128, 0, 0);     //0x800000
  const color ClrMediumAquamarine          = color(102, 205, 170); //0x66CDAA
  const color ClrMediumBlue                = color(0, 0, 205);     //0x0000CD
  const color ClrMediumOrchid              = color(186, 85, 211);  //0xBA55D3
  const color ClrMediumPurple              = color(147, 112, 219); //0x9370DB
  const color ClrMediumSeaGreen            = color(60, 179, 113);  //0x3CB371
  const color ClrMediumSlateBlue           = color(123, 104, 238); //0x7B68EE
  const color ClrMediumSpringGreen         = color(0, 250, 154);   //0x00FA9A
  const color ClrMediumTurquoise           = color(72, 209, 204);  //0x48D1CC
  const color ClrMediumVioletRed           = color(199, 21, 133);  //0xC71585
  const color ClrMidnightBlue              = color(25, 25, 112);   //0x191970
  const color ClrMintCream                 = color(245, 255, 250); //0xF5FFFA
  const color ClrMistyRose                 = color(255, 228, 225); //0xFFE4E1
  const color ClrMoccasin                  = color(255, 228, 181); //0xFFE4B5
  const color ClrNavajoWhite               = color(255, 222, 173); //0xFFDEAD
  const color ClrNavy                      = color(0, 0, 128);     //0x000080
  const color ClrOldLace                   = color(253, 245, 230); //0xFDF5E6
  const color ClrOlive                     = color(128, 128, 0);   //0x808000
  const color ClrOliveDrab                 = color(107, 142, 35);  //0x6B8E23
  const color ClrOrange                    = color(255, 165, 0);   //0xFFA500
  const color ClrOrangeRed                 = color(255, 69, 0);    //0xFF4500
  const color ClrOrchid                    = color(218, 112, 214); //0xDA70D6
  const color ClrPaleGoldenrod             = color(238, 232, 170); //0xEEE8AA
  const color ClrPaleGreen                 = color(152, 251, 152); //0x98FB98
  const color ClrPaleTurquoise             = color(175, 238, 238); //0xAFEEEE
  const color ClrPaleVioletRed             = color(219, 112, 147); //0xDB7093
  const color ClrPapayaWhip                = color(255, 239, 213); //0xFFEFD5
  const color ClrPeachPuff                 = color(255, 239, 213); //0xFFDAB9
  const color ClrPeru                      = color(205, 133, 63);  //0xCD853F
  const color ClrPink                      = color(255, 192, 203); //0xFFC0CB
  const color ClrPlum                      = color(221, 160, 221); //0xDDA0DD
  const color ClrPowderBlue                = color(176, 224, 230); //0xB0E0E6
  const color ClrPurple                    = color(128, 0, 128);   //0x800080
  const color ClrRed                       = color(255, 0, 0);     //0xFF0000
  const color ClrRosyBrown                 = color(188, 143, 143); //0xBC8F8F
  const color ClrRoyalBlue                 = color(65, 105, 225);  //0x4169E1
  const color ClrSaddleBrown               = color(139, 69, 19);   //0x8B4513
  const color ClrSalmon                    = color(250, 128, 114); //0xFA8072
  const color ClrSandyBrown                = color(244, 164, 96);  //0xF4A460
  const color ClrSeaGreen                  = color(46, 139, 87);   //0x2E8B57
  const color ClrSeashell                  = color(255, 245, 238); //0xFFF5EE
  const color ClrSienna                    = color(160, 82, 45);   //0xA0522D
  const color ClrSilver                    = color(192, 192, 192); //0xC0C0C0
  const color ClrSkyBlue                   = color(135, 206, 235); //0x87CEEB
  const color ClrSlateBlue                 = color(106, 90, 205);  //0x6A5ACD
  const color ClrSlateGray                 = color(112, 128, 144); //0x708090
  const color ClrSnow                      = color(255, 250, 250); //0xFFFAFA
  const color ClrSpringGreen               = color(0, 255, 127);   //0x00FF7F
  const color ClrSteelBlue                 = color(70, 130, 180);  //0x4682B4
  const color ClrTan                       = color(210, 180, 140); //0xD2B48C
  const color ClrTeal                      = color(0, 128, 128);   //0x008080
  const color ClrThistle                   = color(216, 191, 216); //0xD8BFD8
  const color ClrTomato                    = color(255, 99, 71);   //0xFF6347
  const color ClrTurquoise                 = color(64, 224, 208);  //0x40E0D0
  const color ClrViolet                    = color(238, 130, 238); //0xEE82EE
  const color ClrWheat                     = color(245, 222, 179); //0xF5DEB3
  const color ClrWhite                     = color(255, 255, 255); //0xFFFFFF
  const color ClrWhiteSmoke                = color(245, 245, 245); //0xF5F5F5
  const color ClrYellow                    = color(255, 255, 0);   //0xFFFF00
  const color ClrYellowGreen               = color(154, 205, 50);  //0x9ACD32
#else
  const color vexClrAliceBlue                 = color(240, 248, 255); //0xF0F8FF
  const color vexClrAntiqueWhite              = color(250, 235, 215); //0xFAEBD7
  const color vexClrAqua                      = color(0, 255, 255);   //0x00FFFF
  const color vexClrAquamarine                = color(127, 255, 212); //0x7FFFD4
  const color vexClrAzure                     = color(240, 255, 255); //0xF0FFFF
  const color vexClrBeige                     = color(245, 245, 220); //0xF5F5DC
  const color vexClrBisque                    = color(255, 228, 196); //0xFFE4C4
  const color vexClrBlack                     = color(0, 0, 0);       //0x000000
  const color vexClrBlanchedAlmond            = color(255, 235, 205); //0xFFEBCD
  const color vexClrBlue                      = color(0, 0, 255);     //0x0000FF
  const color vexClrBlueViolet                = color(138, 43, 226);  //0x8A2BE2
  const color vexClrBrown                     = color(165, 42, 42);   //0xA52A2A
  const color vexClrBurlyWood                 = color(222, 184, 135); //0xDEB887
  const color vexClrCadetBlue                 = color(95, 158, 160);  //0x5F9EA0
  const color vexClrChartreuse                = color(127, 255, 0);   //0x7FFF00
  const color vexClrChocolate                 = color(210, 105, 30);  //0xD2691E
  const color vexClrCoral                     = color(255, 127, 80);  //0xFF7F50
  const color vexClrCornflowerBlue            = color(100, 149, 237); //0x6495ED
  const color vexClrCornsilk                  = color(255, 248, 220); //0xFFF8DC
  const color vexClrCrimson                   = color(220, 20, 60);   //0xDC143C
  const color vexClrCyan                      = color(0, 255, 255);   //0x00FFFF
  const color vexClrDarkBlue                  = color(0, 0, 139);     //0x00008B
  const color vexClrDarkCyan                  = color(0, 139, 139);   //0x008B8B
  const color vexClrDarkGoldenrod             = color(184, 134, 11);  //0xB8860B
  const color vexClrDarkGray                  = color(169, 169, 169); //0xA9A9A9
  const color vexClrDarkGreen                 = color(0, 100, 0);     //0x006400
  const color vexClrDarkKhaki                 = color(189, 183, 107); //0xBDB76B
  const color vexClrDarkMagenta               = color(139, 0, 139);   //0x8B008B
  const color vexClrDarkOliveGreen            = color(85, 107, 47);   //0x556B2F
  const color vexClrDarkOrange                = color(255, 140, 0);   //0xFF8C00
  const color vexClrDarkOrchid                = color(153, 50, 204);  //0x9932CC
  const color vexClrDarkRed                   = color(139, 0, 0);     //0x8B0000
  const color vexClrDarkSalmon                = color(233, 150, 122); //0xE9967A
  const color vexClrDarkSeaGreen              = color(143, 188, 143); //0x8FBC8F
  const color vexClrDarkSlateBlue             = color(72, 61, 139);   //0x483D8B
  const color vexClrDarkSlateGray             = color(47, 79, 79);    //0x2F4F4F
  const color vexClrDarkTurquoise             = color(0, 206, 209);   //0x00CED1
  const color vexClrDarkViolet                = color(148, 0, 211);   //0x9400D3
  const color vexClrDeepPink                  = color(255, 20, 147);  //0xFF1493
  const color vexClrDeepSkyBlue               = color(0, 191, 255);   //0x00BFFF
  const color vexClrDimGray                   = color(105, 105, 105); //0x696969
  const color vexClrDodgerBlue                = color(30, 144, 255);  //0x1E90FF
  const color vexClrFireBrick                 = color(178, 34, 34);   //0xB22222
  const color vexClrFloralWhite               = color(255, 250, 240); //0xFFFAF0
  const color vexClrForestGreen               = color(34, 139, 34);   //0x228B22
  const color vexClrFuchsia                   = color(255, 0, 255);   //0xFF00FF
  const color vexClrGainsboro                 = color(220, 220, 220); //0xDCDCDC
  const color vexClrGhostWhite                = color(248, 248, 255); //0xF8F8FF
  const color vexClrGold                      = color(255, 215, 0);   //0xFFD700
  const color vexClrGoldenrod                 = color(218, 165, 32);  //0xDAA520
  const color vexClrGray                      = color(128, 128, 128); //0x808080
  const color vexClrGreen                     = color(0, 128, 0);     //0x008000
  const color vexClrGreenYellow               = color(173, 255, 47);  //0xADFF2F
  const color vexClrHoneydew                  = color(240, 255, 240); //0xF0FFF0
  const color vexClrHotPink                   = color(255, 105, 180); //0xFF69B4
  const color vexClrIndianRed                 = color(205, 92, 92);   //0xCD5C5C
  const color vexClrIndigo                    = color(75, 0, 130);    //0x4B0082
  const color vexClrIvory                     = color(255, 255, 240); //0xFFFFF0
  const color vexClrKhaki                     = color(240, 230, 140); //0xF0E68C
  const color vexClrLavender                  = color(230, 230, 250); //0xE6E6FA
  const color vexClrLavenderBlush             = color(255, 240, 245); //0xFFF0F5
  const color vexClrLawnGreen                 = color(124, 252, 0);   //0x7CFC00
  const color vexClrLemonChiffon              = color(255, 250, 205); //0xFFFACD
  const color vexClrLightBlue                 = color(173, 216, 230); //0xADD8E6
  const color vexClrLightCoral                = color(240, 128, 128); //0xF08080
  const color vexClrLightCyan                 = color(224, 255, 255); //0xE0FFFF
  const color vexClrLightGoldenrodYellow      = color(250, 250, 210); //0xFAFAD2
  const color vexClrLightGreen                = color(144, 238, 144); //0x90EE90
  const color vexClrLightGrey                 = color(211, 211, 211); //0xD3D3D3
  const color vexClrLightPink                 = color(255, 182, 193); //0xFFB6C1
  const color vexClrLightSalmon               = color(255, 160, 122); //0xFFA07A
  const color vexClrLightSeaGreen             = color(32, 178, 170);  //0x20B2AA
  const color vexClrLightSkyBlue              = color(135, 206, 250); //0x87CEFA
  const color vexClrLightSlateGray            = color(119, 136, 153); //0x778899
  const color vexClrLightSteelBlue            = color(176, 196, 222); //0xB0C4DE
  const color vexClrLightYellow               = color(255, 255, 224); //0xFFFFE0
  const color vexClrLime                      = color(0, 255, 0);     //0x00FF00
  const color vexClrLimeGreen                 = color(50, 205, 50);   //0x32CD32
  const color vexClrLinen                     = color(250, 240, 230); //0xFAF0E6
  const color vexClrMagenta                   = color(255, 0, 255);   //0xFF00FF
  const color vexClrMaroon                    = color(128, 0, 0);     //0x800000
  const color vexClrMediumAquamarine          = color(102, 205, 170); //0x66CDAA
  const color vexClrMediumBlue                = color(0, 0, 205);     //0x0000CD
  const color vexClrMediumOrchid              = color(186, 85, 211);  //0xBA55D3
  const color vexClrMediumPurple              = color(147, 112, 219); //0x9370DB
  const color vexClrMediumSeaGreen            = color(60, 179, 113);  //0x3CB371
  const color vexClrMediumSlateBlue           = color(123, 104, 238); //0x7B68EE
  const color vexClrMediumSpringGreen         = color(0, 250, 154);   //0x00FA9A
  const color vexClrMediumTurquoise           = color(72, 209, 204);  //0x48D1CC
  const color vexClrMediumVioletRed           = color(199, 21, 133);  //0xC71585
  const color vexClrMidnightBlue              = color(25, 25, 112);   //0x191970
  const color vexClrMintCream                 = color(245, 255, 250); //0xF5FFFA
  const color vexClrMistyRose                 = color(255, 228, 225); //0xFFE4E1
  const color vexClrMoccasin                  = color(255, 228, 181); //0xFFE4B5
  const color vexClrNavajoWhite               = color(255, 222, 173); //0xFFDEAD
  const color vexClrNavy                      = color(0, 0, 128);     //0x000080
  const color vexClrOldLace                   = color(253, 245, 230); //0xFDF5E6
  const color vexClrOlive                     = color(128, 128, 0);   //0x808000
  const color vexClrOliveDrab                 = color(107, 142, 35);  //0x6B8E23
  const color vexClrOrange                    = color(255, 165, 0);   //0xFFA500
  const color vexClrOrangeRed                 = color(255, 69, 0);    //0xFF4500
  const color vexClrOrchid                    = color(218, 112, 214); //0xDA70D6
  const color vexClrPaleGoldenrod             = color(238, 232, 170); //0xEEE8AA
  const color vexClrPaleGreen                 = color(152, 251, 152); //0x98FB98
  const color vexClrPaleTurquoise             = color(175, 238, 238); //0xAFEEEE
  const color vexClrPaleVioletRed             = color(219, 112, 147); //0xDB7093
  const color vexClrPapayaWhip                = color(255, 239, 213); //0xFFEFD5
  const color vexClrPeachPuff                 = color(255, 239, 213); //0xFFDAB9
  const color vexClrPeru                      = color(205, 133, 63);  //0xCD853F
  const color vexClrPink                      = color(255, 192, 203); //0xFFC0CB
  const color vexClrPlum                      = color(221, 160, 221); //0xDDA0DD
  const color vexClrPowderBlue                = color(176, 224, 230); //0xB0E0E6
  const color vexClrPurple                    = color(128, 0, 128);   //0x800080
  const color vexClrRed                       = color(255, 0, 0);     //0xFF0000
  const color vexClrRosyBrown                 = color(188, 143, 143); //0xBC8F8F
  const color vexClrRoyalBlue                 = color(65, 105, 225);  //0x4169E1
  const color vexClrSaddleBrown               = color(139, 69, 19);   //0x8B4513
  const color vexClrSalmon                    = color(250, 128, 114); //0xFA8072
  const color vexClrSandyBrown                = color(244, 164, 96);  //0xF4A460
  const color vexClrSeaGreen                  = color(46, 139, 87);   //0x2E8B57
  const color vexClrSeashell                  = color(255, 245, 238); //0xFFF5EE
  const color vexClrSienna                    = color(160, 82, 45);   //0xA0522D
  const color vexClrSilver                    = color(192, 192, 192); //0xC0C0C0
  const color vexClrSkyBlue                   = color(135, 206, 235); //0x87CEEB
  const color vexClrSlateBlue                 = color(106, 90, 205);  //0x6A5ACD
  const color vexClrSlateGray                 = color(112, 128, 144); //0x708090
  const color vexClrSnow                      = color(255, 250, 250); //0xFFFAFA
  const color vexClrSpringGreen               = color(0, 255, 127);   //0x00FF7F
  const color vexClrSteelBlue                 = color(70, 130, 180);  //0x4682B4
  const color vexClrTan                       = color(210, 180, 140); //0xD2B48C
  const color vexClrTeal                      = color(0, 128, 128);   //0x008080
  const color vexClrThistle                   = color(216, 191, 216); //0xD8BFD8
  const color vexClrTomato                    = color(255, 99, 71);   //0xFF6347
  const color vexClrTurquoise                 = color(64, 224, 208);  //0x40E0D0
  const color vexClrViolet                    = color(238, 130, 238); //0xEE82EE
  const color vexClrWheat                     = color(245, 222, 179); //0xF5DEB3
  const color vexClrWhite                     = color(255, 255, 255); //0xFFFFFF
  const color vexClrWhiteSmoke                = color(245, 245, 245); //0xF5F5F5
  const color vexClrYellow                    = color(255, 255, 0);   //0xFFFF00
  const color vexClrYellowGreen               = color(154, 205, 50);  //0x9ACD32
#endif
#endif // COLORS_H