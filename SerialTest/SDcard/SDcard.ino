/*
 Name:		SDcard.ino
 Created:	6/30/2021 10:22:06 AM
 Author:	Rob Antonisse

 Sketch om een SD card te kunnen gebruiken op een TFT 1.8 scherm.


*/





// the setup function runs once when you press reset or power the board

#include <SD.h>
#include <SPI.h>

const int chipSelect = 10;
File root;

void setup() {

	Serial.begin(9600);
	while (!Serial);

	Serial.print("Initializing SD card...");


	if (!SD.begin(chipSelect)) {
		Serial.println("initialization failed. Things to check:");
		Serial.println("1. is a card inserted?");
		Serial.println("2. is your wiring correct?");
		Serial.println("3. did you change the chipSelect pin to match your shield or module?");
		Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");
		while (true);
	}

	Serial.println("initialization done.");
	//root = SD.open("/");
	//printDirectory(root, 0);
	Serial.println("done!");
}

void printDirectory(File dir, int numTabs) {
	while (true) {
		File entry = dir.openNextFile();
		if (!entry) {
			// no more files
			break;
		}
		for (uint8_t i = 0; i < numTabs; i++) {
			Serial.print('\t');
		}
		Serial.print(entry.name());
		if (entry.isDirectory()) {
			Serial.println("/");
			printDirectory(entry, numTabs + 1);
		}
		else {
			// files have sizes, directories do not
			Serial.print("\t\t");
			Serial.println(entry.size(), DEC);
		}
		entry.close();
	}
}

// the loop function runs over and over again until power down or reset
void loop() {

}
