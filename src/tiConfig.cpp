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

#include "tiConfig.h"
#include "keyParser.h"

TiConfig::TiConfig(){
  char variables[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',CONST_CHAR_THETA};
  vector<TiVariant> titab;titab.push_back(TiVariant(3));titab.push_back(TiVariant(4));
  for (int i=0;i< sizeof(variables) / sizeof(char);i++)
    _variables.insert( std::pair<char,TiVariant>(variables[i],TiVariant(titab)) );
  for (int i=0;i<4;i++)
    _functionsToPlot.push_back(TiString());
  _Ans=0;
  
}

TiVariant TiConfig::getVariableValue(char c)
{
return _variables[c];
}

TiString& TiConfig::getFunctionsToPlot(int i)
{
  if (i>=0 and i<_functionsToPlot.size())
      return _functionsToPlot[i];
  else return _functionsToPlot[0];
}

void TiConfig::setFunctionToPlot(int i,TiString s)
{
    if (i>=0 and i<_functionsToPlot.size())
      return _functionsToPlot[i]=s;
}


void TiConfig::setVariableValue(char c, TiVariant value)
{
_variables[c]=value;
}


bool TiConfig::isVariable(char c)
{
 for (std::map<char,TiVariant>::iterator it=_variables.begin(); it!=_variables.end(); ++it)
    if(it->first==c)
      return true;
     
   return false;
}

TiVariant TiConfig::getAns()
{
return _Ans;
}

void TiConfig::setAns(TiVariant Ans)
{
_Ans=Ans;
}
