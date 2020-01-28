#include <CapacitiveSensor.h>

// 4.1MOhm resistor. Pin numbers set for Linkit 7688 Duo
CapacitiveSensor touchSwitch = CapacitiveSensor(22,20);

#define LED_PIN A5 //LED turns on indicating correct sensivitiy



void setup()
{
 pinMode(LED_PIN, OUTPUT);
 Serial.begin(9600);
}

void loop()
{
 //code form CapacitiveSensor Library.
 long start = millis();
 long val = touchSwitch.capacitiveSensor(30);

//val > 800 closed hand
//turns LED on with closed hand holding triangle
if (val > 800) {

    //for debug
    //Serial.print(val);
    digitalWrite(LED_PIN, HIGH);
 } else {
    
    digitalWrite(LED_PIN, LOW);
 }
 Serial.write(val);
}
