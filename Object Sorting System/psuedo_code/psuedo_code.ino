#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TCS34725.h>
Servo pickServo;
Servo dropServo;
const int s0 = 19;  
const int s1 = 18;  
const int s2 = 2;  
const int s3 = 4;  
const int out = 15;   
int red,blue ,green,white;
int r=0;
int w=0;
int b=0;
int g=0;
int CLOSE_ANGLE = 90;
int OPEN_ANGLE = 0; 
void setup()   
{  
  Serial.begin(115200); 
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
  pickServo.attach(13);
  dropServo.attach(21);
  pickServo.write(90);
  dropServo.write(0);
}

void loop() 
{  
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2,LOW);
  digitalWrite(s3, HIGH);  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  digitalWrite(s3,HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2,HIGH);
  digitalWrite(s3, LOW);  
  white = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
  Serial.print("R Intensity:");  
  Serial.print(red, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(blue, DEC); 
  Serial.print(" W Intensity: "); 
  Serial.print(white,DEC);
  Serial.println();
  delay(1000);
  if(red<blue & red<green){
    dropServo.write(45);
    delay(1000);
    r++;
    Serial.print("Red:");
    Serial.println(r);  
    open1();
    delay(1000);
    close1();
  }
  else if(green<red & green<blue)
  {
    dropServo.write(90);
    delay(1000);
    g++;
    Serial.print("Green:");
    Serial.println(g);
    open1();
    delay(1000);
    close1();
  }
  else if(blue<green & blue< red)
  {
    dropServo.write(135);
    delay(1000);
    b++;
    Serial.print("Blue:");
    Serial.println(b);
    open1();
    delay(1000);
    close1();
  }
  else if(white<10)
  {
    dropServo.write(180);
    delay(1000);
    w++;
    Serial.print("White:");
    Serial.println(w);
    open1();
    delay(1000);
    close1();
  } 
  else
  {
    Serial.println("No colour Detected");
    dropServo.write(0);
    delay(1000);
    open1();
    delay(1000);
    close1();
  }
  Serial.println();  
 // delay(1000); 
} 
void open1(){ 
  pickServo.write(OPEN_ANGLE);
}
void close1(){ 
  pickServo.write(CLOSE_ANGLE);
}