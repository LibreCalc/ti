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

#include "menu.h"
#include <iostream>

Menu::Menu(CharPutter* putt, TiString title, vector< TiString > choices)
{
_cputt=putt;
_currentOffset=0;
_currentSectedItem=0;
_title=title;
_choices=choices;
}

void Menu::reDisplay()
{
_cputt->clear();
_cputt->putString(_title.toStdString(),1,1,true);
for (int i=_currentOffset;i<_currentOffset+7;i++)
    {
      if (_choices.size()>i)
      {
	char tmp[5];
	sprintf(tmp,"%d:",i+1);
	TiString tiTmp;
	tiTmp.push_back(string(tmp));
	tiTmp=tiTmp+_choices[i];
	_cputt->putString(tiTmp.toStdString(),1,i-_currentOffset+2);
	if (_currentSectedItem==i)
	{
	  _cputt->blink(1,i-_currentOffset+2);
	  _cputt->blink(2,i-_currentOffset+2);	  
	}
      }
    }
    _cputt->refreshScreen();
}

void Menu::sendKey(SDL_keysym k1)
{
  
  SDLKey k=k1.sym;
  
	  switch (k)
		    {
		   case SDLK_UP:
		      if (_currentSectedItem>0)
			_currentSectedItem--;
		      break;
		   case SDLK_DOWN:
		      if (_choices.size()-1>_currentSectedItem)
			_currentSectedItem++;
		      break;   
		      
		    }
		    if (_currentOffset>_currentSectedItem)
		      _currentOffset=_currentSectedItem;
		    if (_currentOffset<_currentSectedItem-6)
		      _currentOffset=_currentSectedItem-6;		    
		    reDisplay();
}

int Menu::getSelectedItem()
{
return _currentSectedItem;
}
