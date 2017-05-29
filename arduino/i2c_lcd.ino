//###############  IOT BASED SMART IRRIGATION SYSTEM     ######################

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
const int pump1 = 10;
const int pump2 = 1;
const int pump3 = 11;
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
int m1,m2;
bool p1=false,p2=false,p3=false;
Servo myservo;
int pos = 0;

void setup()  
{
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);  
  lcd.begin(16,4);   
  lcd.backlight();
  delay(500);
  myservo.attach(9);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,OUTPUT);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  
  lcd.setCursor(0,0);
  lcd.print("IOT BASED SMART");
  lcd.setCursor(0,1);
  lcd.print("IRRIGATION SYS.");
  delay(4000);  


}

void loop()  {
  lcd.clear();
  secure();
  
  m1 = analogRead(A3);
  m2 = analogRead(A2);
  lcd.setCursor(0,0);
  lcd.print("Moisture 1: ");
  lcd.setCursor(12,0);
  lcd.print(m1);
  lcd.setCursor(0,1);
  lcd.print("Moisture 2: ");
  lcd.setCursor(12,1);
  lcd.print(m2);
  delay(2000);
  lcd.clear();
  
  secure();
  printStatus(1,m1);
  printStatus(2,m2);
  delay(2000);

  lcd.clear();
  secure();
  pumpStatus();
  delay(2000);
  lcd.clear();
  secure();
  tankstatus();
  delay(2000);
  if(p1){
    int k ;
    digitalWrite(pump1,HIGH);
    delay(500);
    for( k = 0; k<4; k++){
      for (pos = 70; pos <= 120; pos += 1) { 
    // in steps of 1 degree
    myservo.write(pos);              
    delay(15);                     
  }
  for (pos = 120; pos >= 70; pos -= 1) { 
    myservo.write(pos);             
    delay(15);                      
  } 
  }
  digitalWrite(pump1,LOW);
  delay(500);
    }
}



void printStatus(int i,int m){
  if(i == 1 ){
    lcd.setCursor(0,0);
    lcd.print("Soil 1: ");
    lcd.setCursor(9,0);
    if(m < 400){
      lcd.print("WET");
      p1 = false;
    }   
    else if(m < 800){
      lcd.print("NORMAL");
      p1 =false;
    }
    else{
      lcd.print("DRY");
      p1 = true;
    }
  }
   if(i == 2 ){
    lcd.setCursor(0,1);
    lcd.print("Soil 2: ");
    lcd.setCursor(9,1);
    if(m < 400){
      lcd.print("WET");
      p2 = false;
    }
    else if(m < 800){
      lcd.print("NORMAL");
      p2  = false;
    }
    else{
      lcd.print("DRY");
      p2  = true;
    }
  }
}


void pumpStatus(){
  lcd.setCursor(0,0);
  lcd.print("PUMP 1 : ");
  lcd.setCursor(10,0);
  if(p1)
    lcd.print("ON");
   else
      lcd.print("OFF");

  lcd.setCursor(0,1);
  lcd.print("PUMP 2 : ");
  lcd.setCursor(10,1);
  if(p3){
    digitalWrite(pump2,HIGH);
    lcd.print("ON");}
   else{
      digitalWrite(pump2,LOW);
      lcd.print("OFF");}
}

void tankstatus(){
  bool a,b;
  a = digitalRead(2);
  b = digitalRead(3);
  if(a==1 && b==1){
    lcd.setCursor(0,0);
    lcd.print("TANK IS EMPTY");
    digitalWrite(pump3,HIGH);
    p3=true;
  }
  else if(a==0 && b==1){
    lcd.setCursor(0,0);
    lcd.print("TANK IS MODERATELY");
    lcd.setCursor(0,1);
    lcd.print("FILLED");
  }
  if(a==0 && b==0){
    digitalWrite(pump3,LOW);
    lcd.setCursor(0,0);
    lcd.print("TANK IS FULL");
    p3= false;
  }
}

void secure(){
  int tmp;
  tmp = analogRead(A1);
  if(tmp>890){
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    lcd.setCursor(0,0);
    lcd.print(" Security ");
    lcd.setCursor(0,1);
    lcd.print(" Violated ");
    delay(1000);
    lcd.clear();
  }
  else{
    digitalWrite(12,LOW);
     digitalWrite(13,LOW);
  }
}

