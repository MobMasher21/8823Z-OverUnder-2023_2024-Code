/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       colors.hpp                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      11 Nov 2023                                               */
/*    Description:  Redefines all the colors in "v5_color.h" so they use the  */
/*                  vex color class.                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef COLORS_H
#define COLORS_H

#include "vex_color.h"
#include "evAPISettings.h"

//Undefine the color objects if REDEFINE_COLORS is set
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
#endif

namespace evAPI
{
  //Custom colors
  extern const vex::color fieldGrey;                 //0x003C3C3C
  extern const vex::color vexDisplayBackgroundDark;  //0x15171a

  //rgb.txt
  #if REDEFINE_COLORS
    extern const vex::color ClrAliceBlue                 ;//0xF0F8FF
    extern const vex::color ClrAntiqueWhite              ;//0xFAEBD7
    extern const vex::color ClrAqua                      ;//0x00FFFF
    extern const vex::color ClrAquamarine                ;//0x7FFFD4
    extern const vex::color ClrAzure                     ;//0xF0FFFF
    extern const vex::color ClrBeige                     ;//0xF5F5DC
    extern const vex::color ClrBisque                    ;//0xFFE4C4
    extern const vex::color ClrBlack                     ;//0x000000
    extern const vex::color ClrBlanchedAlmond            ;//0xFFEBCD
    extern const vex::color ClrBlue                      ;//0x0000FF
    extern const vex::color ClrBlueViolet                ;//0x8A2BE2
    extern const vex::color ClrBrown                     ;//0xA52A2A
    extern const vex::color ClrBurlyWood                 ;//0xDEB887
    extern const vex::color ClrCadetBlue                 ;//0x5F9EA0
    extern const vex::color ClrChartreuse                ;//0x7FFF00
    extern const vex::color ClrChocolate                 ;//0xD2691E
    extern const vex::color ClrCoral                     ;//0xFF7F50
    extern const vex::color ClrCornflowerBlue            ;//0x6495ED
    extern const vex::color ClrCornsilk                  ;//0xFFF8DC
    extern const vex::color ClrCrimson                   ;//0xDC143C
    extern const vex::color ClrCyan                      ;//0x00FFFF
    extern const vex::color ClrDarkBlue                  ;//0x00008B
    extern const vex::color ClrDarkCyan                  ;//0x008B8B
    extern const vex::color ClrDarkGoldenrod             ;//0xB8860B
    extern const vex::color ClrDarkGray                  ;//0xA9A9A9
    extern const vex::color ClrDarkGreen                 ;//0x006400
    extern const vex::color ClrDarkKhaki                 ;//0xBDB76B
    extern const vex::color ClrDarkMagenta               ;//0x8B008B
    extern const vex::color ClrDarkOliveGreen            ;//0x556B2F
    extern const vex::color ClrDarkOrange                ;//0xFF8C00
    extern const vex::color ClrDarkOrchid                ;//0x9932CC
    extern const vex::color ClrDarkRed                   ;//0x8B0000
    extern const vex::color ClrDarkSalmon                ;//0xE9967A
    extern const vex::color ClrDarkSeaGreen              ;//0x8FBC8F
    extern const vex::color ClrDarkSlateBlue             ;//0x483D8B
    extern const vex::color ClrDarkSlateGray             ;//0x2F4F4F
    extern const vex::color ClrDarkTurquoise             ;//0x00CED1
    extern const vex::color ClrDarkViolet                ;//0x9400D3
    extern const vex::color ClrDeepPink                  ;//0xFF1493
    extern const vex::color ClrDeepSkyBlue               ;//0x00BFFF
    extern const vex::color ClrDimGray                   ;//0x696969
    extern const vex::color ClrDodgerBlue                ;//0x1E90FF
    extern const vex::color ClrFireBrick                 ;//0xB22222
    extern const vex::color ClrFloralWhite               ;//0xFFFAF0
    extern const vex::color ClrForestGreen               ;//0x228B22
    extern const vex::color ClrFuchsia                   ;//0xFF00FF
    extern const vex::color ClrGainsboro                 ;//0xDCDCDC
    extern const vex::color ClrGhostWhite                ;//0xF8F8FF
    extern const vex::color ClrGold                      ;//0xFFD700
    extern const vex::color ClrGoldenrod                 ;//0xDAA520
    extern const vex::color ClrGray                      ;//0x808080
    extern const vex::color ClrGreen                     ;//0x008000
    extern const vex::color ClrGreenYellow               ;//0xADFF2F
    extern const vex::color ClrHoneydew                  ;//0xF0FFF0
    extern const vex::color ClrHotPink                   ;//0xFF69B4
    extern const vex::color ClrIndianRed                 ;//0xCD5C5C
    extern const vex::color ClrIndigo                    ;//0x4B0082
    extern const vex::color ClrIvory                     ;//0xFFFFF0
    extern const vex::color ClrKhaki                     ;//0xF0E68C
    extern const vex::color ClrLavender                  ;//0xE6E6FA
    extern const vex::color ClrLavenderBlush             ;//0xFFF0F5
    extern const vex::color ClrLawnGreen                 ;//0x7CFC00
    extern const vex::color ClrLemonChiffon              ;//0xFFFACD
    extern const vex::color ClrLightBlue                 ;//0xADD8E6
    extern const vex::color ClrLightCoral                ;//0xF08080
    extern const vex::color ClrLightCyan                 ;//0xE0FFFF
    extern const vex::color ClrLightGoldenrodYellow      ;//0xFAFAD2
    extern const vex::color ClrLightGreen                ;//0x90EE90
    extern const vex::color ClrLightGrey                 ;//0xD3D3D3
    extern const vex::color ClrLightPink                 ;//0xFFB6C1
    extern const vex::color ClrLightSalmon               ;//0xFFA07A
    extern const vex::color ClrLightSeaGreen             ;//0x20B2AA
    extern const vex::color ClrLightSkyBlue              ;//0x87CEFA
    extern const vex::color ClrLightSlateGray            ;//0x778899
    extern const vex::color ClrLightSteelBlue            ;//0xB0C4DE
    extern const vex::color ClrLightYellow               ;//0xFFFFE0
    extern const vex::color ClrLime                      ;//0x00FF00
    extern const vex::color ClrLimeGreen                 ;//0x32CD32
    extern const vex::color ClrLinen                     ;//0xFAF0E6
    extern const vex::color ClrMagenta                   ;//0xFF00FF
    extern const vex::color ClrMaroon                    ;//0x800000
    extern const vex::color ClrMediumAquamarine          ;//0x66CDAA
    extern const vex::color ClrMediumBlue                ;//0x0000CD
    extern const vex::color ClrMediumOrchid              ;//0xBA55D3
    extern const vex::color ClrMediumPurple              ;//0x9370DB
    extern const vex::color ClrMediumSeaGreen            ;//0x3CB371
    extern const vex::color ClrMediumSlateBlue           ;//0x7B68EE
    extern const vex::color ClrMediumSpringGreen         ;//0x00FA9A
    extern const vex::color ClrMediumTurquoise           ;//0x48D1CC
    extern const vex::color ClrMediumVioletRed           ;//0xC71585
    extern const vex::color ClrMidnightBlue              ;//0x191970
    extern const vex::color ClrMintCream                 ;//0xF5FFFA
    extern const vex::color ClrMistyRose                 ;//0xFFE4E1
    extern const vex::color ClrMoccasin                  ;//0xFFE4B5
    extern const vex::color ClrNavajoWhite               ;//0xFFDEAD
    extern const vex::color ClrNavy                      ;//0x000080
    extern const vex::color ClrOldLace                   ;//0xFDF5E6
    extern const vex::color ClrOlive                     ;//0x808000
    extern const vex::color ClrOliveDrab                 ;//0x6B8E23
    extern const vex::color ClrOrange                    ;//0xFFA500
    extern const vex::color ClrOrangeRed                 ;//0xFF4500
    extern const vex::color ClrOrchid                    ;//0xDA70D6
    extern const vex::color ClrPaleGoldenrod             ;//0xEEE8AA
    extern const vex::color ClrPaleGreen                 ;//0x98FB98
    extern const vex::color ClrPaleTurquoise             ;//0xAFEEEE
    extern const vex::color ClrPaleVioletRed             ;//0xDB7093
    extern const vex::color ClrPapayaWhip                ;//0xFFEFD5
    extern const vex::color ClrPeachPuff                 ;//0xFFDAB9
    extern const vex::color ClrPeru                      ;//0xCD853F
    extern const vex::color ClrPink                      ;//0xFFC0CB
    extern const vex::color ClrPlum                      ;//0xDDA0DD
    extern const vex::color ClrPowderBlue                ;//0xB0E0E6
    extern const vex::color ClrPurple                    ;//0x800080
    extern const vex::color ClrRed                       ;//0xFF0000
    extern const vex::color ClrRosyBrown                 ;//0xBC8F8F
    extern const vex::color ClrRoyalBlue                 ;//0x4169E1
    extern const vex::color ClrSaddleBrown               ;//0x8B4513
    extern const vex::color ClrSalmon                    ;//0xFA8072
    extern const vex::color ClrSandyBrown                ;//0xF4A460
    extern const vex::color ClrSeaGreen                  ;//0x2E8B57
    extern const vex::color ClrSeashell                  ;//0xFFF5EE
    extern const vex::color ClrSienna                    ;//0xA0522D
    extern const vex::color ClrSilver                    ;//0xC0C0C0
    extern const vex::color ClrSkyBlue                   ;//0x87CEEB
    extern const vex::color ClrSlateBlue                 ;//0x6A5ACD
    extern const vex::color ClrSlateGray                 ;//0x708090
    extern const vex::color ClrSnow                      ;//0xFFFAFA
    extern const vex::color ClrSpringGreen               ;//0x00FF7F
    extern const vex::color ClrSteelBlue                 ;//0x4682B4
    extern const vex::color ClrTan                       ;//0xD2B48C
    extern const vex::color ClrTeal                      ;//0x008080
    extern const vex::color ClrThistle                   ;//0xD8BFD8
    extern const vex::color ClrTomato                    ;//0xFF6347
    extern const vex::color ClrTurquoise                 ;//0x40E0D0
    extern const vex::color ClrViolet                    ;//0xEE82EE
    extern const vex::color ClrWheat                     ;//0xF5DEB3
    extern const vex::color ClrWhite                     ;//0xFFFFFF
    extern const vex::color ClrWhiteSmoke                ;//0xF5F5F5
    extern const vex::color ClrYellow                    ;//0xFFFF00
    extern const vex::color ClrYellowGreen               ;//0x9ACD32
  #else
    extern const vex::color vexClrAliceBlue                 ;//0xF0F8FF
    extern const vex::color vexClrAntiqueWhite              ;//0xFAEBD7
    extern const vex::color vexClrAqua                      ;//0x00FFFF
    extern const vex::color vexClrAquamarine                ;//0x7FFFD4
    extern const vex::color vexClrAzure                     ;//0xF0FFFF
    extern const vex::color vexClrBeige                     ;//0xF5F5DC
    extern const vex::color vexClrBisque                    ;//0xFFE4C4
    extern const vex::color vexClrBlack                     ;//0x000000
    extern const vex::color vexClrBlanchedAlmond            ;//0xFFEBCD
    extern const vex::color vexClrBlue                      ;//0x0000FF
    extern const vex::color vexClrBlueViolet                ;//0x8A2BE2
    extern const vex::color vexClrBrown                     ;//0xA52A2A
    extern const vex::color vexClrBurlyWood                 ;//0xDEB887
    extern const vex::color vexClrCadetBlue                 ;//0x5F9EA0
    extern const vex::color vexClrChartreuse                ;//0x7FFF00
    extern const vex::color vexClrChocolate                 ;//0xD2691E
    extern const vex::color vexClrCoral                     ;//0xFF7F50
    extern const vex::color vexClrCornflowerBlue            ;//0x6495ED
    extern const vex::color vexClrCornsilk                  ;//0xFFF8DC
    extern const vex::color vexClrCrimson                   ;//0xDC143C
    extern const vex::color vexClrCyan                      ;//0x00FFFF
    extern const vex::color vexClrDarkBlue                  ;//0x00008B
    extern const vex::color vexClrDarkCyan                  ;//0x008B8B
    extern const vex::color vexClrDarkGoldenrod             ;//0xB8860B
    extern const vex::color vexClrDarkGray                  ;//0xA9A9A9
    extern const vex::color vexClrDarkGreen                 ;//0x006400
    extern const vex::color vexClrDarkKhaki                 ;//0xBDB76B
    extern const vex::color vexClrDarkMagenta               ;//0x8B008B
    extern const vex::color vexClrDarkOliveGreen            ;//0x556B2F
    extern const vex::color vexClrDarkOrange                ;//0xFF8C00
    extern const vex::color vexClrDarkOrchid                ;//0x9932CC
    extern const vex::color vexClrDarkRed                   ;//0x8B0000
    extern const vex::color vexClrDarkSalmon                ;//0xE9967A
    extern const vex::color vexClrDarkSeaGreen              ;//0x8FBC8F
    extern const vex::color vexClrDarkSlateBlue             ;//0x483D8B
    extern const vex::color vexClrDarkSlateGray             ;//0x2F4F4F
    extern const vex::color vexClrDarkTurquoise             ;//0x00CED1
    extern const vex::color vexClrDarkViolet                ;//0x9400D3
    extern const vex::color vexClrDeepPink                  ;//0xFF1493
    extern const vex::color vexClrDeepSkyBlue               ;//0x00BFFF
    extern const vex::color vexClrDimGray                   ;//0x696969
    extern const vex::color vexClrDodgerBlue                ;//0x1E90FF
    extern const vex::color vexClrFireBrick                 ;//0xB22222
    extern const vex::color vexClrFloralWhite               ;//0xFFFAF0
    extern const vex::color vexClrForestGreen               ;//0x228B22
    extern const vex::color vexClrFuchsia                   ;//0xFF00FF
    extern const vex::color vexClrGainsboro                 ;//0xDCDCDC
    extern const vex::color vexClrGhostWhite                ;//0xF8F8FF
    extern const vex::color vexClrGold                      ;//0xFFD700
    extern const vex::color vexClrGoldenrod                 ;//0xDAA520
    extern const vex::color vexClrGray                      ;//0x808080
    extern const vex::color vexClrGreen                     ;//0x008000
    extern const vex::color vexClrGreenYellow               ;//0xADFF2F
    extern const vex::color vexClrHoneydew                  ;//0xF0FFF0
    extern const vex::color vexClrHotPink                   ;//0xFF69B4
    extern const vex::color vexClrIndianRed                 ;//0xCD5C5C
    extern const vex::color vexClrIndigo                    ;//0x4B0082
    extern const vex::color vexClrIvory                     ;//0xFFFFF0
    extern const vex::color vexClrKhaki                     ;//0xF0E68C
    extern const vex::color vexClrLavender                  ;//0xE6E6FA
    extern const vex::color vexClrLavenderBlush             ;//0xFFF0F5
    extern const vex::color vexClrLawnGreen                 ;//0x7CFC00
    extern const vex::color vexClrLemonChiffon              ;//0xFFFACD
    extern const vex::color vexClrLightBlue                 ;//0xADD8E6
    extern const vex::color vexClrLightCoral                ;//0xF08080
    extern const vex::color vexClrLightCyan                 ;//0xE0FFFF
    extern const vex::color vexClrLightGoldenrodYellow      ;//0xFAFAD2
    extern const vex::color vexClrLightGreen                ;//0x90EE90
    extern const vex::color vexClrLightGrey                 ;//0xD3D3D3
    extern const vex::color vexClrLightPink                 ;//0xFFB6C1
    extern const vex::color vexClrLightSalmon               ;//0xFFA07A
    extern const vex::color vexClrLightSeaGreen             ;//0x20B2AA
    extern const vex::color vexClrLightSkyBlue              ;//0x87CEFA
    extern const vex::color vexClrLightSlateGray            ;//0x778899
    extern const vex::color vexClrLightSteelBlue            ;//0xB0C4DE
    extern const vex::color vexClrLightYellow               ;//0xFFFFE0
    extern const vex::color vexClrLime                      ;//0x00FF00
    extern const vex::color vexClrLimeGreen                 ;//0x32CD32
    extern const vex::color vexClrLinen                     ;//0xFAF0E6
    extern const vex::color vexClrMagenta                   ;//0xFF00FF
    extern const vex::color vexClrMaroon                    ;//0x800000
    extern const vex::color vexClrMediumAquamarine          ;//0x66CDAA
    extern const vex::color vexClrMediumBlue                ;//0x0000CD
    extern const vex::color vexClrMediumOrchid              ;//0xBA55D3
    extern const vex::color vexClrMediumPurple              ;//0x9370DB
    extern const vex::color vexClrMediumSeaGreen            ;//0x3CB371
    extern const vex::color vexClrMediumSlateBlue           ;//0x7B68EE
    extern const vex::color vexClrMediumSpringGreen         ;//0x00FA9A
    extern const vex::color vexClrMediumTurquoise           ;//0x48D1CC
    extern const vex::color vexClrMediumVioletRed           ;//0xC71585
    extern const vex::color vexClrMidnightBlue              ;//0x191970
    extern const vex::color vexClrMintCream                 ;//0xF5FFFA
    extern const vex::color vexClrMistyRose                 ;//0xFFE4E1
    extern const vex::color vexClrMoccasin                  ;//0xFFE4B5
    extern const vex::color vexClrNavajoWhite               ;//0xFFDEAD
    extern const vex::color vexClrNavy                      ;//0x000080
    extern const vex::color vexClrOldLace                   ;//0xFDF5E6
    extern const vex::color vexClrOlive                     ;//0x808000
    extern const vex::color vexClrOliveDrab                 ;//0x6B8E23
    extern const vex::color vexClrOrange                    ;//0xFFA500
    extern const vex::color vexClrOrangeRed                 ;//0xFF4500
    extern const vex::color vexClrOrchid                    ;//0xDA70D6
    extern const vex::color vexClrPaleGoldenrod             ;//0xEEE8AA
    extern const vex::color vexClrPaleGreen                 ;//0x98FB98
    extern const vex::color vexClrPaleTurquoise             ;//0xAFEEEE
    extern const vex::color vexClrPaleVioletRed             ;//0xDB7093
    extern const vex::color vexClrPapayaWhip                ;//0xFFEFD5
    extern const vex::color vexClrPeachPuff                 ;//0xFFDAB9
    extern const vex::color vexClrPeru                      ;//0xCD853F
    extern const vex::color vexClrPink                      ;//0xFFC0CB
    extern const vex::color vexClrPlum                      ;//0xDDA0DD
    extern const vex::color vexClrPowderBlue                ;//0xB0E0E6
    extern const vex::color vexClrPurple                    ;//0x800080
    extern const vex::color vexClrRed                       ;//0xFF0000
    extern const vex::color vexClrRosyBrown                 ;//0xBC8F8F
    extern const vex::color vexClrRoyalBlue                 ;//0x4169E1
    extern const vex::color vexClrSaddleBrown               ;//0x8B4513
    extern const vex::color vexClrSalmon                    ;//0xFA8072
    extern const vex::color vexClrSandyBrown                ;//0xF4A460
    extern const vex::color vexClrSeaGreen                  ;//0x2E8B57
    extern const vex::color vexClrSeashell                  ;//0xFFF5EE
    extern const vex::color vexClrSienna                    ;//0xA0522D
    extern const vex::color vexClrSilver                    ;//0xC0C0C0
    extern const vex::color vexClrSkyBlue                   ;//0x87CEEB
    extern const vex::color vexClrSlateBlue                 ;//0x6A5ACD
    extern const vex::color vexClrSlateGray                 ;//0x708090
    extern const vex::color vexClrSnow                      ;//0xFFFAFA
    extern const vex::color vexClrSpringGreen               ;//0x00FF7F
    extern const vex::color vexClrSteelBlue                 ;//0x4682B4
    extern const vex::color vexClrTan                       ;//0xD2B48C
    extern const vex::color vexClrTeal                      ;//0x008080
    extern const vex::color vexClrThistle                   ;//0xD8BFD8
    extern const vex::color vexClrTomato                    ;//0xFF6347
    extern const vex::color vexClrTurquoise                 ;//0x40E0D0
    extern const vex::color vexClrViolet                    ;//0xEE82EE
    extern const vex::color vexClrWheat                     ;//0xF5DEB3
    extern const vex::color vexClrWhite                     ;//0xFFFFFF
    extern const vex::color vexClrWhiteSmoke                ;//0xF5F5F5
    extern const vex::color vexClrYellow                    ;//0xFFFF00
    extern const vex::color vexClrYellowGreen               ;//0x9ACD32
  #endif

} // namespace evAPI

#endif // COLORS_H