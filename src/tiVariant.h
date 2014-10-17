#ifndef TI_VARIANT_H
#define TI_VARIANT_H

#include <string>
#include <vector>

using namespace std;

class TiVariant{
public:
  TiVariant(double a);
  TiVariant(double re,double im);
  TiVariant(string s);
  TiVariant(vector<TiVariant> list);
  TiVariant();
  
  double toDouble();
  string toString();
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
  
  void operator=(const TiVariant & other);
  
  void setDim(int n);
  void setDim(int n,int m);
  void fill(TiVariant v);
private:
  char _type;
  double _valueReal;
  double _valueImaginary;
  string _valueString;
  vector<TiVariant> _valueList;
};












#endif