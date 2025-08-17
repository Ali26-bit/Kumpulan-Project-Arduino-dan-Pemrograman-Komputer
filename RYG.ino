//Initiation
const int pinledA = 2;
const int pinledB = 3;
const int pinledC = 4;

void setup() {
  pinMode(pinledA,OUTPUT);
  pinMode(pinledB,OUTPUT);
  pinMode(pinledC,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinledA,HIGH);
  delay(10000);
  digitalWrite(pinledA,LOW);
  digitalWrite(pinledB,HIGH);
  delay(500);
  digitalWrite(pinledB,LOW);
  digitalWrite(pinledC,HIGH);
  delay(10000);
  digitalWrite(pinledC,LOW);
}
