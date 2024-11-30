/* 1byte CC1101 Receiver example.
/* Tutorial link: http://electronoobs.com/eng_arduino_tut98.php
 * Code: http://electronoobs.com/eng_arduino_tut98_code2.php
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
int received_number = 0;
// int LED = 3;

 void setup()
{
  // pinMode(LED, OUTPUT);
  Serial.begin(9600);
  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.SetReceive();
}

byte RX_buffer[11]={0};
byte size,i,flag;

void loop()
{
  if(ELECHOUSE_cc1101.CheckReceiveFlag())
  {
    size=ELECHOUSE_cc1101.ReceiveData(RX_buffer);
    for(int i=0; i<size; i++)
    {
      received_number = RX_buffer[i];
      Serial.println(received_number);     
    }
    // analogWrite(LED,received_number);
    ELECHOUSE_cc1101.SetReceive();
  }
}
