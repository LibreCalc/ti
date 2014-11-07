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

/**
 * @brief Fonction importante: permet d'évaluer la valeur d'une expression qui se trouve dans une chaine de caractères.
 * 
 * @param s La chaine de caractères
 * @param x La valeur de la variable x désirée
 * @param config La configuration actuelle de la TI
 * @return la valeur de l'expression
 */
TiVariant eval(TiString s, TiVariant x, TiConfig& config);

namespace evalFormula{
bool isSuroundedByUselessParenthesis(TiString s);
bool isNumber(TiString s, double& theNumber);
bool isString(TiString s, string& theNumber);
bool isList(TiString s, vector<TiString>& theList);
bool isMatrix(TiString s, vector<vector<TiString > >& theMatrix);
int findCharOutsideOfParenthesis(TiString s, int c);
bool isSuroundedByParFct(TiString s,int fct);
int handleRandInt(TiString s,double x, TiConfig& config);
int handlePixelTest(TiString s,double x, TiConfig& config);
void checkForLackingParenthesis(TiString &s);
vector<TiString> ParseComas(TiString );
}
#endif