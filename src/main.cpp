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

#include "charPutter.h"
#include "yEqualsMenu.h"
#include "curveViewer.h"
#include "mainScreen.h"
#include "tiConfig.h"
#include "tiString.h"
#include "keyParser.h"
#include "tiBasicParser.h"
#include <iostream>
#include "83pReadWrite.h"
#include <cstring>
#include <time.h>  
#include <dirent.h>
#include <string.h>
#include "menu.h"
#include "curveRangeEditor.h"

main(int argc, char **argv){
   
    srand (time(NULL));
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
  {
    cout<<"Cannot initialise SDL"<<endl;
    exit (1) ;
  }
  SDL_Surface *display=SDL_SetVideoMode(400, 240, 16, SDL_SWSURFACE|SDL_ANYFORMAT|SDL_DOUBLEBUF/*|SDL_FULLSCREEN*/);
  if (display==NULL)
  {
    cout<<"Can't open a SDL display for unknown reason, exiting"<<endl;
    cout<<"check main.cpp, second line. The given flags may not be the right one."<<endl;
    exit(0);
  }
  SDL_WM_SetCaption("Ti 82 Stat emulator", NULL); 
  SDL_EnableUNICODE(1);
  
  vector<TiString> programsMenu;
  vector<string> programsFiles;
    struct dirent **namelist;
    int n;

    n = scandir("working", &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        while (n--) {
	  string tmp(namelist[n]->d_name);
	  if (tmp.size()>4 and (tmp.substr(tmp.size()-4,tmp.size())==".83p"
	    or tmp.substr(tmp.size()-4,tmp.size())==".82p"  or tmp.substr(tmp.size()-4,tmp.size())==".82P" 
	    or tmp.substr(tmp.size()-4,tmp.size())==".83P" ))
	  {
            programsFiles.push_back(tmp);
	    programsMenu.push_back(TiString(tmp.substr(0,tmp.size()-4)));
	  }
            free(namelist[n]);
        }
        free(namelist);
    }
    
   
  SDL_Surface *ecr=SDL_CreateRGBSurface(SDL_SWSURFACE,96,64,8,255,255,255,0);
  
//Création des différents élements   
  TiConfig conf;
  CharPutter charput(ecr,display,16,8);
  CurveViewer curve(ecr,display,conf);
  YEqualsMenu yeq(&charput,&conf);
  MainScreen ms(&charput,conf);
  Menu menuPrgrm(&charput,TiString("Prgrm"),programsMenu);
  CurveRangeEditor rangeEdit(&charput,&conf);

  charput.clear();
  vector<TiString> program;
  TiString tmp;
  
  
  charput.clear();
  charput.putString("=Ti 82/83 EMU=",2,2);
  charput.putString("Pierre Et =^=",2,6);
  charput.putString(" =^=     Ael  ",3,7);  
  charput.refreshScreen();
  
  SDL_UpdateRect(display,0,0,0,0);
  
    SDL_Delay(1500);
  ms.reDisplay();
  SDL_Event event;
  int mode=1;
  
  Uint32 old_time;
  old_time=SDL_GetTicks();
  
  while (1)
{
  SDL_Delay(15);
    if(SDL_PollEvent(&event))
    {
    
    
    switch(event.type)
    {
	case SDL_QUIT:
	  SDL_Quit();
	return 1; break;
	
	case SDL_KEYDOWN:
	  
	      if (event.key.keysym.sym==SDLK_F1)
	      {
		mode=1;
		ms.reDisplay();
	      }
	      else if(event.key.keysym.sym==SDLK_F2)
	      {mode=2;
		yeq.reDisplay();
	      }
	     else if(event.key.keysym.sym==SDLK_F3)
	      {
		mode=3;
		conf.setFunctionToPlot(1,yeq.getFirstEq());
		
		curve.reDisplay();
	      } 
	     else if(event.key.keysym.sym==SDLK_F4)
	      {
		mode=4;
		menuPrgrm.reDisplay();
	      } 
	      
	     else if(event.key.keysym.sym==SDLK_F5)
	      {
		mode=5;
		rangeEdit.loadVariables();
		rangeEdit.reDisplay();
	      } 
	     else if(event.key.keysym.sym==SDLK_RETURN and mode==4)
	      {
		 SDL_EnableKeyRepeat(1,75);
		program=read83pFile("working/"+programsFiles[menuPrgrm.getSelectedItem()]);
// 		for (int i=0;i<program.size();i++)  
// 		  cout<<":"<<program[i].toStdString()<<endl;
  
  
		TiParser parser(&charput,conf);
		parser.execProgram(program);
		ms.setBuffer(charput.getBuffer());
		SDL_EnableKeyRepeat(0,20);
		mode=1;
		ms.reDisplay();
	      } 	      
	     else if(event.key.keysym.sym==SDLK_ESCAPE)
	      {
		SDL_Quit();
		exit(1);
	      } 	      
	      else
	      {
		switch (mode)
		{
		  case 1:
		    ms.sendKey( event.key.keysym);
		  break;
		 case 2:
		    yeq.sendKey( event.key.keysym);
		 break;
		 case 4:
		    menuPrgrm.sendKey( event.key.keysym);
		 break;	
		 case 5:
		    rangeEdit.sendKey( event.key.keysym);
		 break;			 
		}
	      }
            break;
    }
}

if (SDL_GetTicks()-old_time>350)
  {
    if (SDL_GetTicks()-old_time>500)
    {
      cout<<"WARNING slow app!!: took "<<SDL_GetTicks()-old_time<<"ms before could blink cursor again (should be <400 ms)"<<endl;
    }
    if (mode==1)
    {
    ms.blinkCursor();
    ms.reDisplay();
    }
    
    if (mode==5)
    {
     rangeEdit.blinkCursor();
     rangeEdit.reDisplay();
    }
    old_time=SDL_GetTicks();
  }
}


}
