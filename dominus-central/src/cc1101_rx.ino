#include <ELECHOUSE_CC1101.h>

int received_number = 0;
// int LED = 3;

 void setup()
{
  // pinMode(LED, OUTPUT);
  pinMode(4, OUTPUT);
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
    size = ELECHOUSE_cc1101.ReceiveData(RX_buffer);
    for(int i=0; i<size; i++)
    {
      received_number = RX_buffer[i];
      Serial.println(received_number);
      digitalWrite(4, HIGH); // sets the digital pin 13 on
      delay(3000);            // waits for a second
      digitalWrite(4, LOW);  // sets the digital pin 13 off
      delay(3000);            // waits for a second
    }
    // analogWrite(LED,received_number);
    ELECHOUSE_cc1101.SetReceive();
  }
}
