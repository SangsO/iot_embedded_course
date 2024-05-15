

void spin_up() {
  int temp;
  for (int i = 0; i < steps; i++) {
    temp = i % 4;
    digitalWrite(pinArray[0], bitRead(CW[temp], 0));
    digitalWrite(pinArray[1], bitRead(CW[temp], 1));
    digitalWrite(pinArray[2], bitRead(CW[temp], 2));
    digitalWrite(pinArray[3], bitRead(CW[temp], 3));
    delay(3);
  }
}
void spin_down() {
  int temp;
  for (int i = 0; i < steps; i++) {
    temp = i % 4;
    digitalWrite(pinArray[0], bitRead(CCW[temp], 0));
    digitalWrite(pinArray[1], bitRead(CCW[temp], 1));
    digitalWrite(pinArray[2], bitRead(CCW[temp], 2));
    digitalWrite(pinArray[3], bitRead(CCW[temp], 3));

    delay(3);
  }
}
