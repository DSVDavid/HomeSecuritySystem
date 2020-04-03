#include <SoftwareSerial.h>
#define MOTION 12
#define GREEN 3
#define BLUE 4
#define RED 5
#define SOUND 8
SoftwareSerial BTserial(11, 10); // RX | TX
char c = ' ';
enum state{
  on,off,start
};
int st=0;
int motionState=LOW;
int soundState=LOW;
int buzzState=LOW;
int buzzS=0;

void setup() 
{
Serial.begin(9600);
Serial.println("Arduino is ready");
pinMode(13,OUTPUT);
// HC-05 default serial speed for commincation mode is 9600
BTserial.begin(9600);  
pinMode(13,OUTPUT);
pinMode(2,OUTPUT);
pinMode(8,INPUT);
pinMode(MOTION,INPUT);

}

void loop()
{
  blueMode();
  
  if(st==1){
    motionDetect();
    soundDetect();
    buzz();
  }
  leds();
}

void leds(){
  if(st==0){
    digitalWrite(GREEN,HIGH);
    digitalWrite(BLUE,LOW);
  }else if(st==1){
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,HIGH);
  }
  if(buzzState==HIGH)
    digitalWrite(RED,HIGH);
  else
    digitalWrite(RED,LOW);
}

void soundDetect(){
  if(digitalRead(8)==LOW){
  Serial.println("Sound detected");
  soundState=HIGH;
  }else{
  soundState=LOW;
//  Serial.println("No sound detected");
  }
}
void buzz(){
  if(motionState==HIGH || soundState==HIGH){
    buzzState=HIGH;
  }
  digitalWrite(2,buzzState);
  if(buzzState==HIGH&&buzzS==0){
    buzzS=1;
  }
  if(buzzS==1)
    buzz1();
   if(buzzS==2)
    buzz2();
    if(buzzS==3)
    buzz3();
    if(buzzS==4)
    buzzEnd();
}
void buzz1(){
  Serial.println("buzz1");
  if(c=='p')
  buzzS=2;
}
void buzz2(){
  Serial.println("buzz2");
  if(c!='p'&&c!='a')
   buzzS=1;
   if(c=='a')
   buzzS=3;
}
void buzz3(){
  Serial.println("buzz3");
  if(c!='a'&&c!='s')
  buzzS=1;
  if(c=='s')
  buzzS=4;
}
void buzzEnd(){
  Serial.println("buzzEnd");
  buzzState=LOW;
  buzzS=0;
  motionState=LOW;
  soundState=LOW;
  digitalWrite(2,buzzState);
  st=0;
}
void motionDetect(){
  
  if(motionState==LOW)
    if(digitalRead(MOTION)==HIGH){
      motionState=HIGH;
      Serial.println("Motion detected");
    }else{
      motionState=LOW;
    //  Serial.println("No motion");
    }
}


void blueMode(){
  if (BTserial.available())
{  
  
    c = BTserial.read();
    Serial.write(c);
    if(c=='1' && buzzState==LOW){
      if(st==0){
        st=2;
        Serial.println("a");
      }else if(st==1){
        st=0;
        Serial.println("b");
      }
     
    }
   
}
 switch(st){
      case 1:
        onState();
        break;
      case 0:
        offState();
        break;
      case 2:
        startingState();
        break;
      default:
        offState();
    }

}
void onState(){
  digitalWrite(13,HIGH);
 
  }
void offState(){
  digitalWrite(13,LOW);
  motionState=LOW;
  }
void startingState(){
  delay(5000);
  
  st=1;

  }