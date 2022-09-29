#include <Servo.h>

Servo servo;
int pos = 0;
int switchState = LOW;
int switch1 = 7;
int switch2 = 6;

void setup() {
    servo.attach(3);
    pinMode(switch1, INPUT);
    pinMode(switch2, INPUT);
    Serial.begin(9600);
    servo.write(0);
}

void loop() {
    if (digitalRead(switch1) == HIGH) {
        if (checkButtonBoth()) { buttonBoth(); }
        else {
            button1();
        }
    } else {
        if (digitalRead(switch2) == HIGH) {
            if (checkButtonBoth()) { buttonBoth(); }
            else {
                button2();
            }
        }
    }
}

bool checkButtonBoth() {
    delay(50);
    if (digitalRead(switch2) == HIGH && digitalRead(switch1) == HIGH) {
        return true;
    }
    return false;
}


void turn(int start, int end, int time) {
    if (start < end) turntowards(start, end, time);
    if (start > end) turnback(start, end, time);
}

void turntowards(int start, int end, int time) {
    for (pos = start; pos <= end; pos += 1) {
        servo.write(pos);
        delay(time);
        Serial.print("\n -to");
        Serial.print(pos);
    }
}

void turnback(int start, int end, int time) {
    for (pos = start; pos >= end; pos -= 1) {
        servo.write(pos);
        delay(time);
        Serial.print("\n -ba");
        Serial.print(pos);
    }
}

void button1() {
    Serial.print("\n -button1");
    turn(0, 120, (1000 / 120));
    turn(120, 0, (1000 / 120));
}


void button2() {
    Serial.print("\n -button2");
    turn(0, 120, (500 / 120));
    turn(120, 0, (500 / 120));
}

void buttonBoth() {
    Serial.print("\n -both");
    turn(0, 120, (1000 / 120));
    delay(2000);
    turn(120, 0, (1000 / 120));
};
