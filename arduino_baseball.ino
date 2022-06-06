#include <LiquidCrystal_I2C.h>
//#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
//SoftwareSerial BTSerial(6, 7);

long a, b, c, d;
int sw1 = 8;    //sw1는 count
int sw2 = 9;    //sw2는 next(옆으로 이동)
int sw3 = 10;   //sw3는 비교

int count_A = -1;
int count_B = -1;
int count_C = -1;
int count_D = -1;

int next_out = 0;
int ball_c = 0;
int strike_c = 0;

int errorlist = 2;

int time = 3000;
int chance = 0;

void setup()
{
  //BTSerial.begin(115200);  //블루투스 통신
  Serial.begin(9600);     //Serial 통신
  lcd.init();
  lcd.setBacklight(HIGH);

  randomSeed(analogRead(0)); //random함수 반드시 필요!
  check();                   //random으로 초기값 설정

  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
}

///////////////////////////////

void loop()
{
  /*char speak;
  if ( BTSerial.available() )
  {
    speak = BTSerial.read();
    if ( speak == 'a' )
    {
      BTSerial.print(a);
      BTSerial.print(b);
      BTSerial.print(c);
      BTSerial.println(d);
    }
    if ( speak == 'c' )
    {
      BTSerial.print("Try = ");
      BTSerial.println(chance);
    }
  } //블루투스 통신
*/
  int count = digitalRead(sw1);
  int next = digitalRead(sw2);
  int result = digitalRead(sw3);

  if (count == LOW)
  {
    if (next_out == 0)
    {
      count_A = count_A + 1;
      lcd.print(count_A);
    }
    else if (next_out == 1)
    {
      count_B = count_B + 1;
      lcd.print(count_B);
    }
    else if (next_out == 2)
    {
      count_C = count_C + 1;
      lcd.print(count_C);
    }
    else
    {
      count_D = count_D + 1;
      lcd.print(count_D);
    }
  }
  //각 자리마다 따로 저장

  if (next == LOW)
    next_out = next_out + 1;

  checkB();   //a,b,c,d가 모두 달라야됨
  checkC();   //sw2누를때마다 커서 설정

  if (next_out == 3 && result == HIGH)
    check_error();
  if (errorlist == 0)
  {
    checkD();   //입력값과 정해준 값 비교(stike_c)
    checkE();   //입력값과 정해준 값 비교(ball_c)
    lcd.setCursor(0, 1);
    lcd.print(strike_c);
    lcd.setCursor(1, 1);
    lcd.print("S");

    lcd.setCursor (3, 1);
    lcd.print(ball_c);
    lcd.setCursor(4, 1);
    lcd.print("B");

    if (strike_c == 4)
    {
      lcd.setCursor(9, 1);
      lcd.print("HOMERUN"); //homerun 출력
    }
    else
    {
      lcd.setCursor(9, 1);
      lcd.print("       "); //homerun 초기화(=없음)
    }

    next_out = 0; //cursor 초기화
    strike_c = 0; //strike 초기화
    ball_c = 0;   //ball 초기화
    errorlist = 2; //errorlist 초기화

    delay(time);
    time = time + 500;  //연속으로 도전 못하게 방지
    chance = chance + 1;//도전횟수
  }
  else if (errorlist == 1)
  {
    lcd.setCursor(9, 1);
    lcd.print("  error");
    delay(3000);
    lcd.setCursor(11, 1);
    lcd.print("       ");
    errorlist = 2;  //errorlist 초기화(=없음)
  }

  lcd.cursor();     //커서위치확인

  delay(300);

  //Serial 확인창//
  Serial.print("password:");
  Serial.print(a);
  Serial.print(b);
  Serial.print(c);
  Serial.print(d);
  Serial.print(" time:");
  Serial.println(time);
}

///////////////////////////////

void check()
{
  do
  {
    a = random(0, 10);    //0~9 랜덤 숫자 생성
    b = random(0, 10);
    c = random(0, 10);
    d = random(0, 10);
  }
  while ( a == b || a == c || a == d || b == c || b == d || c == d );
  //do-while문은 최초 1회는 실행,거짓조건 출력
}//random으로 초기값 설정
///////////////////////////////
void checkB()
{
  if (count_A == 9)
    count_A = -1;
  if (count_B == 9)
    count_B = -1;
  if (count_C == 9)
    count_C = -1;
  if (count_D == 9)
    count_D = -1;

  if (next_out == 4)
    next_out = 0;
}//a,b,c,d가 모두 달라야됨
///////////////////////////////
void checkC()
{
  if (next_out == 0)
    lcd.setCursor(0, 0);
  else if (next_out == 1)
    lcd.setCursor(4, 0);
  else if (next_out == 2)
    lcd.setCursor(8, 0);
  else
    lcd.setCursor(12, 0);
}//sw2누를때마다 커서 설정
///////////////////////////////
void checkD()
{
  if (a == count_A || a == 9 && count_A == -1)
    strike_c = strike_c + 1;
  if (b == count_B || b == 9 && count_B == -1)
    strike_c = strike_c + 1;
  if (c == count_C || c == 9 && count_C == -1)
    strike_c = strike_c + 1;
  if (d == count_D || d == 9 && count_D == -1)
    strike_c = strike_c + 1;
}//입력값과 정해준 값 비교(stike_c)
///////////////////////////////
void checkE()
{
  if (a == count_B || a == count_C || a == count_D)
    ball_c = ball_c + 1;
  if (b == count_A || b == count_C || b == count_D)
    ball_c = ball_c + 1;
  if (c == count_A || c == count_B || c == count_D)
    ball_c = ball_c + 1;
  if (d == count_A || d == count_B || d == count_C)
    ball_c = ball_c + 1;
}//입력값과 정해준 값 비교(ball_c)
///////////////////////////////
void check_error()
{
  if (count_A == count_B || count_A == count_C || count_A == count_D || count_B == count_C || count_B == count_D || count_C == count_D )
    errorlist = 1;
  else
    errorlist = 0;
}
