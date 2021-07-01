/*
 Name:		SerialTest.ino
 Created:	6/30/2021 9:02:24 AM
 Author:	Rob Antonisse

 Diverse test met serial com poort en groter displays.


*/



#include <SD.h>
#include <TFT.h>
#include <SPI.h>

#define cs 10
#define dc 9
#define rst 8


TFT TFTscreen = TFT(cs, dc, rst);

//declarations
unsigned long SW_time;
byte SW_status=0xFF;
PImage pic;



void setup() {
	Serial.begin(9600);
	TFTscreen.begin();
	//ports

	PORTC |= (15 << 0); //pins A0~A4 as inputs with pullups

	TFTscreen.background(0, 0, 0);

	//TFTscreen.fillCircle(40, 30, 10, 0xFF0000);

	if (SD.begin(4)) {
		Serial.println(F("SD_OK"));	
	}


	//pic = TFTscreen.loadImage("Davin.bmp");

	//if (pic.isValid() == true) {
	//	Serial.println("plaatje ok");
	//}

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
		TFTscreen.fillScreen(0xFFFF00);
		break;

	case 1: //rechtsboven color=BGR
		TFTscreen.background(0, 0, 255);
		TFTscreen.stroke(0, 255, 0);
		TFTscreen.setTextSize(2);
		TFTscreen.text("Wisselmotor", 15, 40);
		break;



	case 3: //links boven display
		pic = TFTscreen.loadImage("Davin.bmp");
		TFTscreen.background(0, 0, 0);
		TFTscreen.image(pic, 10, 10);
		break;
	}


}

void SW_off(byte sw) {
	Serial.print("SW-off "); Serial.println(sw);
}