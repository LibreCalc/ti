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
#include "constantSpecialChar.h"
#include <iostream>

  int variables[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
		    ,CONST_CHAR_THETA,CONST_SPE_L1,CONST_SPE_L2,CONST_SPE_L3,CONST_SPE_L4,CONST_SPE_L5,CONST_SPE_L6,CONST_SPE_L7,CONST_SPE_L8,CONST_SPE_L9,
		    CONST_SPE_MATA,CONST_SPE_MATB,CONST_SPE_MATC,CONST_SPE_MATD,CONST_SPE_MATE,CONST_SPE_MATF,CONST_SPE_MATG,CONST_SPE_MATH,CONST_SPE_MATI,
		    CONST_SPE_YMIN,CONST_SPE_YMAX,CONST_SPE_YSCL,CONST_SPE_XMIN,CONST_SPE_XMAX,CONST_SPE_XSCL};
		    
using namespace std;
TiConfig::TiConfig(){
  _variables.clear();

  vector<TiVariant> titab;titab.push_back(TiVariant(3));titab.push_back(TiVariant(4));
  TiVariant mat(2);
  mat.setDim(2,2);
  for (int i=0;i< sizeof(variables) / sizeof(int);i++)
  { 
        if (variables[i]>=CONST_SPE_L1 and variables[i]<=CONST_SPE_L9)
            _variables.insert( std::pair<int,TiVariant>(variables[i],TiVariant(titab)) );
        else if (variables[i]>=CONST_SPE_MATA and variables[i]<=CONST_SPE_MATI)
            _variables.insert( std::pair<int,TiVariant>(variables[i],mat) );
        else
            _variables.insert( std::pair<int,TiVariant>(variables[i],TiVariant(3)) );
  }
  
  _variables[CONST_SPE_YMIN]=-10;
  _variables[CONST_SPE_YMAX]=10;
  _variables[CONST_SPE_YSCL]=1;  
  _variables[CONST_SPE_XMIN]=-10;
  _variables[CONST_SPE_XMAX]=10; 
  _variables[CONST_SPE_XSCL]=1;   
  for (int i=0;i<9;i++)
    _functionsToPlot.push_back(TiString());
  _Ans=0;
}

TiVariant TiConfig::getVariableValue(int c)
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


void TiConfig::setVariableValue(int c, TiVariant value)
{
_variables[c]=value;
}

TiVariant& TiConfig::getVariable(int c)
{
  return _variables[c];
}

#include <iostream>
using namespace std;
bool TiConfig::isVariable(int c)
{
  if (c>='A' and c<='Z')
    return true;
  //warning TODO pretty slow!!!
  for (int i=0;i< sizeof(variables) / sizeof(int);i++)
  {
    if(variables[i]==c)
      return true;
 }
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
