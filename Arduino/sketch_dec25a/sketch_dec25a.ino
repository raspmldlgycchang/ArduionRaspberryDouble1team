#include<LiquidCrystal_I2C.h>
#include<Servo.h>
#include "LedControl.h"
LedControl lc = LedControl(12,11,10,1);
#define DO 261
#define RE 293
#define MI 329
#define FA 349
#define SOL 392
#define LA 440
#define SI 493
#define DOS 523
int music[] = {MI,0,MI,0,MI,MI,MI,0,MI,0,MI,0,MI,MI,MI,0,MI,0,SOL,SOL,DO,DO,RE,RE,MI,MI,MI,0,0,0,FA,0,FA,0,FA,0,FA,0,FA,0,MI,0,MI,0,MI,0,MI,0,RE,0,RE,0,DO,DO,RE,RE,RE,SOL};
int R=5;
int G=6;
int pos=0;
int buz=3;
Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  // put your setup code here, to run once:
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(buz, OUTPUT);
  myservo.attach(9);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lc.shutdown(0,false);
  lc.setIntensity(0,5);
  lc.clearDisplay(0);
}
void loop() {
  pos = 0;
  myservo.write(pos);
  delay(1000);
  // put your main code here, to run repeatedly:
  digitalWrite(R,HIGH);
  digitalWrite(G,LOW);
  delay(250);
  digitalWrite(R,LOW);
  digitalWrite(G,HIGH);
  delay(250);
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Happy Christmas!");
  delay(2000);
  for(;pos<180;pos+=30){
    myservo.write(pos);
    delay(1000);
  }
  delay(2000);
  for(int i=0;i<(sizeof(music)/sizeof(int));i++){
    tone(buz,music[i], 1050);
    delay(130);
  }
  for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
      lc.setLed(0,col,row,true);
      delay(25);
    }
  }
  for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
      lc.setLed(0,col,row,false);
      delay(25);
    }
  }
  lcd.clear();
}
