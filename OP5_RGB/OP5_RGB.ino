const int ledR = 11;
const int ledG = 10;
const int ledB = 9;
const int boost = 0;

void setup() {
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledB, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    for (int rValue = 0; rValue < 255; rValue++) {
        analogWrite(ledR, rValue);
        rValue += boost;
        Serial.print("Red");
        Serial.print(rValue);
        Serial.print("\n");
        for (int gValue = 0; gValue < 255; gValue++) {
            analogWrite(ledG, gValue);
            gValue += boost;
            Serial.print("\t");
            Serial.print("Green");
            Serial.print(gValue);
            Serial.print("\n \t \t");
            for (int bValue = 0; bValue < 255; bValue++) {
                analogWrite(ledB, bValue);
                bValue += boost;
                Serial.print("Blue");
                Serial.print(bValue);
                Serial.print("\t");
            }
            Serial.print("\n");
        }
    }
  delay(10000);
}
