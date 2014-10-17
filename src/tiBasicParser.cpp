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

#include "tiBasicParser.h"
#include "evalFormula.h"
#include "keyParser.h"
#include <iostream>
#include <cmath>
#include <unistd.h>
#include "menu.h"

using namespace std;

TiParser::TiParser(CharPutter* charPutter,TiConfig &conf):_conf(conf)
{
_charPutter=charPutter;
_key=0;
 _needToRefresh=false;
}

void TiParser::execProgram(vector< TiString >& program)
{
_needToGoto=1;
int labelPos=0;
map<char, int> labels;
for (int i=0;i<program.size();i++)
 {
 if (program[i].size()==2 and program[i][0]==CONST_SPE_LABEL)
   labels.insert(pair<char,int>(program[i][1],i));
 }

while (_needToGoto>=0)
  {	
  exec(program,labelPos,program.size());
  if (_needToGoto>=0)
  {
//      cout<<"goto "<<(char)_needToGoto<<endl;
   labelPos=labels.at(_needToGoto);
  }
  }
}


void TiParser::exec(vector< TiString >& program, int start, int end)
{ 
  _needToGoto=-1;
  start--;
  
  while (start+1<end and _needToGoto<0)
  {
    usleep(500);
  start++;
  if(program[start].size()==0)
    continue;
   //   cout<<_conf.getAns()<<" "<<_conf.getVariableValue('Z')<<" "<<program[start].toStdString()<<endl;
  if (program[start][0]==CONST_SPE_OUTPUT)
  {
    handleOutput(program[start]); continue;
  }
  
  if (program[start][0]==CONST_SPE_DISP)
  {
    handleDisp(program[start]); continue;
  }
    
  if (program[start][0]==CONST_SPE_LABEL)
    continue;
  
  if (program[start][0]==CONST_SPE_PAUSE)
  {
    TiString s;
    _charPutter->refreshScreen();
    while (s.toStdString()!="105")
      {s.clear();s.push_back(CONST_SPE_GETKEY);checkForGetKey(s);SDL_Delay(50);}
    continue;  
  }
  
  if (program[start][0]==CONST_SPE_GOTO)
  { _needToGoto =program[start][1];continue;} 
    
  if (program[start][0]==CONST_SPE_MENU)
  { handleMenu(program[start]); continue;} 
  
  if (program[start][0]==CONST_SPE_CLEARHOME)
  {
  /* cout<<"Clearhome"<<endl;*/;_charPutter->refreshScreen();SDL_Delay(39); _charPutter->clear(); needToRefresh();continue;
  }  
    
  /****************************************************************
   * 	While
   * ****************************************************************/
if ( program[start].size()>1 and program[start][0]==CONST_SPE_WHILE)
  {
    TiString condition=program[start];
    condition.erase(0);
    int stopWhile=lookForEnd(program,start+1,end);
    while(eval(condition,_conf.getVariableValue('X'),_conf).toDouble()){
      exec(program,start+1,stopWhile);
      if (_needToGoto>=0)
	  break; 
    }
    start=stopWhile;
    continue;
  }
  
    /****************************************************************
   * 	Repeat
   * ****************************************************************/
if ( program[start].size()>1 and program[start][0]==CONST_SPE_REPEAT)
  {
    TiString condition=program[start];
    condition.erase(0);
    int stopRepeat=lookForEnd(program,start+1,end);
    while(!(eval(condition,_conf.getVariableValue('X'),_conf).toDouble())){
      _conf.setAns(eval(condition,_conf.getVariableValue('X'),_conf)); 
      exec(program,start+1,stopRepeat);
      if (_needToGoto>=0)
	  break; 
    }
    start=stopRepeat;
    continue;
  }
  
  /****************************************************************
   * 	For
   * ****************************************************************/
if ( program[start].size()>3 and program[start][0]==CONST_SPE_FOR)
  {
    TiString condition=program[start];
    condition.erase(0);
    if (condition[condition.size()-1]==')')
      condition.erase(condition.size()-1);
    vector<TiString> strs =evalFormula::ParseComas(condition);
    int stopFor=lookForEnd(program,start+1,end);    
    if ((strs.size()!=4 and strs.size()!=3) or strs[0].size()!=1 or stopFor==-1)
    {
      cout<<"Erreur For "<<program[start].toStdString()<<endl;
      exit(0);
    }
    else
    {
      int min=eval(strs[1],_conf.getVariableValue('X'),_conf).toDouble();
      int max=eval(strs[2],_conf.getVariableValue('X'),_conf).toDouble(); 
      int step=1;
      if (strs.size()==4)
      step=eval(strs[3],_conf.getVariableValue('X'),_conf).toDouble();   
      for (int i=min;i<=max;i+=step)
      {
	_conf.setVariableValue(strs[0][0],i);
	if (start+1==stopFor)
	  SDL_Delay(1);
	else
	  exec(program,start+1,stopFor);
	if (_needToGoto>=0)
	  break;
      }
    }
    start=stopFor;
    continue;
  }  
  
  /****************************************************************
   * 	IF (Then else)
   * ****************************************************************/
if ( program[start].size()>1 and program[start][0]==CONST_SPE_IF)
  {
    TiString condition=program[start];
    condition.erase(0);
    if (program.size()>start+1 and program[start+1].size()==1 and program[start+1][0]==CONST_SPE_THEN)
    {
      int elsePos=lookForElse(program,start+2,end);
      int endPos=lookForEnd(program,start+2,end);
      if (eval(condition,_conf.getVariableValue('X'),_conf).toDouble())
      {
	if (elsePos>=0)
	 exec(program,start+2,elsePos);
	else
	  exec(program,start+2,endPos);
      }
      else if (elsePos>=0)
      	 exec(program,elsePos+1,endPos);
      start=endPos;
    }
    else
    {
      if(!(eval(condition,_conf.getVariableValue('X'),_conf).toDouble()))
	start=start+1;
    }
    continue;
  }  
  
  
  /*************************************************************
   * Normal eval
   **************************************************************/
  TiString _currString=program[start];
  checkForGetKey(_currString);
if (_currString.size()>2  and _conf.isVariable(_currString[_currString.size()-1])
  and _currString[_currString.size()-2]==CONST_CHAR_STO)
  {
    int res;
    char var=_currString[_currString.size()-1];
    _currString.erase(_currString.size()-1);
    _currString.erase(_currString.size()-1);    
    res=eval(_currString,_conf.getVariableValue('X'),_conf).toDouble();
    _conf.setVariableValue(var,res);
    _conf.setAns(res); 
  }
  else
  {
   _conf.setAns(eval(_currString,_conf.getVariableValue('X'),_conf));
  }
  
  }
  
}

int TiParser::lookForEnd(vector< TiString >& program, int loc,int end)
{
 int nbopen=0;
for (int i=loc;i<end;i++)
  {
  if(program[i].size()==1 and program[i][0]==CONST_SPE_END)
    if ( nbopen==0)
    return i;
    else
      nbopen--;
  if (program[i].size()>0 and(program[i][0]==CONST_SPE_WHILE or program[i][0]==CONST_SPE_THEN  or program[i][0]==CONST_SPE_FOR or program[i][0]==CONST_SPE_REPEAT))
  { 
    nbopen++;
  }
//   cout<<program[i].toStdString()<<" "<<nbopen<<endl;
  }
  return program.size();
}

int TiParser::lookForElse(vector< TiString >& program, int loc, int end)
{
 int nbopen=0;
for (int i=loc;i<end;i++)
  {
   
  if(program[i].size()==1 and program[i][0]==CONST_SPE_ELSE)
    return i;
  if(program[i].size()==1 and program[i][0]==CONST_SPE_THEN)
    {
      i=lookForEnd(program,i+1,end); //TODO chexk this!
      if (i<loc or i>=end)
	return-1;
    }
  }
  return -1;
}

void TiParser::handleOutput(TiString s)
{
  if (s.size()>0 and s[s.size()-1]==')')
    s.erase(s.size()-1);
  TiString tmp=s;
  s.erase(0);
vector<TiString> strs=evalFormula::ParseComas(s);
if (strs.size()!=3)
{
 cout<<"Outuput error  "<<s.toStdString()<<endl;  
}
else
{
int y=round(eval(strs[0],_conf.getVariableValue('X'),_conf).toDouble());
int x=round(eval(strs[1],_conf.getVariableValue('X'),_conf).toDouble());
// cout<<"Outuput "<<x<<" "<<y<<" "<<strs[0].toStdString()<<endl;
strs[2].erase(0);
if (strs[2][strs[2].size()-1]=='\"')
  strs[2].erase(strs[2].size()-1);
_charPutter->putString(strs[2].toStdString(),x,y);
SDL_Delay(strs[2].toStdString().size()*1.5);
 _charPutter->refreshScreen();

needToRefresh();
}
}

void TiParser::needToRefresh()
{
if (!_needToRefresh)
{
  //TODO!!
}
_needToRefresh=true;
}

void TiParser::checkForGetKey(TiString& s)
{
  
//   SDL_EnableKeyRepeat(20,20);
   SDL_Event event;
  while (SDL_PollEvent(&event))
  {
     switch(event.type)
    {
	case SDL_QUIT:
	exit(0); break;
	
	case SDL_KEYDOWN:
	  
	      if (event.key.keysym.sym==SDLK_UP)
		_key=25;
	      if (event.key.keysym.sym==SDLK_LEFT)
		_key=24;
	      if (event.key.keysym.sym==SDLK_RIGHT)
		_key=26;
	      if (event.key.keysym.sym==SDLK_DOWN)
		_key=34;	   
	      if (event.key.keysym.sym==SDLK_INSERT)
		_key=22;
	      if (event.key.keysym.sym==SDLK_LALT)
		_key=21;	      
	      if (event.key.keysym.sym==SDLK_RETURN)
		_key=105;	      
	      
    }
  }
  TiString sx=s;
for (int i=0;i<sx.size();i++)
  if (sx[i]==CONST_SPE_GETKEY)
  {
    char tab[5];
     sprintf(tab,"%d",_key);
    
    TiString s1,s2,s3;
    int size=sx.size();
    if (i>0)
      s1=(sx.subString(0,i));
      s2.push_back(string(tab));
      s3=(sx.subString(i+1,size));
    sx=(s1+s2+s3);
    _key=0;
    break;
  }
  s=sx;
}

void TiParser::handleDisp(TiString s)
{
s.erase(0);
vector<TiString> strs=evalFormula::ParseComas(s);
if (strs.size()==0)
{
 cout<<"Erreur Disp"<<endl; 
}
for (int i=0;i<strs.size();i++)
  {
    if (strs[i].size()==2 and strs[i][0]=='\"' and  strs[i][1]=='\"')
    {
     _charPutter->disp(""); 
    }
    else
    {
      strs[i].erase(0);
      _charPutter->disp(strs[i].toStdString());
    }
      
  }
  SDL_Delay(20);
}

void TiParser::handleMenu(TiString s)
{
      
  if (s.size()<4)
  {
    cout<<"Erreur  Menu"<<endl;
    return;
  }
  s.erase(0);
  if (s[s.size()-1]==')')
    s.erase(s.size()-1);
  vector<TiString> strs=evalFormula::ParseComas(s);
  if (strs.size()<4)
  {
    cout<<"Erreur  Menu"<<endl;
    return;
  }
  TiString title=strs[0];
  vector<TiString> choices;
  vector<TiString> gotos;  
  for (int i=0;i<(strs.size()-1)/2;i++)
  {
    choices.push_back(strs[i*2+1]);
    gotos.push_back(strs[i*2+2]);
  }
    
  Menu m(_charPutter,title,choices);
  m.reDisplay();
  SDL_Event event;
  int stop=0;
  while (!stop)
  {
    SDL_WaitEvent(&event);
     switch(event.type)
    {
	case SDL_QUIT:
	exit(0); break;
	
	case SDL_KEYDOWN:   
	      if (event.key.keysym.sym==SDLK_RETURN)
	      {stop=1;break;}
	      else
		m.sendKey(event.key.keysym);    
    }
  }
  int choice=m.getSelectedItem();
  _needToGoto=gotos[choice][0];
}

