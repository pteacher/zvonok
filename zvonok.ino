#include <SPI.h>
#include <DS1302.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10,  9,  8);

#define OLED_RESET 4
#define relay 2
Adafruit_SSD1306 display(OLED_RESET);

int beeep = 0;
int buttonState = 1;
bool R = 0;

const int kCePin   = 7;  // Chip Enable
const int kIoPin   = 6;  // Input/Output
const int kSclkPin = 5;  // Serial Clock

DS1302 rtc(kCePin, kIoPin, kSclkPin);

void setup() {
  rtc.halt(false);
  rtc.writeProtect(false);

  lcd.begin(16, 2);
  pinMode(4, INPUT);
  pinMode(relay, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.setTextColor(WHITE); 

void dateSetup(int D, int M, int Y, int s, int m, int h)
{
  //rtc.setDOW(THURSDAY);
  rtc.setDate(D,M,Y);
  rtc.setTime(h,m,s);
  //rtc.setTime(17,45,0,27,01,2015); 
}

}
const int nz=6;
int zv[nz][2]={{08,30},{9,15},{9,25},{10,10},{10,25},{11,10}};

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(4,8);
  display.println(rtc.getTimeStr());
  
  lcd.setCursor(0, 1);
  lcd.print(rtc.getTimeStr());
  lcd.setCursor(0, 0);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  lcd.setCursor(5, 0);
  lcd.print(rtc.getDateStr());
  if (R==1) {
    lcd.setCursor(9, 1);
    lcd.print("SKR");
  }
  Time t = rtc.getTime();
  for (int i=0; i<nz; i++)
  {
  if (t.min==zv[i][1] && t.hour==zv[i][0])
  {
    if (t.sec<20)
      digitalWrite(relay, HIGH);
    else 
      digitalWrite(relay, LOW);
  }
    
  }
  buttonState = digitalRead(4);

  if (buttonState == LOW) 
  {
     R=1;
  }
  display.display();
  delay(1000);
}