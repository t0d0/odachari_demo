#include <Servo.h>
#include <Wire.h>

int constPulse[9] = {1700, 1630, 1530, 1480, 1430, 1380, 1330, 1260, 1200};
bool up_down;//over stroke用
#define manuLPin  1
#define manuRPin  3
#define braLPin   5
#define braRPin   7
#define cadPin    9
#define spePin   11
#define ServoPin 13
#define serialToggle 12

// コンフィグ用
#define EPR_ADDR 0x51  // EEPROM address A2=Low,A1=Low,A0=HIGH
#define DATA_NUM 14 // 扱うデータ個数

int recv_data; //シリアル通信用

int Gear_Pos   = 1;//ギア初期位置
int Before_Pos = 1;
//int gear_steps   = 10;//ギア段数
float Debug_num;

//傾斜周り
int correc[3];
int Output;
int Output_before = 0;
int angle = 0;
int uphill_angle = 10;
int downhill_angle = -10;


int attach_min = 1100;
int attach_max = 1900;

Servo myservo;
int count = 0;
//float wire = 7.9;
//int wire=9
float adjust = 0;
unsigned long beforemills_cad = 0;
unsigned long beforemills_speed   = 0;
unsigned long beforemills_chat1 = 0;
unsigned long beforemills_chat2 = 0;
unsigned long stop_time = 0;
unsigned long shift_start = 0;
unsigned long stoper = 0;
unsigned long shift_once = 0;

//コンフィグ用各種パラメータ
int uphill_border;
int downhill_border;
int gear_steps;
int flat_accell_gear_up;
int flat_accell_gear_down;
int flat_cruise_gear_up;
int flat_cruise_gear_down;
int uphill_accell_gear_up;
int uphill_accell_gear_down;
int uphill_cruise_gear_up;
int uphill_cruise_gear_down;
int downhill_gear_up;
int downhill_gear_down;
int stop_speed;

int flat_speed_border = 25;
int uphill_speed_border = 10;



//unsigned long shift_start = 0;
//int parse = 54;

int cadence = 0;
int wheel_speed = 0;
int brake   = 0;
int Mode    = 7;
//int Stop_Flag = 0;
bool wait_flag = false;
bool over_strokeflag = false;

int tire_size = 2096;
int speed_const;
int cad_const;

boolean shift_up = false;

//関数群
void CHANGE_Gear(void);
void Cadence(void);
void Speed(void);
void Brake(void);
void AT_Shift(int);
void MODE_Select(void);
int SHIFTER(void);
int getGyro(void);
void over_stroke(void);
void reflesh(void);
void AdcBooster()
{
  ADC->CTRLA.bit.ENABLE = 0;                     // Disable ADC
  while( ADC->STATUS.bit.SYNCBUSY == 1 );        // Wait for synchronization
  ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 |   // Divide Clock by 64.
                   ADC_CTRLB_RESSEL_10BIT;       // Result on 10 bits
  ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 |   // 1 sample
                     ADC_AVGCTRL_ADJRES(0x00ul); // Adjusting result by 0
  ADC->SAMPCTRL.reg = 0x00;                      // Sampling Time Length = 0
  ADC->CTRLA.bit.ENABLE = 1;                     // Enable ADC
  while( ADC->STATUS.bit.SYNCBUSY == 1 );        // Wait for synchronization
} // AdcBooster



double SPEED(double);
double RPM(double);



void setup() {
  AdcBooster();
  //割り込みの有効化
  attachInterrupt(manuLPin, MT_UP, RISING); //マニュアルシフトアップ端子
  attachInterrupt(manuRPin, MT_DOWN, RISING); //マニュアルシフトダウン端子

  //pin setting
  pinMode(cadPin, INPUT); //ケイデンス端子
  pinMode(spePin, INPUT); //スピード端子
  pinMode(braRPin, INPUT); //ブレーキ端子1
  pinMode(braLPin, INPUT); //ブレーキ端子2
  pinMode(serialToggle, INPUT); //シリアル通信用ボタン


  //  myservo.write(0);
  SerialUSB.begin(38400);
//  while (!SerialUSB) {
//    ;//serial接続チェック
//  }
  //    MsTimer2::set(5000, reflesh); // 500msごとにオンオフ
  //    MsTimer2::start();

  Wire.begin();       // I2C master
  //  SerialUSB.write((byte)255);
  readConfig(0);
  acc_init(correc);
//  debugConfig();
}
void loop() {
  //digitalRead(serialToggle) == HIGH
  while(digitalRead(serialToggle) == HIGH) { //シリアル用のトグルスイッチON
    SerialUSB.println("serial mode");
    writeConfig(0);
  }
  //  Serial.println("test");
  Debug_num =  map(analogRead(A5), 0, 1023, 0, (attach_max - attach_min) / gear_steps); //パルスの最小最大をmin
  //    SerialUSB.println(Debug_num);
  //        SerialUSB.println((int)((Gear_Pos * Debug_num) + attach_min + adjust));
  
  CHANGE_Gear();
  over_stroke();
  Cadence();
  Speed();
  getAngle();

  Brake();

  //    Serial.println(Before_Pos);
//    SerialUSB.println("test");

  if (millis() - stop_time > 200000) { //マニュアル変速があった場合、20秒自動変速停止
    if (millis() - stoper > 300) {
      noInterrupts();//割込み禁止
      MODE_Select();
      AT_Shift(SHIFTER());
      interrupts();//割込み許可
    }
  }
}

