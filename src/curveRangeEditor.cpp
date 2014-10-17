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

#include "curveRangeEditor.h"
#include "evalFormula.h"
#include <iostream>
#include "keyParser.h"

using namespace std;

CurveRangeEditor::CurveRangeEditor(CharPutter* putt, TiConfig* conf)
{
for (int i=0;i<6;i++)
  _editedLines.push_back("1.0");
_putt=putt;
_conf=conf;
_currentLine=1;
_currentCursPosInStr=1;
}


void CurveRangeEditor::reDisplay()
{
  _putt->clear();
  _putt->putString("RANGE",1,1);
  _putt->putString("Ymin="+_editedLines[0],1,2);
  _putt->putString("Ymax="+_editedLines[1],1,3);
  _putt->putString("Yscl="+_editedLines[2],1,4);  
  _putt->putString("Xmin="+_editedLines[3],1,5);
  _putt->putString("Xmax="+_editedLines[4],1,6);
  _putt->putString("Xscl="+_editedLines[5],1,7);
  if (_isCursorBlinked)
    _putt->blink(_currentCursPosInStr+5,_currentLine+1);
  _putt->refreshScreen();
}

void CurveRangeEditor::loadVariables()
{
_editedLines[0]=_conf->getVariableValue(CONST_SPE_YMIN).toString();
_editedLines[1]=_conf->getVariableValue(CONST_SPE_YMAX).toString();
_editedLines[2]=_conf->getVariableValue(CONST_SPE_YSCL).toString();
_editedLines[3]=_conf->getVariableValue(CONST_SPE_XMIN).toString();
_editedLines[4]=_conf->getVariableValue(CONST_SPE_XMAX).toString();
_editedLines[5]=_conf->getVariableValue(CONST_SPE_XSCL).toString();
}

void CurveRangeEditor::writeVariables()
{
_conf->setVariableValue(CONST_SPE_YMIN,eval(_editedLines[0],_conf->getVariableValue('X'),*_conf));
_conf->setVariableValue(CONST_SPE_YMAX,eval(_editedLines[1],_conf->getVariableValue('X'),*_conf));
_conf->setVariableValue(CONST_SPE_YSCL,eval(_editedLines[2],_conf->getVariableValue('X'),*_conf));
_conf->setVariableValue(CONST_SPE_XMIN,eval(_editedLines[3],_conf->getVariableValue('X'),*_conf));
_conf->setVariableValue(CONST_SPE_XMAX,eval(_editedLines[4],_conf->getVariableValue('X'),*_conf));
_conf->setVariableValue(CONST_SPE_XSCL,eval(_editedLines[5],_conf->getVariableValue('X'),*_conf));
}

void CurveRangeEditor::sendKey(SDL_keysym k1)
{
    SDLKey k=k1.sym;
    if (keyParser::isChar(k1) and ((keyParser::getChar(k1)>='0' and keyParser::getChar(k1)<='9') or keyParser::getChar(k1)=='.' 
      or keyParser::getChar(k1)=='-' or keyParser::getChar(k1)==CONST_CHAR_SMALL_MINUS))
    {
      if ( keyParser::getChar(k1)=='-')
	sendChar(CONST_CHAR_SMALL_MINUS);
      else
        sendChar(keyParser::getChar(k1));
    }
    else {
        switch (k)
        {
        case SDLK_DELETE:
            rmChar();
            break;
        case SDLK_UP:
            _currentCursPosInStr=1;
            if (_currentLine>1)
                _currentLine--;
            _isCursorBlinked=true;
            break;
        case SDLK_DOWN:
            _currentCursPosInStr=1;
            if (_currentLine<6)
                _currentLine++;
            _isCursorBlinked=true;
            break;
        case SDLK_LEFT:
            if (_currentCursPosInStr>1)
                _currentCursPosInStr--;
            break;
        case SDLK_RIGHT:
            if (_currentCursPosInStr<=_editedLines[_currentLine-1].size())
                _currentCursPosInStr++;
            break;

        }
    }
    reDisplay();
    writeVariables();
}

void CurveRangeEditor::blinkCursor()
{
_isCursorBlinked=!_isCursorBlinked;
}

void CurveRangeEditor::rmChar()
{
    if (_currentCursPosInStr-1<_editedLines[_currentLine-1].size())
        _editedLines[_currentLine-1].erase(_currentCursPosInStr-1,1);
}

void CurveRangeEditor::sendChar(int c)
{
  string s; s.push_back(c);
if (_editedLines[_currentLine-1].size()<10)
{
  _editedLines[_currentLine-1].insert(_currentCursPosInStr-1,s);
  _currentCursPosInStr++;
}
reDisplay();
}

