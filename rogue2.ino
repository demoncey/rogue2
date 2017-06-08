#include <SoftwareSerial.h>              "
//bluetooth
#define TX 11 //11 nano   
#define RX 12 //12 nano
SoftwareSerial bluetooth(RX,TX); 
//motor one weaker than two
#define ENA 10
#define IN1 9
#define IN2 8
#define SPEEDA 150
// motor two
#define ENB 5
#define IN3 7
#define IN4 6
#define SPEEDB 160
char old_cmd='3';
char cmd='3';

struct measurment
{
   float temp;
   int hum;
   int distance;
};
typedef struct measurment Measurment;

void setup() {
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("rogue 2 connected!");
  bluetooth.begin(38400);
  //motor conf
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}

void loop() {
  reciveMsg();
  switch(cmd){
    case '1':
      goForward(); 
      break;
    case '2':
      goBackward();
      break;
    case '3':
      stopMotor();
      break;
    case '4':
      goLeft();
      break;
    case '5':
      goRight();
      break;
    default:
      break; 
  }
  delay(500);
  bluetooth.println("Status: OK");
}

void reciveCmd(){
  if(Serial.available()>0){
    Serial.println("data received");
    bluetooth.print("data received");
    cmd=Serial.read(); 
  } 
}

void reciveMsg(){
  if(bluetooth.available()>0){
    Serial.println("data received");
    cmd=bluetooth.read(); 
  } 
}


void sendMsg(String msg){
  bluetooth.println(msg);
  Serial.println(msg);
}

void silentStopMotor(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void stopMotor(){
  if(old_cmd==cmd){
    return;
  }
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  displayMsg("stop motor");
  //store state
  old_cmd=cmd;
}

void goForward(){
  if(old_cmd==cmd){
    return;
  }
  if(old_cmd=='2'){
    silentStopMotor();
    delay(500);   
   }  
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,SPEEDA);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENB,SPEEDB);
  displayMsg("go forward");
  //store state
  old_cmd=cmd;
}

void goLeft(){
  if(old_cmd==cmd){
    return;
  }
  if(old_cmd=='2'){
    silentStopMotor();
    delay(500);   
   }  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENB,SPEEDB);
  displayMsg("go left");
  //store state
  old_cmd=cmd;
}

void goRight(){
  if(old_cmd==cmd){
    return;
  }
  if(old_cmd=='2'){
    silentStopMotor();
    delay(500);   
   }
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,SPEEDA);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  displayMsg("go right");
  //store state
  old_cmd=cmd;
}

void goBackward(){
  if(old_cmd==cmd){
    return;
  }
  if(old_cmd=='1'){
    silentStopMotor();
    delay(500);   
   }
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,SPEEDA); 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB,SPEEDB); 
  displayMsg("go backward");
  old_cmd=cmd;
  }

void displayMsg(char * msg){
  sendMsg(String(msg));
}

void displayMsg(String msg){
  sendMsg(msg);
}








