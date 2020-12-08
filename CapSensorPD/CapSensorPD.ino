// Triaume: An augmented triangle
// Description: Using Arduino CapSense Library, this code will acquire the thumb finger
// touch gestures on the triangle. Through touch detection, signals will be sent to Pure Data,
// triggering sounds.


#include <CapacitiveSensor.h>
#include <TimerOne.h>

#define SEND_PIN 4
#define RECEIVE_PIN 2
#define ACTIVATE_BUTTON A0
#define LED_PIN 8

// Send Pin: 4 
// Receive Pin: 2
// The Sensor Pin is where the wire is attached to the triangle
CapacitiveSensor   cs_4_2 = CapacitiveSensor(SEND_PIN,RECEIVE_PIN); 
int ButtonStatus = 0;

void setup()                    
{
   pinMode(LED_PIN,OUTPUT);
   pinMode(ACTIVATE_BUTTON,INPUT);
   Timer1.initialize(150000);
   Timer1.attachInterrupt(check_button);
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(115200);
}


void check_button() {
  if(analogRead(ACTIVATE_BUTTON))
    {
      ButtonStatus = !ButtonStatus;
      digitalWrite(LED_PIN,!digitalRead(LED_PIN));
    }
}


void loop()                    
{
    //Serial.println(ButtonStatus);
    
    if(ButtonStatus) {
  
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(1000);

    //Serial.println(millis() - start);        // check on performance in milliseconds
    //Serial.print("\t");                    // tab character for debug windown spacing

    Serial.println(total1);                  // print sensor output 1

    }
    
    //delay(10);                             // arbitrary delay to limit data to serial port 
}
