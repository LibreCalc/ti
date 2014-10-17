#include "tiVariant.h"
#include <iostream>
#include <math.h>
#include <cstdio>

using namespace std;

TiVariant::TiVariant(vector< TiVariant > list)
{
_type=4;
_valueList=list;
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
}

void TiVariant::setDim(int n)
{
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


void TiVariant::operator=(const TiVariant& other)
{
_type=other._type;
_valueReal=other._valueReal;
_valueImaginary=other._valueImaginary;
_valueString=other._valueString;
_valueList=other._valueList;
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
    cout<<"Erreur multiplication ti variant: Types incompatiples"<<endl;
  
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




