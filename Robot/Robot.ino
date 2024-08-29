#include <CustomQTRSensors.h>

const int buzzerPin = 11;

const int echoPin = 2;
const int trigPin = 4;

const int ledPin = 8;

#define MotorR1 7
#define MotorR2 6
#define MotorRE 9
#define MotorL1 5
#define MotorL2 10
#define MotorLE 3

#define KP 0.5
#define KF 2

float duration, distance;
float theWantedDistance = 5.0;

const int maxSpeed = 255;
const int speed = 180;
int rightSpeed;
int leftSpeed;
int addSpeed;
const int turningSpeed = 100;
const int backwardSpeed = 100;

int error;
int lastError = 0;

int check = 0;

const int backwardDuration = 500;
const int turningDuration = 500;

int endOfEverything = 0;

#define NUM_SENSORS   6     
#define TIMEOUT       2000  
#define EMITTER_PIN  12     

QTRSensorsRC qtrrc((unsigned char[]) {A5,A4,A3,A2,A1,A0,254,8},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];
unsigned int position;

void setup() {
  delay(500);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  Serial.println("Robot başlatılıyor...")

  for (int i = 3; i>=0; i--) {  
    Serial.println(i);
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }

  digitalWrite(ledPin, HIGH);

  qtrrc.restoreCalibration();

}

void loop() {

  if(endOfEverything != 0){
    while(true);
  }

  digitalWrite(trigPin, LOW);
  delayMicroSeconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroSeconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.03432 / 2.0;

  if (distance <= theWantedDistance) QTRing();

  else {
    encCheck();
  }

}

void QTRing() {

  check = 0;
  position = qtrrc.readLine(sensorValues);
  if (position > 4700 || position < 300) { // dikkat et

    error = position - 2500;
    addSpeed = KP * error + KD * (error * lastError);
    lastError = error;
    rightSpeed = speed + addSpeed;
    leftSpeed = speed - addSpeed;

    if(rightSpeed > maxSpeed) rightSpeed = maxSpeed;
    if(leftSpeed > maxSpeed) leftSpeed = maxSpeed;

    if(rightSpeed < 0) rightSpeed = 0;
    if(leftSpeed < 0) leftSpeed = 0;

    forward(rightSpeed, leftSpeed);

    check = 1;
  }
  

}

void forward(int rightSpeed, int leftSpeed) {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  digitalWrite(MotorRE, rightSpeed);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  digitalWrite(MotorLE, leftSpeed);
}

void backward() {
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  digitalWrite(MotorRE, backwardSpeed);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  digitalWrite(MotorLE, backwardSpeed);
}

void Stop() {
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);
  digitalWrite(MotorRE, 0);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);
  digitalWrite(MotorLE, 0);
}
void FturnLeft() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW)
  digitalWrite(MotorRE, turningSpeed);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  digitalWrite(MotorLE, 0);
}

void FturnRight() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  digitalWrite(MotorRE, 0);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  digitalWrite(MotorLE, turningSpeed);
}

void BturnLeft() {
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH)
  digitalWrite(MotorRE, turningSpeed);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  digitalWrite(MotorLE, 0);
}

void BturnRight() {
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  digitalWrite(MotorRE, 0);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  digitalWrite(MotorLE, turningSpeed);
}


void envCheck() {

  backward();
  delay(backwardDuration);

  Stop();
  delay(500);

  FturnLeft();
  delay(turningDuration);

  Stop();
  delay(500);

  lastError = 0; // Emin değilim
  QTRing();

  if (check == 0) {

    BturnLeft();
    delay(turningDuration);

    Stop();
    delay(500);

    FturnRight();
    delay(turningDuration);

    Stop();
    delay(500);

    lastError = 0; // Emin değilim
    QTRing();    

    if (check == 0) {
      Stop();
      delay(500);

      digitalWrite(buzzerPin, HIGH);
      endOfEverything++;
    }

  }

}
