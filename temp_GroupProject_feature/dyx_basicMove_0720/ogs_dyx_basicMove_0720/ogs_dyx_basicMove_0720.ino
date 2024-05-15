#include <DynamixelWorkbench.h>
#include <ros.h>             //로스 헤더
#include <std_msgs/String.h> //스트링 메세지(로스 통신 원형 지정)
#include <sstream>
using namespace std;

#if defined(__OPENCM904__)
  #define DEVICE_NAME "1" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__) //opencr 보드 선언
  #define DEVICE_NAME ""
#endif  

#define BAUDRATE  1000000 //10만(다이나믹셀이 모드 해당 Baudrate)

DynamixelWorkbench dxl_wb;

uint8_t id_list[4]= {1,2,3,4};        //일반(1축)
uint8_t id_list_2horn[2] = {7,8};     //2축은 2horn
bool result = false;

ros::NodeHandle  nh;
std_msgs::String str_msg;                      //보내는애
ros::Publisher Position("Position", &str_msg); //보내는애 토픽 이름 = position -> 내용 위에 있는 msg

void DLX_Set();
void Horn2_DLX_Set();

void setup() 
{
  Serial.begin(115200);
  while(!Serial); // Wait for Opening Serial Monitor

  nh.initNode();         //ROS
  nh.advertise(Position);//ROS
  DLX_Set();    //초기화 함수
}

void loop() 
{
  //if(receiveData == 1)
  //{
  Find_hall();
  //}
  //nh.spinOnce();  
}
/*
//2축 이슈?
->예제파일
1)workbench : 개발 중단
조인트모드->해제->다시 반복.... 두개 하 번에 못움직인다(사실상 2축 아닌거같이 동작)
2)sdk(protocol using) ->  개발지속
*/
