/*
 Name:		TFT_Adafruit.ino
 Created:	7/1/2021 9:34:53 PM
 Author:	Rob Antonisse

 Test met TFT 1.8 display, nu gebruik makend van de adafruit librarie


 Aansluiting Display:SCK(pin13) MOSI(pin11) MISO(pin12) CS(pin10) Reset(pin8) DS(pin9)
Verder LED op 3.3V en natuurlijk VCC aan 5V en GND aan GND
Ook card reader aansluiten op de SCK (Pin13) MOSI(pin11) MISO(pin12) CS (pin4)

*/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>



Adafruit_ST7735 display = Adafruit_ST7735(10, 9, 8);

//declarations
unsigned long SW_time;
byte SW_status = 0xFF;
//PImage pic;
bool colors = false;
int colorcount;

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(9600);

	// initialise the display
	display.setFont();
	display.fillScreen(0x0000);
	display.setTextColor(0xFFFF);
	display.setTextSize(1);

	display.write(50);

	// the display is now on
	//isDisplayVisible = true;

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