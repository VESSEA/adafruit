// 
// 
// 

#include "DeviceConfiguration.h"
#include <FlashStorage.h>

typedef struct {
	boolean valid;
	char name[10];
	//char secret1[20];
	//char secret2[20];
} DeviceStorage;

FlashStorage(flash_store, DeviceStorage);
DeviceStorage device_storage;

void DeviceConfiguration::read_flash()
{
	device_storage = flash_store.read();
	Serial.println(device_storage.name);
}

void DeviceConfiguration::write_flash()
{
	const String device_name = "Device001";
	device_name.toCharArray(device_storage.name, 10);
	flash_store.write(device_storage);
	Serial.println("Device name saved");
}

DeviceConfiguration device_configuration;

