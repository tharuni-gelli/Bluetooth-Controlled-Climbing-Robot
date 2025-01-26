#include <Servo.h>
#include <AFMotor.h>

// Define motor and servo objects
AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(2);
Servo cleaningServo;

// Define pins for Bluetooth module
const int bluetoothTx = 10;
const int bluetoothRx = 11;

// Define pin for BLDC motor control
const int bldcPWM = 9;
const int bldcEnable = 8;

// Define control variables
char command;

void setup() {
    Serial.begin(9600);
    cleaningServo.attach(6);
    pinMode(bldcPWM, OUTPUT);
    pinMode(bldcEnable, OUTPUT);
    digitalWrite(bldcEnable, HIGH);
    
    // Initialize motors
    leftMotor.setSpeed(150);
    rightMotor.setSpeed(150);
    leftMotor.run(RELEASE);
    rightMotor.run(RELEASE);
}

void loop() {
    if (Serial.available()) {
        command = Serial.read();
        Serial.println(command);
        handleCommand(command);
    }
}

void handleCommand(char cmd) {
    switch(cmd) {
        case 'F':  // Move forward
            leftMotor.run(FORWARD);
            rightMotor.run(FORWARD);
            break;
        case 'B':  // Move backward
            leftMotor.run(BACKWARD);
            rightMotor.run(BACKWARD);
            break;
        case 'L':  // Turn left
            leftMotor.run(BACKWARD);
            rightMotor.run(FORWARD);
            break;
        case 'R':  // Turn right
            leftMotor.run(FORWARD);
            rightMotor.run(BACKWARD);
            break;
        case 'S':  // Stop movement
            leftMotor.run(RELEASE);
            rightMotor.run(RELEASE);
            break;
        case 'C':  // Activate cleaning mechanism
            cleaningServo.write(90); // Adjust as needed
            delay(1000);
            cleaningServo.write(0);
            break;
        case 'T':  // Start BLDC motor (Thrust)
            analogWrite(bldcPWM, 255);
            break;
        case 'O':  // Stop BLDC motor
            analogWrite(bldcPWM, 0);
            break;
        default:
            Serial.println("Invalid Command");
            break;
    }
}
