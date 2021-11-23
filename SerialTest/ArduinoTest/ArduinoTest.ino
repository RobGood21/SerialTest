/*
 Name:		ArduinoTest.ino
 Created:	11/23/2021 12:37:45 PM
 Author:	gebruiker

 Test voor werking van een arduino en wissen EEPROM geheugen
 leds op pinnen 8-13 schakelaars op A0-A4

*/


#include <EEPROM.h>
unsigned long slowtimer;
byte ledcount;
byte ledactive = 0;
byte switchstatus = 255;


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	PORTC |= (15 << 0); //pull up to A0~A4
	DDRB |= B00111111; //pin8~pin13 outputs

}

// the loop function runs over and over again until power down or reset
void loop() {
	if (millis() - slowtimer > 50) {
		slowtimer = millis();
		switchExe();
		if (GPIOR0 & (1 << 0)) {
			ledcount++;
			if (ledcount > 20) {
				ledsoff();
				ledcount = 0;
				ledactive++;
				if (ledactive > 5)ledactive = 0;
				PORTB |= (1 << ledactive);
			}
		}
	}
}
void ledsoff() {
	PORTB = 0;
}
void switchExe() {
	byte changed = 0;
	byte read = PINC;
	changed = read ^ switchstatus;

	for (byte i = 0; i < 5; i++) {
		if (changed & (1 << i)) {
			if (~read & (1 << i))switchOn(i);
		}
	}
	switchstatus = read;
}
void switchOn(byte sw) {
	byte ok = 1;

	Serial.println(sw);
	switch (sw) {
	case 0:
		ledsoff();
		GPIOR0 ^= (1 << 0); //flip looplicht aan uit
		break;
	case 1:
		PORTB = 255;
		break;
	case 2:
		ledsoff();
		break;
	case 3:
		//Factory reset
		for (int i = 0; i < EEPROM.length(); i++) {
			EEPROM.write(i, 0xFF);
		}		
		for (int i = 0; i < EEPROM.length(); i++) {
			if (EEPROM.read(i) != 255) ok = 0;
		}

		if (ok == 1)PORTB = 255;

		break;
	}
}
