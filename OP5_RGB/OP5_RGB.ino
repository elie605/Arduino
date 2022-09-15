const int ledR = 11;
const int ledG = 10;
const int ledB = 9;
//Om de for loops sneller te laten lopen, hoe hoger de boost waarde hoe sneller de loop gaat, aangeraden  max 40.
const int boost = 0;

void setup() {
    //Zet pins van led op output
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledB, OUTPUT);
    //Logboek aanzetten op een snelheid van 9600
    Serial.begin(9600);
}

void loop() {
    //Voor de teller waarde(rood in dit geval) doe {iets} als de waarde onder 255 is en tel er 1 bij de waarde bij op
    for (int rValue = 0; rValue < 255; rValue++) {
        //Geef het led lampje de waarde van de teller
        analogWrite(ledR, rValue);
        //Tel een extra waarde bij de teller op zodat de loop sneller gaat
        rValue += boost;
        //Schrijf iets op logboek
        Serial.print("Red");
        //Schrijf de waarde van de teller/lampje op het logboek
        Serial.print(rValue);
        //Ga naar de volgende regel in het logboek
        Serial.print("\n");
        //Voor de teller waarde(rood in dit geval) doe {iets} als de waarde onder 255 is en tel er 1 bij de waarde bij op
        for (int gValue = 0; gValue < 255; gValue++) {
            analogWrite(ledG, gValue);
            //Tel een extra waarde bij de teller op zodat de loop sneller gaat
            gValue += boost;
            //Zet een tab in het logboek
            Serial.print("\t");
            Serial.print("Green");
            Serial.print(gValue);
            Serial.print("\n \t \t");
            //Voor de teller waarde(rood in dit geval) doe {iets} als de waarde onder 255 is en tel er 1 bij de waarde bij op
            for (int bValue = 0; bValue < 255; bValue++) {
                analogWrite(ledB, bValue);
                //Tel een extra waarde bij de teller op zodat de loop sneller gaat
                bValue += boost;
                Serial.print("Blue");
                Serial.print(bValue);
                Serial.print("\t");
            }
            Serial.print("\n");
        }
    }
    //wachten voor 10 sec
  delay(10000);
}
