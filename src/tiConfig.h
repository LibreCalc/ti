#ifndef TI_CONFIG
#define TI_CONFIG
#include <string>
#include <vector>
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

#include <map>
#include "tiString.h"
#include "tiVariant.h"
#include <SDL/SDL.h>

using namespace std;

class TiConfig
{
public:
  TiConfig();
  TiVariant getVariableValue(int c);
  void setVariableValue(int c,TiVariant value);
  bool isVariable(int c);
  TiVariant& getVariable(int c);
  TiVariant getAns();
  void setAns(TiVariant Ans);
  TiString& getFunctionsToPlot(int i);
  void setFunctionToPlot(int i,TiString s);
  bool isPixelXYBlack(int x, int y);
  SDL_Surface * getCanvasScreen();
private:
  SDL_Surface *_screen;
  map<int,TiVariant> _variables;
  TiVariant _Ans;
  vector<TiString> _functionsToPlot;
};


#endif