//==================================
// 차종에 따라 충전구 선택 및 자리 선택
//==================================

void Check_Type(int connecterTy) {
  const char *log;


  if (connecterTy == 1) {
    dxl_wb.goalPosition(id_list[0], (int32_t)Degree(180));
    dxl_wb.goalPosition(id_list[1], (int32_t)Degree(270));
    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(270));
    dxl_wb.goalPosition(id_list[3], (int32_t)Degree(180));

    move_horn(0, 180, 1000, &log);
    move_horn(1, 180, 1000, &log);

    Serial.printf("This is Not Electric Car... Wait for Charging");

    //if (connecterTy != 1)
    //break;
  } // type1 -> Not Electric Car
  else if (connecterTy == 2) {

    //============================================================ 충전기 선택
    move_horn(0, 215, 1000, &log);

    dxl_wb.goalPosition(id_list[3], (int32_t)Degree(215));
    delay(500);
    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(215));
    move_horn(1, 145, 1000, &log);
    delay(2000);

    //============================================================ 타입별 충전 초기 포즈

    move_horn(1, 180, 1000, &log);
    dxl_wb.goalPosition(id_list[3], (int32_t)Degree(270));
    delay(300);
    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(270));
    delay(300);

    move_horn(0, 180, 1000, &log);
    delay(500);
    dxl_wb.goalPosition(id_list[0], (int32_t)Degree(90));
    delay(500);
    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(90));
    delay(500);
    dxl_wb.goalPosition(id_list[3], (int32_t)Degree(90));
    delay(500);
  } //electric car connecter type 2
  else if (connecterTy == 3) {    
    //============================================================ 충전기 선택
    move_horn(0, 145, 1000, &log);

    dxl_wb.goalPosition(id_list[3], (int32_t)Degree(215));
    delay(500);
    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(215));
    delay(500);
    move_horn(1, 145, 1000, &log);
    delay(2000);

    //============================================================ 타입별 충전 초기 포즈

    move_horn(1, 180, 1000, &log);
    dxl_wb.goalPosition(id_list[3], (int32_t)Degree(270));
    delay(300);
    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(270));
    delay(300);

    move_horn(0, 180, 1000, &log);
    delay(500);
    dxl_wb.goalPosition(id_list[0], (int32_t)Degree(0));
    delay(500);
    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(90));
    delay(500);
    dxl_wb.goalPosition(id_list[3], (int32_t)Degree(90));
    delay(500);
    
    
    
  } //electric car connecter type 3

}
