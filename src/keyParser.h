#ifndef KEY_PARSER_H
/*
  Copyright (c) 2014 Pierre Parent
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define KEY_PARSER_H
#include <SDL/SDL.h>

#define CONST_CHAR_STO '$'
#define CONST_CHAR_DIFFERENT '~'
#define CONST_CHAR_GREATEROREQUAL (char)(-100)
#define CONST_CHAR_DEGREE (char)(-101)
#define CONST_CHAR_EPOW10 (char)(-102)
#define CONST_CHAR_TRANSPOSE (char)(-103)
#define CONST_CHAR_SMALL_MINUS (char)(-104)
#define CONST_CHAR_PI (char)(-105)
#define CONST_CHAR_THETA (char)(-106)
#define CONST_CHAR_LUSER (char)(-123)
#define CONST_CHAR_SMALL4 (char)(-116)
#define CONST_CHAR_SMALL5 (char)(-117)
#define CONST_CHAR_SMALL6 (char)(-118)
#define CONST_CHAR_SMALL7 (char)(-119)
#define CONST_CHAR_SMALL8 (char)(-120)
#define CONST_CHAR_SMALL9 (char)(-121)
#define CONST_CHAR_LESSOREQUAL (char)(-122)

namespace keyParser {
bool isChar(SDL_keysym k);
int getChar(SDL_keysym k);
}



#endif
