#ifndef TI_BASIC_EDITOR
#define TI_BASIC_EDITOR

#include <vector>
#include "tiString.h"
#include "charPutter.h"
#include "tiConfig.h"
#include "menu.h"

using namespace std;


class TiBasicEditor
{
  
  public:
  TiBasicEditor(CharPutter *putt,TiConfig *conf);
  void reDisplay();
  void blinkCursor();
  void sendKey(SDL_keysym k);
  void setProgramm(vector<TiString> program);
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
  
  
  
};








#endif