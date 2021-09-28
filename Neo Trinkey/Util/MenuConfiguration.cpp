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
Device device;

void MenuConfiguration::run()
{

	switch (tolower(menu_main.rx_byte))
	{
	case 'h':
		configuration_help();
		break;
	case 'r':
		read_flash();
		break;
	case 'w':
		write_flash();
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
	Serial.println("'r' Read flash.");
	Serial.println("'w' Write default values to flash.");
	Serial.println("'x' Exit and go to main menu.");
}

void MenuConfiguration::read_flash()
{
	//Serial.println("TODO read flash!");
	Serial.println("TODO read flash!");
}

void MenuConfiguration::write_flash()
{
	Serial.println("TODO write flash!");
}

MenuConfiguration menu_configuration;

