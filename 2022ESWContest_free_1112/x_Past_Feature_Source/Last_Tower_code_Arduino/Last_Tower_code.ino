//==================================
// client.read를 통해 받은 데이터를 Recv_msg 배열에 저장
// parsing을 통해 어떤 client가 보내는지 구별
// client별로 받은 데이터 내용을 통해 flow별로 각 구동
// 충전이 100%가 되면 Jetson에게 완료 데이터 전송
// 충전구 해지 데이터받으면 주차타워 작동
//=================================

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <string.h>


//=================================
// WiFi Variable
//=================================
ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

const char * host = "10.10.141.188";
const uint16_t port = 5000;

int ClientLogin = 0; //프로그램 시작시 클라이언트 로그인 flag

//=================================
// Communication Variable
//=================================
#define USE_SERIAL Serial
#define Button 5

String car_info[4];
char SendMsgData[30] = {}; //server로 보낼 메시지내용

int InOutState = 1; //충전구역입출차시 In,Out 상태알림 flag
int flow = -1; //각 실행문들의 시작동작 flag
//=================================
// Tower Variable
//=================================
#define motorPin1 0
#define motorPin2 4
#define motorPin3 15
#define motorPin4 16
#define steps 1124

int pinArray[4] = { motorPin1, motorPin2, motorPin3, motorPin4};
int CW[4] = {0b1000, 0b0100, 0b0010, 0b0001};

int CCW[4] = {0b0001, 0b0010, 0b0100, 0b1000};

//=================================
// Rest Variable
//=================================
// 1. Car In/Out Check
int trig = 13;
int echo = 12; 
bool led_status = false; //주차장 진입시 LED 깜박임
int led = 14;

// 2. Battery Check
int pre_RechargeVal = 0; //연속 충전량값 제어
int ori_RechargeVal, cur_RechargeVal; //연속 충전량값 제어
int recharge = 0; //충전량 flag





void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);

  pinMode(Button, INPUT);
  for (int i = 0; i < 4; i++) pinMode(pinArray[i], OUTPUT);

  WiFi.begin("iot24kcci", "iot40000");  //WiFi 연결
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Connected to wifi successful!");
}

void loop() {
  char Recv_msg[30] = {0};
  int index = 0;
  int str_len;

  if (ClientLogin == 0) {
    ClientConn();
    client.print("[SPOT1:PASSWD]");//서버 연결할 아이디와 비번 정보
    ClientLogin = 1;
  }

  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    memset(Recv_msg, 0, sizeof(Recv_msg));
    while (client.available()) {
      Recv_msg[index++] = static_cast<char>(client.read());
      if (Recv_msg[index - 1] == 'L')
      {
        char *pToken;
        char *pArray[10] = {0};
        Recv_msg[index - 1] = '\0';
        Recv_msg[0] = '@';
        Recv_msg[6] = '@';
        str_len = strlen(Recv_msg);
        pToken = strtok(Recv_msg, "@");

        int i = 0;
        while (pToken != NULL)
        {
          pArray[i] = pToken;
          Serial.print(i);
          Serial.print(" = ");
          Serial.println(pToken);

          if (++i > 5)
            break;
          pToken = strtok(NULL, "@");
        }
        Serial.println(pArray[0]);

        if (strcmp(pArray[0], "admin") == 0)
        {
          flow = 1;
        }
        else if (strcmp(pArray[0], "block") == 0)
        {
          Serial.println("receive from block");
          car_info[1] = String(pArray[1]);
          car_info[2] = String(pArray[2]);
          car_info[3] = String(pArray[3]);


          if (car_info[1].toInt() == 1)
          {
            flow = 2;
          }
          else if (car_info[1].toInt() == 0)
          {
            flow = 3;
          }
        }

        else if (strcmp(pArray[0], "Jets1") == 0)
        {
          Serial.println(pArray[1]);
          if (strcmp(pArray[1], "5") == 0)
          {
            flow = 4;
          }
          else if (strcmp(pArray[1], "7") == 0)
          {
            flow = 5;
          }
          else if (strcmp(pArray[1], "8") == 0)
          {
            flow = 6;
          }
        }
        fflush(stdout);
      }
    }
    if (flow == 1)
    {
      char sendJetson[50];
      sprintf(sendJetson, "%s@%s@%sL", car_info[1], car_info[2], car_info[3]);
      MsgSend_Jet(sendJetson);
      flow = 2;
    }

    else if (flow == 2) { // 차가 들어왔을 때
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
      int dis = pulseIn(echo, HIGH) * 340 / 2 / 10000;

      if (dis <= 18 && dis != 0)
      {
        if (InOutState == 1)
        {
          digitalWrite(14, HIGH);

          MsgSend_adm(1);
          delay(100);

          InOutState = 2;
          delay(10);
        }
        else if (InOutState == 2) {
          digitalWrite(14, HIGH);
          if (digitalRead( Button ) == HIGH) {
            char sendJetson[50];
            sprintf(sendJetson, "%s@%s@%sL", car_info[1], car_info[2], car_info[3]);
            Serial.println(sendJetson);
            MsgSend_Jet(sendJetson);
            InOutState = 0;
          }
        }

      }
      else if (dis > 18) {
        if (InOutState == 0 or InOutState == 2)
        {
          MsgSend_adm(0);
          delay(10);
          //MsgSend_Jet("0");
          InOutState = 1;
          flow = 2;
        }
        if (led_status == false) {
          digitalWrite(14, HIGH);
        }
        else {
          digitalWrite(14, LOW);
        }
        led_status = !led_status;
        delay(1000);
      }
    }

    else if (flow == 3) {
      digitalWrite(14, LOW);
    }
    else if (flow == 4) {
      recharge = 1;
    }
    else if (flow == 5) {
      spin_up();
      flow = 2;
    }
    else if (flow == 6) {
      spin_down();
      flow = 2;
    }

    Recv_msg[index] = '\0';
    if (recharge == 1) {
      ori_RechargeVal = analogRead(A0);
      cur_RechargeVal = map(ori_RechargeVal, 0, 1023, 0, 100);
      if (cur_RechargeVal != pre_RechargeVal)
      {
        sprintf(SendMsgData, "[admin] %d@\n", cur_RechargeVal);
        client.print(SendMsgData);
        pre_RechargeVal = cur_RechargeVal;
        delay(100);
      }
      if (cur_RechargeVal == 100)
      {
        MsgSend_Jet("6@");
        recharge = 0;
        flow = 2;
      }
    }
    delay(10);
  }
}
