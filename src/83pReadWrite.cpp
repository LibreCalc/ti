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
      	  cout<<"error parsing"<<endl;
      break;  
     case 113:
	tmp.push_back("-");break; 
     case -126:
	tmp.push_back("*");break; 
     case -125:
	tmp.push_back("/");break;   
     case -81:
	tmp.push_back("?");break;
     case 22:
	tmp.push_back("|");break;
     case 6:
	tmp.push_back("[");break;
     case 7:
	tmp.push_back("]");break;	
     case 8:
	tmp.push_back("{");break;
     case 9:
	tmp.push_back("}");break;	
     case -85:
	tmp.push_back(CONST_SPE_RAND);break; 
     case -46:
	tmp.push_back(CONST_SPE_REPEAT);break; 
     case -79:    
	tmp.push_back(CONST_SPE_INT);break;    
     case -75:
	tmp.push_back(CONST_SPE_DIM);break;  
     case -30:
	tmp.push_back(CONST_SPE_FILL);break; 	
     case -36:
	tmp.push_back(CONST_SPE_INPUT);break;
     case 92:	
       ifs.get(c_u); c=c_u;
	if (c==0)
	{tmp.push_back(CONST_SPE_MATA);break; }
	if (c==1)
	{tmp.push_back(CONST_SPE_MATB);break; }
	if (c==2)
	{tmp.push_back(CONST_SPE_MATC);break; }
	if (c==3)
	{ tmp.push_back(CONST_SPE_MATD);break;}
	if (c==4)
	{tmp.push_back(CONST_SPE_MATE);break;} 	
	if (c==5)
	{tmp.push_back(CONST_SPE_MATF);break;} 
	if (c==6)
	{tmp.push_back(CONST_SPE_MATG);break;} 
	if (c==7)
	{tmp.push_back(CONST_SPE_MATH);break;}
	if (c==8)
	{tmp.push_back(CONST_SPE_MATI);break;}	
	  cout<<"error parsing"<<endl;
     case 93:
        ifs.get(c_u); c=c_u;
	if (c==0)
	{tmp.push_back(CONST_SPE_L1);break; }
	if (c==1)
	{tmp.push_back(CONST_SPE_L2);break; }
	if (c==2)
	{tmp.push_back(CONST_SPE_L3);break; }
	if (c==3)
	{ tmp.push_back(CONST_SPE_L4);break;}
	if (c==4)
	{tmp.push_back(CONST_SPE_L5);break;} 	
	if (c==5)
	{tmp.push_back(CONST_SPE_L6);break;} 
	if (c==6)
	{tmp.push_back(CONST_SPE_L7);break;} 
	if (c==7)
	{tmp.push_back(CONST_SPE_L8);break;}
	if (c==8)
	{tmp.push_back(CONST_SPE_L9);break;}	
	  cout<<"error parsing"<<endl;
      break;
     case -21:
	tmp.push_back(CONST_CHAR_LUSER);break;	
     case -6:
	tmp.push_back(CONST_SPE_CLRLIST);break;	
     case 11:     
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
     case 18:
      tmp.push_back(CONST_SPE_ROUND);break;  
     case -39:
      tmp.push_back(CONST_SPE_STOP);break;      
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
// 	      for (int i=0;i<res.size();i++)
// 	  cout<<res[i].toStdString()<<endl;
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


void write83pFile(string loc, vector< TiString > program)
{
    using std::ifstream;
    using std::ofstream;
    ofstream myfile(loc.c_str(), std::ios::binary);
    char c;
    for (int i=0; i<=71; i++)
        myfile.put(0);

    for (int i=0; i<program.size(); i++)
    {
        for (int j=0; j<program[i].size(); j++)
        {
            switch (program[i][j])
            {
            case CONST_SPE_CLEARHOME:
                myfile.put(-31);break;
            case ' ':
                myfile.put(41);break;
	    case CONST_SPE_IF:
                 myfile.put(-50);break;
	    case CONST_SPE_OUTPUT:
	       myfile.put(-32);  break;
	    case ',':
	       myfile.put(43);  break;
	    case '=':
	       myfile.put(106);  break;
	    case '\"':
	       myfile.put(42);  break;	
	    case CONST_CHAR_STO:
	       myfile.put(4);  break;
	    case CONST_SPE_GETKEY:
	       myfile.put(-83);  break;	       
	    case CONST_SPE_LABEL:
	       myfile.put(-42);  break;	 
	    case CONST_SPE_FOR:
	       myfile.put(-45);  break;		       
	    case CONST_SPE_OR:
	       myfile.put(60);  break;	
	    case CONST_SPE_DISP:
	       myfile.put(-34);  break;	
	    case CONST_CHAR_SMALL_MINUS:
	       myfile.put(-80);  break;	
	    case CONST_CHAR_PI:
	       myfile.put(-84);  break;		       
	    case CONST_SPE_MENU:
	       myfile.put(-26);  break;	
	    case CONST_CHAR_THETA:
	       myfile.put(91);  break;	
	    case CONST_SPE_RANDINT:
	       myfile.put(-69);myfile.put(10);  break;	
	    case '-':
	       myfile.put(113);  break;	
	    case '*':
	       myfile.put(-126);  break;	
	    case '/':
	       myfile.put(-125);  break;
	    case '?':
	       myfile.put(-81);  break;
	    case '|':
	       myfile.put(22);  break;
	    case '[':
	       myfile.put(6);  break;
	    case ']':
	       myfile.put(7);  break;
	    case '{':
	       myfile.put(8);  break;
	    case '}':
	       myfile.put(9);  break;	       
	    case CONST_SPE_RAND:
	       myfile.put(-85);  break;	
	    case CONST_SPE_REPEAT:
	       myfile.put(-46);  break;	
	    case CONST_SPE_INT:
	       myfile.put(-79);  break;	
	    case CONST_SPE_DIM:
	       myfile.put(-75);  break;	
	    case CONST_SPE_FILL:
	       myfile.put(-30);  break;
	    case CONST_SPE_INPUT:
	       myfile.put(-36);  break;
	    case CONST_SPE_MATA:
	       myfile.put(92);myfile.put(0);  break;
	    case CONST_SPE_MATB:
	       myfile.put(92);myfile.put(1);  break;
	    case CONST_SPE_MATC:
	       myfile.put(92);myfile.put(2);  break;	 
	    case CONST_SPE_MATD:
	       myfile.put(92);myfile.put(3);  break;
	    case CONST_SPE_MATE:
	       myfile.put(92);myfile.put(4);  break;
	    case CONST_SPE_MATF:
	       myfile.put(92);myfile.put(5);  break;
	    case CONST_SPE_MATG:
	       myfile.put(92);myfile.put(6);  break;
	    case CONST_SPE_MATH:
	       myfile.put(92);myfile.put(7);  break;	
	    case CONST_SPE_MATI:
	       myfile.put(92);myfile.put(8);  break;		       
	    case CONST_SPE_L1:
	       myfile.put(93);myfile.put(0);  break;
	    case CONST_SPE_L2:
	       myfile.put(93);myfile.put(1);  break;
	    case CONST_SPE_L3:
	       myfile.put(93);myfile.put(2);  break;
	    case CONST_SPE_L4:
	       myfile.put(93);myfile.put(3);  break;	
	    case CONST_SPE_L5:
	       myfile.put(93);myfile.put(4);  break;
	    case CONST_SPE_L6:
	       myfile.put(93);myfile.put(5);  break;
	    case CONST_SPE_L7:
	       myfile.put(93);myfile.put(6);  break;	
	    case CONST_SPE_L8:
	       myfile.put(93);myfile.put(7);  break;	
	    case CONST_SPE_L9:
	       myfile.put(93);myfile.put(8);  break;		       
	    case CONST_CHAR_LUSER:
	       myfile.put(-21);  break;	
	    case CONST_SPE_CLRLIST:
	       myfile.put(-6);  break;
	    case CONST_CHAR_DEGREE:
	       myfile.put(11);  break;
	    case '(':
	       myfile.put(16);  break;
	    case CONST_SPE_AND:
	       myfile.put(64);  break;
	    case CONST_CHAR_DIFFERENT:
	      myfile.put(111);  break;
	    case ')':
	      myfile.put(17);  break;	      
	    case '+':
	      myfile.put(112);  break;	
	    case '!':
	      myfile.put(45);  break;
	    case '.':
	      myfile.put(58);  break;	      
	    case CONST_SPE_GOTO:
	      myfile.put(-41);  break;
	    case CONST_SPE_ROUND:
	      myfile.put(18);  break;
	    case CONST_SPE_STOP:
	      myfile.put(-39);  break;	      
	    case CONST_SPE_THEN:
	      myfile.put(-49);  break;	
	    case CONST_SPE_ELSE:
	      myfile.put(-48);  break;	
	    case CONST_SPE_END:
	      myfile.put(-44);  break;	
	    case CONST_SPE_WHILE:
	      myfile.put(-47);  break;
	    case CONST_SPE_RETURN:
	      myfile.put(-43);  break;	      
	    case '^':
	      myfile.put(-16);  break;
	    case '<':
	      myfile.put(107);  break;
	    case CONST_CHAR_GREATEROREQUAL:
	      myfile.put(110);  break;
	    case CONST_CHAR_LESSOREQUAL:
	      myfile.put(109);  break;	      
	    //TODO transpose
	    case CONST_SPE_NOT:
	      myfile.put(-72);  break;	  
	    case CONST_CHAR_EPOW10:
	      myfile.put(59);  break;		      
	    case CONST_SPE_ANS:
	      myfile.put(114);  break;
	    case '>':
	      myfile.put(108);  break;
	    case CONST_SPE_PAUSE:
	      myfile.put(-40);  break;

            default:
                if ((program[i][j]>='0' and program[i][j]<='9')
                        or program[i][j]>='A' and program[i][j]<='Z' )
                    myfile.put(program[i][j]);

                break;

            }
        }

        myfile.put(62);
    }
}
