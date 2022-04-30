#pragma once

#include "bn_sprite_font.h"
#include "bn_sprite_items_font_variable_8x8_creepy_castle.h"
#include "bn_utf8_characters_map_ref.h"

namespace crecat::font
{

inline constexpr int8_t variable_8x8_creepy_castle_char_widths[] = {
    3, // 32
    3, // 33 !
    4, // 34 "
    6, // 35 #
    6, // 36 $
    6, // 37 %
    7, // 38 &
    3, // 39 '
    4, // 40 (
    4, // 41 )
    4, // 42 *
    6, // 43 +
    3, // 44 ,
    6, // 45 -
    3, // 46 .
    6, // 47 /
    6, // 48 0
    6, // 49 1
    6, // 50 2
    6, // 51 3
    6, // 52 4
    6, // 53 5
    6, // 54 6
    6, // 55 7
    6, // 56 8
    6, // 57 9
    3, // 58 :
    3, // 59 ;
    4, // 60 <
    6, // 61 =
    4, // 62 >
    7, // 63 ?
    7, // 64 @
    6, // 65 A
    6, // 66 B
    6, // 67 C
    6, // 68 D
    6, // 69 E
    6, // 70 F
    6, // 71 G
    6, // 72 H
    5, // 73 I
    6, // 74 J
    6, // 75 K
    6, // 76 L
    7, // 77 M
    6, // 78 N
    6, // 79 O
    6, // 80 P
    7, // 81 Q
    6, // 82 R
    6, // 83 S
    7, // 84 T
    6, // 85 U
    6, // 86 V
    7, // 87 W
    6, // 88 X
    6, // 89 Y
    6, // 90 Z
    3, // 91 [
    6, // 92
    3, // 93 ]
    6, // 94 ^
    6, // 95 _
    4, // 96 `
    6, // 97 a
    5, // 98 b
    4, // 99 c
    5, // 100 d
    5, // 101 e
    4, // 102 f
    5, // 103 g
    5, // 104 h
    2, // 105 i
    3, // 106 j
    4, // 107 k
    3, // 108 l
    6, // 109 m
    4, // 110 n
    5, // 111 o
    5, // 112 p
    5, // 113 q
    4, // 114 r
    5, // 115 s
    4, // 116 t
    5, // 117 u
    6, // 118 v
    6, // 119 w
    5, // 120 x
    5, // 121 y
    5, // 122 z
    4, // 123 {
    3, // 124 |
    4, // 125 }
    7, // 126 ~
};

inline constexpr bn::sprite_font variable_8x8_creepy_castle(bn::sprite_items::font_variable_8x8_creepy_castle,
                                                            bn::utf8_characters_map_ref(),
                                                            variable_8x8_creepy_castle_char_widths);

} // namespace crecat::font
