#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

#include "Adafruit_WS2801.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
#include <avr/power.h>
#endif

int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];
int DC_One_Data;
int DC_Two_Data;
int i;

uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

Adafruit_WS2801 strip = Adafruit_WS2801(32, dataPin, clockPin);

void setup() {
  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  digitalWrite(RESET, LOW);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin();
  strip.show();
}

void loop() {
  Read_Frequencies();
  EQ();
}

void EQ() {  
  strip.setPixelColor(0,map(Frequencies_One[0],0,1023,0,255),0,map(Frequencies_One[0],0,1023,0,15));
  strip.setPixelColor(1,map(Frequencies_One[1],0,1023,0,239),0,map(Frequencies_One[1],0,1023,0,31));
  strip.setPixelColor(2,map(Frequencies_One[2],0,1023,0,223),0,map(Frequencies_One[2],0,1023,0,47));
  strip.setPixelColor(3,map(Frequencies_One[3],0,1023,0,207),0,map(Frequencies_One[3],0,1023,0,63));
  strip.setPixelColor(4,map(Frequencies_One[4],0,1023,0,191),0,map(Frequencies_One[4],0,1023,0,79));
  strip.setPixelColor(5,map(Frequencies_One[5],0,1023,0,175),0,map(Frequencies_One[5],0,1023,0,95));
  strip.setPixelColor(6,map(Frequencies_One[6],0,1023,0,159),0,map(Frequencies_One[6],0,1023,0,111));


  strip.show();
}

void Read_Frequencies() {
  digitalWrite(RESET, HIGH);
  delayMicroseconds(200);
  digitalWrite(RESET, LOW);
  delayMicroseconds(200);

  for (freq_amp = 0; freq_amp < 7; freq_amp++)
  {
    digitalWrite(STROBE, HIGH);
    delayMicroseconds(50);
    digitalWrite(STROBE, LOW);
    delayMicroseconds(50);

    DC_One_Data = analogRead(DC_One);

    if(DC_One_Data <= 100){
      Frequencies_One[freq_amp] = 0;      
      }else{
      Frequencies_One[freq_amp] = DC_One_Data;        
      }

  }
}
