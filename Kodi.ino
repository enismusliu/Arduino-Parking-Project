int sound = 250;
int n=0;
int i;
int counter=0;
long duration, distance;
//pershifrja e librarive
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>
//definimi i pinave 
#define trigPin A4
#define echoPin A5
#define SS_PIN 10
#define RST_PIN 9
#define LED_G A0 
#define LED_R A1 
#define LED_ska A3
#define LED_ka A2
//definimi i pinave per LCD
LiquidCrystal lcd(2, 3, 7, 6, 5, 4);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
//definimi i emrit te servo-motorit
Servo myServo; 
//loopi i cili lexohet vetem nje here
void setup() 
{
lcd.begin(16, 2);
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
myServo.attach(8);
Serial.begin(9600);   // Initiate a serial communication
SPI.begin();      // Initiate  SPI bus
mfrc522.PCD_Init();   // Initiate MFRC522
//definimi i pinit per servo-motorit
myServo.attach(8); 
//pozita fillesatare e servo-motorit
myServo.write(90); //servo start position
//definimi i ledave si gjendje e daljes
pinMode(LED_G, OUTPUT);
pinMode(LED_R, OUTPUT);
pinMode(LED_ska, OUTPUT);
pinMode(LED_ka, OUTPUT);
}
//loopi i cili perseritet gjithmone
void loop()
{
  
   int a=3-n;
   //teksti qe del ne LCD
   lcd.print(a);
   lcd.print("-vende te lira");
   delay(1000);
   lcd.clear();
   //ndryshimet e LEDave ne baze vendeve te lira
   if(n<3)
  {
      digitalWrite(LED_ska, LOW); 
      digitalWrite(LED_ka, HIGH);
  }
  else if (n>=3)
  {
      digitalWrite(LED_ka, LOW); 
      digitalWrite(LED_ska, HIGH);    
  }
 // shikon a ka kartela te reja
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // selekton njeren nga kartelat
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  //pyet se a ka kartela qasje ne parking si dhe a ka vend 
  if (content.substring(1) == "29 36 DE A2"&(n<3)) 
  {
    lcd.print("Ju mund te hyni! ");
    myServo.write(0);
    digitalWrite(LED_G, HIGH);
    delay(1000);
    digitalWrite(LED_G, LOW);
    lcd.clear();
    delay(1000);
    //mbyllja e laures pas 5 sekondave
    lcd.print("Mbyllja e laures pas: ");
    delay(1000);
    lcd.clear();
     lcd.print(" 5 sekondi");
    delay(1000);
    lcd.clear(); 
     lcd.print(" 4 sekondi");
    delay(1000);
    lcd.clear(); 
    lcd.print(" 3 sekondash");
    delay(1000);
    lcd.clear(); 
    lcd.print(" 2 sekondash");
    delay(1000);
    lcd.clear(); 
    lcd.print(" 1 sekondi");
    delay(1000);
    lcd.clear(); 
    checkDistance();
    if (distance < 5)
   { 
    n=n+1;
    //kjo pjese e kodit perdoret qe nese vetura gjendet ne pozite te njejte me lauren, laura mos te bie
  while(true){
  checkDistance();
     if (distance < 5)
  {
   myServo.write(0);
   counter = 0;
  }
  else {
      if(counter==5)
     {
      myServo.write(90);
      counter = 0;
      break;
      }
      delay(1000);
      counter = counter+1;
      }
      }}
 else{
     myServo.write(90);
      lcd.print("Laura u mbylle");
      delay(1000);
      lcd.clear(); 
  }}
  else   {
    lcd.print("Nuk mund te hyni! ");
    digitalWrite(LED_R, HIGH);
    delay(1000);
    digitalWrite(LED_R, LOW);
    delay(1000);
    lcd.clear();
   }
} 
//funksioni per matjen e distances me sensorin ultrasonik
 void checkDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
}
