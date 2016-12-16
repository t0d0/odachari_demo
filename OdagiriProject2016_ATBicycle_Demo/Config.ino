void writeConfig(int addr) {
  byte configTable[DATA_NUM];
  byte softbuff = 0;
  byte data;
  int ans = 255;
  int count = 0;

  while (1) {
    if (SerialUSB.available() > 0) {
      int buf = SerialUSB.read();
      //      data = Se
      //      serialFlush();
      if (buf != -1) {
        data = (byte)buf;
        if (data == softbuff) {
          SerialUSB.write(ans);
          configTable[count] = data;
          //        delay(100);
                  serialFlush();
          softbuff = 0;
          count++;
          if(data == 15){
            pinMode(13,OUTPUT);
            digitalWrite(13,HIGH);
          }//test用
        }
        else {
//          SerialUSB.write(byte(0));
          softbuff = data;
        }
      }
//      delay(100);
    }
    if (count == DATA_NUM) break;
  }

  Wire.beginTransmission(EPR_ADDR);
  Wire.write(highByte(addr));
  Wire.write(lowByte(addr));
  Wire.write(configTable, DATA_NUM);
  Wire.endTransmission();
  delay(5);
//
///  return;
}

void readConfig(int addr) {
  
  Wire.beginTransmission(EPR_ADDR);
  Wire.write(highByte(addr));
  Wire.write(lowByte(addr));
  Wire.endTransmission();
  Wire.requestFrom(EPR_ADDR, DATA_NUM);
  
  uphill_border = Wire.read();
  downhill_border = Wire.read();
  gear_steps = Wire.read();
  flat_accell_gear_up = Wire.read();
  flat_accell_gear_down = Wire.read();
  flat_cruise_gear_up = Wire.read();
  flat_cruise_gear_down = Wire.read();
  uphill_accell_gear_up = Wire.read();
  uphill_accell_gear_down = Wire.read();
  uphill_cruise_gear_up = Wire.read();
  uphill_cruise_gear_down = Wire.read();
  downhill_gear_up = Wire.read();
  downhill_gear_down = Wire.read();
  stop_speed = Wire.read();
  
  return;
}

void serialFlush() {
  while (SerialUSB.available() > 0) {
    char t = SerialUSB.read();
  }
}

void debugConfig() {
  SerialUSB.print("uphill_border = "); SerialUSB.println(uphill_border);
  SerialUSB.print("downhill_border = "); SerialUSB.println(downhill_border);
  SerialUSB.print("gear_steps = "); SerialUSB.println(gear_steps);
  SerialUSB.print("flat_accell_gear_up = "); SerialUSB.println(flat_accell_gear_up);
  SerialUSB.print("flat_accell_gear_down = "); SerialUSB.println(flat_accell_gear_down);
  SerialUSB.print("flat_cruise_gear_up = "); SerialUSB.println(flat_cruise_gear_up);
  SerialUSB.print("flat_cruise_gear_down = "); SerialUSB.println(flat_cruise_gear_down);
  SerialUSB.print("uphill_accell_gear_up = "); SerialUSB.println(uphill_accell_gear_up);
  SerialUSB.print("uphill_accell_gear_down = "); SerialUSB.println(uphill_accell_gear_down);
  SerialUSB.print("uphill_cruise_gear_up = "); SerialUSB.println(uphill_cruise_gear_up);
  SerialUSB.print("uphill_cruise_gear_down = "); SerialUSB.println(uphill_cruise_gear_down);
  SerialUSB.print("downhill_gear_up = "); SerialUSB.println(downhill_gear_up);
  SerialUSB.print("downhill_gear_down = "); SerialUSB.println(downhill_gear_down);
  SerialUSB.print("stop_speed = "); SerialUSB.println(stop_speed);
}
