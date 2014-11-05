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

#ifndef MENU_H
#define MENU_H
#include "charPutter.h"
#include "tiString.h"
#include <vector>
class Menu{
public: 
  /**
   * @brief Création d'un menu simple
   * 
   * @param cputt le charPutter
   * @param title l'unique titres
   * @param choices l'unique liste de choix
   */
  Menu(CharPutter *cputt,TiString title,vector<TiString> choices);
  
  /**
   * @brief Création d'un menu à multiple titres en haut
   * 
   * @param cputt le charPutter
   * @param title la liste des titres
   * @param choices la liste des liste de choix
   */
  Menu(CharPutter *cputt,vector<TiString> title,vector< vector<TiString> > choices);
  
  int getSelectedTitle();
  int getSelectedItem();
  TiString getSelectedString();
  void reDisplay();
  void sendKey(SDL_keysym  k);
private:
  void changeTitle(bool left);
  
  
  
  CharPutter *_cputt;
  TiString _title;
  vector<TiString> _choices; 
  
  bool _isMultipleMenu;
  vector<TiString> _multipleTitles;
  vector<vector<TiString> > _multipleChoices;
  int _selectedTitle;
  
  
  int _currentSectedItem;
  int _currentOffset;
};


#endif