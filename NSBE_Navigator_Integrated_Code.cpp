// Trig - Pin 9
const int trigPin =9;
// Echo - Pin 8
const int echoPin= 8;
// Left2 - Pin 5
const int Left2= 5;
// Left1 - Pin 6
const int Left1= 6;
// Left2 - Pin 5
const int Right2= 10;
// Left1 - Pin 6
const int Right1= 11;

int incomingByte = 0;

void Sensor_Setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
}

void Motor_Setup()
{
  pinMode(Left1, OUTPUT);
  pinMode(Left2, OUTPUT);
  pinMode(Right1, OUTPUT);
  pinMode(Right2, OUTPUT);
}

float Sensor_Read()
{
  float duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.0343)/2;
  
  Serial.print("distance:");
  Serial.println(distance);
  delay(200);
}

void Motor_Forward(float input, int duration)
{
  int speed = input * 255;
  analogWrite(Left1, speed);
  analogWrite(Left2, 0);
  analogWrite(Right1, speed);
  analogWrite(Right2, 0);
  delay(duration*1000);
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
  delay(1000);
}

void Motor_Backward(float input, int duration)
{
  int speed = input * 255;
  analogWrite(Left1, 0);
  analogWrite(Left2, speed);
  analogWrite(Right1, 0);
  analogWrite(Right2, speed);
  delay(duration*1000);
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
  delay(1000);
}

void Motor_Right(float input, int duration)
{
  int speed = input * 255;
  analogWrite(Left1, 0);
  analogWrite(Left2, speed);
  analogWrite(Right1, speed);
  analogWrite(Right2, 0);
  delay(duration*1000);
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
  delay(1000);
}

void Motor_Left(float input, int duration)
{
  int speed = input * 255;
  analogWrite(Left1, speed);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, speed);
  delay(duration*1000);
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
  delay(1000);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Sensor_Setup();
  Motor_Setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  Sensor_Read();
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if(incomingByte == 119) // Forward if UART Byte is 'w'
    {
      Motor_Forward(1, 3);
    }

    if(incomingByte == 119) // Backwards if UART Byte is 's'
    {
      Motor_Backward(1, 3);
    }

    if(incomingByte == 119) // Left if UART Byte is 'a'
    {
      Motor_Left(1, 3);
    }

    if(incomingByte == 119) // Right if UART Byte is 'd'
    {
      Motor_Right(1, 3);
    }
  }

}


