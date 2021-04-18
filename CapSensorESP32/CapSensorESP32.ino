// Triaume: An augmented triangle
// Description: Using Arduino CapSense Library, this code will acquire the thumb finger
// touch gestures on the triangle. Through touch detection, signals will be sent to Pure Data,
// triggering sounds.

#include <CapacitiveSensor.h>
#include <OSCMessage.h>
#include <SLIPEncodedSerial.h>
#include <Ticker.h>

#define SEND_PIN 13
#define RECEIVE_PIN 12
#define ACTIVATE_BUTTON 5
#define LED_PIN 2
#define SAMPLING_PERIOD 80000//period for each interrupt (microsseconds)
#define BAUD_RATE 115200
#define ESP32_PRESCALER 1

#define RXD2 16 
#define TXD2 17

// Send Pin: 4
// Receive Pin: 2
// The Sensor Pin is where the wire is attached to the triangle
CapacitiveSensor   cs_4_2 = CapacitiveSensor(SEND_PIN, RECEIVE_PIN);
SLIPEncodedSerial SLIPSerial(Serial); // For Sending OSC Messages Over Serial
int ButtonStatus = 0;
volatile int SendFlag = 0;
int debounceTime = 0;
long counter = 0;
float num;

Ticker t;
hw_timer_t * timer = NULL;

void stop_timer(){
    timerEnd(timer);
    timer = NULL; 
}

void setup()
{
  Serial1.begin(BAUD_RATE, SERIAL_8N1, RXD2, TXD2);

  //start_timer();

  //begin SLIPSerial just like Serial
  SLIPSerial.begin(BAUD_RATE);

  digitalWrite(LED_PIN, LOW);

  t.attach(0.001,&send_data);
}

void send_data() {
  SendFlag = 1;
}

void loop()
{
  if (SendFlag) {
    SendFlag = 0;
    OSCMessage msg("/data");
    //long start = millis();  //check performance time
    float total1 =  cs_4_2.capacitiveSensor(200);

    msg.add(total1);
    SLIPSerial.beginPacket();
    msg.send(SLIPSerial);
    SLIPSerial.endPacket();
    msg.empty();
  }
}
