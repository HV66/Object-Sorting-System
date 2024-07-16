#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TCS34725.h>
#include <WiFi.h>;
#include <ThingSpeak.h>;

unsigned long myChannelNumber = 2438062;
const char * myWriteAPIKey = "7UX7NDWFZLCNIN3L ";
const char *ssid =  "Annu";     // Enter your WiFi Name
const char *pass =  "apkv_919"; // Enter your WiFi Password
WiFiClient client;

Servo pickServo;
Servo dropServo;
const int s0 = 19;  
const int s1 = 18;  
const int s2 = 2;  
const int s3 = 4;  
const int out = 15;   
int red,blue,green,white;
int r=0;
int w=0;
int b=0;
int g=0;
int p=0;
int y=0;
int bl=0;
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

  ThingSpeak.begin(client);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(550);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}

void loop() 
{  
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, LOW);  
  white = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
  Serial.print("R Intensity:");  
  Serial.print(red, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.println(blue, DEC);  

  if(red>24 & red<30 & green>45 & green<51 & blue>13 & blue<15)
  {
    dropServo.write(120);
    delay(1000);
    r++;
    Serial.print("Red:");
    Serial.println(r);  
    open1();
    delay(1000);
    close1();
    ThingSpeak.writeField(myChannelNumber, 1,r, myWriteAPIKey);
  }
  else if(red>25 & red<29 & green>40 & green<44 & blue >11 & blue<15)
  {
    dropServo.write(130);
    delay(1000);
    g++;
    Serial.print("Green:");
    Serial.println(g);
    open1();
    delay(1000);
    close1();
    ThingSpeak.writeField(myChannelNumber, 2,g, myWriteAPIKey);
  }
else if(red>20 & red<25 & green>31 & green<35 & blue>10 & blue<15)
  {
    dropServo.write(140);
    delay(1000);
    b++;
    Serial.print("Blue:");
    Serial.println(b);
    open1();
    delay(1000);
    close1();
    ThingSpeak.writeField(myChannelNumber, 3,b, myWriteAPIKey);
  }
/*  else if(red>20 & red<25 & green>35 & green<40 & blue>10 & blue<15)
  {
    dropServo.write(150);
    delay(1000);
    y++;
    Serial.print("Yellow:");
    Serial.println(y);
    open1();
    delay(1000);
    close1();
    ThingSpeak.writeField(myChannelNumber, 5,y, myWriteAPIKey);
  } */
  else if(blue<=red & green<40 & red>20)
  {
    dropServo.write(160);
    delay(1000);
    p++;
    Serial.print("purple:");
    Serial.println(p);
    open1();
    delay(1000);
    close1();
    ThingSpeak.writeField(myChannelNumber, 6,p, myWriteAPIKey);
  }
  else if(white<10)
  {
    dropServo.write(170);
    delay(1000);
    w++;
    Serial.print("White:");
    Serial.println(w);
    open1();
    delay(1000);
    close1();
    ThingSpeak.writeField(myChannelNumber, 4,w, myWriteAPIKey);
  } 
  else{
    dropServo.write(180);
    delay(1000);
   // bl++;
    Serial.print("No object placed");
    //Serial.println(bl);
    //open1();
    delay(1000);
    //close1();
    //ThingSpeak.writeField(myChannelNumber, 7,bl, myWriteAPIKey);
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