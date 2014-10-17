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
#include "keyParser.h"

map<specialChars,string> init_const()
{
   string smallfour;smallfour.push_back(CONST_CHAR_SMALL4);
 string smallfive;smallfive.push_back(CONST_CHAR_SMALL5); 
 string smallsix;smallsix.push_back(CONST_CHAR_SMALL6); 
 string smallseven;smallseven.push_back(CONST_CHAR_SMALL7);  
 string smallheight;smallheight.push_back(CONST_CHAR_SMALL8);  
 string smallnine;smallnine.push_back(CONST_CHAR_SMALL9); 
 
  map<specialChars,string> res;
  res.insert(pair<specialChars,string>(CONST_SPE_SIN,string("sin(")));
  res.insert(pair<specialChars,string>(CONST_SPE_IF,string("If ")));
  res.insert(pair<specialChars,string>(CONST_SPE_END,string("End ")));   
  res.insert(pair<specialChars,string>(CONST_SPE_THEN,string("Then ")));  
  res.insert(pair<specialChars,string>(CONST_SPE_ELSE,string("Else ")));    
  res.insert(pair<specialChars,string>(CONST_SPE_WHILE,string("While ")));   
  res.insert(pair<specialChars,string>(CONST_SPE_OUTPUT,string("Output(")));    
  res.insert(pair<specialChars,string>(CONST_SPE_CLEARHOME,string("ClrHome")));    
  res.insert(pair<specialChars,string>(CONST_SPE_RANDINT,string("RandInt(")));  
  res.insert(pair<specialChars,string>(CONST_SPE_AND,string(" And "))); 
  res.insert(pair<specialChars,string>(CONST_SPE_OR,string(" Or ")));   
  res.insert(pair<specialChars,string>(CONST_SPE_GETKEY,string("GetKey ")));  
  res.insert(pair<specialChars,string>(CONST_SPE_FOR,string("For("))); 
  res.insert(pair<specialChars,string>(CONST_SPE_LABEL,string("Lbl "))); 
  res.insert(pair<specialChars,string>(CONST_SPE_GOTO,string("Goto ")));
  res.insert(pair<specialChars,string>(CONST_SPE_NOT,string("Not("))); 
  res.insert(pair<specialChars,string>(CONST_SPE_PAUSE,string("Pause "))); 
  res.insert(pair<specialChars,string>(CONST_SPE_REPEAT,string("Repeat ")));  
  res.insert(pair<specialChars,string>(CONST_SPE_ANS,string("Ans")));
  res.insert(pair<specialChars,string>(CONST_SPE_RAND,string("RAND")));  
  res.insert(pair<specialChars,string>(CONST_SPE_ROUND,string("Round(")));   
  res.insert(pair<specialChars,string>(CONST_SPE_INT,string("int(")));  
  res.insert(pair<specialChars,string>(CONST_SPE_DELVAR,string("DelVar")));  
  res.insert(pair<specialChars,string>(CONST_SPE_DISP,string("Disp(")));  
  res.insert(pair<specialChars,string>(CONST_SPE_RETURN,string("Return ")));
  res.insert(pair<specialChars,string>(CONST_SPE_MENU,string("Menu("))); 
  res.insert(pair<specialChars,string>(CONST_SPE_DIM,string("Dim(")));  
  res.insert(pair<specialChars,string>(CONST_SPE_FILL,string("Fill(")));
  res.insert(pair<specialChars,string>(CONST_SPE_CLRLIST,string("ClrList "))); 
  res.insert(pair<specialChars,string>(CONST_SPE_INPUT,string("Input ")));  
  res.insert(pair<specialChars,string>(CONST_SPE_STOP,string("Stop ")));    
  res.insert(pair<specialChars,string>(CONST_SPE_L1,string("L&")));  
  res.insert(pair<specialChars,string>(CONST_SPE_L2,string("L~")));  
  res.insert(pair<specialChars,string>(CONST_SPE_L3,string("L#")));
  res.insert(pair<specialChars,string>(CONST_SPE_L4,string("L")+smallfour)); 
  res.insert(pair<specialChars,string>(CONST_SPE_L5,string("L")+smallfive));  
  res.insert(pair<specialChars,string>(CONST_SPE_L6,string("L")+smallsix));
  res.insert(pair<specialChars,string>(CONST_SPE_L7,string("L")+smallseven)); 
  res.insert(pair<specialChars,string>(CONST_SPE_L8,string("L")+smallheight)); 
  res.insert(pair<specialChars,string>(CONST_SPE_L9,string("L")+smallnine));   
  res.insert(pair<specialChars,string>(CONST_SPE_MATA,string("[[A]]"))); 
  res.insert(pair<specialChars,string>(CONST_SPE_MATB,string("[[B]]"))); 
  res.insert(pair<specialChars,string>(CONST_SPE_MATC,string("[[C]]")));  
  res.insert(pair<specialChars,string>(CONST_SPE_MATD,string("[[D]]"))); 
  res.insert(pair<specialChars,string>(CONST_SPE_MATE,string("[[E]]")));    
  res.insert(pair<specialChars,string>(CONST_SPE_MATF,string("[[F]]")));    
  res.insert(pair<specialChars,string>(CONST_SPE_MATG,string("[[G]]")));  
  res.insert(pair<specialChars,string>(CONST_SPE_MATH,string("[[H]]")));  
  res.insert(pair<specialChars,string>(CONST_SPE_MATI,string("[[I]]")));    
  return res;
}

map<specialChars,string> specialCharsText=init_const();

int& TiString::operator[](int i)
{
return _data[i];
}

TiString::TiString(string s)
{
 for (int i=0;i<s.size();i++)
   _data.push_back(s[i]);
}


void TiString::push_back(int c)
{
_data.push_back(c);
}

void TiString::push_back(string s)
{
for (int i=0;i<s.size();i++)
  push_back(s[i]);
}

void TiString::clear()
{
_data.clear();
}



int TiString::size() const
{
return _data.size();
}

TiString::TiString()
{

}
#include <iostream>

using namespace std;

TiString::TiString(const TiString& other)
{
_data=other._data;
}

TiString TiString::subString(int i, int j)
{
TiString res;
res._data=vector<int>(_data.begin()+i,_data.begin()+j);
  
return res;
}

TiString::~TiString()
{
_data.clear();
}


string TiString::toStdString()
{
string res;
for (int i=0;i<_data.size();i++)
  if (_data[i]>=-128 and _data[i]<=255)
    res.push_back(char(_data[i]));
   else
    res=res+specialCharsText.at((specialChars)_data[i]);
   return res;
}


int TiString::getCursorPosInStdStr(int crsPosInTiStr)
{
  int res=0;
  for (int i=0;i<crsPosInTiStr;i++)
  if (_data[i]>=-128 and _data[i]<=255)
    res++;
   else
    res=res+specialCharsText.at((specialChars)_data[i]).size();
return res; 
}


void TiString::erase(int i)
{
_data.erase(_data.begin()+i);
}

void TiString::insert(int i, int c)
{
_data.insert(_data.begin()+i,c);
}

TiString TiString::operator+(const TiString &other)
{
TiString res;
res._data=_data;
if (other._data.size()>0)
res._data.insert( res._data.end(), other._data.begin(), other._data.end() );
return res;

}

int TiString::getCursorDownLine(int crsPosInTiStr)
{
  int init=getCursorPosInStdStr(crsPosInTiStr);
while (crsPosInTiStr<size() and getCursorPosInStdStr(crsPosInTiStr)-init<16)
  crsPosInTiStr++;
return crsPosInTiStr;
}

int TiString::getCursorUpLine(int crsPosInTiStr)
{
  int init=getCursorPosInStdStr(crsPosInTiStr);
if (toStdString().size()<16)
  return crsPosInTiStr;
while (crsPosInTiStr>0 and init-getCursorPosInStdStr(crsPosInTiStr)<16)
  crsPosInTiStr--;
return crsPosInTiStr;
}

void TiString::operator=(const TiString& other)
{
 _data=other._data;
}

