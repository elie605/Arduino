int state;
int flag = 0;

void setup() {
 Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        state = Serial.read();

        Serial.println("Something");
        Serial.println(state);

        flag = 0;
    }
}
