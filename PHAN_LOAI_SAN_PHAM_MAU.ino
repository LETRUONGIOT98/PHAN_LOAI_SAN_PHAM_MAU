#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x21,16,2);
/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
#include <Servo.h>
Servo Mxanh;
Servo Mdo;
int Do, Xanh, Vang,i;
#define cb 2
void setup() {
  Serial.begin(9600);
  pinMode(cb, INPUT_PULLUP);
  Mdo.attach(3);
  Mxanh.attach(4);
  Mdo.write(0);
  Mxanh.write(0);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DEM  SAN PHAM");
  tcs.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DO     XL     V");
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void loop() {
  unsigned int r, g, b,c;
  tcs.getRawData(&r, &g, &b, &c);
  Serial.print("R: "); Serial.print(r); Serial.print(" ");
  Serial.print("G: "); Serial.print(g); Serial.print(" ");
  Serial.print("B: "); Serial.print(b); Serial.print(" ");
  Serial.println(" ");

  
  if ((r >= 90 && g <= 80) || (r >= 400 && g <= 200)) {
     Mdo.write(90);
     Mxanh.write(0);
     Do = Do+1;
     lcd.setCursor(0, 1);
     lcd.print(Do);
     delay(3000);
    
  }
  else if ((g >= 90 && r <= 80) || (g >= 200 && r <= 150)) {
     Mxanh.write(90);
     Mdo.write(0);
     Xanh = Xanh + 1;
     lcd.setCursor(6, 1);
     lcd.print(Xanh);
     delay(3000);
  }
  else if ((g >= 100 && r > 100 && b <= 90)|| (g >= 500 && r >350 && b <=  300)) {
     Vang = Vang + 1;
     Mdo.write(0);
     Mxanh.write(0);
     lcd.setCursor(13, 1);
     lcd.print(Vang);
     delay(3000);
  }  
}
