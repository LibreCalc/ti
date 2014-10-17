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
#include <SDL/SDL.h>
#include <string>
#include <vector>
#include "tiConfig.h"

using namespace std;

#ifndef CURVE_VIEWER_H
#define CURVE_VIEWER_H

/**
 * @brief Cette courbe gère l'affichage des courbes
 */
class CurveViewer
{
public:
  CurveViewer(  SDL_Surface *ecran,SDL_Surface *display,TiConfig &conf);
   void clear();
   void reDisplay();
  
private:
  SDL_Surface *_ecran;
  SDL_Surface *_display;  
  TiConfig & _config;
  double _minX;
  double _maxX;
  double _minY;
  double _maxY;
};









#endif