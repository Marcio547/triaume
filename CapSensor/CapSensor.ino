#include <CapacitiveSensor.h>

// 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor touchSwitch = CapacitiveSensor(22,20);

#define LED_PIN A5



void setup()
{
 pinMode(LED_PIN, OUTPUT);
 Serial.begin(9600);
}

void loop()
{
 long start = millis();
 long val = touchSwitch.capacitiveSensor(30);

//1500 toque do triangulo
//3000 moeda
// fechar a mao
if (val > 800) {

 //Serial.print(val);
 digitalWrite(LED_PIN, HIGH);
 
 } else {
 
 digitalWrite(LED_PIN, LOW);
 
 }
 Serial.write(val);
}
