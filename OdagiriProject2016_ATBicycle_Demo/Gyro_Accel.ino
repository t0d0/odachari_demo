
void gyroSetup() {
  // put your setup code here, to run once:
  //gyro_init();
//  SerialUSB.begin(9600);
//  delay(100);
  acc_init(correc);

}

int getAngle() {
  // put your main code here, to run repeatedly:
  int gyro = 0;  
  int accelerate = acc(correc[0],correc[1],correc[2]);
  Output = 0.95 * (Output_before + gyro) + 0.05 * accelerate;
  Output_before = Output;
  angle = Output;
  return(Output);
  //(Output:出力　Output_before:1回前のOutput　gyro:ジャイロセンサで得た角度　
  //accelerate:加速度センサで得た角度)
  
}
