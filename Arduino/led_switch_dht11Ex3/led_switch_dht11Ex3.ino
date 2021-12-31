#include<LiquidCrystal_I2C.h>
#include<Servo.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#define DO 523
#define DOS 554
#define RE 622
#define MI 659
#define FA 740
#define SO 830
#define SI 493
#define LA 440
#define LAS 465
#define SOL 415
//Heize_h<80 || else
int music[] = {RE,MI,MI,0,MI,MI,0,MI,DOS,RE,SO,SO,RE,RE,SI,DOS,DOS,RE,MI,MI,0,MI,FA,FA,SI,SI,SI,SI,0,0,0,DOS,DOS,RE,MI,MI,0,MI,FA,SI,SI,MI,MI,SI,SI,SOL,SOL,0,SOL,LAS,0,LA,LA,DO,DO,0,DOS,DOS,0,DOS,DO,DOS,DO,DOS,DOS,DOS,0,DOS,RE,RE};
//pedestrian
int R=5;
int Y=6;
int G=11;
int pos=0;
int buz=3;
//3color led
int redPin=13;
int greenPin=12;
int bluePin=10;
Servo myservo;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buz, OUTPUT);
  myservo.attach(9);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  dht.begin();
}
void loop() {
  pos = 0;
  myservo.write(pos);
  delay(1000);
  // put your main code here, to run repeatedly:
  digitalWrite(R,HIGH);
  digitalWrite(Y,LOW);
  digitalWrite(G,LOW);
  delay(250);
  digitalWrite(R,LOW);
  digitalWrite(Y,HIGH);
  digitalWrite(G,LOW);
  delay(250);
  digitalWrite(R,LOW);
  digitalWrite(Y,LOW);
  digitalWrite(G,HIGH);
  delay(250);
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("Humidity:");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.print(t);
  lcd.print("°C");
  delay(2000);
  //dht11 : condition
  if(h<30){
    lcd.setCursor(0,0);
    lcd.print("Discomfort Index:");
    lcd.setCursor(0,1);
    lcd.print("Happy SUNNY Day!");
    delay(1000);
    setColor(0,255,255);
    delay(2000);
    pos = 60;
    myservo.write(pos);
    delay(2000);
  }
  else if(h<60){
    lcd.setCursor(0,0);
    lcd.print("Discomfort Index:");
    lcd.setCursor(0,1);
    lcd.print("Not Bad, So SO..");
    delay(1000);
    setColor(255,255,0);
    delay(2000);
    pos = 120;
    myservo.write(pos);
    delay(2000);
    for(int i=0;i<(sizeof(music)/sizeof(int));i++){
      tone(buz,music[i], 1050);
      delay(130);
    }
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Discomfort Index:");
    lcd.setCursor(0,1);
    lcd.print("It Rainy! So Bad");
    delay(1000);
    setColor(255,0,255);
    delay(2000);
    pos = 160;
    myservo.write(pos);
    delay(2000);
    for(int i=0;i<(sizeof(music)/sizeof(int));i++){
      tone(buz,music[i], 1050);
      delay(130);
    }
  }
  lcd.clear();
}
void setColor(int red, int green, int blue)
{
  analogWrite(redPin,red);
  analogWrite(greenPin,green);
  analogWrite(bluePin,blue);
}
