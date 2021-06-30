/*
 Name:		SerialTest.ino
 Created:	6/30/2021 9:02:24 AM
 Author:	Rob Antonisse

 Diverse test met serial com poort en groeter displays.
 Tweede 

*/



#include <TFT.h>
#include <SPI.h>

#define cs 10
#define dc 9
#define rst 8

TFT TFTscreen = TFT(cs, dc, rst);




void setup() {
	TFTscreen.begin();
	TFTscreen.background(0, 0, 0);
	TFTscreen.stroke(255, 255, 255);
	TFTscreen.setTextSize(2);

	TFTscreen.text("Wisselmotor", 20, 20);

}

void loop() {
  
}
