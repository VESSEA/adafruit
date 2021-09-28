// MenuConfiguration.h
/*
File:
Author: Matthew David Elgert
Create Date: 9/28/2021
Last Updated: 9/28/2021
Note:
*/

#ifndef _MENUCONFIGURATION_h
#define _MENUCONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MenuConfiguration
{
 protected:
	 static void read_flash();
	 static void write_flash();
 public:
	static void run();
	static void configuration_help();
};

extern MenuConfiguration menu_configuration;

#endif

