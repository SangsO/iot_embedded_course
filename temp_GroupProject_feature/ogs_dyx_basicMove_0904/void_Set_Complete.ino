/*

  #include <DynamixelWorkbench.h>
  #include <ros.h>             //로스 헤더
  #include <std_msgs/String.h> //스트링 메세지(로스 통신 원형 지정)
  #include <sstream>
  using namespace std;
  //#define x_line 0.13
  //#define y_line 0

  void Set_Complete () {

  int length_1 = 0.1 ; //ID[2] - ID[7] 사이의 길이
  int length_2 = 0;

  int get_x = 5;
  int get_y = 5;

  //int i = 0;
  float length_1_theta = 0;
  float ceta_move = 0;

  if (get_x != NULL) {
    float length_1_theta = asin(get_x / length_1);

    for (int i = 0; i < length_1_theta; i++)
    {
      dxl_wb.goalPosition(id_list[[0], (int32_t)Degree(180 - 2 * i));
      delay(100);
    }
    for (int i = 0; i < length_1_theta; i++)
    {
      move_horn(0, (180 + length_1_theta), 1000, &log);
    }
  }
}
*/
