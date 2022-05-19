#include <Thread.h>
#include <ThreadController.h>

#define TRIG_L 9 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO_L 8 //ECHO 핀 설정 (초음파 받는 핀)

#define TRIG_R 13 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO_R 12 //ECHO 핀 설정 (초음파 받는 핀)

#define Dir1Pin_A  2      // 제어신호 1핀
#define Dir2Pin_A  3      // 제어신호 2핀
#define SpeedPin_A  10    // PWM제어를 위한 핀

#define Dir1Pin_B  4      // 제어신호 1핀
#define Dir2Pin_B  5      // 제어신호 2핀
#define SpeedPin_B  11    // PWM제어를 위한 핀

ThreadController controller = ThreadController();

Thread SenserLeftThread = Thread();
Thread SenserRightThread = Thread();

//----------------------------------------------------------- sona
void leftcalc() {
  analogWrite(SpeedPin_A, 0); 
  long sonaTime;

  digitalWrite(TRIG_L, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_L, LOW);

  sonaTime = pulseIn (ECHO_L, HIGH); //물체에 반사되어 돌아온 초음파의 시간을 변수에 저장

  TimeToDistance(sonaTime, "L"); 
}

void rightcalc() {
  analogWrite(SpeedPin_B, 0); 
  long sonaTime;

  digitalWrite(TRIG_R, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_R, LOW);

  sonaTime = pulseIn (ECHO_R, HIGH); //물체에 반사되어 돌아온 초음파의 시간을 변수에 저장

  TimeToDistance(sonaTime, "R"); 
}
//----------------------------------------------arduino
void TimeToDistance(int sonaTime, String LR){
  int distance;
  //34000*초음파가 물체로 부터 반사되어 돌아오는0시간 /1000000 / 2
  //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산
  distance = (sonaTime * 17 / 1000)/6; //최대거리 30 5단계로 나눔 6이상이면버림
  //PC모니터로 초음파 거리값을 확인

  
  Serial.println("Distance "+LR+": "+ sonaTime * 17 / 1000 +"cm "+ distance+" Level");//측정된 물체로부터 거리값(5단계) 출력

  
  if(distance<5&&distance>-1){
    distanceToVolt(LR, distance);         
    }
}

//-------------------------------------------------motor
void distanceToVolt(String place, int len){
  int volt = 255/len;
  if(place == "L"){
    digitalWrite(Dir1Pin_A, HIGH);         //모터가 시계 방향으로 회전
    digitalWrite(Dir2Pin_A, LOW);
    analogWrite(SpeedPin_A, volt);          //모터 속도를 최대로 설정
  }else if(place == "R"){
    digitalWrite(Dir1Pin_B, HIGH);         //모터가 시계 방향으로 회전
    digitalWrite(Dir2Pin_B, LOW);
    analogWrite(SpeedPin_B, volt);          //모터 속도를 최대로 설정
  }
}

void setup() {
  Serial.begin(9600); //시리얼 통신을 정의(모니터로 센서값을 확인)
  pinMode(TRIG_L, OUTPUT);                //초음파
  pinMode(ECHO_L, INPUT);                 //초음파
  pinMode(TRIG_R, OUTPUT);                //초음파
  pinMode(ECHO_R, INPUT);                 //초음파
  
  pinMode(Dir1Pin_A, OUTPUT);             // 모터 1번핀 
  pinMode(Dir2Pin_A, OUTPUT);             // 모터 2번핀 
  pinMode(SpeedPin_A, OUTPUT);            // 모터 PWM제어핀 

  pinMode(Dir1Pin_B, OUTPUT);             // 모터 1번핀 
  pinMode(Dir2Pin_B, OUTPUT);             // 모터 2번핀 
  pinMode(SpeedPin_B, OUTPUT);            // 모터 PWM제어핀 
  
  SenserLeftThread.onRun(leftcalc);       //좌쓰레드
  SenserLeftThread.setInterval(1000);
  
  SenserRightThread.onRun(rightcalc);     //우쓰레드
  SenserRightThread.setInterval(1000);    

  controller.add(&SenserLeftThread);      //쓰레드 컨트롤러
  controller.add(&SenserRightThread);
}

void loop() {
  controller.run();
}
