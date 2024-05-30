// Trig - Pin 9
const int trigPin =9;
// Echo - Pin 8
const int echoPin= 8;
// Trig2 - Pin 9
const int trigPin2 =12;
// Echo2 - Pin 8
const int echoPin2= 13;
// Trig3 - Pin 9
const int trigPin3 =15;
// Echo3 - Pin 8
const int echoPin3= 14;
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
  pinMode(trigPin2, OUTPUT);
  pinMode (echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode (echoPin3, INPUT);
}

void Motor_Setup()
{
  pinMode(Left1, OUTPUT);
  pinMode(Left2, OUTPUT);
  pinMode(Right1, OUTPUT);
  pinMode(Right2, OUTPUT);
}

int Sensor_Decision()
{
  float duration1, duration2, duration3, distance1, distance2, distance3;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration1 = pulseIn(echoPin, HIGH);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  duration2 = pulseIn(echoPin2, HIGH);

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  
  duration3 = pulseIn(echoPin3, HIGH);


  distance1 = (duration1*0.0343)/2;
  distance2 = (duration2*0.0343)/2;
  distance3 = (duration3*0.0343)/2;
  
  int max = distance1;

  if(distance2 > max)
  {
    max = distance2;
  }

  if(distance3 > max)
  {
    max = distance3;
  }
  
  if(max == distance1)
  {
    Serial.print("max distance:");
    Serial.println(distance1);
    return 1;
  }
  else if (max == distance2)
  {
    Serial.print("max distance:");
    Serial.println(distance2);
    return 2;
  }
  else if (max == distance3)
  {
    Serial.print("max distance:");
    Serial.println(distance3);
    return 3;
  }
  
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
  delay(duration);
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
}

void Motor_Backward(float input, int duration)
{
  int speed = input * 255;
  analogWrite(Left1, 0);
  analogWrite(Left2, speed);
  analogWrite(Right1, 0);
  analogWrite(Right2, speed);
  delay(duration);
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
}

void Motor_Right(float input, int duration)
{
  int speed = input * 255;
  analogWrite(Left1, 0);
  analogWrite(Left2, speed);
  analogWrite(Right1, speed);
  analogWrite(Right2, 0);
  delay(duration);
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
}

void Motor_Left(float input, int duration)
{
  int speed = input * 255;
  analogWrite(Left1, speed);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, speed);
  delay(duration);
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Sensor_Setup();
  Motor_Setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  //Sensor_Read();
  int direction = Sensor_Decision();
  if(direction == 1)
  {
    Motor_Forward(0.2, 500);
  }
  else if(direction == 2)
  {
    Motor_Right(0.2, 500);
  }
  else if(direction == 3)
  {
    Motor_Left(0.2, 500);
  }

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if(incomingByte == 119) // Forward if UART Byte is 'w'
    {
      Motor_Forward(1, 50);
    }

    if(incomingByte == 115) // Backwards if UART Byte is 's'
    {
      Motor_Backward(1, 50);
    }

    if(incomingByte == 97) // Left if UART Byte is 'a'
    {
      Motor_Left(1, 50);
    }

    if(incomingByte == 100) // Right if UART Byte is 'd'
    {
      Motor_Right(1, 50);
    }
  }

  else 
  {
    Motor_Forward(0, 0.1);
  }

}


