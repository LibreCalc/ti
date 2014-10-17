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

#include <string>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include "evalFormula.h"
#include "keyParser.h"

using namespace std;
using namespace evalFormula;

TiVariant eval(TiString s, TiVariant x, TiConfig& config)
{
  
  while (s.size()>0 and s[0]==' ')
    s.erase(0);
  
  //cas vide
  if (s.size()==0)
    return-1;
  
  checkForLackingParenthesis(s);
 /*-------------------------------------------
  *  Check if it is possible to remove parenthesis at the begining and end
  * -------------------------------------------*/
  if (isSuroundedByUselessParenthesis(s))
   return  eval(s.subString(1,s.size()-1),x,config);
  
   /*---------------------------------------------------
  * S'il s'agit de la variable X on retourne sa valeur
  * --------------------------------------------------*/
 if (s.toStdString()=="X")
   return x;
 
    /*---------------------------------------------------
  * S'il s'agit de ANS
  * --------------------------------------------------*/
 if (s.size()==1 and s[0]==CONST_SPE_ANS)
   return config.getAns();
 

 
   /*---------------------------------------------------
  * S'il s'agit d'une valeur de variable pré enregistré on la retourne
  * --------------------------------------------------*/
  if (s.size()==1 and config.isVariable(s[0]))
    return config.getVariableValue(s[0]);
  
    /*---------------------------------------------------
  * S'il s'agit de RAND
  * --------------------------------------------------*/
 if (s.size()==1 and s[0]==CONST_SPE_RAND)
 {
   return TiVariant(double(1.0*rand()/RAND_MAX));
 }
 
   /*-------------------------------------------
  *  Check small minus
  * -------------------------------------------*/ 
   if (s.size()>1 and s[0]==CONST_CHAR_SMALL_MINUS)
     return TiVariant(0.0)-eval(s.subString(1,s.size()),x,config);
 
   /*-------------------------------------------
  *  Check fonctions
  * -------------------------------------------*/
#define FONCTIONS_PAR  s[i]==CONST_SPE_SIN or s[i]==CONST_SPE_RANDINT or s[i]==CONST_SPE_NOT or s[i]==CONST_SPE_INT
  if (isSuroundedByParFct(s,CONST_SPE_SIN))
    return  sin(eval(s.subString(1,s.size()-1),x,config).toDouble());
  if (isSuroundedByParFct(s,CONST_SPE_RANDINT))
    return  TiVariant(handleRandInt(s.subString(1,s.size()-1),x.toDouble(),config));  
  if (isSuroundedByParFct(s,CONST_SPE_NOT))
    return  TiVariant(!(eval(s.subString(1,s.size()-1),x,config).toDouble()));
  if (isSuroundedByParFct(s,CONST_SPE_INT))
   { double val=eval(s.subString(1,s.size()-1),x,config).toDouble();return  TiVariant(int(val)-(val<0));}
  if (isSuroundedByParFct(s,CONST_SPE_ROUND))
   { double val=eval(s.subString(1,s.size()-1),x,config).toDouble();return  TiVariant(round(val));}   
  if (isSuroundedByParFct(s,CONST_SPE_DIM))
    return  eval(s.subString(1,s.size()-1),x,config).getDim();
 

  
  /*---------------------------------------------------------
  * S'il s'agit d'une valeur numérique on renvoit cette dernière
  * --------------------------------------------------*/
 double number;
 if (isNumber(s,number))
   return TiVariant(number);
 
   /*---------------------------------------------------------
  * S'il s'agit du nombre imagnaire renvois le
  * --------------------------------------------------*/
   if (s.size()==1 and s[0]=='i')
     return TiVariant(0,1);
 
  /*---------------------------------------------------------
  * S'il s'agit d'une chaine de carcatère revoit cette derniere
  * --------------------------------------------------*/
 string str;
 if (isString(s,str))
   return TiVariant(str); 
 
   /*---------------------------------------------------------
  * S'il s'agit d'une Liste renvoit cette derniere
  * --------------------------------------------------*/
 vector<TiString> strs;
 if (isList(s,strs))
 {
   vector<TiVariant> listres;
   for (int i=0;i<strs.size();i++)
   {
    listres.push_back(eval(strs[i],x,config));
   }
   return TiVariant(listres);
 }
 
 //TODO  optimise this
   /*------------------------------------------------------------------
  * Opérateur Logiques
  * ----------------------------------------------------------------*/ 
   {
  int posOR=findCharOutsideOfParenthesis(s,CONST_SPE_OR); 
  if (posOR!=-1)
    return (eval(s.subString(0,posOR),x,config)
	or eval(s.subString(posOR+1,s.size()),x,config));
  }
  
  {
  int posAND=findCharOutsideOfParenthesis(s,CONST_SPE_AND); 
  if (posAND!=-1)
    return (eval(s.subString(0,posAND),x,config)
	and eval(s.subString(posAND+1,s.size()),x,config));
  }
  
 
 
  /*------------------------------------------------------------------
  * Opérations ULTRA non-prioritaaires 
  * ----------------------------------------------------------------*/
  {
  int posSup=findCharOutsideOfParenthesis(s,'>'); 
  int posEq=findCharOutsideOfParenthesis(s,'=');  
  if (posSup!=-1 and posSup>posEq)
    return eval(s.subString(0,posSup),x,config)
	>eval(s.subString(posSup+1,s.size()),x,config);
  if (posEq!=-1 and posEq>posSup)
    return eval(s.subString(0,posEq),x,config)
    ==eval(s.subString(posEq+1,s.size()),x,config);
  
    int posnEq=findCharOutsideOfParenthesis(s,CONST_CHAR_DIFFERENT);  
   if (posnEq!=-1) 
  return eval(s.subString(0,posnEq),x,config)
    !=eval(s.subString(posnEq+1,s.size()),x,config);
    
    int posnDiwn=findCharOutsideOfParenthesis(s,'<');  
   if (posnDiwn!=-1) 
  return eval(s.subString(0,posnDiwn),x,config)
    <eval(s.subString(posnDiwn+1,s.size()),x,config);   
    
   posnDiwn=findCharOutsideOfParenthesis(s,CONST_CHAR_LESSOREQUAL);  
   if (posnDiwn!=-1) 
  return eval(s.subString(0,posnDiwn),x,config)
    <=eval(s.subString(posnDiwn+1,s.size()),x,config); 
    
    
  posSup=findCharOutsideOfParenthesis(s,CONST_CHAR_GREATEROREQUAL); 
  if (posSup!=-1)
    return eval(s.subString(0,posSup),x,config)
	>=eval(s.subString(posSup+1,s.size()),x,config);    
  }
  
 /*------------------------------------------------------------------
  * Opérations non-prioritaaires 
  * ----------------------------------------------------------------*/
  {
  int posPlus=findCharOutsideOfParenthesis(s,'+'); 
  int posMinus=findCharOutsideOfParenthesis(s,'-');
  if (posPlus!=-1 and posPlus>posMinus)
    return eval(s.subString(0,posPlus),x,config)
	+eval(s.subString(posPlus+1,s.size()),x,config);
  if (posMinus!=-1 and posMinus>posPlus)
    return eval(s.subString(0,posMinus),x,config)
    -eval(s.subString(posMinus+1,s.size()),x,config);
  }
 
  /*------------------------------------------------------------------
  * Opérations prioritaaires
  * ----------------------------------------------------------------*/
  {  
  int posMult=findCharOutsideOfParenthesis(s,'*'); 
  int posdiv=findCharOutsideOfParenthesis(s,'/');
  if (posMult!=-1 and posMult>posdiv)
    return eval(s.subString(0,posMult),x,config)
    *eval(s.subString(posMult+1,s.size()),x,config);
  if (posdiv!=-1 and posdiv>posMult)
    return eval(s.subString(0,posdiv),x,config)
    /eval(s.subString(posdiv+1,s.size()),x,config); 
  }
  
   /*------------------------------------------------------------------
  * Opérations ultra-prioritaaires
  * ----------------------------------------------------------------*/
   {  
    int posExp=findCharOutsideOfParenthesis(s,'^');
    if (posExp!=-1)
    return pow(eval(s.subString(0,posExp),x,config).toDouble(),
	  eval(s.subString(posExp+1,s.size()),x,config).toDouble());  
  }
  
  
  
  
  
  
  
  
  
  /*********************************************************
   * Multiplications implicites
   * *******************************************************/
     /*---------------------------------------------------
  * S'il s'agit de la variable X on retourne sa valeur
  * --------------------------------------------------*/
 if (s.size()>1 and s[0]=='X')
   return x*eval(s.subString(1,s.size()),x,config);
 
    /*---------------------------------------------------
  * S'il s'agit de ANS
  * --------------------------------------------------*/
 if (s.size()>1 and s[0]==CONST_SPE_ANS )
   return config.getAns()*eval(s.subString(1,s.size()),x,config);
 
    /*---------------------------------------------------
  * S'il s'agit d'une valeur de variable Accés case tableau
  * --------------------------------------------------*/
    if (s.size()>2 and config.isVariable(s[0]) and s[1]=='(')
    {
      //On vérifie qu'il n'y a pas d'autre parenthèses pour assombrir l'analyse
        bool isOtherParenthesis=false;
        for (int i=2; i<s.size(); i++)
            if (s[i]=='(')
                isOtherParenthesis=true;
	//S'il n'y en a pas on traite l'accés à la case
        if (!isOtherParenthesis)
        {
            TiString s2= s.subString(2,s.size());
            if (s2[s2.size()-1]==')')
                s2.erase(s2.size()-1);
            vector<TiString> strs=evalFormula::ParseComas(s2);
            //List
            if (strs.size()==1)
            {
		
                int pos=eval(s2,config.getVariableValue('X'),config).toDouble();
		if (config.getVariable(s[0]).isList())
		  return config.getVariable(s[0])[pos-1];
            }

            //Matrices
            if (strs.size()==2)
            {
                int posi=eval(strs[0],config.getVariableValue('X'),config).toDouble();
                int posj=eval(strs[1],config.getVariableValue('X'),config).toDouble();
		if (config.getVariable(s[0]).isMatrix())
		    return config.getVariable(s[0]).accesMatrixValue(posi,posj);
            }

        }
    }
  
   /*---------------------------------------------------
  * S'il s'agit d'une valeur de variable pré enregistré on la retourne
  * --------------------------------------------------*/
  if (s.size()>1 and config.isVariable(s[0]))
    return TiVariant(config.getVariableValue(s[0]))*eval(s.subString(1,s.size()),x,config);
  
   /*---------------------------------------------------
  * S'il s'agit de RAND
  * --------------------------------------------------*/
 if (s.size()>1 and s[0]==CONST_SPE_RAND)
   return TiVariant(1.0*rand()/RAND_MAX)*eval(s.subString(1,s.size()),x,config);
 
  TiString tmpStr;
  tmpStr.push_back(s[0]);
  int i=1;
  while (isNumber(tmpStr,number) and i<s.size()) 
  {
      tmpStr.push_back(s[i]);
      i++;
  }
  if(!isNumber(tmpStr,number))
  {
   tmpStr.erase(tmpStr.size()-1);i--;}
   
   
  if(tmpStr.size()>0 and isNumber(tmpStr,number))
  {
  return TiVariant(number)*eval(s.subString(i,s.size()),x,config);
  }
  
     /*---------------------------------------------------
  *Handle "(a+b)(c+d)"
  * --------------------------------------------------*/
  //TODO WARNINGmor check would me necessary
  for (int i=1;i<s.size()-2;i++)
  {
   if (s[i]==')' and s[i+1]=='(')
     return eval(s.subString(0,i+1),x,config)
    *eval(s.subString(i+1,s.size()),x,config);
  }
  
  return TiVariant(-1);
}






bool evalFormula::isSuroundedByUselessParenthesis( TiString s)
{
  int parCount=0;
if (s.size()>2 and s[0]=='(' and s[s.size()-1]==')')
 {
   parCount=1;
   for (int i=1;i<s.size()-1;i++)
   {
     //TODO have a list elsewher
        if (s[i]=='('or FONCTIONS_PAR)
	  parCount++;
   //Warning
   if (s[i]==')')
	  parCount--;
   if (parCount==0)
     break;
   }
   if (parCount>0)
   return  true;
 }
 return false;
}

bool evalFormula::isSuroundedByParFct(TiString s, int fct)
{
  int parCount=0;
if (s.size()>2 and s[0]==fct and s[s.size()-1]==')')
 {
   parCount=1;
   for (int i=1;i<s.size()-1;i++)
   {
        if (s[i]=='(' or FONCTIONS_PAR)
	  parCount++;
   //Warning
   if (s[i]==')')
	  parCount--;
   if (parCount==0)
     break;
   }
   if (parCount>0)
   return  true;
 }
 return false;
}


bool evalFormula::isNumber(TiString s, double& theNumber)
{
 bool isNumber=true;
 int nbDot=0;
 for (int i=0;i<s.size();i++)
 {
   if (s[i]!='0' and s[i]!='1' and s[i]!='2' and s[i]!='3' and s[i]!='4' and s[i]!='5' and s[i]!='6' and s[i]!='7' and s[i]!='8' and s[i]!='9' and s[i]!='0' and s[i]!='.')
     isNumber=false;
   if (s[i]=='.')
     nbDot++;
 }
 
 if(nbDot>1)
   isNumber=false;
 
 if (isNumber and s.size()<17)
   sscanf(s.toStdString().c_str(),"%lf",&theNumber);
 
 return isNumber;
}

int evalFormula::findCharOutsideOfParenthesis(TiString s, int c)
{
 int parCount=0;
 for (int i=s.size()-1;i>=0;i--)
 {
   if (parCount==0)
   {
     if (s[i]==c and i>0 and i<s.size())
       return i; 
   } 
   //TODO !!!!!!!
   if (s[i]=='(' or FONCTIONS_PAR)
	  parCount++;
   //Warning
   if (s[i]==')')
	  parCount--;
 }
 return -1;
}

void evalFormula::checkForLackingParenthesis(TiString& s)
{
 int parCount=0;
 for (int i=s.size()-1;i>=0;i--)
 {
   if (s[i]=='(' or FONCTIONS_PAR)
	  parCount++;
   //Warning
   if (s[i]==')')
	  parCount--;
 }
 if (parCount>=1)
   for (int i=0;i<parCount;i++)
    s.push_back(')');
}



int evalFormula::handleRandInt(TiString s,double x, TiConfig& config)
{
vector <TiString> cos=ParseComas(s);
if(cos.size()!=2)
  {
  cout<<"Erreur fatale parsing "<<cos.size()<<" "<<s.toStdString()<<" "<<cos[0].toStdString()<<endl; 
  }
else
  {
    int i=round(eval(cos[0],x,config).toDouble());
    int j=round(eval(cos[1],x,config).toDouble());
    return int(i+rand()%int(j-i+1));
  }  

}

vector< TiString > evalFormula::ParseComas(TiString s)
{
  //TODO !! this is not correct!!
  vector<TiString> res;
  int last=0;
for (int i=0;i<s.size();i++)
  if (s[i]==',')
  {
    res.push_back(s.subString(last,i));
    last=i+1;
  }
  
  if (last<s.size())
  {
    res.push_back(s.subString(last,s.size()));
  }
  return res;
  
}

bool evalFormula::isString(TiString s, string& theString)
{
    if (s.size()<2)
	return false;
	 
    if (s[0]=='\"' )
    {
      for (int i=1;i<s.size()-1;i++)
	if (s[i]>256 or s[i]=='\"')
	  return false;
      string tmp=s.toStdString();
      if (s[s.size()-1]=='\"')
	  theString=tmp.substr(1,tmp.size()-2);
      else
	theString=tmp.substr(1,tmp.size()-1);
      return true;
    }
    return false;
}

bool  evalFormula::isList(TiString s, vector< TiString >& theList)
{
    if (s.size()<3)
	return false;
	 
    if (s[0]=='{' and s[s.size()-1]=='}')
    {
      vector<TiVariant> res;
      vector<TiString> strs =ParseComas(s.subString(1,s.size()-1));
      theList=strs;
      return true;
    }
    return false;
}

