#include <ELECHOUSE_CC1101.h>
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
