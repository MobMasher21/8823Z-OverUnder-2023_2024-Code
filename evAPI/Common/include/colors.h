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

#include <sys/types.h>
#include "vex_color.h"

namespace evAPI
{
  //Custom colors
  extern const vex::color fieldGrey; //0x3C3C3C
  
  //rgb.txt
  
  extern const vex::color AliceBlue                 ; //0xF0F8FF
  extern const vex::color AntiqueWhite              ; //0xFAEBD7
  extern const vex::color Aqua                      ; //0x00FFFF
  extern const vex::color Aquamarine                ; //0x7FFFD4
  extern const vex::color Azure                     ; //0xF0FFFF
  extern const vex::color Beige                     ; //0xF5F5DC
  extern const vex::color Bisque                    ; //0xFFE4C4
  extern const vex::color Black                     ; //0x000000
  extern const vex::color BlanchedAlmond            ; //0xFFEBCD
  extern const vex::color Blue                      ; //0x0000FF
  extern const vex::color BlueViolet                ; //0x8A2BE2
  extern const vex::color Brown                     ; //0xA52A2A
  extern const vex::color BurlyWood                 ; //0xDEB887
  extern const vex::color CadetBlue                 ; //0x5F9EA0
  extern const vex::color Chartreuse                ; //0x7FFF00
  extern const vex::color Chocolate                 ; //0xD2691E
  extern const vex::color Coral                     ; //0xFF7F50
  extern const vex::color CornflowerBlue            ; //0x6495ED
  extern const vex::color Cornsilk                  ; //0xFFF8DC
  extern const vex::color Crimson                   ; //0xDC143C
  extern const vex::color Cyan                      ; //0x00FFFF
  extern const vex::color DarkBlue                  ; //0x00008B
  extern const vex::color DarkCyan                  ; //0x008B8B
  extern const vex::color DarkGoldenrod             ; //0xB8860B
  extern const vex::color DarkGray                  ; //0xA9A9A9
  extern const vex::color DarkGreen                 ; //0x006400
  extern const vex::color DarkKhaki                 ; //0xBDB76B
  extern const vex::color DarkMagenta               ; //0x8B008B
  extern const vex::color DarkOliveGreen            ; //0x556B2F
  extern const vex::color DarkOrange                ; //0xFF8C00
  extern const vex::color DarkOrchid                ; //0x9932CC
  extern const vex::color DarkRed                   ; //0x8B0000
  extern const vex::color DarkSalmon                ; //0xE9967A
  extern const vex::color DarkSeaGreen              ; //0x8FBC8F
  extern const vex::color DarkSlateBlue             ; //0x483D8B
  extern const vex::color DarkSlateGray             ; //0x2F4F4F
  extern const vex::color DarkTurquoise             ; //0x00CED1
  extern const vex::color DarkViolet                ; //0x9400D3
  extern const vex::color DeepPink                  ; //0xFF1493
  extern const vex::color DeepSkyBlue               ; //0x00BFFF
  extern const vex::color DimGray                   ; //0x696969
  extern const vex::color DodgerBlue                ; //0x1E90FF
  extern const vex::color FireBrick                 ; //0xB22222
  extern const vex::color FloralWhite               ; //0xFFFAF0
  extern const vex::color ForestGreen               ; //0x228B22
  extern const vex::color Fuchsia                   ; //0xFF00FF
  extern const vex::color Gainsboro                 ; //0xDCDCDC
  extern const vex::color GhostWhite                ; //0xF8F8FF
  extern const vex::color Gold                      ; //0xFFD700
  extern const vex::color Goldenrod                 ; //0xDAA520
  extern const vex::color Gray                      ; //0x808080
  extern const vex::color Green                     ; //0x008000
  extern const vex::color GreenYellow               ; //0xADFF2F
  extern const vex::color Honeydew                  ; //0xF0FFF0
  extern const vex::color HotPink                   ; //0xFF69B4
  extern const vex::color IndianRed                 ; //0xCD5C5C
  extern const vex::color Indigo                    ; //0x4B0082
  extern const vex::color Ivory                     ; //0xFFFFF0
  extern const vex::color Khaki                     ; //0xF0E68C
  extern const vex::color Lavender                  ; //0xE6E6FA
  extern const vex::color LavenderBlush             ; //0xFFF0F5
  extern const vex::color LawnGreen                 ; //0x7CFC00
  extern const vex::color LemonChiffon              ; //0xFFFACD
  extern const vex::color LightBlue                 ; //0xADD8E6
  extern const vex::color LightCoral                ; //0xF08080
  extern const vex::color LightCyan                 ; //0xE0FFFF
  extern const vex::color LightGoldenrodYellow      ; //0xFAFAD2
  extern const vex::color LightGreen                ; //0x90EE90
  extern const vex::color LightGrey                 ; //0xD3D3D3
  extern const vex::color LightPink                 ; //0xFFB6C1
  extern const vex::color LightSalmon               ; //0xFFA07A
  extern const vex::color LightSeaGreen             ; //0x20B2AA
  extern const vex::color LightSkyBlue              ; //0x87CEFA
  extern const vex::color LightSlateGray            ; //0x778899
  extern const vex::color LightSteelBlue            ; //0xB0C4DE
  extern const vex::color LightYellow               ; //0xFFFFE0
  extern const vex::color Lime                      ; //0x00FF00
  extern const vex::color LimeGreen                 ; //0x32CD32
  extern const vex::color Linen                     ; //0xFAF0E6
  extern const vex::color Magenta                   ; //0xFF00FF
  extern const vex::color Maroon                    ; //0x800000
  extern const vex::color MediumAquamarine          ; //0x66CDAA
  extern const vex::color MediumBlue                ; //0x0000CD
  extern const vex::color MediumOrchid              ; //0xBA55D3
  extern const vex::color MediumPurple              ; //0x9370DB
  extern const vex::color MediumSeaGreen            ; //0x3CB371
  extern const vex::color MediumSlateBlue           ; //0x7B68EE
  extern const vex::color MediumSpringGreen         ; //0x00FA9A
  extern const vex::color MediumTurquoise           ; //0x48D1CC
  extern const vex::color MediumVioletRed           ; //0xC71585
  extern const vex::color MidnightBlue              ; //0x191970
  extern const vex::color MintCream                 ; //0xF5FFFA
  extern const vex::color MistyRose                 ; //0xFFE4E1
  extern const vex::color Moccasin                  ; //0xFFE4B5
  extern const vex::color NavajoWhite               ; //0xFFDEAD
  extern const vex::color Navy                      ; //0x000080
  extern const vex::color OldLace                   ; //0xFDF5E6
  extern const vex::color Olive                     ; //0x808000
  extern const vex::color OliveDrab                 ; //0x6B8E23
  extern const vex::color Orange                    ; //0xFFA500
  extern const vex::color OrangeRed                 ; //0xFF4500
  extern const vex::color Orchid                    ; //0xDA70D6
  extern const vex::color PaleGoldenrod             ; //0xEEE8AA
  extern const vex::color PaleGreen                 ; //0x98FB98
  extern const vex::color PaleTurquoise             ; //0xAFEEEE
  extern const vex::color PaleVioletRed             ; //0xDB7093
  extern const vex::color PapayaWhip                ; //0xFFEFD5
  extern const vex::color PeachPuff                 ; //0xFFDAB9
  extern const vex::color Peru                      ; //0xCD853F
  extern const vex::color Pink                      ; //0xFFC0CB
  extern const vex::color Plum                      ; //0xDDA0DD
  extern const vex::color PowderBlue                ; //0xB0E0E6
  extern const vex::color Purple                    ; //0x800080
  extern const vex::color Red                       ; //0xFF0000
  extern const vex::color RosyBrown                 ; //0xBC8F8F
  extern const vex::color RoyalBlue                 ; //0x4169E1
  extern const vex::color SaddleBrown               ; //0x8B4513
  extern const vex::color Salmon                    ; //0xFA8072
  extern const vex::color SandyBrown                ; //0xF4A460
  extern const vex::color SeaGreen                  ; //0x2E8B57
  extern const vex::color Seashell                  ; //0xFFF5EE
  extern const vex::color Sienna                    ; //0xA0522D
  extern const vex::color Silver                    ; //0xC0C0C0
  extern const vex::color SkyBlue                   ; //0x87CEEB
  extern const vex::color SlateBlue                 ; //0x6A5ACD
  extern const vex::color SlateGray                 ; //0x708090
  extern const vex::color Snow                      ; //0xFFFAFA
  extern const vex::color SpringGreen               ; //0x00FF7F
  extern const vex::color SteelBlue                 ; //0x4682B4
  extern const vex::color Tan                       ; //0xD2B48C
  extern const vex::color Teal                      ; //0x008080
  extern const vex::color Thistle                   ; //0xD8BFD8
  extern const vex::color Tomato                    ; //0xFF6347
  extern const vex::color Turquoise                 ; //0x40E0D0
  extern const vex::color Violet                    ; //0xEE82EE
  extern const vex::color Wheat                     ; //0xF5DEB3
  extern const vex::color White                     ; //0xFFFFFF
  extern const vex::color WhiteSmoke                ; //0xF5F5F5
  extern const vex::color Yellow                    ; //0xFFFF00
  extern const vex::color YellowGreen               ; //0x9ACD32
}

#endif // COLORS_H
