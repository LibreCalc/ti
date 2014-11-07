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

#ifndef TI_PARSER_H
#define TI_PARSER_H
#include "charPutter.h"
#include <vector>
#include "tiString.h"
#include "tiConfig.h"
#include "canvas.h"

class TiParser{
  
  
public:
  TiParser(CharPutter* charPutter, TiConfig& conf);
  void execProgram(vector< TiString >& program);  
  void exec(vector< TiString >& program, int start, int end);
  int lookForElse(vector<TiString> &program,int loc,int end);  
  int lookForEnd(vector<TiString> &program,int loc,int end);
  
private:
  void handleOutput(TiString s);
  void handleDisp(TiString s);  
  void handleClearList(TiString s);    
  void handleInput(TiString s);   
  void handleMenu(TiString s);   
  void handleFill(TiString s); 
  void handleLine(TiString s); 
  void handleText(TiString s); 
  void checkForGetKey(TiString &s);
  void needToRefresh();
  string removeQuote(string s);
 
  //Goto
  string _needToGoto;
  
  //Configuration Ti
  TiConfig &_conf; 
  
  //Affichage
  bool _needToRefresh;
  CharPutter * _charPutter;  
  Canvas _canvas;
  
  //clavier
  int _key;
  
};









#endif