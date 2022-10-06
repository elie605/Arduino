#include <IRremote.h>

const int lPins[] = {7, 6, 5, 4};
const int timings[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
const int irPin = 11;

IRrecv irrecv(irPin);
decode_results results;

unsigned long lastTimes[] = {0, 0, 0, 0};

int ledStatus[] = {LOW, LOW, LOW, LOW};
int ledTiming[] = {0, 0, 0, 0};
int ledOn[] = {0, 0, 0, 0};
int ledselected = -1;

void setup() {
    Serial.begin(9600);

    for (int pin: lPins) {
        pinMode(pin, OUTPUT);
    }
    irrecv.enableIRIn();

    update(2, 8);
    delay(50);
    update(3, 5);
}

int irDo() {

    if (irrecv.decode(&results)) {
        Serial.println(results.value);
        irrecv.resume();
        if (results.value != 0) {
            return (results.value);
        }

    }
}


void loop() {
    if (ledselected == -1) {
        ledselected = ledon(irDo());
    }
    if (ledselected >= 0) {
        strengt(ledselected);
    }
    for (int t = 0; t < 4; t++) {
        roll(t);
    }
}


int ledon(int string) {
    switch (string) {
        case 0xFF30CF:
            return (0);
            break;

        case 0xFF18E7:
            return (1);
            break;

        case 0xFF7A85:
            return (2);
            break;

        case 0xFF10EF:
            return (3);
            break;

    }
    return -1;
}

void strengt(int led) {
    Serial.print("selected");
    Serial.print(led);
    Serial.println(" | set length");
    int string = irDo();

    switch (string) {
        case 0xFF30CF:
            update(led, 1);
            break;

        case 0xFF18E7:
            update(led, 2);
            break;

        case 0xFF7A85:
            update(led, 3);
            break;

        case 0xFF10EF:
            update(led, 4);
            break;

        case 0xFF38C7:
            update(led, 5);
            break;

        case 0xFF5AA5:
            update(led, 6);
            break;

        case 0xFF42BD:
            update(led, 7);
            break;

        case 0xFF4AB5:
            update(led, 8);
            break;

        case 0xFF52AD:
            update(led, 9);
            break;
    }
}

void update(int l, int t) {
    ledselected = -1;
    Serial.print("\n led: ");
    Serial.print(l);
    Serial.print("\t string: ");
    Serial.print(t);
    Serial.print("\n");
    if (ledOn[l] == 0) {
        int ic = 0;
        for (int i: ledOn) {
            if (i == 2) {
                ledStatus[ic] = LOW;
                ledOn[ic] = 0;
                digitalWrite(lPins[ic], LOW);
            }
            if (i == 1) {
                ledOn[ic] = 2;
            }
            ic++;
        }
        ledStatus[l] = HIGH;
        ledOn[l] = 1;
        digitalWrite(lPins[l], HIGH);
    }
    ledTiming[l] = timings[t];
    roll(l);

}

void roll(int l) {
    unsigned long curTime = millis();

    if (curTime - lastTimes[l] >= ledTiming[l] && ledOn[l] >= 1) {
        lastTimes[l] = curTime;

        ledStatus[l] = (ledStatus[l] == LOW) ? HIGH : LOW;

        digitalWrite(lPins[l], ledStatus[l]);
    }

}
