/*Program ini dibuat oleh Andaru Nugroho (30 Agustus 2021)
 * sertakan watermark (sumber) ini apabila ingin melakukan pemrograman
 * menyertakan credit by telah menghargai hasil orang lain
 * terimakasih
 */


#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//our L298N control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("Start :");
  lcd.setCursor(3,1);
  lcd.print("5  (Five)");
  delay(1000);
  lcd.setCursor(3,1);
  lcd.print("4  (Four)");
  delay(1000);
  lcd.setCursor(3,1);
  lcd.print("3 (Three)");
  delay(1000);
  lcd.setCursor(3,1);
  lcd.print("2   (Two)");
  delay(1000);
  lcd.setCursor(3,1);
  lcd.print("1   (One)");
  delay(1000);
  lcd.setCursor(3,1);
  lcd.print("GO !!!!!");
  delay(1000);
  
  
  pinMode(8, OUTPUT); //lampu kanan
  pinMode(12, OUTPUT); //lampu kiri
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  lcd.setCursor(2,0);
  lcd.print("Created By :");
  lcd.setCursor(1,1);
  lcd.print("Andaru Nugroho");
  
  digitalWrite(8, HIGH); //lampu kanan
  digitalWrite(12, HIGH); //lampu kiri
  digitalWrite(1, HIGH); //lampu mundur
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 35){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  digitalWrite(8, HIGH); //lampu kanan
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  digitalWrite(8, LOW); //lampu kanan
  return distance;
}

int lookLeft(){
  digitalWrite(12, HIGH); //lampu kiri
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  digitalWrite(12, LOW); //lampu kiri
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
  digitalWrite(8, HIGH); //lampu kanan
  digitalWrite(12, HIGH); //lampu kiri
  delay(400);
  digitalWrite(8, LOW); //lampu kanan
  digitalWrite(12, LOW); //lampu kiri
  delay(400);
}

void moveStop(){
  digitalWrite(8, LOW); //lampu kanan
  digitalWrite(12, LOW); //lampu kiri
  digitalWrite(1, HIGH); //lampu mundur
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(1, LOW); //lampu mundur
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveBackward(){

  goesForward=false;
  digitalWrite(1, HIGH); //lampu mundur
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRight(){
  digitalWrite(8, LOW); //lampu kanan
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
 
  
  
}

void turnLeft(){
  digitalWrite(12, LOW); //lampu kiri
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
