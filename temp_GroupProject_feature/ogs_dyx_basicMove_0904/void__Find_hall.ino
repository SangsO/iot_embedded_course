void Find_hall() {
  const char *log;
  int connecterTy;

  //**************************************************************************************************************//
  // 초기 각 설정                                                                                                   //
  //**************************************************************************************************************//
  dxl_wb.goalPosition(id_list[0], (int32_t)Degree(180));
  dxl_wb.goalPosition(id_list[1], (int32_t)Degree(270));
  dxl_wb.goalPosition(id_list[2], (int32_t)Degree(270));
  dxl_wb.goalPosition(id_list[3], (int32_t)Degree(180));

  //초기상태 지정....//

  move_horn(0, 180, 1000, &log);
  move_horn(1, 180, 1000, &log);

  Serial.printf("Baisc Postion Setting FINISH");

  connecterTy = 2; //(1번 차종일 경우)

  //**************************************************************************************************************//
  // 충전기 커넥터 결정                                                                                              //
  //**************************************************************************************************************//
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
    move_horn(0, 215, 1000, &log);
    move_horn(1, 145, 1000, &log);
    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(215));

    delay(1000);

    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(270));
    delay(300);
    move_horn(1, 180, 1000, &log);
    move_horn(0, 180, 1000, &log);
  } //electric car connecter type 2
  else if (connecterTy == 3) {
    move_horn(0, 215, 1000, &log);
    move_horn(1, 145, 1000, &log);
    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(215));

    delay(1000);

    dxl_wb.goalPosition(id_list[2], (int32_t)Degree(270));
    delay(300);
    move_horn(1, 180, 1000, &log);
    move_horn(0, 180, 1000, &log);
  } //electric car connecter type 3

  //**************************************************************************************************************//
  // (충전기 기준)우측, 커넥터 2..._move start                                                                        //
  //**************************************************************************************************************//
  if (connecterTy == 2) {
    //dxl_wb.goalPosition(id_list[0], (int32_t)Degree(360)); //왼쪽으로 1번 1축 move
    Serial.printf("For LOOP START");
    for (int i = 0; i < 180; i++) {
      dxl_wb.goalPosition(id_list[0], (int32_t)Degree(180 + 2 * i));
      delay(100);
    }
    delay(1000);

    //dxl_wb.goalPosition(id_list[0], (int32_t)Degree(315));
    for (int i = 0 ; i < 45; i++) {
      dxl_wb.goalPosition(id_list[0], (int32_t)Degree(180 - 2 * i));
      delay(100);
    }
    delay(1000);

    move_horn(0, 215, 1000, &log);

    //for(int i =0 ; i<45; i++){
    //  dxl_wb.goalPosition(id_list[0], (int32_t)Degree(360-i));
    //  delay(100);
    //}

    //dxl_wb.goalPosition(id_list[2], (int32_t)Degree(180));
    for (int i = 0 ; i < 90; i++) {
      dxl_wb.goalPosition(id_list[2], (int32_t)Degree(270 - 2 * i));
      delay(100);
    }

    delay(1000);
    //dxl_wb.goalPosition(id_list[3], (int32_t)Degree(0));
    for (int i = 0 ; i < 180; i++) {
      dxl_wb.goalPosition(id_list[3], (int32_t)Degree(360 - 2 * i));
      delay(100);
    }
    delay(1000);
  }

  if (connecterTy == 3) {
    //dxl_wb.goalPosition(id_list[0], (int32_t)Degree(360)); //왼쪽으로 1번 1축 move
    Serial.printf("For LOOP START");
    for (int i = 0; i < 180; i++) {
      dxl_wb.goalPosition(id_list[0], (int32_t)Degree(180 + 2 * i));
      delay(100);
    }
    delay(1000);

    //dxl_wb.goalPosition(id_list[0], (int32_t)Degree(315));
    for (int i = 0 ; i < 45; i++) {
      dxl_wb.goalPosition(id_list[0], (int32_t)Degree(360 - 2 * i));
      delay(100);
    }
    delay(1000);

    move_horn(0, 215, 1000, &log);

    //for(int i =0 ; i<45; i++){
    //  dxl_wb.goalPosition(id_list[0], (int32_t)Degree(360-i));
    //  delay(100);
    //}

    //dxl_wb.goalPosition(id_list[2], (int32_t)Degree(180));
    for (int i = 0 ; i < 90; i++) {
      dxl_wb.goalPosition(id_list[2], (int32_t)Degree(270 - 2 * i));
      delay(100);
    }

    delay(1000);
    //dxl_wb.goalPosition(id_list[3], (int32_t)Degree(0));
    for (int i = 0 ; i < 180; i++) {
      dxl_wb.goalPosition(id_list[3], (int32_t)Degree(360 - 2 * i));
      delay(100);
    }
    delay(1000);
  }
}
