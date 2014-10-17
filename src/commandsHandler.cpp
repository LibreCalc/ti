#include "commandsHandler.h"
#include "keyParser.h"
#include "evalFormula.h"
#include <iostream>

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

using namespace std;
TiVariant SendCommand( TiString s, TiConfig& conf)
{
 
  TiVariant res;
  int sto=findSto(s);

  if (sto==-1)
  {
   res=eval(s,conf.getVariableValue('X'),conf);
   conf.setAns(res);
   return res;
  }
  
  if (sto==s.size()-2 and s.size()>2)
  {
    int var=s[s.size()-1];
    //TODO
   // s=string(s.begin(),s.begin()+s.size()-2);
    s.erase(s.size()-1);
    s.erase(s.size()-1);    
    res=eval(s,conf.getVariableValue('X'),conf);
    conf.setVariableValue(var,res);
   conf.setAns(res);   
    return res;
  }
  
  if(sto<s.size()-2 and s.size()>2 and s[sto+1]==CONST_SPE_DIM)
  {
    TiString s2=s.subString(0,sto);
    res=eval(s2,conf.getVariableValue('X'),conf);
    conf.getVariable(s[sto+2]).setDim(res);
    conf.setAns(res);   
    return res;
  }
  
  if(sto<s.size()-3 and s.size()>3 and conf.isVariable(s[sto+1]) and s[sto+2]=='(')
  {
    TiString s2= s.subString(sto+3,s.size());
    if (s2[s2.size()-1]==')')
      s2.erase(s2.size()-1);
    TiString s3=s.subString(0,sto);
    res=eval(s3,conf.getVariableValue('X'),conf);
    vector<TiString> strs=evalFormula::ParseComas(s2);
    //List
    if (strs.size()==1)
    {
    int pos=eval(s2,conf.getVariableValue('X'),conf).toDouble();
    TiString test; test.push_back(s[sto+1]);
    conf.getVariable(s[sto+1]).setListCase(pos-1,res);
    }
    
    //Matrices
    if (strs.size()==2)
    {
    int posi=eval(strs[0],conf.getVariableValue('X'),conf).toDouble();
    int posj=eval(strs[1],conf.getVariableValue('X'),conf).toDouble();    
    conf.getVariable(s[sto+1]).accesMatrixValue(posi,posj)=res;
    }
  }
  conf.setAns(res);

  
  return res;
}

int findSto(TiString s)
{
for (int i=0;i<s.size();i++)
  if (s[i]==CONST_CHAR_STO)
    return i;
  return -1;
}

