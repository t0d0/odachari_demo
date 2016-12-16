////Soursed by http://www.geocities.jp/zattouka/GarageHouse/micon/Arduino/Acceleration/Acceleration.htm

#define Xpin A0
#define Ypin A1
#define Zpin A2

void acc_init(int data[3]) { //長さ3以上
  //SerialUSB.begin(9600);
  data[0] = analogRead(Xpin);
  data[1] = analogRead(Ypin);
  data[2] = 400; //zには1Gかかっているのでこれだけ事前の測定値
//  SerialUSB.println("test");
//  SerialUSB.println(analogRead(Xpin));
//  SerialUSB.println(data[0]);
}

int acc(int aa,int bb,int cc) {
  long x,y,z;
  int a;
  x = y = z = 0;
  for(int i = 0; i < 10; i++) {
    x = x + analogRead(Xpin);
    y = y + analogRead(Ypin);
    z = z + analogRead(Zpin);
  }
  x = x / 10;
  y = y / 10;
  z = z / 10;  
//  SerialUSB.println("x is " + (String)x);
//  SerialUSB.println("y is " + (String)y);
//  SerialUSB.println("z is " + (String)z);
  
  a=atan2(x-aa,z-cc) / 3.14159 * 180.0 ; //X軸
  return a;
//  SerialUSB.print("X=") ;
//  SerialUSB.print(a) ;             // X軸方向角度表示
//  SerialUSB.print(" Y=") ;
//  a=atan2(y-bb,z-cc) / 3.14159 * 180.0 ;
//  SerialUSB.println(a) ;
//  SerialUSB.print(" Z=") ;
//  a=atan2(z-cc,y-bb) / 3.14159 * 180.0 ;
//  SerialUSB.println(a) ;
  //delay(500);
}
