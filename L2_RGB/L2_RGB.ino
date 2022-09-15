int switchPin = 8;
int ledPin = 11;
int switchState = LOW;
int onOffCounter = 0;

int stands[7][3] = {{0, 0, 0},
                    {0, 0, 1},
                    {0, 1, 0},
                    {0, 1, 1},
                    {1, 0, 1},
                    {1, 1, 0},
                    {1, 1, 1}};

void setup() {
    //Zet pin van led op output
    pinMode(ledPin, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    //Zet pin van led op input
    pinMode(switchPin, INPUT);
}

void loop() {
    //Als button ingedrukt is
    if (digitalRead(switchPin) == HIGH) {
        //En lamp uit is
        if (onOffCounter == 0) {
            //Zet lamp aan
            onOffCounter = 1;
        }
        delay(50);
        //Als button nog ingedrukt is wachten
    }
    //Als counter 1 staat led aan
    if (onOffCounter == 1) {
        for (int i = 1; i < sizeof(stands); i++) {
            digitalWrite(ledPin, stands[i][1]);
            digitalWrite(10, stands[i][2]);
            digitalWrite(9, stands[i][3]);

            delay(500);

        }
        onOffCounter = 0;
    }
    //Als counter 0 staat led uit
    if (onOffCounter == 0) {
        digitalWrite(ledPin, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
    }
}
