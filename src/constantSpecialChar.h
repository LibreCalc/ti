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

#include <map>
#include <string>
#ifndef CONST_SPE_CHAR_H
#define CONST_SPE_CHAR_H
using namespace std;
enum specialChars{
  CONST_SPE_SIN=1000,
  CONST_SPE_IF,
  CONST_SPE_THEN,  
  CONST_SPE_ELSE,  
  CONST_SPE_END,  
  CONST_SPE_WHILE,  
  CONST_SPE_FOR,
  CONST_SPE_REPEAT,
  CONST_SPE_OUTPUT,
  CONST_SPE_GETKEY,
  CONST_SPE_CLEARHOME, 
  CONST_SPE_RANDINT,  
  CONST_SPE_AND,  
  CONST_SPE_OR,  
  CONST_SPE_GOTO,  
  CONST_SPE_LABEL,
  CONST_SPE_NOT,
  CONST_SPE_PAUSE,
  CONST_SPE_ANS,
  CONST_SPE_RAND,  
  CONST_SPE_INT,
  CONST_SPE_DELVAR,
  CONST_SPE_DISP,
  CONST_SPE_RETURN,
  CONST_SPE_MENU,
  CONST_SPE_DIM
};

extern map<specialChars,string> specialCharsText;
#endif