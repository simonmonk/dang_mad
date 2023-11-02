// Survelance Bot

#define HALT 0
#define CLOCKWISE 1
#define COUNTER_CLOCKWISE 2

int leftAPin = 7;
int leftBPin = 6;
int rightAPin = 5;
int rightBPin = 4;

int posPin = 14;
int negPin = 15;
int proxPin = 2;
int pirPin = 3;
int buzzPlusPin = 9;
int buzzMinusPin = 8;

float proxThreshold = 500;
float alpha = 0.5;
int pirThreshold = 10;
int monitorDuration = 120; // seconds
int alarmDuration = 10; // seconds

void setup()
{
 pinMode(leftAPin, OUTPUT);
 pinMode(leftBPin, OUTPUT);
 pinMode(rightAPin, OUTPUT);
 pinMode(rightBPin, OUTPUT);
 pinMode(pirPin, INPUT);

 digitalWrite(leftAPin, LOW);
 digitalWrite(leftBPin, LOW);
 digitalWrite(rightAPin, LOW);
 digitalWrite(rightBPin, LOW);
 
 pinMode(posPin, OUTPUT);
 pinMode(negPin, OUTPUT);
 pinMode(buzzPlusPin, OUTPUT);
 pinMode(buzzMinusPin, OUTPUT);
 digitalWrite(posPin, HIGH);
 digitalWrite(negPin, LOW); 
 Serial.begin(9600);
}

void loop()
{
  monitor();
  moveToNewPlace();
  delay(1000);
}
 
void monitor()
{
  int alarmTimeout = 0;
  for (int i = 1; i < monitorDuration; i++)
  {
     int pirValue = analogRead(pirPin);
     if (pirValue > 10)
     {
        digitalWrite(buzzPlusPin, HIGH);
        alarmTimeout = alarmDuration;
     }
     if (alarmTimeout <= 0)
     {
       digitalWrite(buzzPlusPin, LOW);
     }
     alarmTimeout --;
     delay(1000);
  }
}

void moveToNewPlace()
{
  turnInRandomDirection();
  forwardOrProximity(1500);
}

void turnInRandomDirection()
{
   int duration = random(100, 3000);
   left();
   delay(duration);
   halt();
}

void forwardOrProximity(int duration)
{
  int x = 0;
  forward();
  static float lastProx = 0;
  float prox = 0;
  while (x < duration)
  {
    int rawProx = analogRead(proxPin);
    prox = alpha * rawProx + (1 - alpha) * lastProx;
    Serial.print(rawProx); Serial.print(" "); Serial.print(lastProx); Serial.print(" "); Serial.println(prox);
    lastProx = prox;
    if (prox > proxThreshold)
    {
      halt();
      buzz(50); buzz(50);
      delay(100);
      back();
      delay(700);
      halt();
      return;
    }
    x += 10;
    delay(10); 
  }
}

void forward()
{
 setLeft(CLOCKWISE);
 setRight(CLOCKWISE);
}

void back()
{
 setLeft(COUNTER_CLOCKWISE);
 setRight(COUNTER_CLOCKWISE);
}

void left()
{
 setLeft(CLOCKWISE);
 setRight(COUNTER_CLOCKWISE);
}

void right()
{
 setLeft(COUNTER_CLOCKWISE);
 setRight(CLOCKWISE);
}

void halt()
{
 setLeft(HALT);
 setRight(HALT);
}

void setLeft(int rotation)
{
 if (rotation == HALT)
 {
   digitalWrite(leftAPin, LOW);
   digitalWrite(leftBPin, LOW);
 }
 else if (rotation == CLOCKWISE)
 {
   digitalWrite(leftAPin, HIGH);
   digitalWrite(leftBPin, LOW);
 }
 else if (rotation == COUNTER_CLOCKWISE)
 {
   digitalWrite(leftAPin, LOW);
   digitalWrite(leftBPin, HIGH);
 }
}

void setRight(int rotation)
{
 if (rotation == HALT)
 {
   digitalWrite(rightAPin, LOW);
   digitalWrite(rightBPin, LOW);
 }
 else if (rotation == CLOCKWISE)
 {
   digitalWrite(rightAPin, HIGH);
   digitalWrite(rightBPin, LOW);
 }
 else if (rotation == COUNTER_CLOCKWISE)
 {
   digitalWrite(rightAPin, LOW);
   digitalWrite(rightBPin, HIGH);
 }
}

void buzz(int duration)
{
  digitalWrite(buzzPlusPin, HIGH);
  delay(duration);
  digitalWrite(buzzPlusPin, LOW);  
  delay(duration);
}
