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
#define CONST_CHAR_LESSOREQUAL (char)(-101)
#define CONST_CHAR_DEGREE (char)(-101)
#define CONST_CHAR_EPOW10 (char)(-102)
#define CONST_CHAR_TRANSPOSE (char)(-103)
#define CONST_CHAR_SMALL_MINUS (char)(-104)
#define CONST_CHAR_PI (char)(-105)
#define CONST_CHAR_THETA (char)(-106)
#define CONST_CHAR_L1 (char)(-107)
#define CONST_CHAR_L2 (char)(-108)
#define CONST_CHAR_L3 (char)(-109)
#define CONST_CHAR_L4 (char)(-110)
#define CONST_CHAR_L5 (char)(-111)
#define CONST_CHAR_L6 (char)(-112)
#define CONST_CHAR_L7 (char)(-113)
#define CONST_CHAR_L8 (char)(-114)
#define CONST_CHAR_L9 (char)(-115)
#define CONST_CHAR_SMALL4 (char)(-116)

namespace keyParser {
bool isChar(SDL_keysym k);
int getChar(SDL_keysym k);
}



#endif
