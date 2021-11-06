/*
 Name:		SerialMonitorOLED.ino
 Created:	11/6/2021 9:56:54 AM
 Author:	gebruiker
 Serial monitor met een OLED scherm...
 Bedoeld voor Processing testen



*/

//libraries
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>
#include <splash.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <EEPROM.h>

//constructors
Adafruit_SSD1306 dp(128, 64, &Wire, -1); 


//variables
unsigned long slowtime;
byte switchstatus=0xFF;



void setup() {
	Serial.begin(9600);
	dp.begin(0x02, 0x3C); 
	//poorten
	PORTC |= (15 << 0);
	
	
	
	welcome();




}
void loop() {
	if (Serial.available()) {
		int inByte = Serial.read();
		//Serial.print(inByte, DEC);
		if(inByte !=10) printtxt(inByte);
	} 

	if (millis() - slowtime > 20) {
		slowtime = millis();
		SW_exe();
	}


}

void sendSerial(byte data) {
	Serial.print(data);
}

void printtxt(byte input) {
	dp.clearDisplay();
	dp.setCursor(10, 20);
	dp.setTextColor(1);
	dp.setTextSize(2);
	dp.print(input);
	dp.display();
}

void welcome() {
	dp.clearDisplay();
	dp.setTextSize(1);
	dp.setTextColor(1);
	dp.setCursor(10, 10);
	dp.print("Processingtest");
	dp.display();	
}

void SW_exe() {
	byte status = PINC;
	byte changed=0x00;
	changed = status ^ switchstatus;
	if (changed > 0) {
		for (byte i = 0; i < 4; i++) {
			if (changed & (1 << i)) {
				if (status & (1 << i)) { //off

				}
				else { //on
					SW_on(i);
				}

			}
		}
	}
	switchstatus = status;
}
void SW_on(byte sw) {
	//printtxt(sw);
	switch (sw){
		case 0:
			Serial.write(10);
			break;
		case 1:
			Serial.write(50);
			break;
		case 2:
			Serial.write(75);
			break;
		case 3:
			Serial.print(125);
			break;
	}
}

