
int state;
int flag = 0;

//Pins van de relay's van de stoplichten
const int ledPins[] = {4, 3, 2};
//Array van de mogelijke lengtes van aanstaan lampen/relay's
int t[] = {8000, 15000};
//De laatste keer dat de lamp is aangegaan
unsigned long lastTimes[] = {0, 0, 0};
//Hoelang de lamp aan moet staan
int ledTiming[] = {0, 0, 0};
//Welke lamp aan moet staan
//Hier wordt in de roll() naar gekeken, als het hoger of gelijk is aan een
//Dan mag het door de roll functie aan of uitgezet worden
int ledHistory[] = {0, 0, 0};
//Status van elke lamp aan of out
int ledStatus[] = {LOW, LOW, LOW};
//cycle status van het stoplicht, cycle is of het stoplicht een rotatie groen orangje blauw moet doen
//-1 geen cycle dus niks doen
//0 stoplicht cycle begint dus groen
//1 stoplicht op oranje
//2 stoplicht op rood
int docycle = -1;

void setup() {
    Serial.begin(9600);
    //Voor elke led in ledpins
    for (int pin: ledPins) {
        //Zet de pin modus op output
        pinMode(pin, OUTPUT);
    }
}

void loop() {
    //Voor elke lamp
    for (int op = 0; op < 3; op++) {
        //Kijken of hij aan of uit mag
        roll(op);
    }

    //Als er data binnen komt via de HC-05 bluetooth module zo ja dan
    if (Serial.available() > 0) {
        //Als er geen rotatie bezig is
        if(docycle < 0){
          //begin een rotatie
          cycle();
        }
        flag = 0;
    }
}
//Een random waar of onwaar terug geven
bool randomBool() {
    if ((rand() % 2) + 1 == 2)return 1;
    return 0;
}

void cycle() {
    //Een aan lengte aan de groene lamp geven
    ledTiming[0] = t[randomBool()];
    //Een aan lengte aan de groene lamp geven
    ledTiming[2] = t[randomBool()];
    //Als randombool een onwaar okwel een 0 terug geeft dan pakt het de
    //eerste timing uit de timing array dus 8000,als hij waar is dus 1 pakt
    //het de tweede timing dus 15000

    //Timing van de oranje is altijd 3 sec tijdens een cycle
    //Timing van de oranje lamp zetten
    ledTiming[1] = 3000;

    //Alle waardes van de geschiedenis resetten omdat we een nieuwe cycle beginnen
    ledHistory[0] = 0;
    ledHistory[1] = 0;
    ledHistory[2] = 0;
    lastTimes[0] = 0;
    lastTimes[1] = 0;
    lastTimes[2] = 0;
    ledStatus[0] = 0;
    ledStatus[1] = 0;
    ledStatus[2] = 0;

    //Alle lampen uitzetten aan het begin van een cycle
    digitalWrite(ledPins[0], 0);
    digitalWrite(ledPins[1], 0);
    digitalWrite(ledPins[2], 0);

    //Cycle op 0 zettten zodat de rotatie kan gaan beginnen
    docycle = 0;
}

void update() {
    //Als de lamp rood is geweest dan is de rotatie afgelopen en kan cycle
    //weer terug op -1 en moet de rode lamp uitgaan
    if(docycle > 2){
        docycle = -1;
        ledHistory[2] = 0;
    }
    //Als de cycle niet begonnen is dan moet de alleen de oranje lamp aan gaan
    //met de timing van 1 seconden
    if (docycle == -1) {
        //de timing van de oranje lamp op 1 seconden zetten
        ledTiming[1] = 1000;
        //Er voor zorgen dat lamp 1 in de roll aan of uit gezet wordt
        ledHistory[1] = 1;
    }
    //als de cycle is begonnen
    if (docycle == 0) {
        //Haal de oranje lamp weg uit de roll
        ledHistory[1] = 0;
        //Zet de groene lamp in de roll
        ledHistory[0] = 1;
    }
    //Als de groene lamp is uitgegaan in de cycle
    if (docycle == 1) {
        //Haal de groene lamp weg uit de roll
        ledHistory[0] = 0;
        //Zet de oranje lamp in de roll
        ledHistory[1] = 1;
    }
    if (docycle == 2) {
        //Haal de oranje lamp weg uit de roll
        ledHistory[1] = 0;
        //Zet de rode lamp in de roll
        ledHistory[2] = 1;
    }
}

//Het aan of uitzetten van een lamp als het hoger of gelijk is aan 1 in de ledhistory
//En het langer is geweest dan de aangegeven timing in ledTiming
void roll(int l) {
    //kijken of er een andere lamp in roll moet, als de rotatie/cycle stap/nummer
    //is verhoogd
    update();

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
        //als de lampstatus op uit staat en de cycle/rotatie is begonnen
        if (ledStatus[l] == 0 && docycle >= 0) {
            //Dan is het de volgende stap in de cycle
            //dus ophogen van cycle nummer
            docycle++;
            //Het noteren van de volgende stap van de cycle
            //met daarbij de relevante waardes
            Serial.println("next light");
            Serial.println(docycle);
            Serial.println(ledHistory[0]);
            Serial.println(ledHistory[1]);
            Serial.println(ledHistory[2]);
        }
        //Lamp daadwerkelijk aan of uitzetten
        digitalWrite(ledPins[l], ledStatus[l]);
    }
}
