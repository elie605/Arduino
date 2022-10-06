#include <IRremote.h>

const int lPins[] = {12, 11, 10, 9};
const int timings[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
const int irPin = 8;

IRrecv irrecv(irPin);
decode_results results;

unsigned long lastTimes[] = {0, 0, 0, 0};

int ledStatus[] = {LOW, LOW, LOW, LOW};
int ledTiming[] = {0, 0, 0, 0};
int ledOn[] = {0, 0, 0, 0};

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
        return (results.value);
    }
}


void loop() {
    ledon(irDo());
    for (int t = 0; t < 4; t++) {
        roll(t);
    }

}


void ledon(int string) {

    switch (string) {
        case 16582903:
            strengt(0, irDo());
            break;

        case 16615543:
            strengt(1, irDo());
            break;

        case 16599223:
            strengt(2, irDo());
            break;

        case 16591063:
            strengt(3, irDo());
            break;
    }

}

void strengt(int led, int string) {

    switch (string) {
        case 16582903:
            update(led, timings[1]);
            break;

        case 16615543:
            update(led, timings[2]);
            break;

        case 16599223:
            update(led, timings[3]);
            break;

        case 16591063:
            update(led, timings[4]);
            break;

        case 16623703:
            update(led, timings[5]);
            break;

        case 16607383:
            update(led, timings[6]);
            break;

        case 16586983:
            update(led, timings[7]);
            break;

        case 16619623:
            update(led, timings[8]);
            break;

        case 16603303:
            update(led, timings[9]);
            break;
    }
}

void update(int l, int t) {
    if (ledOn[l] == 0) {
        int ic = 0;
        for (int i: ledOn) {
            if (i == 2) {
                ledStatus[l] = LOW;
                digitalWrite(lPins[ic], LOW);
                i == 0;
            }
            if (i == 1) {
                i++;
            }
        }
        ledStatus[l] = HIGH;
        digitalWrite(lPins[l], HIGH);
    }

    ledTiming[l] = timings[t];
    Serial.println(ledTiming[l]);
    roll(l);

}

void roll(int l) {
    unsigned long curTime = millis();

    if (curTime - lastTimes[l] >= ledTiming[l]) {
        lastTimes[l] = curTime;

        ledStatus[l] = (ledOn[l] == 1) ? HIGH : LOW;
        digitalWrite(lPins[l], ledStatus[l]);
    }

}
