/*
 Name:		TFT_test.ino
 Created:	6/30/2021 9:02:24 AM
 Author:	Rob Antonisse

Testen met TFT 1.8 display


Gaat via SPI, twee CS (chip select) nodig
PIN10 voor het display
PIN4 voor de card reader.

Aansluiting Display:SCK(pin13) MOSI(pin11) MISO(pin12) CS(pin10) Reset(pin8) DS(pin9)
Verder LED op 3.3V en natuurlijk VCC aan 5V en GND aan GND
Ook card reader aansluiten op de SCK (Pin13) MOSI(pin11) MISO(pin12) CS (pin4)

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
byte SW_status = 0xFF;
PImage pic;
bool colors = false;
int colorcount;


void setup() {
	Serial.begin(9600);
	SPI.begin(); //niet noodzakelijk, gebeurt ook in de library constructor

	TFTscreen.begin(); //constructor
	//ports
	PORTC |= (15 << 0); //pins A0~A4 as inputs with pullups
		if (SD.begin(4)) {
		//Serial.println(F("SD_OK"));
	}
	TFTscreen.background(0, 0, 0);
	//pic = TFTscreen.loadImage("Davin.bmp");
	//if (pic.isValid() == true) {
	//	Serial.println("plaatje ok");
	//}

	TFTscreen.setRotation(3); //1,2,3 draait het scherm

}

void loop() {

	if (millis() - SW_time > 20) {
		SW_time = millis();
		SW_exe();

		if (colors) {
			colorcount++;
			if (colorcount > 10) {
				colorcount = 0;
				changecolors();
			}
		}
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

void changecolors() {
	TFTscreen.stroke(random(0, 0xFF), random(0, 0xFF), random(0, 0xFF)); //randen
	TFTscreen.fill(random(0, 0xFF), random(0, 0xFF), random(0, 0xFF)); //invulling
	TFTscreen.circle(random(10, 150), random(10, 118), random(1, 20));
}


void SW_on(byte sw) {
	Serial.print("SW-on "); Serial.println(sw);
	switch (sw) {
	case 0:
		
		break;

	case 1: //rechtsboven color=BGR
		TFTscreen.background(0, 0, 255);
		TFTscreen.stroke(0, 255, 0);
		TFTscreen.setTextSize(2);
		TFTscreen.text("tekst", 15, 40);
		break;

	case 2:
		colors = !colors;
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