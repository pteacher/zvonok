#include <SPI.h>
#include <DS1302.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10,  9,  8);

#define OLED_RESET 4
#define rele 2
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
  pinMode(rele, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.setTextColor(WHITE); 

void dateSetup()
{
  // ===================================
  // Do not clear that
  // rtc.setDOW(THURSDAY);
  //-------------------------------------------------------------------------- rtc.setTime(18,41,0);
  // rtc.setDate(30,01,2015);
  // rtc.setTime(16,45,0);
  //rtc.setTime(17,45,0,27,01,2015); 
}

}
const int nz=6;
int zv[nz][2]={{17,48},{16,48},{16,50},{17,07},{18,59},{19,10}};

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
      digitalWrite(rele, HIGH);
    else 
      digitalWrite(rele, LOW);
  
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