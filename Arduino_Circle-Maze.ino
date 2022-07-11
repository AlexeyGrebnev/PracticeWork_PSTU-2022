//Engine Driver TB6612FNG
#define PWMA 5  //выходы arduino
#define PWMB 6 //
#define AIN1 7
#define AIN2 4
#define BIN1 9 //
#define BIN2 8
//Black Line sensors
#define L A1 // Пин для подключения датчика линии
#define C A2 // Пин для подключения датчика линии
#define R A3 // Пин для подключения датчика линии
//Axel ADXL335
//#define x A0
//#define y A6
//#define z A7
//#define Period 500

unsigned long temptime = 0; // перепенная счетчик

uint8_t global = 111; // Текущее состояние системы
int i = 120;


void setup() {

  Serial.begin(9600);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  //pinMode(PIN_LED, OUTPUT);
  pinMode(L, INPUT);
  pinMode(C, INPUT);
  pinMode(R, INPUT);

}

void left(int motorSpeedRotate) {
  digitalWrite(AIN1, 0);      // влево
  digitalWrite(AIN2, 1);
  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 0);
  analogWrite(PWMA, motorSpeedRotate);
  analogWrite(PWMB, motorSpeedRotate);
}


void right(int motorSpeedRotate) {
  digitalWrite(AIN1, 1);      // вправо
  digitalWrite(AIN2, 0);
  digitalWrite(BIN1, 0);
  digitalWrite(BIN2, 1);
  analogWrite(PWMA, motorSpeedRotate);
  analogWrite(PWMB, motorSpeedRotate);
}

void backward(int motorSpeed)
{
  digitalWrite(AIN1, 0);      // назад
  digitalWrite(AIN2, 1);
  digitalWrite(BIN1, 0);
  digitalWrite(BIN2, 1);
  analogWrite(PWMA, motorSpeed);
  analogWrite(PWMB, motorSpeed);
}

void forward(int tempspeed)
{
  digitalWrite(AIN1, 1);      // движение вперед
  digitalWrite(AIN2, 0);
  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 0);
  analogWrite(PWMA, tempspeed);
  analogWrite(PWMB, tempspeed);

}


void loop() {
  global = digitalRead(L) * 100 + digitalRead(C) * 10 + digitalRead(R);

  if (global == 111 && i < 255 && (millis() - temptime <= 200))
  {
    temptime = millis();
    i++;
  }
  else if (global != 111)
  {
    temptime = millis();
    i = 120;
  }

  switch (global)
  {
    case 0: // 000
      { //Serial.println("case 000");


        backward(250);
        delay(200);
        left(150);
        delay(400);

        break;
      }

    case 111: // 111
      {
        //        Serial.println("case 111");
        Serial.println(i);
        forward(i);

        break;
      }

    case 110: // 110
      {
        //        Serial.println("case 110");
        left(150);

        break;
      }

    case 11: // 011
      {
        //        Serial.println("case 011");
        right(150);

        break;
      }

    case 101: // 101
      {
        //        Serial.println("case 101");
        backward(200);
        left(150);
        break;
      }

    case 1: // 001
      {
        //        Serial.println("case 001");
        right(150);

        break;
      }

    case 100: // 100
      {
        //        Serial.println("case 100");
        left(150);

        break;
      }

    case 10: // 010
      {
        //        Serial.println("case 010");
        backward(200);
        left(150);

        break;
      }
    default: {
        break;
      }
  }
}
