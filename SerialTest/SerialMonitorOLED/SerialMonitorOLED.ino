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
byte switchstatus = 0xFF;

//specifiek voor de serial communicatie met Processing
byte usbfase=0; //fase van de communicatie
byte usbdata[6]; //buffer voor de ontvangen msg 
//usbdata[0] =aantal bytes te ontvangen
//usbdata[1] =instructie
//usbdat[2][3][4][5]  databytes



void setup() {
	Serial.begin(9600);
	dp.begin(0x02, 0x3C);
	//poorten
	PORTC |= (15 << 0);
	welcome();
}
void loop() {
	readSerial();

	if (millis() - slowtime > 20) {
		slowtime = millis();
		SW_exe();
	}


}

void readSerial() {
	byte ib; 
	bool ready = true;

	if (Serial.available()) { //while beter niet wordt telkens in loop() aangeroepen
		ib = Serial.read();

		switch (usbfase) {
		case 0: //niet bezig met een communicatie
			if (ib == 0xFF) { //startbyte msg
				usbfase = 1; //
				ready = false;
			}
			break;
		case 1: //bezig met communicatie nu aantal te ontvangen bytes ontvangen usbdata[0]
			usbdata[0] = ib;
			usbfase = 2;
			ready = false;
			break;
		case 2: //ontvangen 2e byte instructie
			usbdata[1] = ib; //instructiebyte
			//printbyte(200);
			//delay(1000);
			if (usbdata[0] > 1) {
				usbfase = 3;
				ready = false;
			}
			break;
		case 3:
			usbdata[2] = ib; //databyte 0 LSB
			if (usbdata[0] > 2) {
				usbfase = 4;
				ready = false;
			}
			break;
		case 4:
			usbdata[3] = ib; //databyte 1
			if (usbdata[0] > 3) {
				usbfase = 5;
				ready = false;
			}
			break;
		case 5:
			usbdata[4] = ib; //databyte 2
			if (usbdata[0] > 4) {
				usbfase = 6;
				ready = false;
			}
			break;
		case 6:
			usbdata[5] = ib; //databyte 3 MSB
			//ready blijft true, laatst mogelijke byte;
			break;
		}
		if (ready == true) {
			usbfase = 0;
			USB_exe();
		}
	}
}
void USB_exe() {
	//voert het ONTVANGEN instructie uit
	printbyte(usbdata[1]); //print instructie byte
	switch (usbdata[1]) { //instructie ontvangen
	case 10: //request productID
		//product ID voor monitor =1 voor PendelDCC =10
		sendSerial(1);
		break;
	}
	//sendSerial(150);
}


void sendSerial(byte data) {
	Serial.write(data);
}

void printbyte(byte input) {
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
	byte changed = 0x00;
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
	switch (sw) {
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

