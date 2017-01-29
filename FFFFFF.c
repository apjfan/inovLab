#include <Servo.h>
#include <SoftwareSerial.h>
#define RFIDoutput 11
#define ldrDataPin A0
#define LDRoutput 12
#define ULTRAoutput 10
#define trigPin 9
#define echoPin 5
#define servoPin 6
Servo ser;
SoftwareSerial RFID=SoftwareSerial(2, 3); // RX and TX
String st="\0";
String str="\0";
String strArray[10];
String fin="\0";
int i,j,test=1;
int ldrData = 0;
void setup(){
  RFID.begin(9600);
  Serial.begin(9600);
  ser.attach(servoPin);
  RFIDsetup();
  LDRsetup();
  ULTRAsetup();
}
void loop(){
  while(1){
  getRfidData();
  getLdrData();
  getUltraData();
  }
}
void RFIDsetup(){
  strArray[0]="24848484849704856515250513";
  strArray[1]="24948484851535568695766493";
  strArray[2]="25155484852657054515666513";
  pinMode(RFIDoutput,OUTPUT);
}
void LDRsetup(){
  pinMode(LDRoutput,OUTPUT);
}
void ULTRAsetup(){
    pinMode(trigPin,OUTPUT);
    pinMode(ULTRAoutput,OUTPUT);
    pinMode(echoPin,INPUT);  
}
void getRfidData(){
 fin=getData();
 Serial.println(fin);
 if(fin.length()){
           int chk=0;
           for(i=0;i<3;i++){              
                if(fin==strArray[i]){
                   Serial.println("Access Allowed!");
                                ser.write(90);
                                delay(100);
                                ser.write(-90);
                 
                  fin="\0";
                  str="\0";
                  st="\0";
                  test=0;
                  chk=1; 
            //      return;
            break;
                }
            }
            if(chk==0){
                     for(j=0;j<5;j++){
                        digitalWrite(RFIDoutput,0);
                        delay(20);
                      }
                  Serial.println("Access denied!");
                  fin="\0";
                  test=1;
                  delay(100);
                  digitalWrite(RFIDoutput,1);
            }
            else{
                  digitalWrite(RFIDoutput,1); 
                  fin="\0";
            }
  }  
  delay(10);
  fin="";
}
String getData(){
    str="\0";
    st="\0";
    while(RFID.available()>0){
         st = RFID.read();
         //getLdrData(); //...............
         str+=st;
        if(str.length()>=26){
        Serial.println(str);
        // delay(100);
           break;
         }
      }
      return str;
}
void getLdrData(){
  ldrData = analogRead(ldrDataPin);
  Serial.println(ldrData);
  if(ldrData<50){
    digitalWrite(LDRoutput,0);
  //  getUltraData();
  }
  else
    digitalWrite(LDRoutput,1);
}
void getUltraData(){
  float dura, dis;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  dura = pulseIn(echoPin, HIGH);
  dis = (dura / 2.0) * 0.0344;
  if (dis<= 20.0){
    digitalWrite(ULTRAoutput,1);
    delay(100);
  }
  else {
    digitalWrite(ULTRAoutput,0);
    delay(100);
  }  
  Serial.println(dis);
}
