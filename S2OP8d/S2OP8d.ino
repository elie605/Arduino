#include <Arduino.h>

int switchPin = 4;
int ledA = 11;
int ledB = 10;
int switchState = LOW;
int onOffCounter = 0;

void setup() {
    //Zet pin van led op output
    pinMode(ledA, OUTPUT);
    pinMode(ledB, OUTPUT);
    //Zet pin van led op input
    pinMode(switchPin, INPUT);
}

void loop() {
    //Als button ingedrukt is
    if (digitalRead(switchPin) == HIGH) {
        //En lamp uit is
        if (onOffCounter == 0) {
            //Zet lamp aan
            onOffCounter = 1;
        } else {
            //Anders zet lamp uit
            onOffCounter = 0;
        }

        //Als button nog ingedrukt is wachten
        while (digitalRead(switchPin) == HIGH) {
            delay(1);
        }
    }
    //Als counter 1 staat led aan
    if (onOffCounter == 1) {
        digitalWrite(ledA, LOW);
        digitalWrite(ledB, HIGH);
    }
    //Als counter 0 staat led uit
    if (onOffCounter == 0) {
        digitalWrite(ledB, LOW);
        digitalWrite(ledA, HIGH);
    }
}
