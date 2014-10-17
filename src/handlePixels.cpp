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
#include <iostream>

using namespace std;

/* ********************************************************************* */
/*obtenirPixel : permet de'obtenir la couleur d'un pixel
Paramètres d'entrée/sortie :
SDL_Surface *surface : la surface sur laquelle on va obtenir la couleur d'un pixel
int x : la coordonnée en x du pixel à obtenir
int y : la coordonnée en y du pixel à obtenir
*/
#define  obtenirPixel(surf,x,y) *((Uint8 *)surf->pixels + y * surf->pitch + x)/*
inline Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)
{
/*    /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.
    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
    de l'image : 8, 16, 24 ou 32 bits.*/
//     int nbOctetsParPixel = surface->format->BytesPerPixel;
    /* Ici p est l'adresse du pixel que l'on veut connaitre */
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
//     Uint8 *p =*/ 
    
//    return *((Uint8 *)surface->pixels + y * surface->pitch + x);

//     /*Gestion différente suivant le nombre d'octets par pixel de l'image*/
//     switch(nbOctetsParPixel)
//     {
//         case 1:
//             return *p;
// 
//         case 2:
//             return *(Uint16 *)p;
// 
//         case 3:
//             /*Suivant l'architecture de la machine*/
//             if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
//                 return p[0] << 16 | p[1] << 8 | p[2];
//             else
//                 return p[0] | p[1] << 8 | p[2] << 16;
// 
//         case 4:
//             return *(Uint32 *)p;
// 
//         /*Ne devrait pas arriver, mais évite les erreurs*/
//         default:
//             return 0; 
//     }
//}
/* ********************************************************************* */
/*definirPixel : permet de modifier la couleur d'un pixel
Paramètres d'entrée/sortie :
SDL_Surface *surface : la surface sur laquelle on va modifier la couleur d'un pixel
int x : la coordonnée en x du pixel à modifier
int y : la coordonnée en y du pixel à modifier
Uint32 pixel : le pixel à insérer
*/

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{   /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.
    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
    de l'image : 8, 16, 24 ou 32 bits.*/
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    /*Ici p est l'adresse du pixel que l'on veut modifier*/
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    /*Gestion différente suivant le nombre d'octets par pixel de l'image*/
    switch(nbOctetsParPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}



void
putpixel (SDL_Surface *ecran,int xe, int ye, Uint32 couleur);

void
ligne (SDL_Surface *ecran,int x0, int y0, int x1, int y1)
{
  Uint32 c=SDL_MapRGBA(ecran->format, 0, 0, 0, 255);
  int dx, dy, x, y, residu, absdx, absdy, pasx, pasy, i;
  dx = x1 - x0;
  dy = y1 - y0;
  residu = 0;			/* il s’agit d’une division euclidienne, avec quotient et reste */
  x = x0;
  y = y0;
  definirPixel(ecran,x,y, c);
  if (dx > 0)
    pasx = 1;
  else
    pasx = -1;
  if (dy > 0)
    pasy = 1;
  else
    pasy = -1;
  absdx = abs (dx);
  absdy = abs (dy);
  if (dx == 0)
    for (i = 0; i < absdy; i++)
      {
	y += pasy;
	definirPixel(ecran,x, y, c);
      }
/* segment vertical, vers le haut ou vers l bas */
  else if (dy == 0)
    for (i = 0; i < absdx; i++)
      {
	x += pasx;
	definirPixel(ecran,x, y, c);
      }
/* segment horizontal, vers la droite ou vers la gauche */
  else if (absdx == absdy)
    for (i = 0; i < absdx; i++)
      {
	x += pasx;
	y += pasy;
	definirPixel(ecran,x, y, c);
      }
/* segment diagonal dans les 4 cas possibles */
  else if (absdx > absdy)	/* pente douce */
    for (i = 0; i < absdx; i++)
      {
	x += pasx;
	residu += absdy;
	if (residu >= absdx)
	  {
	    residu -= absdx;
	    y += pasy;
	  }
	definirPixel(ecran,x, y, c);
      }
  else
    for (i = 0; i < absdy; i++)	/* pente forte */
      {
	y += pasy;
	residu += absdx;
	if (residu >= absdy)
	  {
	    residu -= absdy;
	    x += pasx;
	  }
	definirPixel(ecran,x, y, c);
      }
}



void adaptSurface(SDL_Surface* toAdapt, SDL_Surface* output, int x1, int x2, int y1, int y2)
{ 
  static bool prev[96][68]={0};
  Uint32 old_time;
  old_time=SDL_GetTicks();
  
  if (x1==-1)
  {
    x1=0; x2=toAdapt->w;
    y1=0;y2=toAdapt->h;
  }
  double multFactorfw=1.0*(output->w)/(toAdapt->w);
  int multFactorw=int((output->w)/(toAdapt->w));
  
  double multFactorfh=1.0*(output->h)/(toAdapt->h);
  int multFactorh=int((output->h)/(toAdapt->h));
  
  SDL_Surface *blackRect=SDL_CreateRGBSurface(SDL_SWSURFACE,multFactorw+(multFactorw!=multFactorfw),multFactorh+(multFactorh!=multFactorfh),32,0,0,0,0);
  SDL_FillRect( blackRect, NULL, SDL_MapRGB(blackRect->format, 0, 0, 0));
  SDL_Surface *whiteRect=SDL_CreateRGBSurface(SDL_SWSURFACE,multFactorw+(multFactorw!=multFactorfw),multFactorh+(multFactorh!=multFactorfh),32,0,0,0,0);
  SDL_FillRect( whiteRect, NULL, SDL_MapRGB(whiteRect->format, 255, 255, 255));  
  Uint8 r,g,b,a,r2,g2,b2,a2;
  
  SDL_LockSurface(toAdapt);
 // SDL_LockSurface(output);
  
    SDL_Rect rect;
    for (int i=x1; i<x2; i++)
        for (int j=y1; j<y2; j++)
        {
            SDL_GetRGBA(obtenirPixel(toAdapt, i, j), toAdapt->format, &r, &g, &b, &a);

            if (prev[i][j]==0 and r+g+b>300)        
	    {
	    rect.x=int(i*multFactorfw);
            rect.y=int(j*multFactorfh);
                    SDL_BlitSurface(whiteRect,NULL,output,&rect);
	    }
            prev[i][j]=((r+g+b)>=300?true:false);
        }
        
    for (int i=x1; i<x2; i++)
        for (int j=y1; j<y2; j++)
        {
            if(!prev[i][j])
            {
                rect.x=int(i*multFactorfw);
                rect.y=int(j*multFactorfh);
                SDL_BlitSurface(blackRect,NULL,output,&rect);
            }
        }
   
  SDL_UnlockSurface(toAdapt);
 // SDL_UnlockSurface(output);
   
   int diff=SDL_GetTicks()-old_time;
   
   free(blackRect);
   free(whiteRect);   
   if (diff>0)
     cout<<"Warning resizing window is too slow: it took "<<diff<<" ms"<<endl;
}


// void
// afficherPoint (SDL_Surface *ecran, int x, int y)
// {
//  Uint32 rouge;
//  rouge=SDL_MapRGB(ecran->format,255,0,0);
//    ligne(ecran,x-5,y,x+5,y,rouge);
//    ligne(ecran,x,y-5,x,y+5,rouge);
// }
// 
