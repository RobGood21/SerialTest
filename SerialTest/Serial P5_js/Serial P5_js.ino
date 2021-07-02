/*
 Name:		Serial_P5_js.ino
 Created:	7/2/2021 10:54:42 AM
 Author:	Rob  Antonisse

 Testen met P5.JS aansturen lokale arduino via de com poort



*/

#include <TFT.h>
#include <SPI.h>

TFT display = TFT(10, 9, 8); //cs pin10 chip select; dc pin9 data/command; reset pin 8

//declarations
unsigned long SW_time;
byte SW_status = 0xFF;


void setup() {
	Serial.begin(9600);
	SPI.begin(); //niet noodzakelijk, gebeurt ook in de library constructor
	display.begin(); //constructor
	//ports

	PORTC |= (15 << 0); //pins A0~A4 as inputs with pullups
	
	display.background(10,10,10); //colors Blue-green-red 
	display.setRotation(3); //1,2,3 draait het scherm
	display.setTextSize(1); //formaat tekens
	display.stroke(0xFFFFFF); //color omlijning blue-green-red (in hex mag ook)
	display.text("Serial test met P5.js",0,0); //text en x,y linker bovenhoek

}

void loop() {
	if (millis() - SW_time > 20) {
		SW_time = millis();
		SW_exe();
	}
}
void SW_exe() {
	//reads switches
	byte sw; byte changed;
	sw = PINC << 4;
	sw = sw >> 4; //only bit 0~3
	changed = sw ^ SW_status;
	if (changed > 0) {

		for (byte i = 0; i < 4; i++) {
			if (changed & (1 << i)) {
				if (sw & (1 << i)) {
					SW_off(i);
				}
				else {
					SW_on(i);
				}
			}
		}
	}
	SW_status = sw;
}

void SW_on(byte sw) {
	Serial.print("SW-on "); Serial.println(sw);
	switch (sw) {
	case 0:
		break;

	case 1: //rechtsboven color=BGR

		break;
	case 2:
		break;

	case 3: //links boven display
		break;
	}
}

void SW_off(byte sw) {
	Serial.print("SW-off "); Serial.println(sw);
}