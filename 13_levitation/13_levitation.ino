// Project 13 - Anti-gravity
// 15 Dangerous Projects for the Evil Genius

#define coilPin 11
#define irPin 13
#define sensorPin 0

int A = 2;
// Adjust B to improve stability 
int B = 60;
int C = 20;
int D = 1000;

int maxPower = 255; 
long powerCountThreshold = 300000;
int objectPresent = 0;
int monitoring = false;

void setup()
{
  pinMode(coilPin, OUTPUT);
  pinMode(irPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  Serial.println("Ready");
  Serial.println("m - toggle monitoring");
  Serial.println("B - increase B");
  Serial.println("b - decrease B");
}

void loop()
{
  static int count = 0;
  static int oldPosition = 0;
  static int ambient = 0;
  static long powerCount = 0;
  count ++;
  
  if (count == 1000)
  {
    ambient = readAmbient();
    count = 0;
    objectPresent = (powerCount < powerCountThreshold);
    powerCount = 0;
  }
  int raw = 1024 - analogRead(sensorPin);
  // position from top (0) of sensor region to the bottom (650)
  int position = raw - ambient; 
  // positive value means going downwards, negative going upwards
  int velocity = position - oldPosition; 
  int power = position / A + velocity * B + C;

  powerCount += power;
  oldPosition = position;
  
  // clip
  if (power > maxPower) power = maxPower;
  if (power < 0) power = 0;

  checkSerial();
  
  if (monitoring)
  {
    Serial.print(position);  Serial.print(","); 
    Serial.println(velocity); 
  }
  
  analogWrite(coilPin, power * objectPresent);
  delayMicroseconds(D);
}

int readAmbient()   //todo try speding up delay in micros
{
  digitalWrite(irPin, LOW);
   // allow time for LED and phototransistor to settle
  delayMicroseconds(100);
  int ambient = 1024 - analogRead(sensorPin);
  digitalWrite(irPin, HIGH);
  return ambient;
}

void checkSerial()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == 'm')
    {
      monitoring = ! monitoring;
    }
    if (ch == 'B') 
    {
      B += 5;
      Serial.println(B);
    }
    if (ch == 'b')
    {
      B -= 5;
      Serial.println(B);
    }
  }
}
