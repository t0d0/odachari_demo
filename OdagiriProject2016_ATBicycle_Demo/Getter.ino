//speed取得
void Speed(void) {
  if (digitalRead(spePin) == HIGH && millis() - beforemills_speed > 75) {
    wheel_speed = millis() - beforemills_speed;
    beforemills_speed = millis();
//    SerialUSB.print("wheel_speed>");
//    SerialUSB.println(SPEED(wheel_speed));
  }
}

//ケイデンス取得
void Cadence(void) {
  if (digitalRead(cadPin) == HIGH && millis() - beforemills_cad > 300) {
    cadence = millis() - beforemills_cad;
    beforemills_cad = millis();
//    SerialUSB.print("cadence>");
//    SerialUSB.println(cadence);

  }
  else if (millis() - beforemills_cad >= 10000) {
    //どうしよう
  }
}


//ブレーキ取得
void Brake(void) {
  if (digitalRead(braLPin) == HIGH || digitalRead(braRPin) == HIGH) {
    brake = 1;
    SerialUSB.println("Brake");
  }
  else {
    brake = 0;
  }
}
