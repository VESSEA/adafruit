/*
File:
Author: Matthew David Elgert
Create Date: 9/28/2021
Last Updated: 9/28/2021
Note:
*/

#include "MenuMain.h"
#include "MenuConfiguration.h"

void MenuMain::read()
{
	rx_byte = Serial.read();

	if (sub_menu == 0)
	{
		switch (tolower(rx_byte))
		{
		case 'h':
			main_help();
			break;
		case 'c':
			sub_menu = 'c';
			MenuConfiguration::configuration_help();
			break;
		default:
			break;
		}
	}
	else
	{
		switch (tolower(sub_menu))
		{
		case 'c':
			MenuConfiguration::run();
			break;
		default:
			break;
		}
	}
}

void MenuMain::main_help()
{
	Serial.println("Main menu help commands.");
	Serial.println("'h' Prints help.");
	Serial.println("'c' Go to configuration menu.");
}

MenuMain menu_main;

