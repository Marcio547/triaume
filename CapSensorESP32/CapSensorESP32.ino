// Triaume: An augmented triangle
// Description: Using Arduino CapSense Library, this code will acquire the thumb finger
// touch gestures on the triangle. Through touch detection, signals will be sent to Pure Data,
// triggering sounds.

#include <CapacitiveSensor.h>
#include <OSCMessage.h>
#include <SLIPEncodedSerial.h>

#define SEND_PIN 13
#define RECEIVE_PIN 12
#define ACTIVATE_BUTTON 5
#define LED_PIN 2
#define SAMPLING_PERIOD 80000//period for each TimerOne interrupt (microsseconds)
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
int SendFlag = 0;
int debounceTime = 0;
long counter = 0;
float num;

hw_timer_t * timer = NULL;


void start_timer()
{
  timer = timerBegin(0, 1, true);
  timerAttachInterrupt(timer, &send_data, true);
  timerAlarmWrite(timer, SAMPLING_PERIOD, true); 
  timerAlarmEnable(timer);

}

void stop_timer(){
    timerEnd(timer);
    timer = NULL; 
}

void setup()
{
  //pin Configurations
  pinMode(LED_PIN, OUTPUT);
  pinMode(ACTIVATE_BUTTON, INPUT_PULLUP);


  Serial1.begin(BAUD_RATE, SERIAL_8N1, RXD2, TXD2);

  //Periodic interrupt to activate send_data ISR routine
  //Timer1.initialize(SAMPLING_PERIOD);
  //Timer1.attachInterrupt(send_data);

  //Button Interrupt
  attachInterrupt(digitalPinToInterrupt(ACTIVATE_BUTTON), check_button, LOW);

  start_timer();

  //begin SLIPSerial just like Serial
  //SLIPSerial.begin(BAUD_RATE);

  digitalWrite(LED_PIN, LOW);
  Serial.begin(BAUD_RATE);
}



void send_data() {
  //Serial.println("Flag Status: " + String(SendFlag));
  SendFlag = 1;
  //Serial.println(500);
  


}


void check_button() {
 stop_timer();
}


void loop()
{
   
    if (SendFlag) {
     
    OSCMessage msg("/data");
    //long start = millis();  //check performance time
    long total1 =  cs_4_2.capacitiveSensor(1000);
    //Serial.println(millis() - start); //check performance time
    //Serial1.println(total1/1000); //check data using Serial Plotter, if desired.
    //Serial1.println(3);
    //Send OSC message
    num = total1;
    msg.add(num);
    SLIPSerial.beginPacket();
    msg.send(SLIPSerial);
    SLIPSerial.endPacket();
    SendFlag = 0;


  }
}
