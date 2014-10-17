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

#ifndef HANDLE_PIXEL_H
#define HANDLE_PIXEL_H
inline Uint32 obtenirPixel(SDL_Surface *surface, int x, int y); 

inline void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void ligne (SDL_Surface *ecran,int x0, int y0, int x1, int y1);
void adaptSurface(SDL_Surface *toAdapt,SDL_Surface *output);
#endif