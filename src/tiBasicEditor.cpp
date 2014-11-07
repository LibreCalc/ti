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


#include "tiBasicEditor.h"
#include "keyParser.h"
#include "83pReadWrite.h"

#include <iostream>

void TiBasicEditor::reDisplay()
{
    if (_isInSpecialCommandsMenu)
    {
        _specialsCommandsMenu->reDisplay();
        return;
    }
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
    for (int i=0; i<_currentProgram.size(); i++)
    {
        y=_putt->putString(":"+_currentProgram[i].toStdString()+" ",1,y);
    }

    _putt->blink(getPointerX(),getPointerY()-_currentDisplayoffset);
    _putt->refreshScreen();
}

int TiBasicEditor::getPointerX()
{
  TiString & line=_currentProgram[_currentLine];
return (line.getCursorPosInStdStr(_currentCursPos)+1)%16+1;
}

int TiBasicEditor::getPointerY()
{
    TiString & line=_currentProgram[_currentLine];
  int res=0;
  for (int i=0;i<_currentProgram.size();i++)
    if (_currentLine>i)
      res+=(_currentProgram[i].toStdString().size()+1)/16+1;

res+=1+(line.getCursorPosInStdStr(_currentCursPos)+1)/16;
return res;
}

void TiBasicEditor::blinkCursor()
{
_isCursorBlinked=!_isCursorBlinked;
}

void TiBasicEditor::changeLine(bool up)
{
if (up)
 {
  if (_currentLine>0)
  {
   _currentLine--;
   _currentCursPos=0;
  } 
 }
 else
 {
     if (_currentLine<_currentProgram.size()-1)
  {
   _currentLine++;
   _currentCursPos=0;
  } 
 }
 reDisplay();
}

void TiBasicEditor::changeCursorPos(bool left)
{
if (left)
{
 if (_currentCursPos>0)
   _currentCursPos--;
}
else
{
   if (_currentCursPos<_currentProgram[_currentLine].size())
   _currentCursPos++;
}
reDisplay();
}

void TiBasicEditor::rmChar()
{
    TiString &eq=_currentProgram[_currentLine];
    if (eq.size()==0)
    {
      if (_currentProgram.size()>_currentLine)
	_currentProgram.erase(_currentProgram.begin()+_currentLine);
      reDisplay();
     return;
    }
    if( _currentCursPos>=eq.size())
    {
     eq.erase(eq.size()-1);
     _currentCursPos--;
    }
    else
    eq.erase(_currentCursPos);
    reDisplay();
}

void TiBasicEditor::sendChar(int c)
{
TiString & eq=_currentProgram[_currentLine];
  if ( eq.size()==0 or _currentCursPos>= eq.size())
     eq.push_back(c);
    else
     eq.insert( _currentCursPos,c);
  _currentCursPos++;
    reDisplay();
}

void TiBasicEditor::addLine()
{
  _currentCursPos=0;
_currentProgram.insert(_currentProgram.begin()+_currentLine,TiString(""));
reDisplay();
}


void TiBasicEditor::sendKey(SDL_keysym k1)
{
    SDLKey k=k1.sym;
    if (keyParser::isChar(k1))
    {
        sendChar(keyParser::getChar(k1));
        return;
    }

    if (_isInSpecialCommandsMenu)
    {
        switch (k)
        {
        case SDLK_RETURN:
           sendChar( _specialsCommandsMenu->getSelectedString()[0]);
            _isInSpecialCommandsMenu=false;
            reDisplay();
            return;
        case SDLK_DELETE:
            _isInSpecialCommandsMenu=false;
            reDisplay();
            return;
        default:
            _specialsCommandsMenu->sendKey(k1);
        }
    }
    else
    {
        switch (k)
        {
        case SDLK_DELETE:
            rmChar();
            break;
        case SDLK_UP:
            changeLine(true);
            break;
        case SDLK_DOWN:
            changeLine(false);
            break;
        case SDLK_LEFT:
            changeCursorPos(true);
            break;
        case SDLK_RIGHT:
            changeCursorPos(false);
            break;
        case SDLK_RETURN:
            addLine();
            break;
        case SDLK_LALT:
            _isInSpecialCommandsMenu=true;
            _specialsCommandsMenu->reDisplay();
            break;
        }
    }
}

TiBasicEditor::TiBasicEditor(CharPutter* putt, TiConfig* conf)
{
_putt=putt;
_conf=conf;
_currentLine=0;
_currentCursPos=0;
_currentDisplayoffset=0;
vector<TiString> choicesCTRL;
choicesCTRL.push_back(TiString(CONST_SPE_IF));
choicesCTRL.push_back(TiString(CONST_SPE_THEN));
choicesCTRL.push_back(TiString(CONST_SPE_ELSE));
choicesCTRL.push_back(TiString(CONST_SPE_END));
choicesCTRL.push_back(TiString(CONST_SPE_WHILE));
choicesCTRL.push_back(TiString(CONST_SPE_REPEAT));
choicesCTRL.push_back(TiString(CONST_SPE_FOR));
choicesCTRL.push_back(TiString(CONST_SPE_GOTO));
choicesCTRL.push_back(TiString(CONST_SPE_LABEL));
choicesCTRL.push_back(TiString(CONST_SPE_PAUSE));
choicesCTRL.push_back(TiString(CONST_SPE_STOP));
choicesCTRL.push_back(TiString(CONST_SPE_RAND));
choicesCTRL.push_back(TiString(CONST_SPE_RANDINT));

vector<TiString> choicesCMP;
choicesCMP.push_back(TiString("="));
choicesCMP.push_back(TiString("<"));
choicesCMP.push_back(TiString(">"));
choicesCMP.push_back(TiString(CONST_CHAR_LESSOREQUAL));
choicesCMP.push_back(TiString(CONST_SPE_AND));
choicesCMP.push_back(TiString(CONST_SPE_OR));
choicesCMP.push_back(TiString(CONST_SPE_NOT));

vector<TiString> choicesDISP;
choicesDISP.push_back(TiString(CONST_SPE_DISP));
choicesDISP.push_back(TiString(CONST_SPE_OUTPUT));
choicesDISP.push_back(TiString(CONST_SPE_CLEARHOME));
choicesDISP.push_back(TiString(CONST_SPE_INPUT));
choicesDISP.push_back(TiString(CONST_SPE_GETKEY));

vector<TiString> choicesDRAW;
choicesDRAW.push_back(TiString(CONST_SPE_CLEARDRAW));
choicesDRAW.push_back(TiString(CONST_SPE_LINE));
choicesDRAW.push_back(TiString(CONST_SPE_TEXT));
choicesDRAW.push_back(TiString(CONST_SPE_PIXEL_TEST));
choicesDRAW.push_back(TiString(CONST_SPE_STOREPIC));
choicesDRAW.push_back(TiString(CONST_SPE_RECALLPIC));
choicesDRAW.push_back(TiString(CONST_SPE_PIC1));
choicesDRAW.push_back(TiString(CONST_SPE_XMIN));
choicesDRAW.push_back(TiString(CONST_SPE_XMAX));
choicesDRAW.push_back(TiString(CONST_SPE_YMIN));
choicesDRAW.push_back(TiString(CONST_SPE_YMAX));

vector< vector<TiString> > choices;
choices.push_back(choicesCTRL);choices.push_back(choicesCMP);
choices.push_back(choicesDISP);choices.push_back(choicesDRAW);

vector<TiString> titles;titles.push_back(TiString("Ctr"));titles.push_back(TiString("Cmp"));
titles.push_back(TiString("I/O"));titles.push_back(TiString("Draw"));
_specialsCommandsMenu=new Menu(_putt,titles,choices);
_isInSpecialCommandsMenu=false;
}

void TiBasicEditor::setProgramm(vector< TiString > program, string loc)
{
_currentProgram=program;
_currentLine=0;
_currentCursPos=0;
_programFileLoc=loc;
}

void TiBasicEditor::saveProgram()
{
write83pFile(_programFileLoc, _currentProgram);
}
