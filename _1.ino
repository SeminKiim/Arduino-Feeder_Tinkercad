#include <Servo.h> 

Servo servo_motor;
String strAngle;
const int a[] = {440, 349, 523, 659, 698, 415}; //음계 주파수를 저장한 배열

int counter = 0;
int led_G = 11; // 빨간색 LED 핀 번호
int led_R = 13;  //초록색 LED 핀 번호
int buzzer = 2; //부저 핀 번호
int pos = 0;
int i = 0;
int TRIG_pin = 6; //초음파 센서의 트리거 핀 번호
int ECHO_pin = 4;
int angle;
boolean flag = false;
char ans;

void setup() 
{ 
  pinMode(buzzer, OUTPUT); 
  servo_motor.attach(9); //servo-motor no pino PWM 9
  Serial.begin(9600);
  pinMode(led_G, OUTPUT); 
  pinMode(led_R, OUTPUT);
  pinMode(ECHO_pin, INPUT);
  pinMode(TRIG_pin, OUTPUT);

  servo_motor.write(0); //orienta o servo_motor a iniciar em 0
  
  Serial.print("Enter Y to feed or N to not feed. ");
  Serial.print("Will you feed your dog? >>> ");
  
}

void loop() 
{
  SV_control();
  digitalWrite(TRIG_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ECHO_pin, LOW);
  delayMicroseconds(10);
  digitalWrite(TRIG_pin, LOW);
  int distance = pulseIn(ECHO_pin, HIGH);
  int ate = distance/58;
  if(ate > 65){
    Serial.print("Didn't eat yet");
  }else{
    Serial.print("Eating");
  }
}

void beep(int note, int cntnue)
{
  //부저로 먹이가 나온다는 신호를 알리는 노래를 튼다.
  tone(buzzer, note, cntnue);
 
  //counter값에 따라 초록색 LED와 빨간색 LED가 번갈아 가며 깜빡인다.
  if(counter % 2 == 0)
  {
    digitalWrite(led_R, HIGH);
    delay(cntnue);
    digitalWrite(led_R, LOW);
  }else
  {
    digitalWrite(led_G, HIGH);
    delay(cntnue);
    digitalWrite(led_G, LOW);
  }
 
  //부저를 멈춘다.
  noTone(buzzer);
 
  delay(50);
 
  //카운터의 값을 1씩 올린다.
  counter++;
}
 
void playMusic()
{
  //노래를 재생하는 함수
  beep(a[0], 500);
  beep(a[0], 500);    
  beep(a[0], 500);
  beep(a[1], 350);
  beep(a[2], 150);  
  beep(a[0], 500);
  beep(a[1], 350);
  beep(a[2], 150);
  beep(a[0], 650);
 
  delay(500);
 
  beep(a[3], 500);
  beep(a[3], 500);
  beep(a[3], 500);  
  beep(a[4], 350);
  beep(a[2], 150);
  beep(a[5], 500);
  beep(a[1], 350);
  beep(a[2], 150);
  beep(a[0], 650);
 
  delay(500);
}

void SV_control(){
  if(flag == true){
    flag = false;
    angle = strAngle.toInt();
    strAngle = "";
}
        
  char ans = Serial.read();

  if(ans == 'Y'){
    playMusic();
    for(pos = 0; pos < 180; pos += 1){
      servo_motor.write(pos);
      delay(20);
    }
    for(pos = 180; pos >= 1; pos -= 1){
      servo_motor.write(pos);
    }
  }else if(ans == 'N'){
    //동작하지 않는다.
  }else{
    Serial.println("Enter 'Y' or 'N'");
  }
}