#include "tiBasicEditor.h"
#include "keyParser.h"

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
     if (_currentLine<_currentProgram.size())
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
_currentProgram.insert(_currentProgram.begin()+_currentLine,TiString(""));
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
vector<TiString> choices;
choices.push_back(TiString(CONST_SPE_IF));
choices.push_back(TiString(CONST_SPE_THEN));
choices.push_back(TiString(CONST_SPE_ELSE));
choices.push_back(TiString(CONST_SPE_END));
choices.push_back(TiString(CONST_SPE_AND));
choices.push_back(TiString(CONST_SPE_OR));
choices.push_back(TiString(CONST_SPE_WHILE));
choices.push_back(TiString(CONST_SPE_RAND));
choices.push_back(TiString(CONST_SPE_DISP));
choices.push_back(TiString(CONST_SPE_OUTPUT));
_specialsCommandsMenu=new Menu(_putt,TiString("Special Words"),choices);
_isInSpecialCommandsMenu=false;
}

void TiBasicEditor::setProgramm(vector< TiString > program)
{
_currentProgram=program;
}
