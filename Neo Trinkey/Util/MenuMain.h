// MenuMain.h
/*
File:
Author: Matthew David Elgert
Create Date: 9/28/2021
Last Updated: 9/28/2021
Note:
*/

#ifndef _MENUMAIN_h
#define _MENUMAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MenuMain
{
 protected:
	 
 public:
	int rx_byte;
	int sub_menu = 0;
	void read();
	static void main_help();
};

extern MenuMain menu_main;

#endif

