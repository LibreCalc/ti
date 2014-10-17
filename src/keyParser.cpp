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

#include "keyParser.h"
#include <iostream>
#include "constantSpecialChar.h"
using namespace std;
bool keyParser::isChar(SDL_keysym k)
{
        //WARNING old method
// if (k==SDLK_x or k==SDLK_KP_PLUS or k==SDLK_LEFTPAREN or k==SDLK_KP_MULTIPLY  or k==SDLK_KP_MINUS or k==SDLK_KP_PLUS
//    or k==SDLK_LEFTPAREN or k==SDLK_KP_MULTIPLY or k==SDLK_KP_MINUS or k==SDLK_KP_DIVIDE or k==SDLK_RIGHTPAREN 
//    or k==SDLK_KP1 or k==SDLK_KP2 or k==SDLK_KP3 or k==SDLK_KP4 or k==SDLK_KP5 or k==SDLK_KP6 or k==SDLK_KP7
//    or k==SDLK_KP8 or k==SDLK_KP9 or  k==SDLK_KP0 or  k==SDLK_0 or k== SDLK_KP_PERIOD)
// return true;

 if ( (k.unicode & 0xFF80) == 0 ) {
	char c=(k.unicode & 0x7F);
	if ( c>='a' and c <='z')
	   c+='A'-'a';
	if (c=='0' or c=='1' or c=='2' or c=='3' or c=='4' or c=='5' or c=='6' or c=='7' or c=='8' or c=='9'
	  or c=='x' or c=='X' or c=='/' or c=='*' or c=='-' or c=='+' or c=='.' or c=='(' or c==')' or c=='^' or c=='\"' or c=='{' or c==',' or c=='}' or
	  c=='A' or c=='B' or c=='C' or c=='D' or c=='E' or c=='F' or c=='G' or c=='H' or c=='I' or c=='J' or c=='K' or c=='L' or c=='i' 
	or c=='M' or c=='N' or c=='O' or c=='P' or c=='Q' or c=='R' or c=='S' or c=='T' or c=='U' or c=='V' or c=='W' or c=='X' or c=='Y' or c=='Z' or c=='<' or c=='S' or c=='Y')
	  return true;
      } 
return false;
}


int keyParser::getChar(SDL_keysym k)
{ 
 if ( (k.unicode & 0xFF80) == 0 ) {
	  int res=char(k.unicode & 0x7F);
	  if (res=='s')
	    res=(int)CONST_SPE_SIN;
	  if (res=='l')
	    res=(int)CONST_SPE_L1;	
	  if (res=='m')
	    res=(int)CONST_SPE_L2;	  
	  if (res=='i')
	  {
	    res=(int)'i';
	    return res;
	  }
	  if (res=='d')
	    res=(int)CONST_SPE_DIM;	  
	  if ( res>='a' and res <='z')
	    res+='A'-'a';
	  if (res=='<')
	  {
	    res=CONST_CHAR_STO ;
	  }
	 
	
	return res;		      
      }  

		  
}
