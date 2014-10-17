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
#include <fstream>
#include <cstdio>
#include "tiString.h"
#include "keyParser.h"
#include <vector>
#include <iostream>

vector<TiString> read83pFile(string loc)
{
using std::ifstream;
using std::ofstream;
ifstream ifs(loc.c_str(), std::ios::binary);
char c_u;
signed char c;

vector<TiString> res;
TiString tmp;
int i=0;
while(ifs.get(c_u) and i<71)
  i++;
  
while(ifs.get(c_u)){
  c=c_u;

  switch (c)
  {
    case -31:
    tmp.push_back(CONST_SPE_CLEARHOME);break;
    case -32:
    tmp.push_back(CONST_SPE_OUTPUT);break;
    case 43:
    tmp.push_back(",");break;
    case 106:
    tmp.push_back("=");break;
    case 42:
    tmp.push_back("\"");break;
    case 62:
    res.push_back(tmp);tmp.clear(); break;
    case 63:
    res.push_back(tmp);tmp.clear(); break;
    case 4:
    tmp.push_back(CONST_CHAR_STO);break;
    case -83:
    tmp.push_back(CONST_SPE_GETKEY);break;
    case -42:
    tmp.push_back(CONST_SPE_LABEL);break; 
     case -45:
    tmp.push_back(CONST_SPE_FOR);break; 
     case 60:
    tmp.push_back(CONST_SPE_OR);break;  
     case -34:
    tmp.push_back(CONST_SPE_DISP);break; 
     case -80:
    tmp.push_back(CONST_CHAR_SMALL_MINUS);break;   
     case -84:
    tmp.push_back(CONST_CHAR_PI);break;      
     case -26:
    tmp.push_back(CONST_SPE_MENU);break;        
     case 91:
       //TODO
    tmp.push_back(CONST_CHAR_THETA);break;//theta      
      case 41:
    tmp.push_back(" ");break;   
     case -69:
      ifs.get(c_u); c=c_u;
      if (c==10)
	tmp.push_back(CONST_SPE_RANDINT);break; 
      break;  
     case 113:
	tmp.push_back("-");break; 
     case -126:
	tmp.push_back("*");break; 
     case -125:
	tmp.push_back("/");break;        
     case -85:
       //TODO
	tmp.push_back(CONST_SPE_RAND);break; 
     case -46:
       //TODO
	tmp.push_back(CONST_SPE_REPEAT);break; 
     case -79:
       //TODO       
	tmp.push_back(CONST_SPE_INT);break;       
     case 11:
       //TODO       
	tmp.push_back(CONST_CHAR_DEGREE);break;        
     case 16:
      tmp.push_back("(");break; 
     case 64:
      tmp.push_back(CONST_SPE_AND);break; 
     case 111:
      tmp.push_back(CONST_CHAR_DIFFERENT);break;      
     case 17:
      tmp.push_back(")");break;  
     case 112:
      tmp.push_back("+");break;  
     case 45:
      tmp.push_back("!");break; 
     case 58:
      tmp.push_back(".");break;       
     case -50:
      tmp.push_back(CONST_SPE_IF);break;   
     case -41:
      tmp.push_back(CONST_SPE_GOTO);break;   
      case -49:
      tmp.push_back(CONST_SPE_THEN);break;   
      case -48:
      tmp.push_back(CONST_SPE_ELSE);break;
      case -44:
      tmp.push_back(CONST_SPE_END);break; 
      case -47:
      tmp.push_back(CONST_SPE_WHILE);break; 
      case -43:
      tmp.push_back(CONST_SPE_RETURN);break;        
      case -16:
      tmp.push_back("^");break;        
      case 107:
      tmp.push_back("<");break;  
      case 110:
      tmp.push_back(CONST_CHAR_GREATEROREQUAL);break;  
      case 109:
      tmp.push_back(CONST_CHAR_LESSOREQUAL);break;  
      //TODO transpose
      case 14:
      tmp.push_back("T");break; 
      
       case -72:
     tmp.push_back(CONST_SPE_NOT);break;      
       case 59:
     tmp.push_back(CONST_CHAR_EPOW10);break;  	 
      case 114:
      //TODO
     tmp.push_back(CONST_SPE_ANS);break;   
      case 108:
      tmp.push_back(">");break;
      
      //TODO check this
      case 98:
      tmp.push_back("c");break; 
      case 24:
      /*tmp.push_back("c");*/break;   
       case 127:
      tmp.push_back("[");break;   
 
           //TODO
      case -40:
	tmp.push_back(CONST_SPE_PAUSE);break;        
      case 95:
      printf("Pause  ");break; 
      //TODO end of programm?
//       case  -6:
// 	//res.push_back(tmp);tmp.clear();
// 	break;
//       case  -115:
// 	res.push_back(tmp);tmp.clear();	
// 	break;	
      
    default:
      if ((c>='0' and c<='9') or c>='A' and c<='Z' )
      tmp.push_back(c);
      else
      {

	

      if(ifs.get(c_u) and ifs.get(c_u))
      {
	printf("Symole ti Basic non reconnu %d %c\n",(int)c,c);
      for (int i=0;i<res.size();i++)
	  cout<<res[i].toStdString()<<endl;
     cout<<tmp.toStdString()<<endl; 
	cout<<"Unable to Parse Exiting \n"<<endl;
      exit(1);
      }
      else
      {
	cout<<"Parse completed successfully"<<endl;
	res.push_back(tmp);
      }
	
      }
  }
}

// for (int i=0;i<res.size();i++)
// {
//    while (res[i].size()>0 and res[i][0]==' ')
//     res[i].erase(0); 
//      while (res[i].size()>0 and res[i][res[i].size()-1]==' ')
//     res[i].erase(res[i].size()-1);  
// }
cout<<"Read size "<<res.size()<<" last "<<int(c)<<endl;
return res;
}
