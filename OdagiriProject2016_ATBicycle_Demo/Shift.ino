void MT_UP() {
  if (millis() - beforemills_chat1 >= 350) {
    SerialUSB.println("mtdown");

    beforemills_chat1 = millis();
    stop_time = millis();
    if (Gear_Pos < gear_steps)Gear_Pos += 1;
    beforemills_chat1 = millis();
  }
}
void MT_DOWN() {
  if (millis() - beforemills_chat2 >= 350) {
    SerialUSB.println("mtup");
    beforemills_chat2 = millis();
    stop_time = millis();
    if (Gear_Pos > 1)Gear_Pos -= 1;
  }
}


