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

#include "curveViewer.h"
#include "evalFormula.h"
#include "handlePixels.h"
#include <cmath>
#define SCREEN_WIDTH 96
#define SCREEN_HEIGHT 64
#include <iostream>

using namespace std;

void CurveViewer::clear()
{
   SDL_FillRect( _ecran, NULL, SDL_MapRGB(_ecran->format, 255, 255, 255)); 
}



CurveViewer::CurveViewer(SDL_Surface* ecran, SDL_Surface* display, TiConfig& conf):_config(conf)
{
_ecran=ecran;
_display=display;
_minX=-10;
_maxX=10;
_minY=-10;
_maxY=10;
}


void CurveViewer::reDisplay()
{
  clear();
  
  //***************************************
  //Draw Axis
  //****************************************/
  if (_minX<0  and _maxX>0)
  {
    int posYAxis=round(SCREEN_WIDTH*_minX/(_maxX-_minX));
    ligne (_ecran,posYAxis,1, posYAxis,SCREEN_HEIGHT);
  }
  
  
  if (_minY<0  and _maxY>0)
  {
    int posXAxis=round(SCREEN_HEIGHT*_maxY/(_maxY-_minY));
    ligne (_ecran,1,posXAxis, 95,posXAxis);
  }
  
 //***************************************
 //Draw Curves
 //****************************************/ 
    for (int l=0; l<4; l++)
    {
      
      if (_config.getFunctionsToPlot(l).size()==0)
	continue;
      
        int lastXPixel=-1;
        int lastYPixel=-1;
        for (int i=0; i<SCREEN_WIDTH; i++)
        {
            double x=_minX+i*(_maxX-_minX)/(1.0*SCREEN_WIDTH);
            double y=eval(_config.getFunctionsToPlot(l),x,_config).toDouble();

            int yPixel=round(SCREEN_HEIGHT-SCREEN_HEIGHT*(y-_minY)/(_maxY-_minY));
            if (yPixel>=0 and yPixel<SCREEN_HEIGHT)
            {
                Uint32 pix=SDL_MapRGBA(_ecran->format, 0, 0, 0, 255);
                definirPixel(_ecran,i,yPixel,pix);
                if (lastXPixel!=-1 and lastYPixel!=-1)
                    ligne(_ecran,i,yPixel, lastXPixel,lastYPixel);
                lastXPixel=i;
                lastYPixel=yPixel;

            }
            else
            {
                if (yPixel<0)
                {

                    if (lastYPixel>0 and i>1 )
                        ligne(_ecran,lastXPixel+1,0, lastXPixel,lastYPixel);
                    lastYPixel=0;
                }
                if (yPixel>=SCREEN_HEIGHT)
                {
                    if (lastYPixel>0 and lastYPixel<SCREEN_HEIGHT-1)
                        ligne(_ecran,lastXPixel+1,SCREEN_HEIGHT-1, lastXPixel,lastYPixel);
                    lastYPixel=SCREEN_HEIGHT-1;
                }
                lastXPixel=i+1;
            }
        }
    }
  //***************************************
 //Refresh Screen
 //****************************************/ 
 adaptSurface(_ecran,_display);
 SDL_Flip(_display);
}
