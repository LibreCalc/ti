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

#ifndef CURVE_RANGE_EDITOR
#define CURVE_RANGE_EDITOR

#include "charPutter.h"
#include "tiConfig.h"

/**
 * @brief Cette classe gére le menu qui permet de définir le RANGE pour le courbes
 * 		(Xmin Xmax, Ymin, Ymax ect..)
 */

class CurveRangeEditor{
public:
  CurveRangeEditor(CharPutter *putt,TiConfig *conf);
  void reDisplay();
  void loadVariables();
  void writeVariables();
  void blinkCursor();
  void sendKey(SDL_keysym k);
private:
  void sendChar(int c);
  void rmChar();
  CharPutter *_putt;
  TiConfig * _conf;
  int _currentLine;
  int _currentCursPosInStr;
  bool _isCursorBlinked;
  
  vector<string> _editedLines; 
};

#endif