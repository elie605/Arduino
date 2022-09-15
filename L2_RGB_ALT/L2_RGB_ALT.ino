int switchPin = 4;
int ledPin = 11;
int switchState = LOW;
int onOffCounter = 1;

int stands[7][3]= {{0, 0, 0},{0, 0, 1},{0, 1, 0},{0, 1, 1},{1, 0, 1},{1, 1, 0},{1, 1, 1}};

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

        if (onOffCounter == 7) {
            //Zet lamp aan
            onOffCounter = 1;
        } else {
            onOffCounter++;
        }
        //Als button nog ingedrukt is wachten
        while (digitalRead(switchPin) == HIGH) {
            delay(1);
        }
        digitalWrite(ledPin, stands[onOffCounter][1]);
        digitalWrite(10, stands[onOffCounter][2]);
        digitalWrite(9, stands[onOffCounter][3]);
    }
}