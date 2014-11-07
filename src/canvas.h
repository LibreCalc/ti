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

#include "tiString.h"
#include "handlePixels.h"
#include "tiConfig.h"

#ifndef CANVAS_H
#define CANVAS_H


/**
 * @brief This Class handles all the graphics drawing on the screen
 * 
 */
class Canvas
{
public:
  Canvas(TiConfig &conf,SDL_Surface *ecran,SDL_Surface *_display);
  
  /**
   * @brief Clear the draw
   * 
   * @return void
   */
  void clearDraw();
  
  /**
   * @brief Allows to set axes On or OFF
   */
  void setAxes(bool on);
  void line(double x1, double y1,double x2,double y2);
  void whiteLine(double x1, double y1,double x2,double y2);  
  void text(int x,int y, string str);
  bool pixelTest(int x,int y);
  void storePic(int picNo);
  void recalPic(int picNo);  
  void reDisplay();
private:
  TiConfig &_conf;
  SDL_Surface *_ecran;  
  SDL_Surface *_display;  
  SDL_Surface *_whiteChar;
  SDL_Surface *_spriteText;  
  SDL_Surface *_spriteTextNumber;    
  bool _axesOn;
  
};


#endif