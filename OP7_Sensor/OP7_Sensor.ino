#include <Servo.h>

//Servo instancieren
Servo servo;

//pins van distance meter
int trigPin = 8;
int echoPin = 12;

float time, distance;

void setup() {
    //Logboek aanzetten op een snelheid van 9600
    Serial.begin(9600);

    //zet pin trigpin op uitvoer
    pinMode(trigPin, OUTPUT);
    //zet pin echoPin op invoer
    pinMode(echoPin, INPUT);

    //Zet pin 3 als de servo output
    servo.attach(3);
    //Servo moter op nul zetten
    servo.write(0);
}

void loop() {
    //de trigger pin uitzetten
    digitalWrite(trigPin, LOW);
    //2 micro seconden wachten zodat we zeker weten dat de trigger pin uit is
    delayMicroseconds(2);
    //zet de trigger pin aan om een ultrasoon geluid er uit te sturen
    digitalWrite(trigPin, HIGH);
    //10 micro seconden wachten
    delayMicroseconds(10);
    //Het uitzetten van de trigger zodat het ultrasoon geluid er uit sturen stopt
    digitalWrite(trigPin, LOW);

    //Het ophalen van hoelang de echo aan was
    time = pulseIn(echoPin, HIGH);

    //de afstand uitrekenen aan de hand van de snelheid van het geluid
    distance = time / 58;

    //In het logboek de afstand met een visiek object zetten
    Serial.print("\n afstand: ");
    Serial.print(distance);

    //als het object minder of 10 cm verweg is
    if (distance <= 10) {
        // als hij minder dan 4 cm verweg is
        if (distance <= 4) {
            //zet de servo op de maximalen waarde
            servo.write(0);
        }
        //het uitrekenen van de hoek van der servo
        //TODO dit uiteggen wat map doet
        int deg = map((distance - 4) * 10, 0, 60, 0, 180);
        //Zet in het logboek dat de graden naar deg gaat
        Serial.print(" deg :");
        Serial.print(deg);
        //zet de servo op de uitgerekende hoek
        servo.write(deg);

        //zet de servo op de minimalen waarde
    } else servo.write(180);

    //Wachten
    delay(100);
}
