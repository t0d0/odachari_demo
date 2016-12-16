void MODE_Select(void) {
  if (cadence <= RPM(10)) { //ケイデンス10以上
    if (brake == 0 || wheel_speed <= SPEED(stop_speed)) {
      if (angle > ((-1) * downhill_border) && angle < uphill_border) {
        if (wheel_speed <= SPEED(flat_speed_border)) {//平地のモード判定
          Mode = 1;
          return;//平地巡航モード
        }
        else {
          Mode = 2;
          return;//平地加速モード
        }
      }
      else if (angle >= uphill_border) {
        if (wheel_speed <= SPEED(uphill_speed_border)) {//登坂のモード判定
          Mode = 3;
          return;//登坂巡航モード
        }
        else {
          Mode = 4;
          return;//登坂加速モード
        }
      }

      else {
        Mode = 5;//下りモード
        return;
      }
    }

    else {
      Mode = 6;
      return;//停止モード    
    }
  }
  else {
    Mode = 7;
    return;//空転モード
  }
  return;
}
