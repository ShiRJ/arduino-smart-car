#define Motor_FR_IN1 8  // Motor1 Direction FR为右前
#define Motor_FR_IN2 7  // Motor1 Direction
#define Motor_FL_IN3 2  // Motor2 Direction FL为左前
#define Motor_FL_IN4 4  // Motor2 Direction
#define Motor_BR_IN5 14 // Motor3 Direction BR为右后
#define Motor_BR_IN6 15 // Motor3 Direction
#define Motor_BL_IN7 17 // Motor4 Direction BL为左后
#define Motor_BL_IN8 16 // Motor4 Direction
#define Motor_FR_ENA 9  // M SPREED
#define Motor_FL_ENB 6  // M SPREED
#define Motor_BR_ENC 5  // M SPREED
#define Motor_BL_END 3  // M SPREED
// 占空比取值：0~VALL
const int VA;
const int VB;
const int VC;
const int VD;
const int VALL = 255;
// 统一速度
void SPEED_SETTING(char A, char B, char C, char D)
{
  analogWrite(Motor_FR_ENA, A);
  analogWrite(Motor_FL_ENB, B);
  analogWrite(Motor_BR_ENC, C);
  analogWrite(Motor_BL_END, D);
}
// 小车向前运动
void FRONTWARD(char VALL)
{
  // 右前轮向前运动
  digitalWrite(Motor_FR_IN1, LOW);
  digitalWrite(Motor_FR_IN2, HIGH);
  analogWrite(Motor_FR_ENA, VALL);
  // 左前轮向前运动
  digitalWrite(Motor_FL_IN3, LOW);
  digitalWrite(Motor_FL_IN4, HIGH);
  analogWrite(Motor_FL_ENB, VALL);
  // 右后轮向前运动
  digitalWrite(Motor_BR_IN5, LOW);
  digitalWrite(Motor_BR_IN6, HIGH);
  analogWrite(Motor_BR_ENC, VALL);
  // 左后轮向前运动
  digitalWrite(Motor_BL_IN7, LOW);
  digitalWrite(Motor_BL_IN8, HIGH);
  analogWrite(Motor_BL_END, VALL);
}
// 小车向后运动
void BACKWARD(char VALL)
{
  // 右前轮向后运动
  digitalWrite(Motor_FR_IN1, HIGH);
  digitalWrite(Motor_FR_IN2, LOW);
  analogWrite(Motor_FR_ENA, VALL);
  // 左前轮向后运动
  digitalWrite(Motor_FL_IN3, HIGH);
  digitalWrite(Motor_FL_IN4, LOW);
  analogWrite(Motor_FL_ENB, VALL);
  // 右后轮向后运动
  digitalWrite(Motor_BR_IN5, HIGH);
  digitalWrite(Motor_BR_IN6, LOW);
  analogWrite(Motor_BR_ENC, VALL);
  // 左后轮向后运动
  digitalWrite(Motor_BL_IN7, HIGH);
  digitalWrite(Motor_BL_IN8, LOW);
  analogWrite(Motor_BL_END, VALL);
}
// 小车向左运动
void LEFTWARD(char VALL)
{
  // 左前轮向后运动
  digitalWrite(Motor_FL_IN3, HIGH);
  digitalWrite(Motor_FL_IN4, LOW);
  analogWrite(Motor_FL_ENB, VALL);
  // 左后轮向前运动
  digitalWrite(Motor_BL_IN7, LOW);
  digitalWrite(Motor_BL_IN8, HIGH);
  analogWrite(Motor_BL_END, VALL);
  // 右前轮向前运动
  digitalWrite(Motor_FR_IN1, LOW);
  digitalWrite(Motor_FR_IN2, HIGH);
  analogWrite(Motor_FR_ENA, VALL);
  // 右后轮向后运动
  digitalWrite(Motor_BR_IN5, HIGH);
  digitalWrite(Motor_BR_IN6, LOW);
  analogWrite(Motor_BR_ENC, VALL);
}
// 小车向右运动
void RIGHTWARD(char VALL)
{
  // 右前轮向后运动
  digitalWrite(Motor_FR_IN1, HIGH);
  digitalWrite(Motor_FR_IN2, LOW);
  analogWrite(Motor_FR_ENA, VALL);
  // 右后轮向前运动
  digitalWrite(Motor_BR_IN5, LOW);
  digitalWrite(Motor_BR_IN6, HIGH);
  analogWrite(Motor_BR_ENC, VALL);
  // 左前轮向前运动
  digitalWrite(Motor_FL_IN3, LOW);
  digitalWrite(Motor_FL_IN4, HIGH);
  analogWrite(Motor_FL_ENB, VALL);
  // 左后轮向后运动
  digitalWrite(Motor_BL_IN7, HIGH);
  digitalWrite(Motor_BL_IN8, LOW);
  analogWrite(Motor_BL_END, VALL);
}
// 小车向左前运动
void LEFT_FRONTWARD(char VALL)
{
  // 右前轮向前运动
  digitalWrite(Motor_FR_IN1, LOW);
  digitalWrite(Motor_FR_IN2, HIGH);
  analogWrite(Motor_FR_ENA, VALL);
  // 左后轮向前运动
  digitalWrite(Motor_BL_IN7, LOW);
  digitalWrite(Motor_BL_IN8, HIGH);
  analogWrite(Motor_BL_END, VALL);
  // 右后轮静止
  digitalWrite(Motor_BR_IN5, LOW);
  digitalWrite(Motor_BR_IN6, LOW);
  analogWrite(Motor_BR_ENC, VALL);
  // 左前轮静止
  digitalWrite(Motor_FL_IN3, LOW);
  digitalWrite(Motor_FL_IN4, LOW);
  analogWrite(Motor_FL_ENB, VALL);
}
// 小车向左后运动
void LEFT_BACKWARD(char VALL)
{
  // 右前轮向后运动
  digitalWrite(Motor_FR_IN1, HIGH);
  digitalWrite(Motor_FR_IN2, LOW);
  analogWrite(Motor_FR_ENA, VALL);
  // 左后轮向后运动
  digitalWrite(Motor_BL_IN7, HIGH);
  digitalWrite(Motor_BL_IN8, LOW);
  analogWrite(Motor_BL_END, VALL);
  // 右后轮静止
  digitalWrite(Motor_BR_IN5, LOW);
  digitalWrite(Motor_BR_IN6, LOW);
  analogWrite(Motor_BR_ENC, VALL);
  // 左前轮静止
  digitalWrite(Motor_FL_IN3, LOW);
  digitalWrite(Motor_FL_IN4, LOW);
  analogWrite(Motor_FL_ENB, VALL);
}
// 小车向右前运动
void RIGHT_FRONTWARD(char VALL)
{
  // 左前轮向前运动
  digitalWrite(Motor_FL_IN3, LOW);
  digitalWrite(Motor_FL_IN4, HIGH);
  analogWrite(Motor_FL_ENB, VALL);
  // 右后轮向前运动
  digitalWrite(Motor_BR_IN5, LOW);
  digitalWrite(Motor_BR_IN6, HIGH);
  analogWrite(Motor_BR_ENC, VALL);
  // 左后轮静止
  digitalWrite(Motor_BL_IN7, LOW);
  digitalWrite(Motor_BL_IN8, LOW);
  analogWrite(Motor_BL_END, VALL);
  // 右前轮静止
  digitalWrite(Motor_FR_IN1, LOW);
  digitalWrite(Motor_FR_IN2, LOW);
  analogWrite(Motor_FR_ENA, VALL);
}
// 小车向右后运动
void RIGHT_BACKWARD(char VALL)
{
  // 左前轮向后运动
  digitalWrite(Motor_FL_IN3, HIGH);
  digitalWrite(Motor_FL_IN4, LOW);
  analogWrite(Motor_FL_ENB, VALL);
  // 右后轮向后运动
  digitalWrite(Motor_BR_IN5, HIGH);
  digitalWrite(Motor_BR_IN6, LOW);
  analogWrite(Motor_BR_ENC, VALL);
  // 右前轮静止
  digitalWrite(Motor_FR_IN1, LOW);
  digitalWrite(Motor_FR_IN2, LOW);
  analogWrite(Motor_FR_ENA, VALL);
  // 左后轮精止
  digitalWrite(Motor_BL_IN7, LOW);
  digitalWrite(Motor_BL_IN8, LOW);
  analogWrite(Motor_BL_END, VALL);
}
// 小车停止
void STOP()
{
  digitalWrite(Motor_FR_IN1, LOW);
  digitalWrite(Motor_FR_IN2, LOW);
  digitalWrite(Motor_BL_IN7, LOW);
  digitalWrite(Motor_BL_IN8, LOW);
  digitalWrite(Motor_BR_IN5, LOW);
  digitalWrite(Motor_BR_IN6, LOW);
  digitalWrite(Motor_FL_IN3, LOW);
  digitalWrite(Motor_FL_IN4, LOW);
  analogWrite(Motor_FR_ENA, 0);
  analogWrite(Motor_FL_ENB, 0);
  analogWrite(Motor_BR_ENC, 0);
  analogWrite(Motor_BL_END, 0);
}
// 小车原地向右转
void RIGHT_TURNAROUND(char VALL)
{
  // 左前轮向前运动
  digitalWrite(Motor_FL_IN3, LOW);
  digitalWrite(Motor_FL_IN4, HIGH);
  analogWrite(Motor_FL_ENB, VALL);
  // 右前轮向后运动
  digitalWrite(Motor_FR_IN1, HIGH);
  digitalWrite(Motor_FR_IN2, LOW);
  analogWrite(Motor_FR_ENA, VALL);
  // 左后轮向前运动
  digitalWrite(Motor_BR_IN5, LOW);
  digitalWrite(Motor_BR_IN6, HIGH);
  analogWrite(Motor_BR_ENC, VALL);
  // 右后轮向后运动
  digitalWrite(Motor_BR_IN5, HIGH);
  digitalWrite(Motor_BR_IN6, LOW);
  analogWrite(Motor_BR_ENC, VALL);
}
// 小车原地左转
void LEFT_TURNAROUND(char VALL)
{
  // 左前轮向后运动
  digitalWrite(Motor_FL_IN3, HIGH);
  digitalWrite(Motor_FL_IN4, LOW);
  analogWrite(Motor_FL_ENB, VALL);
  // 右前轮向前运动
  digitalWrite(Motor_FR_IN1, LOW);
  digitalWrite(Motor_FR_IN2, HIGH);
  analogWrite(Motor_FR_ENA, VALL);
  // 左后轮向后运动
  digitalWrite(Motor_BR_IN5, HIGH);
  digitalWrite(Motor_BR_IN6, LOW);
  analogWrite(Motor_BR_ENC, VALL);
  // 右后轮向前运动
  digitalWrite(Motor_BR_IN5, LOW);
  digitalWrite(Motor_BR_IN6, HIGH);
  analogWrite(Motor_BR_ENC, VALL);
}
// 将引脚设置为输出模式
void setup()
{
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
}
void loop()
{
  BACKWARD(VALL);
  delay(2000);
  STOP();
  delay(2000);
  FRONTWARD(VALL);
  delay(2000);
  STOP();
  delay(2000);
  LEFTWARD(VALL);
  delay(2000);
  STOP();
  delay(2000);
  RIGHTWARD(VALL);
  delay(2000);
  STOP();
  delay(2000);
  LEFT_FRONTWARD(VALL);
  delay(2000);
  STOP();
  delay(2000);
  LEFT_BACKWARD(VALL);
  delay(2000);
  STOP();
  delay(2000);
  RIGHT_FRONTWARD(VALL);
  delay(2000);
  STOP();
  delay(2000);
  RIGHT_BACKWARD(VALL);
  delay(2000);
  STOP();
  delay(2000);
  RIGHT_TURNAROUND(VALL);
  delay(2000);
  STOP();
  delay(2000);
  LEFT_TURNAROUND(VALL);
  delay(2000);
  STOP();
  delay(2000);
}
