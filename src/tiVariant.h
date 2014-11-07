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

#ifndef TI_VARIANT_H
#define TI_VARIANT_H

#include <string>
#include <vector>

using namespace std;

/**
 * @brief Cette classe correspond à un type variant comprenant tous les type gérés par la TI 82 (réel, complexe, string, list et matrice)
 * 
 */
class TiVariant{
public:
  TiVariant(double a);
  TiVariant(double re,double im);
  TiVariant(string s);
  TiVariant(vector<TiVariant> list);
  TiVariant(vector<vector<TiVariant > > matrix);  
  TiVariant();
  
  double toDouble();
  string toString();
  string toStringWithoutQuote();  
  TiVariant getDim();
  
  TiVariant operator+(const TiVariant & other);
  TiVariant operator-(const TiVariant & other);
  TiVariant operator*(const TiVariant & other);  
  TiVariant operator/(const TiVariant & other); 
  TiVariant operator||(const TiVariant & other);  
  TiVariant operator&&(const TiVariant & other);    
  bool operator==(const TiVariant & other);
  bool operator!=(const TiVariant & other);  
  bool operator<(const TiVariant & other);
  bool operator>(const TiVariant & other);
  bool operator>=(const TiVariant & other);
  bool operator<=(const TiVariant & other);
  //for lists
  TiVariant & operator[] (int i);
  //for matrixes!
  TiVariant & accesMatrixValue(int i,int j);  
  void setListCase(int i,TiVariant v);
  
  void operator=(const TiVariant & other);
  
  void setDim(int n);
  void setDim(TiVariant dim);
  void setDim(int n,int m);
  void fill(TiVariant v);
  
  bool isList();
  bool isMatrix();
private:
  char _type;
  double _valueReal;
  double _valueImaginary;
  string _valueString;
  vector<TiVariant> _valueList;
  vector<vector<TiVariant> > _valueMat;  
};












#endif