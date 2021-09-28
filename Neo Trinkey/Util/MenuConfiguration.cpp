/*
File: 
Author: Matthew David Elgert
Create Date: 9/28/2021
Last Updated: 9/28/2021
Note:
*/

#include "MenuConfiguration.h"
#include "MenuMain.h"
#include <FlashStorage.h>

typedef struct {
	boolean valid;
	char name[10];
} Device;

FlashStorage(flash_store, Device);

void MenuConfiguration::run()
{

	switch (tolower(menu_main.rx_byte))
	{
	case 'c':
		print_config();
		break;
	case 'h':
		configuration_help();
		break;
	case 'w':
		//TODO
		break;
	case 'x':
		menu_main.sub_menu = 0;
		MenuMain::main_help();
		break;
	default:
		break;
	}

}

void MenuConfiguration::configuration_help()
{
	Serial.println("Configuration menu help commands.");
	Serial.println("'h' Prints help.");
	Serial.println("'c' Prints configuration.");
	Serial.println("'w' Write default values to flash.");
	Serial.println("'x' Exit and go to main menu.");
}

void MenuConfiguration::print_config()
{
	Serial.println("TODO print config!");
}

MenuConfiguration menu_configuration;

