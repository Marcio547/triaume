// Triaume: An augmented triangle
// Description: Using Arduino CapSense Library, this code will acquire the thumb finger
// touch gestures on the triangle. Through touch detection, signals will be sent to Pure Data,
// triggering sounds.

#include <CapacitiveSensor.h>
#include <TimerOne.h>

#include <OSCMessage.h>
#include <SLIPEncodedSerial.h>

#define SEND_PIN 6
#define RECEIVE_PIN 4
#define ACTIVATE_BUTTON 3
#define LED_PIN 8
#define SAMPLING_PERIOD 50000//period for each TimerOne interrupt (microsseconds)
#define BAUD_RATE 115200

// Send Pin: 4
// Receive Pin: 2
// The Sensor Pin is where the wire is attached to the triangle
CapacitiveSensor   cs_4_2 = CapacitiveSensor(SEND_PIN, RECEIVE_PIN);
SLIPEncodedSerial SLIPSerial(Serial); // For Sending OSC Messages Over Serial
int ButtonStatus = 0;
int SendFlag = 0;
int debounceTime = 0;

void setup()
{
  //pin Configurations
  pinMode(LED_PIN, OUTPUT);
  pinMode(ACTIVATE_BUTTON, INPUT_PULLUP);

  //Periodic interrupt to activate send_data ISR routine
  Timer1.initialize(SAMPLING_PERIOD);
  Timer1.attachInterrupt(send_data);

  //Button Interrupt
  attachInterrupt(digitalPinToInterrupt(ACTIVATE_BUTTON), check_button, CHANGE);

  //begin SLIPSerial just like Serial
  SLIPSerial.begin(BAUD_RATE);
  Serial.begin(BAUD_RATE);
}

float num;
void send_data() {
  //Serial.println("Flag Status: " + String(SendFlag));
  if (SendFlag) {
    OSCMessage msg("/data");
    //long start = millis();  //check performance time
    long total1 =  cs_4_2.capacitiveSensor(1000);
    
    //Serial.println(millis() - start); //check performance time
    //Serial.println(total1); //check data using Serial Plotter, if desired.

    //Send OSC message
    num = total1;
    msg.add(num);
    SLIPSerial.beginPacket();
    msg.send(SLIPSerial);
    SLIPSerial.endPacket();


  }

}


void check_button() {
  //Serial.println("apertou o botao");
  if (analogRead(ACTIVATE_BUTTON))
  {
    SendFlag = !SendFlag;
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));

  }
}


void loop()
{

}
