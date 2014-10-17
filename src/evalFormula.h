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

#ifndef EVAL_FORMULA_H
#define EVAL_FORMULA_H
#include <string>
#include "tiConfig.h"
#include "tiString.h"
#include "tiVariant.h"

using namespace std;
TiVariant eval(TiString s, TiVariant x, TiConfig& config);

namespace evalFormula{
bool isSuroundedByUselessParenthesis(TiString s);
bool isNumber(TiString s, double& theNumber);
bool isString(TiString s, string& theNumber);
bool isList(TiString s, vector<TiString>& theList);
int findCharOutsideOfParenthesis(TiString s, int c);
bool isSuroundedByParFct(TiString s,int fct);
int handleRandInt(TiString s,double x, TiConfig& config);
void checkForLackingParenthesis(TiString &s);
vector<TiString> ParseComas(TiString );
}
#endif