void setup() {
    //Pin 11 tot en met 4 op modus output zetten
    for (int ledVal = 11; ledVal >= 4; ledVal -= 1) {
        pinMode(ledVal, OUTPUT);
    }
}

void loop() {
    //Voor pin 11 tot en met 4
    for (int ledVal = 11; ledVal >= 4; ledVal -= 1) {
        //Pin aanzetten
        digitalWrite(ledVal, HIGH);
        //Vorige pin uitzetten
        digitalWrite(ledVal + 1, LOW);
        //Even wachten
        delay(200);
    }

    //Hetzelfde maar in de tegenovergestelde richting
    //Voor pin 4 tot en met 11
    for (int ledVal = 4; ledVal <= 11; ledVal += 1) {
        //Pin aanzetten
        digitalWrite(ledVal - 1, LOW);
        //Vorige pin uitzetten
        digitalWrite(ledVal, HIGH);
        //Even wachten
        delay(200);
    }
}
