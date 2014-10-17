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
#include "charPutter.h"
#include <unistd.h>
#include "sys/time.h"
#include "handlePixels.h"
#include "keyParser.h"

#include <iostream>
#define loadCharpix(x,y)     case x:  \
      SDL_BlitSurface(y, NULL, _ecran, &pos); \
      break; 
CharPutter::CharPutter(SDL_Surface* ecran, SDL_Surface* display, int dim_X, int dim_Y)
{

  _display=display;
  _dim_X=dim_X;
  _dim_Y=dim_Y;
  _ecran=ecran;//SDL_SetVideoMode(95, 63, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    _heightCurentlyUsed=1;
  
  for (int i=0;i<8;i++)
  {
  mat[i]="                ";  
  }
  
  _img_1=SDL_LoadBMP("img/1.bmp");
  _img_2=SDL_LoadBMP("img/2.bmp");
  _img_3=SDL_LoadBMP("img/3.bmp");
  _img_4=SDL_LoadBMP("img/4.bmp");
  _img_5=SDL_LoadBMP("img/5.bmp");  
  _img_6=SDL_LoadBMP("img/6.bmp");
  _img_7=SDL_LoadBMP("img/7.bmp");    
  _img_8=SDL_LoadBMP("img/8.bmp");  
  _img_9=SDL_LoadBMP("img/9.bmp");    
  _img_A=SDL_LoadBMP("img/A.bmp");  
  _img_B=SDL_LoadBMP("img/B.bmp");   
  _img_C=SDL_LoadBMP("img/C.bmp");  
  _img_D=SDL_LoadBMP("img/D.bmp");   
  _img_E=SDL_LoadBMP("img/E.bmp");
  _img_F=SDL_LoadBMP("img/F.bmp"); 
  _img_G=SDL_LoadBMP("img/G.bmp"); 
  _img_H=SDL_LoadBMP("img/H.bmp"); 
  _img_I=SDL_LoadBMP("img/I.bmp"); 
  _img_J=SDL_LoadBMP("img/J.bmp");   
  _img_K=SDL_LoadBMP("img/K.bmp");    
  _img_L=SDL_LoadBMP("img/L.bmp");    
  _img_M=SDL_LoadBMP("img/M.bmp");
  _img_N=SDL_LoadBMP("img/N.bmp");
  _img_O=SDL_LoadBMP("img/O.bmp");
  _img_P=SDL_LoadBMP("img/P.bmp");  
  _img_Q=SDL_LoadBMP("img/Q.bmp");  
  _img_R=SDL_LoadBMP("img/R.bmp");
  _img_S=SDL_LoadBMP("img/S.bmp");
  _img_T=SDL_LoadBMP("img/T.bmp"); 
  _img_U=SDL_LoadBMP("img/U.bmp");
  _img_V=SDL_LoadBMP("img/V.bmp");
  _img_W=SDL_LoadBMP("img/W.bmp"); 
  _img_X=SDL_LoadBMP("img/X.bmp");    
  _img_Y=SDL_LoadBMP("img/Y.bmp"); 
  _img_Z=SDL_LoadBMP("img/Z.bmp");
  _img_s=SDL_LoadBMP("img/b.bmp");
  _img_s=SDL_LoadBMP("img/d.bmp");
  _img_s=SDL_LoadBMP("img/f.bmp");  
  _img_s=SDL_LoadBMP("img/s.bmp");  
  _img_k=SDL_LoadBMP("img/k.bmp");
  _img_t=SDL_LoadBMP("img/t.bmp");   
  _img_i=SDL_LoadBMP("img/i.bmp"); 
  _img_n=SDL_LoadBMP("img/n.bmp"); 
  _img_a=SDL_LoadBMP("img/a.bmp");   
  _img_e=SDL_LoadBMP("img/e.bmp");    
  _img_o=SDL_LoadBMP("img/o.bmp");  
  _img_u=SDL_LoadBMP("img/u.bmp");   
  _img_l=SDL_LoadBMP("img/l.bmp");  
  _img_r=SDL_LoadBMP("img/r.bmp");
  _img_g=SDL_LoadBMP("img/g.bmp");
  _img_m=SDL_LoadBMP("img/m.bmp");  
  _img_pi=SDL_LoadBMP("img/pi.bmp");   
  _img_superior=SDL_LoadBMP("img/>.bmp");     
  _img_plus=SDL_LoadBMP("img/+.bmp");   
  _img_twoDots=SDL_LoadBMP("img/:.bmp");  
  _img_smallone=SDL_LoadBMP("img/small1.bmp");   
  _img_smalltwo=SDL_LoadBMP("img/small2.bmp");
  _img_smallthree=SDL_LoadBMP("img/small3.bmp"); 
  _img_smallfour=SDL_LoadBMP("img/small4.bmp");
  _img_smallfive=SDL_LoadBMP("img/small5.bmp");  
  _img_smallsix=SDL_LoadBMP("img/small6.bmp");  
  _img_smallseven=SDL_LoadBMP("img/small7.bmp"); 
  _img_smallheight=SDL_LoadBMP("img/small8.bmp");  
  _img_smallnine=SDL_LoadBMP("img/small9.bmp");   
  _img_equal=SDL_LoadBMP("img/=.bmp"); 
  _img_leftParenthesis=SDL_LoadBMP("img/(.bmp"); 
  _img_rightParenthesis=SDL_LoadBMP("img/).bmp"); 
  _img_star=SDL_LoadBMP("img/*.bmp");  
  _img_exclamation=SDL_LoadBMP("img/!.bmp");    
  _img_slash=SDL_LoadBMP("img/slash.bmp");
  _img_minus=SDL_LoadBMP("img/-.bmp");
  _img_dot=SDL_LoadBMP("img/dot.bmp");
  _img_pow=SDL_LoadBMP("img/^.bmp");  
  _img_0=SDL_LoadBMP("img/0.bmp"); 
  _img_degree=SDL_LoadBMP("img/°.bmp");   
  _img_sto=SDL_LoadBMP("img/sto.bmp");  
  _img_guillemet=SDL_LoadBMP("img/\".bmp"); 
  _img_accoladedroite=SDL_LoadBMP("img/}.bmp"); 
  _img_accoladegauche=SDL_LoadBMP("img/{.bmp");  
  _img_v=SDL_LoadBMP("img/v.bmp");  
  _img_x=SDL_LoadBMP("img/x.bmp");
  _img_c=SDL_LoadBMP("img/c.bmp");  
  _img_virgule=SDL_LoadBMP("img/,.bmp");    
   _img_small_minus=SDL_LoadBMP("img/smallMinus.bmp");   
  _voidchar=SDL_LoadBMP("img/void.bmp");  
  _img_crochetdroit=SDL_LoadBMP("img/].bmp");   
  _img_crochetgauche=SDL_LoadBMP("img/[.bmp"); 
  
  if(_voidchar==NULL)
    cout<<"Problème chargement"<<endl;  
}

int CharPutter::disp(string s)
{
  if (_heightCurentlyUsed==8)
  {
   for (int i=1;i<8;i++)
  {
    putString(mat[i],1,i);
    }
//   for (int i=6;i>=0;i--)
//   {
//   mat[i]=mat[i+1];
//   }
  mat[7]="                ";
  _heightCurentlyUsed--;
 }

putString("               ",1,_heightCurentlyUsed+1);
putString(s,1,_heightCurentlyUsed);
_heightCurentlyUsed++;
}


void CharPutter::putChar(char c, int x, int y, bool invert)
{
  SDL_Rect pos;
      pos.x=(x-1)*6;
      pos.y=(y-1)*8;
  mat[y-1][x-1]=c;
//   if (y>_heightCurentlyUsed)
//     _heightCurentlyUsed=y;
SDL_BlitSurface(_voidchar, NULL, _ecran, &pos);
  switch (c)
  {
    case '1': 
      SDL_BlitSurface(_img_1, NULL, _ecran, &pos);
      break;
    case '2': 
      SDL_BlitSurface(_img_2, NULL, _ecran, &pos);
      break;      
    case '3': 
      SDL_BlitSurface(_img_3, NULL, _ecran, &pos);
      break;        
    case '4': 
      SDL_BlitSurface(_img_4, NULL, _ecran, &pos);
      break;  
    case '5': 
      SDL_BlitSurface(_img_5, NULL, _ecran, &pos);
      break;    
    case '6': 
      SDL_BlitSurface(_img_6, NULL, _ecran, &pos);
      break;    
    case '7': 
      SDL_BlitSurface(_img_7, NULL, _ecran, &pos);
      break;   
    case '8': 
      SDL_BlitSurface(_img_8, NULL, _ecran, &pos);
      break; 
    case '9': 
      SDL_BlitSurface(_img_9, NULL, _ecran, &pos);
      break;     
    case '0': 
      SDL_BlitSurface( _img_0, NULL, _ecran, &pos);       
      break;      
    case 'Y': 
      SDL_BlitSurface(_img_Y, NULL, _ecran, &pos);
      break;   
      	loadCharpix('v',_img_v)
	loadCharpix('X',_img_X)	       
	loadCharpix('A',_img_A)	  
	loadCharpix('B',_img_B)  
	loadCharpix('C',_img_C)      
	loadCharpix('D',_img_D)
	loadCharpix('E',_img_E)
	loadCharpix('F',_img_F)	
	loadCharpix('S',_img_S)
	loadCharpix('T',_img_T)	
	loadCharpix('K',_img_K)	
	loadCharpix('L',_img_L)
	loadCharpix('M',_img_M)	
	loadCharpix('N',_img_N)	
	loadCharpix('G',_img_G)		
	loadCharpix('R',_img_R)	
	loadCharpix('O',_img_O)	
	loadCharpix('H',_img_H)		
	loadCharpix('P',_img_P)		
	loadCharpix('I',_img_I)
	loadCharpix('V',_img_V)	
	loadCharpix('W',_img_W)	
	loadCharpix('Q',_img_Q)	
	loadCharpix('Z',_img_Z)	
	loadCharpix('J',_img_J)	
	loadCharpix('U',_img_U)		
	loadCharpix('s',_img_s)
	loadCharpix('i',_img_i)	
	loadCharpix('o',_img_o)	
	loadCharpix('u',_img_u)	
	loadCharpix('e',_img_e)	
	loadCharpix('a',_img_a)	
	loadCharpix('k',_img_k)	
	loadCharpix('t',_img_t)		
	loadCharpix('n',_img_n)	
	loadCharpix('l',_img_l)	
	loadCharpix('r',_img_r)
	loadCharpix('m',_img_m)
	loadCharpix('g',_img_g)	
	loadCharpix('b',_img_b)
	loadCharpix('d',_img_d)
	loadCharpix('f',_img_f)	
	loadCharpix('x',_img_x)
	loadCharpix('c',_img_c)	
	loadCharpix('\"',_img_guillemet)
	loadCharpix(CONST_CHAR_SMALL_MINUS,_img_small_minus)
	loadCharpix('[',_img_crochetgauche)
	loadCharpix(']',_img_crochetdroit)	
	loadCharpix('{',_img_accoladegauche)
	loadCharpix('}',_img_accoladedroite)
	loadCharpix('!',_img_exclamation)	
	loadCharpix(',',_img_virgule)	
	loadCharpix('>',_img_superior)	
	loadCharpix(CONST_CHAR_DEGREE,_img_degree)	
	loadCharpix(CONST_CHAR_PI,_img_pi)	
	loadCharpix(CONST_CHAR_SMALL5,_img_smallfive)	
	loadCharpix(CONST_CHAR_SMALL6,_img_smallsix)
	loadCharpix(CONST_CHAR_SMALL7,_img_smallseven)	
	loadCharpix(CONST_CHAR_SMALL8,_img_smallheight)
// 	loadCharpix(CONST_CHAR_SMALL9,_img_smallnine)				
    case CONST_CHAR_STO: 
      SDL_BlitSurface(_img_sto, NULL, _ecran, &pos);      
      break;       
    case '=': 
      SDL_BlitSurface(_img_equal, NULL, _ecran, &pos);
      break;       
    case '+': 
      SDL_BlitSurface(_img_plus, NULL, _ecran, &pos);
      break; 
    case '^': 
      SDL_BlitSurface(_img_pow, NULL, _ecran, &pos);
      break;       
    case ':': 
      SDL_BlitSurface(_img_twoDots, NULL, _ecran, &pos);
      break;    
    case '&': 
      SDL_BlitSurface(_img_smallone, NULL, _ecran, &pos); 
      break;  
    case '~': 
      SDL_BlitSurface(_img_smalltwo, NULL, _ecran, &pos); 
      break;    
    case '#': 
      SDL_BlitSurface(_img_smallthree, NULL, _ecran, &pos); 
      break; 
    case CONST_CHAR_SMALL4: 
      SDL_BlitSurface(_img_smallfour, NULL, _ecran, &pos); 
      break;         
    case '(': 
      SDL_BlitSurface( _img_leftParenthesis, NULL, _ecran, &pos); 
      break;      
    case ')': 
      SDL_BlitSurface( _img_rightParenthesis, NULL, _ecran, &pos); 
      break;
    case '*': 
      SDL_BlitSurface( _img_star, NULL, _ecran, &pos);       
      break;  
    case '/': 
      SDL_BlitSurface( _img_slash, NULL, _ecran, &pos);       
      break;      
    case '-': 
      SDL_BlitSurface( _img_minus, NULL, _ecran, &pos);       
      break;   
    case '.': 
      SDL_BlitSurface( _img_dot, NULL, _ecran, &pos);       
      break;         
  }
  
 if (invert)
   blink(x,y);
     _areasToRedisplay.push_back(pair<int,int>(x,y));
}

int CharPutter::putString(string s, int x, int y,bool invert)
{
  if (s.size()==0)
    return y+1;
 for (int i=0;i<s.size();i++)
  {  if (x>_dim_X)
    {
      x=1;
      y++;
    }
    if (y>_dim_Y)
      return y;
//     cout<<i<<" "<<x<<" "<<y<<" "<<s[i]<<endl;
    if (y>0)
    putChar(s[i],x,y,invert);
    x++;
  
  }
  return y+1;
}

int CharPutter::blink(int x, int y)
{
 x=(x-1)*6;
 y=(y-1)*8;
Uint8 r,g,b,a;
 for (int i=x;i<x+6 and i<96;i++)
    for (int j=y;j<y+8;j++)  
    {
      Uint32 pix= obtenirPixel(_ecran, i, j);
      SDL_GetRGBA(pix, _ecran->format, &r, &g, &b, &a);
      pix=SDL_MapRGBA(_ecran->format, 255-r, 255-g, 255-b, 255);
      definirPixel(_ecran,i,j,pix);
    }
    _areasToRedisplay.push_back(pair<int,int>(x,y));
}


void CharPutter::clear()
{
   _heightCurentlyUsed=1;
     
  for (int i=0;i<8;i++)
  {
  mat[i]="                ";  
  }
        SDL_FillRect( _ecran, NULL, SDL_MapRGB(_ecran->format, 255, 255, 255)); 
	_needFullRedisplay=true;
}

void CharPutter::refreshScreen()
{
   if (_needFullRedisplay)
  adaptSurface(_ecran,_display);
  else
  {
   for (int i=0;i<_areasToRedisplay.size();i++)
   {
    adaptSurface(_ecran,_display,6*(_areasToRedisplay[i].first-1),6*(_areasToRedisplay[i].first-1)+5,8*(_areasToRedisplay[i].second-1),8*(_areasToRedisplay[i].second-1)+7); 
   }
  }
   SDL_Flip(_display);
   _needFullRedisplay=false;
   _areasToRedisplay.clear();
  
}

string CharPutter::getBuffer()
{
string s;
for (int i=0;i<_heightCurentlyUsed;i++)
  s=s+mat[i];
return s;
}

