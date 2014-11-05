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

#ifndef TI_STRING_H
#define TI_STRING_H
#include "constantSpecialChar.h"

#include <vector>
#include <string>

using namespace std;

class TiString
{
public:
  TiString();
  TiString(const TiString &other);
  ~TiString();
  TiString  (int character);
  TiString(string s);  
  string toStdString();
  int size() const;
  int& operator[](int i);
  void push_back(int c);
  void push_back(string s); 
  void clear();
  int getCursorPosInStdStr(int crsPosInTiStr);
  int getCursorUpLine(int crsPosInTiStr);  
  int getCursorDownLine(int crsPosInTiStr);    
  void erase(int i);
  void insert(int i,int c);
  TiString subString(int i,int j);
  TiString operator+ (const TiString &other);
  void operator= (const TiString &other);  
  
private:
  vector<int> _data; 
  
};







#endif