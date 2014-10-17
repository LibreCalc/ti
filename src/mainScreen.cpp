#include "mainScreen.h"
#include "evalFormula.h"
#include <iostream>
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

#include <math.h>
#include "keyParser.h"

using namespace std;
MainScreen::MainScreen(CharPutter* putt, TiConfig &conf):_conf(conf)
{
_putt=putt;
_currentDisplayoffset=0;
_currentCursPos=0;
_isCursorBlinked=true;
}

void MainScreen::blinkCursor()
{
_isCursorBlinked=!_isCursorBlinked;
}

void MainScreen::changeCursorPos(bool left)
{
 if (left and _currentCursPos>=1)
   _currentCursPos--;
  if (!left and _currentCursPos<_currString.size())
   _currentCursPos++;
  reDisplay();
}

void MainScreen::calc()
{
_buff=_buff+_currString.toStdString();
//TODO
TiVariant res;
if (_currString.size()>2  and _conf.isVariable(_currString[_currString.size()-1])
  and _currString[_currString.size()-2]==CONST_CHAR_STO)
  {
    char var=_currString[_currString.size()-1];
    //TODO
   // _currString=string(_currString.begin(),_currString.begin()+_currString.size()-2);
    _currString.erase(_currString.size()-1);
    _currString.erase(_currString.size()-1);    
    res=eval(_currString,_conf.getVariableValue('X'),_conf);
    _conf.setVariableValue(var,res);
  }
  else
   res=eval(_currString,_conf.getVariableValue('X'),_conf);
int x=16-_buff.size()%16;
 
//TODO use toString
    string c2=res.toString();

   
  //Here we add the necessary spaces to the buffer
  for (int i=0;i<x+(16-c2.size());i++)
    {
    _buff=_buff+" ";
    }
    
  //Add the result to the buffer  
  _buff=_buff+c2;
  _previousString=_currString;
  _currString=TiString();
  _currentCursPos=0;
  //reaffiche
  reDisplay();
}

void MainScreen::reDisplay()
  {
    int y=1;
    _putt->clear();
 
  /*******************************************
   * Clear the display buffer as much as necessary
   * In order for new command to appear
   ******************************************/
    while (_buff.size()>0 and _buff.size()/16+1+_currString.toStdString().size()/16>8)
    {
      if (_buff.size()<=16)
	_buff="";
      else
	_buff=string(_buff.begin()+16,_buff.begin()+_buff.size());
    }
    
    
    /*******************************************
    * Display the buffer dans le currently eddited
    * command
    ******************************************/   
    if (_buff.size()>0)
    {
      y=_putt->putString(_buff,1,1);
      _currentDisplayoffset=0;
    }
    else
    {int pointerPosY=getPointerY();
      if (pointerPosY-_currentDisplayoffset>8)
      {
	_currentDisplayoffset=pointerPosY-8;
      }
      else
      {
	if (pointerPosY-_currentDisplayoffset<1)
	  _currentDisplayoffset=pointerPosY-1;
      }
    }
      
    _putt->putString(_currString.toStdString()+" ",1,y-_currentDisplayoffset); 

    if (_isCursorBlinked)
    _putt->blink(getPointerX(),getPointerY()+y-1-_currentDisplayoffset);
    _putt->refreshScreen();
  }

void MainScreen::sendChar(int c)
{
  if (_currString.size()==0 or _currentCursPos>=_currString.size())
     _currString.push_back(c);
    else
    _currString.insert( _currentCursPos,c);
  _currentCursPos++;
  _isCursorBlinked=true;
  reDisplay();
}

void MainScreen::rmChar()
{
  if (_currString.size()==0)
     return;
    if( _currentCursPos>=_currString.size())
    {
     _currString.erase(_currString.size()-1);
      _currentCursPos--;
    }
    else
    _currString.erase( _currentCursPos);
  reDisplay();
}

void MainScreen::sendKey(SDL_keysym  k2)
{
  SDLKey k=k2.sym;
  if (keyParser::isChar(k2))
  {
   sendChar(keyParser::getChar(k2)); 
   return;
  }
 switch (k)
		    {   
		   case SDLK_DELETE:
		      rmChar();	
		      break;  
		      case SDLK_UP:
			if (_currString.size()==0)
			{
			  _currString=_previousString;
			  _currentCursPos=_currString.size();
			}
			else
			_currentCursPos=_currString.getCursorUpLine(_currentCursPos);
			reDisplay();
		      break;
		      case SDLK_DOWN:
			_currentCursPos=_currString.getCursorDownLine(_currentCursPos);
			reDisplay();
		      break;  
		      
		 	   case SDLK_LEFT:
		      changeCursorPos(true);
		      break;  
			   case SDLK_RIGHT:
		      changeCursorPos(false);
		      break;  
			   case SDLK_RETURN:
		      calc();
		      break; 		      
		      
		    }
}


int MainScreen::getPointerX()
{
return (_currString.getCursorPosInStdStr(_currentCursPos))%16+1;
}

int MainScreen::getPointerY()
{
return (_currString.getCursorPosInStdStr(_currentCursPos))/16+1;
}

void MainScreen::setBuffer(string s)
{
_buff=s;
}

