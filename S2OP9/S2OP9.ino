#include <IRremote.h>

//Pins van de led lampen
const int ledPins[] = {7, 6, 5, 4};
//Array van de mogelijke lengtes van aanstaan lampen/relay's
//Pin van de infrorood sensor
const int irPin = 11;

IRrecv irrecv(irPin);
decode_results results;

int selectedLed = -1;

void setup() {
    Serial.begin(9600);
    //Voor elke led in ledpins
    for (int pin: ledPins) {
        //Zet de pin modus op output
        pinMode(pin, OUTPUT);
    }
    irrecv.enableIRIn();
}

//Het ophalen en teruggeven van de inkomende infrarood data
int getIrValue() {
    //Als er infrarood data binnen komt
    if (irrecv.decode(&results)) {
        Serial.println(results.value);
        irrecv.resume();
        //Als de data niet 0 is
        if (results.value != 0) {
            //Stuur de binnen komende data terug
            return (results.value);
        }
    }
    return -1;
}

void loop() {
    //Ophalen afstandbediening output
    selectedLed = setLedOn(getIrValue());

    //Als er iets binnengekomen is
    if (selectedLed != -1) {
        //Zet output van die pin aan en wacht 0.1 seconden en zet weer uit
        digitalWrite(ledPins[selectedLed], 1);
        delay(100);
        digitalWrite(ledPins[selectedLed], 0);
        //Zet binnengekomen weer op niks
        selectedLed = -1;
    }
    delay(1000);
}

//Stuurt een getal terug gebaseerd op de input
int setLedOn(int hexInt) {
    switch (hexInt) {
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
    //Zit de input er niet tussen dan sturen we -1 terug wat we als niks beschouwen
    return -1;
}
