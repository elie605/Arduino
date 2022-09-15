const int tempr1 = A5;

void setup() {
    Serial.begin(9600);
}

void loop() {
    int val = map(analogRead(tempr1), 0, 1023, 0, 500);
    Serial.print(val);
    Serial.print("\n");
    delay(200);
}