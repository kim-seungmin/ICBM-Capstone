#include <Thread.h>
#include <ThreadController.h>

ThreadController controll = ThreadController();
Thread moterThread = Thread();

int Dir1Pin_A = 2;      // 제어신호 1핀
int Dir2Pin_A = 3;      // 제어신호 2핀
int SpeedPin_A = 10;    // PWM제어를 위한 핀

int Dir1Pin_B = 4;      // 제어신호 1핀
int Dir2Pin_B = 5;      // 제어신호 2핀
int SpeedPin_B = 11;    // PWM제어를 위한 핀

void setup() {
  pinMode(Dir1Pin_A, OUTPUT);             // 제어 1번핀 출력모드 설정
  pinMode(Dir2Pin_A, OUTPUT);             // 제어 2번핀 출력모드 설정
  pinMode(SpeedPin_A, OUTPUT);            // PWM제어핀 출력모드 설정

  pinMode(Dir1Pin_B, OUTPUT);             // 제어 1번핀 출력모드 설정
  pinMode(Dir2Pin_B, OUTPUT);             // 제어 2번핀 출력모드 설정
  pinMode(SpeedPin_B, OUTPUT);            // PWM제어핀 출력모드 설정
}
 
void loop() {
  int len;
  String place = "L";  

  moterThread.onRun(moterTurn(place, len));
  moterThread.setInterval(500);
  controll.add(&moterThread);
   
}
static void moterTurn(String place, int len){
  if(place = "L"){
    digitalWrite(Dir1Pin_A, HIGH);         //모터가 시계 방향으로 회전
    digitalWrite(Dir2Pin_A, LOW);
    analogWrite(SpeedPin_A, 255/len);          //모터 속도를 최대로 설정
    delay(1000);
     analogWrite(SpeedPin_A, 0);
  }else{
    digitalWrite(Dir1Pin_B, HIGH);         //모터가 시계 방향으로 회전
    digitalWrite(Dir2Pin_B, LOW);
    analogWrite(SpeedPin_B, 255/len);          //모터 속도를 최대로 설정
    delay(1000);
    analogWrite(SpeedPin_B, 0);
  }
}
