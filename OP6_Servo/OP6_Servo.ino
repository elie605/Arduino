#include <Servo.h>
//Servo moter instancieren
Servo servo;

int pos = 0;
int switchState = LOW;
int switch1 = 7;
int switch2 = 6;

void setup() {
    //Zet pin 3 als de servo output
    servo.attach(3);

    //Zet pins van knoppen op input
    pinMode(switch1, INPUT);
    pinMode(switch2, INPUT);

    //Logboek aanzetten op een snelheid van 9600
    Serial.begin(9600);

    //Servo moter op nul zetten
    servo.write(0);
}

void loop() {
    // als knop 1 is ingedrukt do dan
    if (digitalRead(switch1) == HIGH) {
        //checken of beide knoppen ingedrukt zijn
        //zo ja voer functie buttonBoth uit
        if (checkButtonBoth()) { buttonBoth(); }
        //zo niet betekent dit dat alleen knop 1 is ingedrukt is, voer dus functie 1 uit
        else {
            button1();
        }
    } else {
        // Als knop 1 niet is ingedrukt dan kijk of knop 2 ingedrukt is
        if (digitalRead(switch2) == HIGH) {
            // zo ja check of beide knoppen zijn ingedrukt
            if (checkButtonBoth()) { buttonBoth(); }
            else {
                //zo niet betekent dit dat alleen knop 2 is ingedrukt is, voer dus functie 2 uit
                button2();
            }
        }
    }
}

bool checkButtonBoth() {
    //Voordaty er gecheckt wordt of beide knoppen zijn ingedrukt wordt er eerst een tijdje gewacht,
    //omdat twee knoppen niet precies gelijk ingedrukt kunnen worden
    delay(50);
    //zijn beide knoppen ingedrukt
    if (digitalRead(switch2) == HIGH && digitalRead(switch1) == HIGH) {
        return true;
    }
    return false;
}

//draaien functie er moet een begin en eindpunt meegegeven worden,
// daarnaast moet er een tijd van wachten tussen de stappen meegegeven worden
void turn(int start, int end, int time) {
    //Als het startpunt minder dan het eind punt is dan moet het er naar toe draaien
    if (start < end) turntowards(start, end, time);
    //Als het startpunt meer dan het eindpunt is moet het terug draaien
    if (start > end) turnback(start, end, time);
}

void turntowards(int start, int end, int time) {
    //voor elk getal tussen het startpunt eindpunt ga een stapje heen
    for (pos = start; pos <= end; pos += 1) {
        //nieuwe stand van de servo
        servo.write(pos);
        //wachten voordat er naar de volgende postie mag gaan
        delay(time);
        //In het logboek zetten dat er naar een positie gegaan is.
        Serial.print("\n -towards");
        Serial.print(pos);
    }
}

void turnback(int start, int end, int time) {
    //voor elk getal tussen het startpunt eindpunt ga een stapje terug
    for (pos = start; pos >= end; pos -= 1) {
        //nieuwe stand van de servo
        servo.write(pos);
        //wachten voordat er naar de volgende postie mag gaan
        delay(time);
        //In het logboek zetten dat er terug gegaan is naar een positie.
        Serial.print("\n -back");
        Serial.print(pos);
    }
}

void button1() {
    //in het logboek zetten dat knop 1 is ingedrukt is en wordt uitgevoerd
    Serial.print("\n -button1");
    //het aan spreken van de draai functie met het begin en eind punt, er word ook een wachttijd voor tussen de stappen uitgerekent
    //De tijd waarin het moet gebeuren (1 sec) gedeelt door de te draaien graden (120)
    turn(0, 120, (1000 / 120));
    turn(120, 0, (1000 / 120));
}


void button2() {
    //in het logboek zetten dat knop 2 is ingedrukt is en wordt uitgevoerd
    Serial.print("\n -button2");
    //De tijd waarin het moet gebeuren (0,5 sec) gedeelt door de te draaien graden (120)
    turn(0, 120, (500 / 120));
    turn(120, 0, (500 / 120));
}

void buttonBoth() {
    //in het logboek zetten dat knoppen 1 en 2 zijn ingedrukt is en de beide functie wordt uitgevoerd
    Serial.print("\n -both");
    //De tijd waarin het moet gebeuren (1 sec) gedeelt door de te draaien graden (120)
    turn(0, 120, (1000 / 120));
    //2 seconden wachten
    delay(2000);
    //De tijd waarin het moet gebeuren (1 sec) gedeelt door de te draaien graden (120)
    turn(120, 0, (1000 / 120));
};
