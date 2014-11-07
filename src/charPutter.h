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
#include <set>

using namespace std;

#ifndef CHAR_PUTTER_H
#define CHAR_PUTTER_H

/**
 * @brief Cette classe permet de gérer l'affichage de caractères à l'écran. 
 */
class CharPutter
{
public:
 CharPutter(SDL_Surface *ecran, SDL_Surface *display, int dim_X,int dim_Y );
 void putChar(char c,int x,int y,bool invert);
 int putString(string s,int x,int y,bool invert=false);
 int disp(string s); 
 int blink(int x, int y);
 void clear();
 void refreshScreen();
 string getBuffer();
 
 //WARNING Temparary
 SDL_Surface *getDisplay();
 SDL_Surface *getScreen(); 
private:
  int _dim_X;
  int _dim_Y;
  string mat[8];
  int _heightCurentlyUsed;
  SDL_Surface *_ecran;
  SDL_Surface *_display;
  SDL_Surface *_img_1;
  SDL_Surface *_img_2;
  SDL_Surface *_img_3;
  SDL_Surface *_img_4;
  SDL_Surface *_img_5;  
  SDL_Surface *_img_6; 
  SDL_Surface *_img_7;
  SDL_Surface *_img_8;
  SDL_Surface *_img_9;
  SDL_Surface *_img_0;    
  SDL_Surface *_img_Y;   
  SDL_Surface *_img_X; 
  SDL_Surface *_img_A;
  SDL_Surface *_img_B;  
  SDL_Surface *_img_C;  
  SDL_Surface *_img_D;
  SDL_Surface *_img_E;
  SDL_Surface *_img_F;  
  SDL_Surface *_img_H;   
  SDL_Surface *_img_I;
  SDL_Surface *_img_K;  
  SDL_Surface *_img_S;
  SDL_Surface *_img_T;
  SDL_Surface *_img_L; 
  SDL_Surface *_img_M;
  SDL_Surface *_img_N;  
  SDL_Surface *_img_G;     
  SDL_Surface *_img_R;
  SDL_Surface *_img_Q;
  SDL_Surface *_img_Z;  
  SDL_Surface *_img_J;
  SDL_Surface *_img_O;
  SDL_Surface *_img_U;  
  SDL_Surface *_img_V; 
  SDL_Surface *_img_W;  
  SDL_Surface *_img_b;
  SDL_Surface *_img_d;
  SDL_Surface *_img_f;  
  SDL_Surface *_img_s;
  SDL_Surface *_img_e;
  SDL_Surface *_img_m; 
  SDL_Surface *_img_g; 
  SDL_Surface *_img_a;
  SDL_Surface *_img_v;  
  SDL_Surface *_img_k; 
  SDL_Surface *_img_t;   
  SDL_Surface *_img_o;
  SDL_Surface *_img_u;  
  SDL_Surface *_img_i;
  SDL_Surface *_img_n;  
  SDL_Surface *_img_l;
  SDL_Surface *_img_h;
  SDL_Surface *_img_p;  
  SDL_Surface *_img_y;  
  SDL_Surface *_img_r; 
  SDL_Surface *_img_x;  
  SDL_Surface *_img_c; 
  SDL_Surface *_img_w;   
  SDL_Surface *_img_theta;  
  SDL_Surface *_img_pi;  
  SDL_Surface *_img_P;   
  SDL_Surface *_img_crochetgauche;   
  SDL_Surface *_img_crochetdroit; 
  SDL_Surface *_img_superior; 
  SDL_Surface *_img_inferior;   
  SDL_Surface *_img_inferiorEq;   
  SDL_Surface *_img_degree;    
  SDL_Surface *_img_plus;
  SDL_Surface *_img_rightParenthesis; 
  SDL_Surface *_img_leftParenthesis; 
  SDL_Surface *_img_twoDots; 
  SDL_Surface *_img_equal; 
  SDL_Surface *_img_smallone;  
  SDL_Surface *_img_smalltwo;  
  SDL_Surface *_img_smallthree;   
  SDL_Surface *_img_smallfour;   
  SDL_Surface *_img_smallfive; 
  SDL_Surface *_img_smallsix;   
  SDL_Surface *_img_smallseven;   
  SDL_Surface *_img_smallheight;   
  SDL_Surface *_img_smallnine;   
  SDL_Surface *_img_star;
  SDL_Surface *_img_slash;   
  SDL_Surface *_img_minus;  
  SDL_Surface *_img_small_minus;   
  SDL_Surface *_img_dot;   
  SDL_Surface *_img_pow;
  SDL_Surface *_img_sto;  
  SDL_Surface *_voidchar;  
  SDL_Surface *_img_guillemet; 
  SDL_Surface *_img_accoladegauche; 
  SDL_Surface *_img_accoladedroite;  
  SDL_Surface *_img_virgule;   
  SDL_Surface *_clearZone;
  SDL_Surface *_img_exclamation; 
  
  vector<pair<int,int> > _areasToRedisplay;
  bool _needFullRedisplay;
};

#endif