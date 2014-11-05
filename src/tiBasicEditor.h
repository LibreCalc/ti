#ifndef TI_BASIC_EDITOR
#define TI_BASIC_EDITOR

#include <vector>
#include "tiString.h"
#include "charPutter.h"
#include "tiConfig.h"
#include "menu.h"

using namespace std;
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


class TiBasicEditor
{
  
  public:
  TiBasicEditor(CharPutter *putt,TiConfig *conf);
  void reDisplay();
  void blinkCursor();
  void sendKey(SDL_keysym k);
  void setProgramm(vector<TiString> program, string loc);
  void saveProgram();
private:
  void sendChar(int c);
  void rmChar();
  void addLine();
  void changeLine(bool up);
  void changeCursorPos(bool left);
  int getPointerX();
  int getPointerY(); 
  
  
  
  CharPutter *_putt;
  TiConfig * _conf;
  int _currentLine;
  int _currentCursPos;
  int _currentDisplayoffset;
  bool _isCursorBlinked;
  
  vector<TiString> _currentProgram;
  
  Menu *_specialsCommandsMenu;
  bool _isInSpecialCommandsMenu;
  
  string _programFileLoc;
  
};








#endif