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

#include "tiVariant.h"
#include <iostream>
#include <math.h>
#include <cstdio>
#include "keyParser.h"

using namespace std;

TiVariant::TiVariant(vector< TiVariant > list)
{
_type=4;
_valueList=list;
}

TiVariant::TiVariant(vector< vector< TiVariant > > matrix)
{
_valueMat=matrix;
_type=5;
}

TiVariant::TiVariant(std::string s)
{
_type=3;
_valueString=s;
}

TiVariant::TiVariant()
{
  _type=1;
  _valueReal=-1;
}

TiVariant TiVariant::getDim()
{
 if (_type==1 or _type==2)
   return TiVariant(1);
 if (_type==3)
   return TiVariant(_valueString.size());
 if (_type==4)
   return TiVariant(_valueList.size());
 if (_type==5)
 {
   vector<TiVariant> list;
   list.push_back(_valueMat.size());
   if (_valueMat.size()>0)
     list.push_back(_valueMat[0].size());
   return TiVariant(list);
 }
}




TiVariant::TiVariant(double re, double im)
{
_type=2;
_valueReal=re;
_valueImaginary=im;
}

TiVariant::TiVariant(double a)
{
_type=1;
_valueReal=a;
}

string TiVariant::toStringWithoutQuote()
{
   if (_type==3)
     return _valueString;
   return toString();
}


std::string TiVariant::toString()
{
    if (_type==1)
    {
        double resDouble=toDouble();
        //crée une chaine de caractère avec le resultat
        char c[150];
        string c2;
        if (resDouble<pow(10,10) and resDouble>-pow(10,10))
        {
            sprintf(c,"%10.9lf",resDouble);
            c2=string(c);

            //WARNING LITTLE PATCH I did not find better
            {
                bool isDot=false;
                for (int i=0; i<c2.size(); i++)if (c2[i]=='.')isDot=true;
                while (c2.size()>1 and isDot and (c2[c2.size()-1]=='0' or c2[c2.size()-1]=='.'))
                {
                    if (c2[c2.size()-1]=='.')isDot=false;
                    c2.erase(c2.size()-1);
                }
            }
        }
        else
        {
            sprintf(c,"%.8e",resDouble);
            c2=string(c);
        }
        if (c2[0]=='-')
	  c2[0]=CONST_CHAR_SMALL_MINUS;
    return c2;
      
    }
   if (_type==2)
     return TiVariant(_valueReal).toString()+"+"+TiVariant(_valueImaginary).toString()+"i";
     
   if (_type==3)
     return "\""+_valueString+"\"";
   
   if (_type==4)
   {
     string res;
     res="{";
     for (int i=0;i<_valueList.size();i++)
     {
       res+=_valueList[i].toString();
       if (i<_valueList.size()-1)
	 res+=",";
     }
     res+="}";
     return res; 
   }
   
   if (_type==5)
   {
     string res;
     res="[";
     for (int i=0;i<_valueMat.size();i++)
     {
       res+="[";
       for (int j=0;j<_valueMat[i].size();j++)
       {
	  res+=_valueMat[i][j].toString();
	 if (j<_valueMat[i].size()-1)
	    res+=",";
       }
       res+="]";
       	 if (i<_valueMat.size()-1)
	    res+=",";
     }
     res+="]";
     return res; 
   }   
}

void TiVariant::fill(TiVariant v)
{
    if (_type==1 or _type==2 or _type==3)
        operator=(v);
    if (_type==4)
    {
        for (int i=0; i<_valueList.size(); i++)
            _valueList[i]=v;
    }
    if (_type==5)
    {
     for (int i=0; i<_valueMat.size(); i++)
	for (int j=0; j<_valueMat[i].size(); j++)       
            _valueMat[i][j]=v;
    }
}

TiVariant& TiVariant::accesMatrixValue(int i, int j)
{
    if (_valueMat.size()>=i and _valueMat[i].size()>=j)
        return _valueMat[i-1][j-1];
    cout<<"Erreur accés case matrice"<<endl;
}


TiVariant& TiVariant::operator[](int i)
{
if (_type==4 and _valueList.size()>i and i>=0)
  return _valueList[i];
else
  cout<<"Grosse erreur accés list"<<endl;
_valueList.push_back(0);
return _valueList[0];
}

void TiVariant::setListCase(int i, TiVariant v)
{
if (_type==4 and _valueList.size()>i and i>=0)
  _valueList[i]=v;
else
  cout<<"Erreur accés case tableau "<<i<<" "<< _valueList.size()<<" "<<int(_type)<<endl;
}

bool TiVariant::isList()
{
return (_type==4);
}


bool TiVariant::isMatrix()
{
return (_type==5);
}


void TiVariant::setDim(int n)
{
  _type=4;
 if (_type==4)
 {
  while (_valueList.size()>n)
    _valueList.erase(_valueList.end());
    
  while (_valueList.size()<n)
     _valueList.push_back(TiVariant(0.0));
 }
 else
   cout<<"Erreur changement de dimention invalide"<<endl;
}

void TiVariant::setDim(int n, int m)
{
    _type=5;
    _valueMat.clear();
    for (int i=0; i<n; i++)
    {
        vector<TiVariant> line;
        for (int j=0; j<m; j++)
        {
            line.push_back(TiVariant(0));
        }
        _valueMat.push_back(line);
    }
}

void TiVariant::setDim(TiVariant dim)
{
 if (dim._type==1 and int(dim.toDouble())==dim.toDouble())
 {
   setDim(dim.toDouble());
   return;
 }
 
  if (dim._type==4 and dim._valueList.size()==2 
	and dim._valueList[0]._type==1 and int(dim._valueList[0].toDouble())==dim._valueList[0].toDouble()
	and dim._valueList[1]._type==1  and int(dim._valueList[1].toDouble())==dim._valueList[1].toDouble())
  {
   setDim(dim._valueList[0].toDouble(),dim._valueList[1].toDouble());
    return;
  }
  cout<<"Erreur Dim type incompatible "<<dim.toString()<<" "<<int(dim._type)<<endl;
}



void TiVariant::operator=(const TiVariant& other)
{
_type=other._type;
_valueReal=other._valueReal;
_valueImaginary=other._valueImaginary;
_valueString=other._valueString;
_valueList=other._valueList;
_valueMat=other._valueMat;
}


TiVariant TiVariant::operator+(const TiVariant& other)
{
    //Real+Real
    if (_type==1 and other._type==1)
        return TiVariant(_valueReal+other._valueReal);
    //Complexe+Real
    if (_type==2 and other._type==1)
        return TiVariant(_valueReal+other._valueReal,_valueImaginary);
    //Real+Complexe
    if (_type==1 and other._type==2)
        return TiVariant(_valueReal+other._valueReal,other._valueImaginary);
    //Complexe+Complexe
    if (_type==2 and other._type==2)
        return TiVariant(_valueReal+other._valueReal,_valueImaginary+other._valueImaginary);    
    //String+String
    if (_type==3 and other._type==3)
    {
      string res=_valueString;
      res.append(other._valueString);
      return TiVariant(res);  
    }
    
    cout<<"Erreur addtion ti variant: Types incompatiples"<<endl;
}

TiVariant TiVariant::operator-(const TiVariant& other)
{
    //Real-Real
    if (_type==1 and other._type==1)
        return TiVariant(_valueReal-other._valueReal);
    //Complexe-Real
    if (_type==2 and other._type==1)
        return TiVariant(_valueReal-other._valueReal,_valueImaginary);
    //Real-Complexe
    if (_type==1 and other._type==2)
        return TiVariant(_valueReal-other._valueReal,other._valueImaginary);
    //Complexe-Complexe
    if (_type==2 and other._type==2)
        return TiVariant(_valueReal-other._valueReal,_valueImaginary-other._valueImaginary);    
    //List-List TODO
//     if (_type==4 and other._type==4)
//         return TiVariant(_valueReal-other._valueReal,_valueImaginary-other._valueImaginary);  
    
    cout<<"Erreur soustraction ti variant: Types incompatiples"<<endl;
}

TiVariant TiVariant::operator*(const TiVariant& other)
{
    //Real*Real
    if (_type==1 and other._type==1)
        return TiVariant(_valueReal*other._valueReal);
    //Complexe*Real
    if (_type==2 and other._type==1)
        return TiVariant(_valueReal*other._valueReal,_valueImaginary*other._valueReal);
    //Real*Complexe
    if (_type==1 and other._type==2)
        return TiVariant(_valueReal*other._valueReal,_valueReal*other._valueImaginary);
    //Complexe-Complexe
    if (_type==2 and other._type==2)
        return TiVariant(_valueReal*other._valueReal-_valueImaginary*other._valueImaginary,_valueReal*other._valueImaginary+other._valueReal*_valueImaginary); 

      if (_type==4 and other._type==1)
	if (int(other._valueReal)-1>=0 and int(other._valueReal)-1<_valueList.size())
	return _valueList[int(other._valueReal)-1];   
      cout<<"Erreur multiplication ti variant: Types incompatiples"<<endl;
  return TiVariant(-1);
}

TiVariant TiVariant::operator/(const TiVariant& other)
{
 //Real/Real
    if (_type==1 and other._type==1)
        return TiVariant(_valueReal/other._valueReal);
    //Complexe/Real
    if (_type==2 and other._type==1)
        return TiVariant(_valueReal/other._valueReal,_valueImaginary/other._valueReal);
//     //Real/Complexe
//     if (_type==1 and other._type==2)
//         return TiVariant(_valueReal*other._valueReal,_valueReal*other._valueImaginary);
//     //Complexe/Complexe
//     if (_type==2 and other._type==2)
//         return TiVariant(_valueReal*other._valueReal-_valueImaginary*other._valueImaginary,_valueReal*other._valueImaginary+other._valueReal*_valueImaginary); 
     cout<<"Erreur multiplication ti variant: Types incompatiples"<<endl;
}

bool TiVariant::operator==(const TiVariant& other)
{
  if (_type!=other._type)
    return false;
  if (_type==1)
    return _valueReal==other._valueReal;
  if (_type==2)
    return (_valueReal==other._valueReal) and (_valueImaginary==other._valueImaginary);  
  if (_type==3)
    return (_valueString==other._valueString); 
      cout<<"Erreur egal ti variant: Types incompatiples"<<endl; 
}

double TiVariant::toDouble()
{
if (_type==1 or (_type==2 and _valueImaginary==0.0))
  return _valueReal;

      cout<<"Erreur cast impossible en double"<<endl; 
      return -1;
}

bool TiVariant::operator!=(const TiVariant& other)
{
return !operator==(other);
}

bool TiVariant::operator<(const TiVariant& other)
{
 return (_type==1 and other._type==1 and _valueReal<other._valueReal);
}

bool TiVariant::operator>(const TiVariant& other)
{
 return (_type==1 and other._type==1 and _valueReal>other._valueReal);
}

TiVariant TiVariant::operator||(const TiVariant& other)
{
 return (_type==1 and other._type==1 and _valueReal||other._valueReal);
}

TiVariant TiVariant::operator&&(const TiVariant& other)
{
 return (_type==1 and other._type==1 and _valueReal&&other._valueReal);
}

bool TiVariant::operator<=(const TiVariant& other)
{
 return (_type==1 and other._type==1 and _valueReal<=other._valueReal);
}

bool TiVariant::operator>=(const TiVariant& other)
{
 return (_type==1 and other._type==1 and _valueReal>=other._valueReal);
}




