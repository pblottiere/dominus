
/* 1byte CC1101 TRANSMITTER example.
/* Tutorial link: http://electronoobs.com/eng_arduino_tut98.php
 * Code: http://electronoobs.com/eng_arduino_tut98_code1.php
 * Scheamtic: http://electronoobs.com/eng_arduino_tut98_sch1.php
 * Youtube Channel: http://www.youtube/c/electronoobs   
// Arduino          CC1101
// GND              GND
// 3.3V             VCC
// D10              CSN/SS   **** Must be level shifted to 3.3V
// D11              SI/MOSI  **** Must be level shifted to 3.3V
// D12              SO/MISO
// D13              SCK      **** Must be level shifted to 3.3V
// D2               GD0
*/

#include <ELECHOUSE_CC1101.h> //Download it here: http://electronoobs.com/eng_arduino_ELECHOUSE_CC1101.php
#define size 1
// int pot = A0;
int I = 0;


byte TX_buffer[size]={0};
byte i;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(pot,INPUT);
  Serial.begin(9600);
  ELECHOUSE_cc1101.Init();
  for(i=0;i<size;i++)
  {
     TX_buffer[i]=i;
  }
}

void loop()
{
  // int val = map(analogRead(pot),0,1024,0,255);
  TX_buffer[0] = I;
  ELECHOUSE_cc1101.SendData(TX_buffer,size);
  I += 1;
  delay(500);

  // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(1000);                       // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(1000);                       // wait for a second
}
