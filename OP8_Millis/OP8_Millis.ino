#include <IRremote.h>

const int ledPins[] = {7, 6, 5, 4};
const int timings[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
const int irPin = 11;

IRrecv irrecv(irPin);
decode_results results;

unsigned long lastTimes[] = {0, 0, 0, 0};

int ledStatus[] = {LOW, LOW, LOW, LOW};
int ledTiming[] = {0, 0, 0, 0};
int ledHistory[] = {0, 0, 0, 0};
int selectedLed = -1;

void setup() {
    Serial.begin(9600);

    for (int pin: ledPins) {
        pinMode(pin, OUTPUT);
    }
    irrecv.enableIRIn();

    update(2, 8);
    update(3, 5);
}

int getIrValue() {
    if (irrecv.decode(&results)) {
        Serial.println(results.value);
        irrecv.resume();
        if (results.value != 0) {
            return (results.value);
        }
    }
}

void loop() {
    if (selectedLed == -1) {
        selectedLed = setLedOn(getIrValue());
    } else {
        if (selectedLed >= 0) {
            strengt(selectedLed);
        }
    }
    for (int t = 0; t < 4; t++) {
        roll(t);
    }
}

int setLedOn(int string) {
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
    Serial.print("selected ");
    Serial.print(led);
    Serial.println(" | set length");

    int string = getIrValue();

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
    selectedLed = -1;

    Serial.print("\n led: ");
    Serial.print(l);
    Serial.print("\t string: ");
    Serial.print(t);
    Serial.print("\n");

    if (ledHistory[l] == 0) {
        int ic = 0;
        for (int i: ledHistory) {
            if (i == 2) {
                ledStatus[ic] = LOW;
                ledHistory[ic] = 0;
                digitalWrite(ledPins[ic], LOW);
            }
            if (i == 1) {
                ledHistory[ic] = 2;
            }
            ic++;
        }
        ledStatus[l] = HIGH;
        ledHistory[l] = 1;
        digitalWrite(ledPins[l], HIGH);
    }

    ledTiming[l] = timings[t];
    roll(l);
}

void roll(int l) {
    unsigned long curTime = millis();

    if (curTime - lastTimes[l] >= ledTiming[l] && ledHistory[l] >= 1) {
        lastTimes[l] = curTime;
        ledStatus[l] = (ledStatus[l] == LOW) ? HIGH : LOW;
        digitalWrite(ledPins[l], ledStatus[l]);
    }
}
