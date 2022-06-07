#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Tone.h>

//const int btn1 = 7;
//const int btn2 = 8;
//const int btn3 = 9;
//const int btn4 = 10;
//const int btn5 = 11;
int ledpin[] = {2, 3, 4, 5}; // LED pins
int btn[] = {7, 8, 9, 10, 11};

LiquidCrystal_I2C lcd(0x27, 20, 4);

/////////////memory game/////////////
Tone speakerpin;
int starttune[] = {NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G4};
int duration2[] = {100, 200, 100, 200, 100, 400};
int note[] = {NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4};
int duration[] = {100, 100, 100, 300, 100, 300};
int button[] = {7, 8, 9, 10}; //The four button input pins

int turn = 0;  // turn counter
int buttonstate = 0;  // button state checker
int randomArray[50]; //long to store up to 50 inputs
int inputArray[50];
int highscore = 0;
int MyScore;

/////////////baseball game/////////////
long a, b, c, d;
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

void setup() {
  lcd.init();
  lcd.setBacklight(HIGH);
  //pinMode(btn1, INPUT_PULLUP);
  //pinMode(btn2, INPUT_PULLUP);
  //pinMode(btn3, INPUT_PULLUP);
  //pinMode(btn4, INPUT_PULLUP);
  //pinMode(btn5, INPUT_PULLUP);
  for (int x = 0; x < 4; x++) // LED pins are outputs
  {
    pinMode(ledpin[x], OUTPUT);
    pinMode(btn[x], INPUT);
  }

}
void loop() {

  showStartSequence();

}


void input() { //Function for allowing user input and checking input against the generated array

  for (int x = 0; x <= turn;)
  { //Statement controlled by turn count

    for (int y = 0; y < 4; y++)
    {
      buttonstate = digitalRead(button[y]);

      if (buttonstate == LOW && button[y] == 2)
      { //Checking for button push
        digitalWrite(ledpin[0], HIGH);
        speakerpin.play(NOTE_G3, 100);
        delay(200);
        digitalWrite(ledpin[0], LOW);
        inputArray[x] = 1;
        delay(250);
        Serial.print(" ");
        Serial.print(1);
        if (inputArray[x] != randomArray[x]) { //Checks value input by user and checks it against
          fail();                              //the value in the same spot on the generated array
        }                                      //The fail function is called if it does not match
        x++;
      }
      else if (buttonstate == LOW && button[y] == 3)
      {
        digitalWrite(ledpin[1], HIGH);
        speakerpin.play(NOTE_A3, 100);
        delay(200);
        digitalWrite(ledpin[1], LOW);
        inputArray[x] = 2;
        delay(250);
        Serial.print(" ");
        Serial.print(2);
        if (inputArray[x] != randomArray[x]) {
          fail();
        }
        x++;
      }

      else if (buttonstate == LOW && button[y] == 4)
      {
        digitalWrite(ledpin[2], HIGH);
        speakerpin.play(NOTE_B3, 100);
        delay(200);
        digitalWrite(ledpin[2], LOW);
        inputArray[x] = 3;
        delay(250);
        Serial.print(" ");
        Serial.print(3);
        if (inputArray[x] != randomArray[x]) {
          fail();
        }
        x++;
      }

      else if (buttonstate == LOW && button[y] == 5)
      {
        digitalWrite(ledpin[3], HIGH);
        speakerpin.play(NOTE_C4, 100);
        delay(200);
        digitalWrite(ledpin[3], LOW);
        inputArray[x] = 4;
        delay(250);
        Serial.print(" ");
        Serial.print(4);
        if (inputArray[x] != randomArray[x])
        {
          fail();
        }
        x++;
      }
    }
  }
  delay(500);
  turn++; //Increments the turn count, also the last action before starting the output function over again
}

void fail() { //Function used if the player fails to match the sequence

  for (int y = 0; y <= 3; y++)
  { //Flashes lights for failure

    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    speakerpin.play(NOTE_G2, 300);
    delay(200);
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    speakerpin.play(NOTE_C2, 300);
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game Over");
  }
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("High: " + (String) (highscore));
  // Serial.print(y);
  // Serial.println("");
  lcd.setCursor(9, 0);
  lcd.print("You: ");
  lcd.setCursor(14, 0);
  lcd.print(MyScore);
  // if(y > highscore) {
  // highscore = y;
  // }
  lcd.setCursor(0, 1);
  lcd.print("<-Press to play again!");
  {
    // buttonstate = digitalRead(button[y]);
    while (digitalRead(button[0]) > 0 && digitalRead(button[1]) > 0 && digitalRead(button[2]) > 0 && digitalRead(button[3]) > 0 ) {
      digitalWrite(ledpin[0], HIGH);
      digitalWrite(ledpin[1], HIGH);
      digitalWrite(ledpin[2], HIGH);
      digitalWrite(ledpin[3], HIGH);
      delay(100);
      digitalWrite(ledpin[0], LOW);
      digitalWrite(ledpin[1], LOW);
      digitalWrite(ledpin[2], LOW);
      digitalWrite(ledpin[3], LOW);
      delay(100);
    }
    delay(1000);

    turn = -1; //Resets turn value so the game starts over without need for a reset button
  }
}

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

void checkC()
{
  if (next_out == 0)
    lcd.setCursor(0, 1);
  else if (next_out == 1)
    lcd.setCursor(5, 1);
  else if (next_out == 2)
    lcd.setCursor(11, 1);
  else
    lcd.setCursor(16, 1);
}//sw2누를때마다 커서 설정

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

void check_error()
{
  if (count_A == count_B || count_A == count_C || count_A == count_D || count_B == count_C || count_B == count_D || count_C == count_D )
    errorlist = 1;
  else
    errorlist = 0;
}
void showStartSequence() {

  if (digitalRead(btn[0]) == HIGH && digitalRead(btn[1]) == HIGH && digitalRead(btn[2]) == HIGH && digitalRead(btn[3]) == HIGH && digitalRead(btn[4]) == HIGH) {
    lcd.init();

    lcd.setCursor(4, 0);
    lcd.print("Select Game");
    //lcd.setCursor(4, 1);
    //lcd.print("Avoiding car");

    lcd.setCursor(1, 2);
    lcd.print("Car         Memory");

    lcd.setCursor(1, 3);
    lcd.print("Baseball    Tetris");
  }

  else if (digitalRead(btn[0]) == LOW) { //버튼을 누르면 차 피하기 게임 시작
  }
  /* else  if (digitalRead(btn2) == LOW) {
     lcd.clear();                  //다시 lcd 스크린을 지움.
     lcd.setCursor(5, 1); //커서를 3,0으로 위치시킴
     lcd.print("Get ready!");      //"Get ready!" 메시지 출력
     delay(1000);                  //1초간 기다렸다가

     lcd.clear();                  //lcd 화면창을 지우고
     lcd.setCursor(5, 1); //커서를 5,0으로 위치시킴
     lcd.print("Start!");               // "Start!" 출력
     delay(1000);
     lcd.clear(); //lcd 화면창을 지움
    }*/
  else  if (digitalRead(btn[1]) == LOW) {

    lcd.init();
    lcd.setBacklight(HIGH);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Your Score: 0");
    lcd.setCursor(0, 0);
    lcd.print("High Score: 0");

    speakerpin.begin(12); // speaker is on pin 12

    for (int x = 0; x < 4; x++)
    {
      pinMode(button[x], INPUT); // button pins are inputs
      digitalWrite(button[x], HIGH);  // enable internal pullup; buttons start in high position; logic reversed
    }
    randomSeed(analogRead(0)); //Added to generate "more randomness" with the randomArray for the output function
    for (int thisNote = 0; thisNote < 6; thisNote ++) {
      // play the next note:
      speakerpin.play(starttune[thisNote]);
      // hold the note:
      if (thisNote == 0 || thisNote == 2)
      {
        digitalWrite(ledpin[0], HIGH);
      }
      else if (thisNote == 1 || thisNote == 3 ) {
        digitalWrite(ledpin[1], HIGH);
      }
      else if (thisNote == 4 || thisNote == 5) {
        digitalWrite(ledpin[2], HIGH);
      }
      else if (thisNote == 6)
      {
        digitalWrite(ledpin[3], HIGH);
      }
      delay(duration2[thisNote]);
      // stop for the next note:
      speakerpin.stop();

      digitalWrite(ledpin[0], LOW);
      digitalWrite(ledpin[1], LOW);
      digitalWrite(ledpin[2], LOW);
      digitalWrite(ledpin[3], LOW);
      delay(25);
    }
    delay(1000);

    for (int y = 0; y <= 2; y++)
    {
      //function for generating the array to be matched by the player
      digitalWrite(ledpin[0], HIGH);
      digitalWrite(ledpin[1], HIGH);
      digitalWrite(ledpin[2], HIGH);
      digitalWrite(ledpin[3], HIGH);

      for (int thisNote = 0; thisNote < 6; thisNote ++) {
        // play the next note:
        speakerpin.play(note[thisNote]);
        // hold the note:
        delay(duration[thisNote]);
        // stop for the next note:
        speakerpin.stop();
        delay(25);
      }

      digitalWrite(ledpin[0], LOW);
      digitalWrite(ledpin[1], LOW);
      digitalWrite(ledpin[2], LOW);
      digitalWrite(ledpin[3], LOW);
      delay(1000);

      for (int y = turn; y <= turn; y++) //untuk sekali random
      { //Limited by the turn variable
        Serial.println(""); //Some serial output to follow along
        Serial.print("Turn: ");
        Serial.print(y);
        Serial.println("");
        lcd.clear();
        MyScore = y;
        lcd.setCursor(0, 1);  //(Column,Row)
        lcd.print("Your Score: ");
        lcd.setCursor(12, 1);
        lcd.print(MyScore);
        if (MyScore > highscore) {
          highscore = y;
        }
        lcd.setCursor(0, 0);
        lcd.print("High Score: " + (String)(highscore));
        Serial.print(y);
        Serial.println("");
        delay(1000);
        randomArray[y] = random(1, 5); //Assigning a random number (1-4) to the randomArray[y], y being the turn count
        for (int x = 0; x <= turn; x++)
        {
          Serial.print(randomArray[x]);

          for (int y = 0; y < 4; y++)
          {

            if (randomArray[x] == 1 && ledpin[y] == 8)
            { //if statements to display the stored values in the array
              digitalWrite(ledpin[y], HIGH);
              speakerpin.play(NOTE_G3, 100);
              delay(400);
              digitalWrite(ledpin[y], LOW);
              delay(100);
            }

            else if (randomArray[x] == 2 && ledpin[y] == 9)
            {
              digitalWrite(ledpin[y], HIGH);
              speakerpin.play(NOTE_A3, 100);
              delay(400);
              digitalWrite(ledpin[y], LOW);
              delay(100);
            }

            else if (randomArray[x] == 3 && ledpin[y] == 10)
            {
              digitalWrite(ledpin[y], HIGH);
              speakerpin.play(NOTE_B3, 100);
              delay(400);
              digitalWrite(ledpin[y], LOW);
              delay(100);
            }

            else if (randomArray[x] == 4 && ledpin[y] == 11)
            {
              digitalWrite(ledpin[y], HIGH);
              speakerpin.play(NOTE_C4, 100);
              delay(400);
              digitalWrite(ledpin[y], LOW);
              delay(100);
            }
          }
        }
      }
      input();
    }
  }
  else if (digitalRead(btn[2]) == LOW) {
    Serial.begin(9600);     //Serial 통신
    lcd.init();
    lcd.setBacklight(HIGH);

    randomSeed(analogRead(0)); //random함수 반드시 필요!
    check();                   //random으로 초기값 설정

    int count = digitalRead(btn[1]);
    int next = digitalRead(btn[2]);
    int result = digitalRead(btn[3]);

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

    if (next == LOW)
      next_out = next_out + 1;

    checkB();   //a,b,c,d가 모두 달라야됨
    checkC();   //sw2누를때마다 커서 설정

    if (next_out == 3 && result == LOW)
      check_error();
    if (errorlist == 0)
    {
      checkD();   //입력값과 정해준 값 비교(stike_c)
      checkE();   //입력값과 정해준 값 비교(ball_c)
      lcd.setCursor(0, 2);
      lcd.print(strike_c);
      lcd.setCursor(1, 2);
      lcd.print("S");

      lcd.setCursor (3, 2);
      lcd.print(ball_c);
      lcd.setCursor(4, 2);
      lcd.print("B");

      if (strike_c == 4)
      {
        lcd.setCursor(9, 2);
        lcd.print("HOMERUN"); //homerun 출력
      }
      else
      {
        lcd.setCursor(9, 2);
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
      lcd.setCursor(9, 2);
      lcd.print("  error");
      delay(3000);
      lcd.setCursor(11, 2);
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

  else  if (digitalRead(btn[3]) == LOW) {
    lcd.clear();                  //다시 lcd 스크린을 지움.
    lcd.setCursor(5, 1); //커서를 3,0으로 위치시킴
    lcd.print("Get ready!");      //"Get ready!" 메시지 출력
    delay(1000);                  //1초간 기다렸다가

    lcd.clear();                  //lcd 화면창을 지우고
    lcd.setCursor(5, 1); //커서를 5,0으로 위치시킴
    lcd.print("Start!");               // "Start!" 출력
    delay(1000);
    lcd.clear(); //lcd 화면창을 지움
  }
}
