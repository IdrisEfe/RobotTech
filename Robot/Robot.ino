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

float duration, distance;
float theWantedDistance = 5.0;
const int speed = 150;
const int turningSpeed = 100;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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

}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroSeconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroSeconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.03432 / 2.0;

  if (distance <= theWantedDistance) {

  }
  else {

  }

  

}

void forward() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  digitalWrite(MotorRE, speed);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  digitalWrite(MotorLE, speed);
}

void backward() {
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  digitalWrite(MotorRE, 0);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  digitalWrite(MotorLE, 0);
}

void FturnLeft() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW)
  digitalWrite(MotorRE, 0);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  digitalWrite(MotorLE, turningSpeed);
}

void FturnRight() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  digitalWrite(MotorRE, turningSpeed);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  digitalWrite(MotorLE, 0);
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
  const int backwardDuration = 500;
  backward();
  delay(backwardDuration);
  FturnLeft();
  // if else
  


}
