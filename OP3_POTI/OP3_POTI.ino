
const int led1 = 7;
const int led2 = 8;
const int led3 = 9;
const int led4 = 10;
const int led5 = 11;
const int led6 = 12;
const int led7 = 13;

const int pot1 = A5;

int potValue = 0;

void setup() {
    //Zet pins van led op output
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(led7, OUTPUT);
}

void loop() {
    //Waarde van de potmeter
    potValue = analogRead(pot1);

    //De 1024 waardes van de potmeter omzetten naar 9 waardes(in simulatie is 8 genoeg, potmeter in het echt was iets minder precies denk ik)
    int val = map(potValue, 0, 1023, 0, 8);
    //Als de omgezette waarde meer dan 0 is lamp 1 aan etc...
    //TODO for loop van maken?
    if (val > 0) {
        digitalWrite(led1, 1);
    } else {
        digitalWrite(led1, 0);
    }
    if (val > 1) {
        digitalWrite(led2, 1);
    } else {
        digitalWrite(led2, 0);
    }
    if (val > 2) {
        digitalWrite(led3, 1);
    } else {
        digitalWrite(led3, 0);
    }
    if (val > 3) {
        digitalWrite(led4, 1);
    } else {
        digitalWrite(led4, 0);
    }
    if (val > 4) {
        digitalWrite(led5, 1);
    } else {
        digitalWrite(led5, 0);
    }
    if (val > 5) {
        digitalWrite(led6, 1);
    } else {
        digitalWrite(led6, 0);
    }
    if (val > 6) {
        digitalWrite(led7, 1);
    } else {
        digitalWrite(led7, 0);
    }
}
