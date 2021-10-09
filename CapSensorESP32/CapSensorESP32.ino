// Triaume: An augmented triangle
// Description: Using Arduino CapSense Library, this code will acquire the thumb finger
// touch gestures on the triangle. Through touch detection, signals will be sent to Pure Data,
// triggering sounds.
#include <WiFi.h>
#include <CapacitiveSensor.h>
#include <OSCMessage.h>
#include <SLIPEncodedSerial.h>
#include <Ticker.h>

#define WIFIMODE 0
#define SEND_PIN 13
#define RECEIVE_PIN 12
#define ACTIVATE_BUTTON 5
#define LED_PIN 2
#define SAMPLING_PERIOD 80000//period for each interrupt (microsseconds)
#define BAUD_RATE 115200
#define ESP32_PRESCALER 1

#define RXD2 16 
#define TXD2 17


// The Sensor Pin is where the wire is attached to the triangle
CapacitiveSensor   cap_sensor = CapacitiveSensor(SEND_PIN, RECEIVE_PIN);
SLIPEncodedSerial SLIPSerial(Serial); // For Sending OSC Messages Over Serial
int ButtonStatus = 0;
volatile int SendFlag = 0;
int debounceTime = 0;
long counter = 0;
float num;

char ssid[] = "";          // your network SSID (name)
char pass[] = "";          // your network password

WiFiUDP Udp;

const IPAddress outIp(192, 168, 0, 104);     // remote IP of your computer
const unsigned int outPort = 9005;          // remote port to receive OSC
const unsigned int localPort = 9000;        // local port to listen for OSC packets (actually not used for sending)



Ticker t;
hw_timer_t * timer = NULL;

void stop_timer(){
    timerEnd(timer);
    timer = NULL; 
}

void setup()
{

#if WIFIMODE == 1
  Serial.begin(BAUD_RATE);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(localPort);
#else

  //start_timer();

  Serial1.begin(BAUD_RATE, SERIAL_8N1, RXD2, TXD2);

  //begin SLIPSerial just like Serial
  SLIPSerial.begin(BAUD_RATE);
#endif
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
    float total1 =  cap_sensor.capacitiveSensor(50);
    msg.add(total1);
#if WIFIMODE == 1
    Udp.beginPacket(outIp, 9005);
    msg.send(Udp);
    Udp.endPacket();
#else
    SLIPSerial.beginPacket();
    msg.send(SLIPSerial);
    SLIPSerial.endPacket();
#endif
    msg.empty();
  }
}
