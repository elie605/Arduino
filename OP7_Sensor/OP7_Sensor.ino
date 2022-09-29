#include <Servo.h>

Servo servo;

int trigPin = 8;
int echoPin = 12;

float time, distance;

void setup() {
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    servo.attach(3);
    servo.write(0);
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    time = pulseIn(echoPin, HIGH);

    distance = time / 58;

    Serial.print("\n afstand: ");
    Serial.print(distance);

    if(distance <= 10){
        if(distance <= 4){
            servo.write(0);
        }
        int deg = map((distance-4)*10, 0, 60, 0, 180);
                 Serial.print(" deg :");
         Serial.print(deg);
        servo.write(deg);
    }else servo.write(180);

    delay(100);
}
