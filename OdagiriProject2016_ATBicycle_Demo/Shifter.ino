
//しきい値判断
int SHIFTER(void) {
  //      Serial.println(Gear_Pos);

  switch (Mode) {
    case 1://平地巡航
      if (cadence <= RPM(flat_cruise_gear_up)) {
        return (-1);
      }
      else if (cadence >= RPM(flat_cruise_gear_down)) {
        return (1);
      }
      else {
        return (0);
      }
      break;
    case 2://平地加速
      if (cadence <= RPM(flat_accell_gear_up)) {
        return (-1);
      }
      else if (cadence >= RPM(flat_accell_gear_down)) {
        return (1);
      }
      else {
        return (0);
      }
      break;

    case 3://登坂巡航
      if (cadence <= RPM(uphill_cruise_gear_up)) {
        return (-1);
      }
      else if (cadence >= RPM(uphill_cruise_gear_down)) {
        return (1);
      }
      else {
        return (0);
      }
      break;

    case 4://登坂加速
      if (cadence <= RPM(uphill_accell_gear_up)) {
        return (-1);
      }
      else if (cadence >= RPM(uphill_accell_gear_down)) {
        return (1);
      }
      else {
        return (0);
      }
      break;

    case 5://下り
      if (cadence <= RPM(downhill_gear_up)) {
        return (-1);
      }
      else if (cadence >= RPM(downhill_gear_down)) {
        return (1);
      }
      else {
        return (0);
      }
      break;

    case 6://停止
      return (-100);
      break;
    case 7://空転
      return (0);
      break;
    default:
      return (0);
      break;
  }
  //    if(cadence>=500)return -1;
  //    if(cadence<=499)return 1;
  //    Serial.println(Gear_Pos);
  return 0;
}

//  int SHIFTER(void){
//  //      Serial.println(Gear_Pos);
//
//      switch (Mode) {
//          case 1://平地巡航
//              if(cadence<=RPM(97)){//97
//                  return(1);
//              }
//              else if(cadence>=RPM(83)){//83
//                  return(-1);
//              }
//              else{
//                  return(0);
//              }
//              break;
//          case 2://平地加速
//              if(cadence<=RPM(90)){//90rpm
//                  return(1);
//              }
//              else if(cadence>=RPM(75)){//75rpm
//                  return(-1);
//              }
//              else{
//                  return(0);
//              }
//              break;
//          case 6://停止
//              return(-100);
//              break;
//          case 7://空転
//              return(0);
//              break;
//          default:
//              return(0);
//              break;
//      }
//  //    if(cadence>=500)return -1;
//  //    if(cadence<=499)return 1;
//  //    Serial.println(Gear_Pos);
//      return 0;
//  }
//
//
//