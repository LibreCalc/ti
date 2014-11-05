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
_isMultipleMenu=false;
}


Menu::Menu(CharPutter* cputt, vector< TiString > title, vector< vector< TiString > > choices)
{
_cputt=cputt;
_currentOffset=0;
_currentSectedItem=0;
_isMultipleMenu=true;
_multipleChoices=choices;
_multipleTitles=title;
if (title.size()==0 or choices.size()==0)
  return;
_title=title[0];
_choices=choices[0];
_selectedTitle=0;
}

void Menu::reDisplay()
{
_cputt->clear();
if (!_isMultipleMenu)
{
_cputt->putString(_title.toStdString(),1,1,true);
}
else
{
  int x=1;
  for (int i=0;i<_multipleTitles.size();i++)
  {
  _cputt->putString(_multipleTitles[i].toStdString(),x,1,_selectedTitle==i);
  x=x+_multipleTitles[i].size()+1;
  }
}
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
		   case SDLK_LEFT:
		     changeTitle(true);
		     break;
		   case SDLK_RIGHT:
		     changeTitle(false);
		     break;		      
		    }
		    if (_currentOffset>_currentSectedItem)
		      _currentOffset=_currentSectedItem;
		    if (_currentOffset<_currentSectedItem-6)
		      _currentOffset=_currentSectedItem-6;		    
		    reDisplay();
}

void Menu::changeTitle(bool left)
{
    if (!_isMultipleMenu)
        return;
    if (left)
    {
        if (_selectedTitle>0)
        {
            _selectedTitle--;
            _currentSectedItem=0;
        }
    }
    else
    {
        if (_selectedTitle<_multipleTitles.size()-1)
        {
            _selectedTitle++;
            _currentSectedItem=0;
        }
    }
    _choices=_multipleChoices[_selectedTitle];
    reDisplay();
}

int Menu::getSelectedItem()
{
return _currentSectedItem;
}

TiString Menu::getSelectedString()
{
return _choices[_currentSectedItem];
}

int Menu::getSelectedTitle()
{
if (_isMultipleMenu)
  return _selectedTitle;
else
  return 0;
}

