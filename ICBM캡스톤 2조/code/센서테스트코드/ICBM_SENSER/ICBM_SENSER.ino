#define TRIG 9 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 8 //ECHO 핀 설정 (초음파 받는 핀)

void setup() {

  Serial.begin(9600); //시리얼 통신을 정의(모니터로 센서값을 확인)
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

}

void loop() {

  long duration, distance;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn (ECHO, HIGH); //물체에 반사되어 돌아온 초음파의 시간을 변수에 저장


  //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2
  //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산

  distance = duration * 17 / 1000;

  //PC모니터로 초음파 거리값을 확인

  Serial.println(duration ); //초음파가 반사되어 돌아오는 시간 출력
  Serial.print("\nDIstance : ");
  Serial.print(distance); //측정된 물체로부터 거리값(cm값)출력
  Serial.println(" Cm");

  delay(1000); //1초마다 측정값을 확인

}
