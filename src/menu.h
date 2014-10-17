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

#ifndef MENU_H
#define MENU_H
#include "charPutter.h"
#include "tiString.h"
#include <vector>
class Menu{
public: 
  Menu(CharPutter *cputt,TiString title,vector<TiString> choices);
  void reDisplay();
  void sendKey(SDL_keysym  k);  
  int getSelectedItem();
private:
  CharPutter *_cputt;
  TiString _title;
  vector<TiString> _choices; 
  int _currentSectedItem;
  int _currentOffset;
};


#endif