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
#include "tiConfig.h"
#include "canvas.h"
#include <cmath>

Canvas::Canvas(TiConfig& conf, SDL_Surface* ecran, SDL_Surface* display):_conf(conf)
{
  _display=display;
  _ecran=_conf.getCanvasScreen();
  _whiteChar=SDL_CreateRGBSurface(SDL_SWSURFACE,1,6,8,255,255,255,0);
 SDL_FillRect(  _whiteChar, NULL, SDL_MapRGB( _whiteChar->format, 255, 255, 255));   
 _spriteText= SDL_LoadBMP("img/spriteText.bmp");
 _spriteTextNumber= SDL_LoadBMP("img/spriteTextNumber.bmp"); 
}

void Canvas::setAxes(bool on)
{
_axesOn=on;
}

void Canvas::clearDraw()
{
 SDL_FillRect( _ecran, NULL, SDL_MapRGB(_ecran->format, 255, 255, 255)); 
 reDisplay();
}

void Canvas::line(double x1, double y1, double x2, double y2)
{
  int x1converted;int x2converted;
  int y1converted;int y2converted;  

  x1converted=round((x1-_conf.getVariableValue(CONST_SPE_XMIN).toDouble())
  /(_conf.getVariableValue(CONST_SPE_XMAX).toDouble()-_conf.getVariableValue(CONST_SPE_XMIN).toDouble())*94)-1;
  
  x2converted=round((x2-_conf.getVariableValue(CONST_SPE_XMIN).toDouble())
  /(_conf.getVariableValue(CONST_SPE_XMAX).toDouble()-_conf.getVariableValue(CONST_SPE_XMIN).toDouble())*94)-1;  
  
  y1converted=round(62-(y1-_conf.getVariableValue(CONST_SPE_YMIN).toDouble())
  /(_conf.getVariableValue(CONST_SPE_YMAX).toDouble()-_conf.getVariableValue(CONST_SPE_YMIN).toDouble())*62)-1;  
  
  y2converted=round(62-(y2-_conf.getVariableValue(CONST_SPE_YMIN).toDouble())
  /(_conf.getVariableValue(CONST_SPE_YMAX).toDouble()-_conf.getVariableValue(CONST_SPE_YMIN).toDouble())*62)-1;
  
  ligne(_ecran,x1converted,y1converted,x2converted,y2converted);
  reDisplay();
}

void Canvas::reDisplay()
{
adaptSurface(_ecran,_display);
SDL_Flip(_display);
}

#include <iostream>
using namespace std;
void Canvas::recalPic(int picNo)
{
    if (picNo==CONST_SPE_PIC1)
    {
        SDL_Surface * img=SDL_LoadBMP("img/pic1.bmp");
        SDL_Rect  rect;
        rect.x=0;
        rect.y=0;
        SDL_BlitSurface(img,NULL,_ecran,&rect);
        SDL_FreeSurface(img);
        return;
    }
    cout<<"Error while recalPic"<<endl;
}

void Canvas::whiteLine(double x1, double y1, double x2, double y2)
{
  int x1converted;int x2converted;
  int y1converted;int y2converted;  

  x1converted=round((x1-_conf.getVariableValue(CONST_SPE_XMIN).toDouble())
  /(_conf.getVariableValue(CONST_SPE_XMAX).toDouble()-_conf.getVariableValue(CONST_SPE_XMIN).toDouble())*94)-1;
  
  x2converted=round((x2-_conf.getVariableValue(CONST_SPE_XMIN).toDouble())
  /(_conf.getVariableValue(CONST_SPE_XMAX).toDouble()-_conf.getVariableValue(CONST_SPE_XMIN).toDouble())*94)-1;  
  
  y1converted=round(62-(y1-_conf.getVariableValue(CONST_SPE_YMIN).toDouble())
  /(_conf.getVariableValue(CONST_SPE_YMAX).toDouble()-_conf.getVariableValue(CONST_SPE_YMIN).toDouble())*62)-1;  
  
  y2converted=round(62-(y2-_conf.getVariableValue(CONST_SPE_YMIN).toDouble())
  /(_conf.getVariableValue(CONST_SPE_YMAX).toDouble()-_conf.getVariableValue(CONST_SPE_YMIN).toDouble())*62)-1;
  
  whiteLigne(_ecran,x1converted,y1converted,x2converted,y2converted);
  reDisplay();
}

void Canvas::storePic(int picNo)
{
    if (picNo==CONST_SPE_PIC1)
    {
      cout<<"storePic !!!"<<endl;
         SDL_SaveBMP(_ecran,"img/pic1.bmp");
	 return;
    }
    cout<<"Error while storePic "<<picNo<<endl;
}


void Canvas::text(int x, int y, string str)
{
  SDL_Rect rec; rec.x=x-1 ; rec.y=y-1;
  if (rec.x<0) rec.x++;
  if (rec.y<0) rec.y++;  
    for (int i=0; i<str.size(); i++)
    {
      if (str[i]==' ')
      {
	 SDL_BlitSurface(_whiteChar,NULL,_ecran,&rec);
	rec.x++;	
      }
      else
      {
	if (str[i]>='A' and str[i]<='Z')
	{
	  
	SDL_Rect rec2; rec2.x=int((str[i]-'A')*3); rec2.y=0; rec2.h=7; rec2.w=3;
	SDL_BlitSurface(_spriteText,&rec2,_ecran,&rec);
	}
	else if (str[i]>='0' and str[i]<='9')
	{
	  
	SDL_Rect rec2; rec2.x=int((str[i]-'0')*3); rec2.y=0; rec2.h=7; rec2.w=3;
	SDL_BlitSurface(_spriteTextNumber,&rec2,_ecran,&rec);
	}
	rec.x+=3;
	if (i<str.size()-1)
	{
        SDL_BlitSurface(_whiteChar,NULL,_ecran,&rec);
	}
	rec.x++;
      }
    }
    SDL_Delay(50);
}


