// 
// 
// 

#include "RandomGenerator.h"

void RandomGenerator::CreateSecret(int numBytes)
{
    char* letters = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+";
    int lettersCount = 48;
    String rand_string = "";

    for (int i = 0; i < numBytes; i++)
    {
        rand_string = rand_string + letters[random(0, lettersCount)];
    }

	Serial.println(rand_string);

	//delay(1000);
}

RandomGenerator random_generator;

