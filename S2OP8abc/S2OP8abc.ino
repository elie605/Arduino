
void setup() {
    //led pins
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    //input pins
    pinMode(6, INPUT);
    pinMode(5, INPUT);
}

void loop() {
    //als input A high is zet output A op HIGH  zo niet zet ouput op low
    if (digitalRead(6) == HIGH) {
        digitalWrite(10, 1);
    } else {
        digitalWrite(10, 0);
    }

    //als input B high is zet output B op HIGH zo niet zet ouput op low
    if (digitalRead(5) == HIGH) {
        digitalWrite(11, 1);
    } else {
        digitalWrite(11, 0);
    }
}