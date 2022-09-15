//id van analog input
const int tempr1 = A5;

void setup() {
    //Logboek aanzetten op een snelheid van 9600
    Serial.begin(9600);
}

void loop() {
    //Waarde die binnenkomt van tempratuur
    //De 1024 waardes van de tempratuur sensor omzetten een tempratuur van 0 tot 500
    int val = map(analogRead(tempr1), 0, 1023, 0, 500);
    //Waarde in logboek schrijven
    Serial.print(val);
    //Volgende regel in logboek
    Serial.print("\n");
    //Wachten
    delay(200);
}