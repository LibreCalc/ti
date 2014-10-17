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

#include "yEqualsMenu.h"
#include "keyParser.h"
#include <iostream>

using namespace std;

YEqualsMenu::YEqualsMenu(CharPutter* putt,TiConfig *conf)
{
 _putt=putt;
 _conf=conf;
/* _equ1="";
 _equ2=""; 
 _equ3=""; 
 _equ3="";*/ 
 _currentEqu=1;
 _currentCursPos=0;
 _currentDisplayoffset=0;
}


void YEqualsMenu::reDisplay()
{
int pointerPosY=getPointerY();
if (pointerPosY-_currentDisplayoffset>8)
{
  _currentDisplayoffset=pointerPosY-8;
}
else
{
  if (pointerPosY-_currentDisplayoffset<1)
  _currentDisplayoffset=pointerPosY-1;
}

int y=1-_currentDisplayoffset;
 _putt->clear();
 string smallfour;smallfour.push_back(CONST_CHAR_SMALL4);
  y=_putt->putString(":Y&="+_conf->getFunctionsToPlot(0).toStdString()+" ",1,y); 
  y=_putt->putString(":Y~="+_conf->getFunctionsToPlot(1).toStdString()+" ",1,y); 
  y=_putt->putString(":Y#="+_conf->getFunctionsToPlot(2).toStdString()+" ",1,y); 
  y=_putt->putString(":Y"+smallfour+"="+_conf->getFunctionsToPlot(3).toStdString()+" ",1,y); 
  _putt->blink(getPointerX(),getPointerY()-_currentDisplayoffset);
  _putt->refreshScreen();
}

void YEqualsMenu::blinkCursor()
{
_isCursorBlinked=!_isCursorBlinked;
}


void YEqualsMenu::sendChar(int c)
{
TiString & eq=getEqu(_currentEqu);
  if ( eq.size()==0 or _currentCursPos>= eq.size())
     eq.push_back(c);
    else
     eq.insert( _currentCursPos,c);
  _currentCursPos++;
    reDisplay();
}

TiString& YEqualsMenu::getEqu(int no)
{
switch (_currentEqu)
    {
  case 1:
    return _conf->getFunctionsToPlot(0);
  case 2:
    return _conf->getFunctionsToPlot(1);
   case 3:
    return _conf->getFunctionsToPlot(2);
      case 4:
    return _conf->getFunctionsToPlot(3);
    }
}


void YEqualsMenu::changeEqu(bool up)
{
 if (up)
 {
  if (_currentEqu>1)
  {
   _currentEqu--;
   _currentCursPos=getEqu(_currentEqu).size();
  } 
 }
 else
 {
     if (_currentEqu<4)
  {
   _currentEqu++;
   _currentCursPos=getEqu(_currentEqu).size();
  } 
 }
 reDisplay();
}

void YEqualsMenu::rmChar()
{

    TiString &eq=getEqu(_currentEqu);
    if (eq.size()==0)
     return;
    if( _currentCursPos>=eq.size())
    {
     eq.erase(eq.size()-1);
     _currentCursPos--;
    }
    else
    eq.erase(_currentCursPos);
     reDisplay();
}

int YEqualsMenu::getPointerY()
{
    TiString & eq=getEqu(_currentEqu);
  int res=0;
if (_currentEqu>1)
  res+=(_conf->getFunctionsToPlot(1).toStdString().size()+3)/16+1;
if (_currentEqu>2)
  res+=(_conf->getFunctionsToPlot(2).toStdString().size()+3)/16+1;
if (_currentEqu>3)
  res+=(_conf->getFunctionsToPlot(3).toStdString().size()+3)/16+1;
res+=1+(eq.getCursorPosInStdStr(_currentCursPos)+4)/16;
return res;
}

int YEqualsMenu::getPointerX()
{
  TiString & eq=getEqu(_currentEqu);
return (eq.getCursorPosInStdStr(_currentCursPos)+4)%16+1;
}


void YEqualsMenu::changeCursorPos(bool left)
{
if (left)
{
 if (_currentCursPos>0)
   _currentCursPos--;
}
else
{
   if (_currentCursPos<getEqu(_currentEqu).size())
   _currentCursPos++;
}
reDisplay();
}

TiString YEqualsMenu::getFirstEq()
{
return _conf->getFunctionsToPlot(1);
}


void YEqualsMenu::sendKey(SDL_keysym k1)
{
  SDLKey k=k1.sym;
  if (keyParser::isChar(k1))
  {
   sendChar(keyParser::getChar(k1)); 
   return;
  }
  
	  switch (k)
		    {
		   case SDLK_DELETE:
		      rmChar();	
		      break;  
		   case SDLK_UP:
		      changeEqu(true);
		      break;
		   case SDLK_DOWN:
		      changeEqu(false);
		      break;  
		 	   case SDLK_LEFT:
		      changeCursorPos(true);
		      break;  
			   case SDLK_RIGHT:
		      changeCursorPos(false);
		      break;  
		      
		    }
}
