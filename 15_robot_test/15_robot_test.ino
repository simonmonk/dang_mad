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
  if (Serial.available())
  {
    char command = Serial.read();
    if (command == 'l')
    {
      left();
    }
    else if (command == 'r')
    {
      right();
    }
    else if (command == 'f')
    {
      forward();
    }
    else if (command == 'b')
    {
      back();
    }
    else if (command == 'h')
    {
      halt();
    }
  }
  Serial.print("PIR="); Serial.println(analogRead(pirPin));
  Serial.print("Prox="); Serial.println(analogRead(proxPin));
  delay(500);
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
