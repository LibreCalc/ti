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

#include "charPutter.h"

#ifndef Y_EQUALS_MENU
#define Y_EQUALS_MENU
#include <string>
#include "tiString.h"
#include "tiConfig.h"

using namespace std;

class YEqualsMenu{
public:
  YEqualsMenu(CharPutter *putt,TiConfig *conf);
  void reDisplay();
  void blinkCursor();
  void sendKey(SDL_keysym k);
  TiString getFirstEq();
private:
  void sendChar(int c);
  void rmChar();
  void changeEqu(bool up);
  void changeCursorPos(bool left);
  TiString & getEqu(int no);
  int getPointerX();
  int getPointerY();  
  CharPutter *_putt;
  TiConfig * _conf;
  int _currentEqu;
  int _currentCursPos;
  int _currentDisplayoffset;
  bool _isCursorBlinked;
  TiString _equ1;
  TiString _equ2;
  TiString _equ3;
  TiString _equ4;  
};






#endif