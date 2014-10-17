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
#include "tiString.h"

#ifndef MAIN_SCREEN_MENU
#define MAIN_SCREEN_MENU
#include <string>
#include "tiConfig.h"

class MainScreen
{
public:
  MainScreen(CharPutter *putt,TiConfig &conf);
  void reDisplay();
  void blinkCursor();
  void sendKey(SDL_keysym  k);
  void setBuffer(string s);
private:
  void calc();
  void sendChar(int c);
  void rmChar();
  void changeCursorPos(bool left);
  int getPointerX();
  int getPointerY();
  
  TiConfig &_conf;
  CharPutter *_putt;
  int _currentCursPos;
  bool _isCursorBlinked;
  TiString _currString;
  TiString _previousString;
  string _buff;
  int currentStringBegin;
  int _currentDisplayoffset;
};

#endif