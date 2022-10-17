#include <IRremote.h>
//Pins van de led lampen
const int ledPins[] = {7, 6, 5, 4};
//Array van de mogelijke lengtes van aanstaan lampen/relay's
const int timings[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
//Pin van de infrorood sensor
const int irPin = 11;

IRrecv irrecv(irPin);
decode_results results;

//De laatste keer dat de lamp is aangegaan
unsigned long lastTimes[] = {0, 0, 0, 0};
//Status van elke lamp aan of out
int ledStatus[] = {LOW, LOW, LOW, LOW};
//Hoelang de lamp aan moet staan
int ledTiming[] = {0, 0, 0, 0};
//Welke lamp aan moet staan
//Hier wordt in de roll() naar gekeken, als het hoger of gelijk is aan een
//Dan mag het door de roll functie aan of uitgezet worden
int ledHistory[] = {0, 0, 0, 0};

int selectedLed = -1;

void setup() {
    Serial.begin(9600);
    //Voor elke led in ledpins
    for (int pin: ledPins) {
        //Zet de pin modus op output
        pinMode(pin, OUTPUT);
    }
    irrecv.enableIRIn();

    //Aanzetten van lamp 3 en 4 met de timing van 900 en 600
    update(2, 8);
    update(3, 5);
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
}

void loop() {
    //Als er geen led lamp is geselecteerd 
    if (selectedLed == -1) {
        //De inkomende waarde van de infrarood sensoor ophalen en de geselecteerde
        //de teruggegeven waarde geven
        selectedLed = setLedOn(getIrValue());
    } else {
        //Als er een lamp is geselecteerd
        if (selectedLed >= 0) {
            //Het bepalen van de snelheid van knipperen van de geselecteerde lamp
            speed(selectedLed);
        }
    }
    //Voor elke lampa
    for (int t = 0; t < 4; t++) {
        //Kijken of hij aan of uit mag
        roll(t);
    }
}

//Als de waarde een van de waardes na de "case" heeft dan geef een waard terug
//Is de waarde niet te vinden in de switchcase dan geef -1 terug (er is geen lamp geselecteerd)
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
    return -1;
}

void speed(int led) {
    //Het noteren van de geselecteerde led lamp in het logboek
    Serial.print("selected ");
    Serial.print(led);
    Serial.println(" | set length");

    //Het ophalen van de inkomende infrarood data
    int hexInt = getIrValue();

    //Als de waarde in de switchcase is dan voor update uit met de eerder
    //geselecteerde lamp en de nu meegeven snelheid
    switch (hexInt) {
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
    //geselecteerde led weer op -1 zetten aangezien er geen meer geselecteerd is na de update
    selectedLed = -1;

    Serial.print("\n led: ");
    Serial.print(l);
    Serial.print("\t string: ");
    Serial.print(t);
    Serial.print("\n");

    //Als de led in nog niet in de roll stond dan
    if (ledHistory[l] == 0) {
        //Bijhouden van led telling binnen de for loop
        int ic = 0;
        //Voor elke led in de roll history
        for (int i: ledHistory) {
            //Als het de waarde 2 heeft, zet de lamp uit en haal het uit de roll
            if (i == 2) {
                ledStatus[ic] = LOW;
                ledHistory[ic] = 0;
                digitalWrite(ledPins[ic], LOW);
            }
            //Als het de waarde 1 heeft veranderd de waarde naar 2
            if (i == 1) {
                ledHistory[ic] = 2;
            }
            ic++;
        }
        //Huidige geselecteerde led status op aan zetten
        ledStatus[l] = HIGH;
        //En history op 1 zetten
        ledHistory[l] = 1;
        //huidige led aanzetten
        digitalWrite(ledPins[l], HIGH);
    }
    //Led timing updaten
    ledTiming[l] = timings[t];
    roll(l);
}

//Het aan of uitzetten van een lamp als het hoger of gelijk is aan 1 in de ledhistory
//En het langer is geweest dan de aangegeven timing in ledTiming
void roll(int l) {
    unsigned long curTime = millis();

    //Als de huidige tijd min de laatste keer dat de lamp is aan of uitgegeaan is
    //hoger is dan de lengte dat hij maximaal aan mag staan dan doe iets
    //ook kijkt het of de lamp hoger of gelijk is aan 1 in ledhistory ,
    //staat het op null mag hij niet aan of uit gezet worden door roll()
    if (curTime - lastTimes[l] >= ledTiming[l] && ledHistory[l] >= 1) {
        //Zet de laatste keer van uit of aangaan op de huidige tijd
        lastTimes[l] = curTime;
        //Zet de lamp status op aan of uit zetten
        ledStatus[l] = (ledStatus[l] == LOW) ? HIGH : LOW;
        //Lamp daadwerkelijk aan of uitzetten
        digitalWrite(ledPins[l], ledStatus[l]);
    }
}
