int ledPins[6][3] = {{4, 3, 2}, {7, 6, 5}, {10, 9, 8}, {13, 12, 11}, {16, 15, 14}, {19, 18, 17}};

// 1 - red
// 2 - green
// 3 - yellow
// 4 - blue
// 5 - mauve
// 6 - cyan
// 7 - white


void setup()
{
 for (int led = 0; led < 6; led ++)
 {
   for (int color = 0; color < 3; color++)
   {
     pinMode(ledPins[led][color], OUTPUT);
   }
 }
}

void loop()
{
    for (int row = 0; row < 6; row++)
    {
      for (int color = 0; color < 7; color++)
      {
        allOff();
        setLed(row, color); 
        delay(500);
      }
    }
}

void setLed(int led, int color)
{
 digitalWrite(ledPins[led][0], !(color & 1));
 digitalWrite(ledPins[led][1], !(color & 2));
 digitalWrite(ledPins[led][2], !(color & 4)); 
}

void allOff()
{
   for (int led = 0; led < 6; led ++)
 {
   for (int color = 0; color < 3; color++)
   {
     digitalWrite(ledPins[led][color], HIGH);
   }
 }
}
