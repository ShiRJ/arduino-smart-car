#include <Arduino.h>
#line 1 "d:\\Codefields\\arduino-smart-car\\firmware\\SmartMKcar\\SmartMKcar.ino"
#include <math.h>
#include "PS2X_lib.h" //for v1.6
#define unsigned int u16
#define signed char u8
#define PS2_DAT 13 // connect to the data pin of PS2 controller
#define PS2_CMD 11 // connect to the command pin of PS2 controller
#define PS2_SEL 10 // connect to the select pin of PS2 controller
#define PS2_CLK 12 // connect to the clock pin of PS2 controller
#define Motor_IN1 8  // Motor1 Direction FR
#define Motor_IN2 7  // Motor1 Direction
#define Motor_IN3 2  // Motor2 Direction FL
#define Motor_IN4 4  // Motor2 Direction
#define Motor_IN5 14 // Motor3 Direction BR
#define Motor_IN6 15 // Motor3 Direction
#define Motor_IN7 17 // Motor4 Direction BL
#define Motor_IN8 16 // Motor4 Direction
#define Motor_ENA 9  // Motor1 Speed
#define Motor_ENB 6  // Motor2 Speed
#define Motor_ENC 5  // Motor3 Speed
#define Motor_END 3  // Motor4 Speed
// #define pressures   true
#define pressures false
// #define rumble true
#define rumble false

// pwm settings
int VA;
int VB;
int VC;
int VD;
int VX;
int VY;
int VW;
u16 VALL = 255;
int count = 10;
int ctr_mode = 1;
const float K = 0.5;
const float L = 0.9;
const float u = 180;

PS2X ps2x; // create PS2 Controller Class
int error = 0;
byte type = 0;
byte vibrate = 0x00;

void SPEED_SETTING(char A, char B, char C, char D); // 设置速度
void FRONTWARD(char VALL);                          // 小车向前运动
void BACKWARD(char VALL);                           // 小车向后运动
void LEFTWARD(char VALL);                           // 小车向左运动
void RIGHTWARD(char VALL);                          // 小车向右运动
void LEFT_FRONTWARD(char VALL);                     // 小车向左前运动
void LEFT_BACKWARD(char VALL);                      // 小车向左后运动
void RIGHT_FRONTWARD(char VALL);                    // 小车向右前运动
void RIGHT_BACKWARD(char VALL);                     // 小车向右后运动
void RIGHT_TURNAROUND(char VALL);                   // 小车原地向右转
void LEFT_TURNAROUND(char VALL);                    // 小车原地向左转

void STOP(); // 小车停止
void demo(); // 小车运动示例
#line 60 "d:\\Codefields\\arduino-smart-car\\firmware\\SmartMKcar\\SmartMKcar.ino"
void setup();
#line 113 "d:\\Codefields\\arduino-smart-car\\firmware\\SmartMKcar\\SmartMKcar.ino"
void loop();
#line 60 "d:\\Codefields\\arduino-smart-car\\firmware\\SmartMKcar\\SmartMKcar.ino"
void setup()
{
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
    Serial.begin(57600);
    delay(300);

    while (count > 0)
    {
        count--;
        error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
        if (error == 0)
        {
            Serial.println("Found Controller, configured successful");
            break;
        }
        else if (error == 1)
            Serial.println("No controller found, check wiring.");
        else if (error == 2)
            Serial.println("Controller found but not accepting commands.");
        else if (error == 3)
            Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

        delay(100);
    }
    type = ps2x.readType();
    switch (type)
    {
    case 0:
        Serial.print("Unknown Controller type found ");
        break;
    case 1:
        Serial.print("DualShock Controller found ");
        break;
    case 2:
        Serial.print("GuitarHero Controller found ");
        break;
    case 3:
        Serial.print("Wireless Sony DualShock Controller found ");
        break;
    }
}

void loop()
{
    if (error == 1) // skip loop if no controller found
        return;

    if (type == 2)
    {
        Serial.print("Type Error");
    }
    else
    { // DualShock Controller
        ps2x.read_gamepad(false, vibrate);
        VX = ps2x.Analog(PSS_LX) - 127;
        VY = -(ps2x.Analog(PSS_LY) - 128);
        VW = -(ps2x.Analog(PSS_RX) - 128);
        VA = (int)(L * (VY - VX + K * VW));
        VB = (int)(L * (VY + VX - K * VW));
        VC = (int)(L * (VY + VX + K * VW));
        VD = (int)(L * (VY - VX - K * VW));
        if (ps2x.Button(PSB_CROSS))
        { // print stick values if either is TRUE
            Serial.print("Stick Values:\n");
            Serial.println(VX, DEC);
            Serial.println(VY, DEC);
            Serial.println(VW, DEC);
            Serial.print("MOD:\n");
            Serial.println(ctr_mode, DEC);
            Serial.print("SPEED:\n");
            Serial.println(VA, DEC);
            Serial.println(VB, DEC);
            Serial.println(VC, DEC);
            Serial.println(VD, DEC);
        }

        if ((VX == 0 || VX == 1) && (VY == 0 || VY == 1) && (VW == 0 || VW == 1))
        {
            if (ctr_mode == 0)
                STOP();
            ctr_mode = 1;
        }
        else
        {
            ctr_mode = 0;
        }

        if (ctr_mode == 0)
        {
            if (VA > 0)
            {
                digitalWrite(Motor_IN1, LOW);
                digitalWrite(Motor_IN2, HIGH);
            }
            else
            {
                digitalWrite(Motor_IN1, HIGH);
                digitalWrite(Motor_IN2, LOW);
                VA = -VA;
            }

            if (VB > 0)
            {
                digitalWrite(Motor_IN3, LOW);
                digitalWrite(Motor_IN4, HIGH);
            }
            else
            {
                digitalWrite(Motor_IN3, HIGH);
                digitalWrite(Motor_IN4, LOW);
                VB = -VB;
            }

            if (VC > 0)
            {
                digitalWrite(Motor_IN5, LOW);
                digitalWrite(Motor_IN6, HIGH);
            }
            else
            {
                digitalWrite(Motor_IN5, HIGH);
                digitalWrite(Motor_IN6, LOW);
                VC = -VC;
            }

            if (VD > 0)
            {
                digitalWrite(Motor_IN7, LOW);
                digitalWrite(Motor_IN8, HIGH);
            }
            else
            {
                digitalWrite(Motor_IN7, HIGH);
                digitalWrite(Motor_IN8, LOW);
                VD = -VD;
            }
            SPEED_SETTING(255, 255, 255, 255);
            delay(10);
            SPEED_SETTING(VA+15, VB+35, VC, VD);
        }

        if (ctr_mode == 1)
        {
            if (ps2x.ButtonPressed(PSB_PAD_UP))
            {
                FRONTWARD(0);
                SPEED_SETTING(210, 255, 210, 210);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_PAD_RIGHT))
            {
                RIGHTWARD(0);
                SPEED_SETTING(210, 255, 210, 210);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_PAD_LEFT))
            {
                LEFTWARD(0);
                SPEED_SETTING(210, 255, 210, 210);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_PAD_DOWN))
            {
                BACKWARD(0);
                SPEED_SETTING(210, 255, 210, 210);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_L2))
            {
                LEFT_FRONTWARD(0);
                SPEED_SETTING(210, 0, 0, 230);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_R2))
            {
                RIGHT_FRONTWARD(0);
                SPEED_SETTING(0, 255, 210, 0);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_L1))
            {
                LEFT_BACKWARD(0);
                SPEED_SETTING(0, 255, 210, 0);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_R1))
            {
                RIGHT_BACKWARD(0);
                SPEED_SETTING(210, 0, 0, 230);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_SQUARE))
            {
                LEFT_TURNAROUND(VALL);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_CIRCLE))
            {
                RIGHT_TURNAROUND(VALL);
                vibrate = 0x10;
            }
            if (ps2x.ButtonPressed(PSB_START))
            {
                demo();
            }

            if (ps2x.ButtonReleased(PSB_PAD_UP))
            {
                STOP();
                vibrate = 0x00;
            }
            if (ps2x.ButtonReleased(PSB_PAD_RIGHT))
            {
                STOP();
                vibrate = 0x00;
            }
            if (ps2x.ButtonReleased(PSB_PAD_LEFT))
            {
                STOP();
                vibrate = 0x00;
            }
            if (ps2x.ButtonReleased(PSB_PAD_DOWN))
            {
                STOP();
                vibrate = 0x00;
            }
            if (ps2x.ButtonReleased(PSB_L2))
            {
                STOP();
                vibrate = 0x00;
            }
            if (ps2x.ButtonReleased(PSB_R2))
            {
                STOP();
                vibrate = 0x00;
            }
            if (ps2x.ButtonReleased(PSB_L1))
            {
                STOP();
                vibrate = 0x00;
            }
            if (ps2x.ButtonReleased(PSB_R1))
            {
                STOP();
                vibrate = 0x00;
            }
            if (ps2x.ButtonReleased(PSB_SQUARE))
            {
                STOP();
                vibrate = 0x00;
            }
            if (ps2x.ButtonReleased(PSB_CIRCLE))
            {
                STOP();
                vibrate = 0x00;
            }
        }
    }
    delay(50);
}

void SPEED_SETTING(char A, char B, char C, char D)
{
    analogWrite(Motor_ENA, A);
    analogWrite(Motor_ENB, B);
    analogWrite(Motor_ENC, C);
    analogWrite(Motor_END, D);
}

// 小车向前运动
void FRONTWARD(char VALL)
{
    // 右前轮向前运动
    digitalWrite(Motor_IN1, LOW);
    digitalWrite(Motor_IN2, HIGH);
    analogWrite(Motor_ENA, VALL);
    // 左前轮向前运动
    digitalWrite(Motor_IN3, LOW);
    digitalWrite(Motor_IN4, HIGH);
    analogWrite(Motor_ENB, VALL);
    // 右后轮向前运动
    digitalWrite(Motor_IN5, LOW);
    digitalWrite(Motor_IN6, HIGH);
    analogWrite(Motor_ENC, VALL);
    // 左后轮向前运动
    digitalWrite(Motor_IN7, LOW);
    digitalWrite(Motor_IN8, HIGH);
    analogWrite(Motor_END, VALL);
}

// 小车向后运动
void BACKWARD(char VALL)
{
    // 右前轮向后运动
    digitalWrite(Motor_IN1, HIGH);
    digitalWrite(Motor_IN2, LOW);
    analogWrite(Motor_ENA, VALL);
    // 左前轮向后运动
    digitalWrite(Motor_IN3, HIGH);
    digitalWrite(Motor_IN4, LOW);
    analogWrite(Motor_ENB, VALL);
    // 右后轮向后运动
    digitalWrite(Motor_IN5, HIGH);
    digitalWrite(Motor_IN6, LOW);
    analogWrite(Motor_ENC, VALL);
    // 左后轮向后运动
    digitalWrite(Motor_IN7, HIGH);
    digitalWrite(Motor_IN8, LOW);
    analogWrite(Motor_END, VALL);
}

// 小车向左运动
void LEFTWARD(char VALL)
{
    // 左前轮向后运动
    digitalWrite(Motor_IN3, HIGH);
    digitalWrite(Motor_IN4, LOW);
    analogWrite(Motor_ENB, VALL);
    // 左后轮向前运动
    digitalWrite(Motor_IN7, LOW);
    digitalWrite(Motor_IN8, HIGH);
    analogWrite(Motor_END, VALL);
    // 右前轮向前运动
    digitalWrite(Motor_IN1, LOW);
    digitalWrite(Motor_IN2, HIGH);
    analogWrite(Motor_ENA, VALL);
    // 右后轮向后运动
    digitalWrite(Motor_IN5, HIGH);
    digitalWrite(Motor_IN6, LOW);
    analogWrite(Motor_ENC, VALL);
}

// 小车向右运动
void RIGHTWARD(char VALL)
{
    // 右前轮向后运动
    digitalWrite(Motor_IN1, HIGH);
    digitalWrite(Motor_IN2, LOW);
    analogWrite(Motor_ENA, VALL);
    // 右后轮向前运动
    digitalWrite(Motor_IN5, LOW);
    digitalWrite(Motor_IN6, HIGH);
    analogWrite(Motor_ENC, VALL);
    // 左前轮向前运动
    digitalWrite(Motor_IN3, LOW);
    digitalWrite(Motor_IN4, HIGH);
    analogWrite(Motor_ENB, VALL);
    // 左后轮向后运动
    digitalWrite(Motor_IN7, HIGH);
    digitalWrite(Motor_IN8, LOW);
    analogWrite(Motor_END, VALL);
}

// 小车向左前运动
void LEFT_FRONTWARD(char VALL)
{
    // 右前轮向前运动
    digitalWrite(Motor_IN1, LOW);
    digitalWrite(Motor_IN2, HIGH);
    analogWrite(Motor_ENA, VALL);
    // 左后轮向前运动
    digitalWrite(Motor_IN7, LOW);
    digitalWrite(Motor_IN8, HIGH);
    analogWrite(Motor_END, VALL);
    // 右后轮静止
    digitalWrite(Motor_IN5, LOW);
    digitalWrite(Motor_IN6, LOW);
    analogWrite(Motor_ENC, VALL);
    // 左前轮静止
    digitalWrite(Motor_IN3, LOW);
    digitalWrite(Motor_IN4, LOW);
    analogWrite(Motor_ENB, VALL);
}

// 小车向左后运动
void LEFT_BACKWARD(char VALL)
{
    // 左前轮向后运动
    digitalWrite(Motor_IN3, HIGH);
    digitalWrite(Motor_IN4, LOW);
    analogWrite(Motor_ENB, VALL);
    // 右后轮向后运动
    digitalWrite(Motor_IN5, HIGH);
    digitalWrite(Motor_IN6, LOW);
    analogWrite(Motor_ENC, VALL);
    // 右前轮静止
    digitalWrite(Motor_IN1, LOW);
    digitalWrite(Motor_IN2, LOW);
    analogWrite(Motor_ENA, VALL);
    // 左后轮精止
    digitalWrite(Motor_IN7, LOW);
    digitalWrite(Motor_IN8, LOW);
    analogWrite(Motor_END, VALL);
}

// 小车向右前运动
void RIGHT_FRONTWARD(char VALL)
{
    // 左前轮向前运动
    digitalWrite(Motor_IN3, LOW);
    digitalWrite(Motor_IN4, HIGH);
    analogWrite(Motor_ENB, VALL);
    // 右后轮向前运动
    digitalWrite(Motor_IN5, LOW);
    digitalWrite(Motor_IN6, HIGH);
    analogWrite(Motor_ENC, VALL);
    // 左后轮静止
    digitalWrite(Motor_IN7, LOW);
    digitalWrite(Motor_IN8, LOW);
    analogWrite(Motor_END, VALL);
    // 右前轮静止
    digitalWrite(Motor_IN1, LOW);
    digitalWrite(Motor_IN2, LOW);
    analogWrite(Motor_ENA, VALL);
}

// 小车向右后运动
void RIGHT_BACKWARD(char VALL)
{
    // 右前轮向后运动
    digitalWrite(Motor_IN1, HIGH);
    digitalWrite(Motor_IN2, LOW);
    analogWrite(Motor_ENA, VALL);
    // 左后轮向后运动
    digitalWrite(Motor_IN7, HIGH);
    digitalWrite(Motor_IN8, LOW);
    analogWrite(Motor_END, VALL);
    // 右后轮静止
    digitalWrite(Motor_IN5, LOW);
    digitalWrite(Motor_IN6, LOW);
    analogWrite(Motor_ENC, VALL);
    // 左前轮静止
    digitalWrite(Motor_IN3, LOW);
    digitalWrite(Motor_IN4, LOW);
    analogWrite(Motor_ENB, VALL);
}

// 小车原地向右转
void RIGHT_TURNAROUND(char VALL)
{
    // 左前轮向前运动
    digitalWrite(Motor_IN3, LOW);
    digitalWrite(Motor_IN4, HIGH);
    analogWrite(Motor_ENB, VALL);
    // 右前轮向后运动
    digitalWrite(Motor_IN1, HIGH);
    digitalWrite(Motor_IN2, LOW);
    analogWrite(Motor_ENA, VALL);
    // 左后轮向前运动
    digitalWrite(Motor_IN5, HIGH);
    digitalWrite(Motor_IN6, LOW);
    analogWrite(Motor_ENC, VALL);
    // 右后轮向后运动
    digitalWrite(Motor_IN7, LOW);
    digitalWrite(Motor_IN8, HIGH);
    analogWrite(Motor_END, VALL);
}

// 小车原地向左转
void LEFT_TURNAROUND(char VALL)
{
    // 左前轮向后运动
    digitalWrite(Motor_IN3, HIGH);
    digitalWrite(Motor_IN4, LOW);
    analogWrite(Motor_ENB, VALL);
    // 右前轮向前运动
    digitalWrite(Motor_IN1, LOW);
    digitalWrite(Motor_IN2, HIGH);
    analogWrite(Motor_ENA, VALL);
    // 左后轮向后运动
    digitalWrite(Motor_IN5, LOW);
    digitalWrite(Motor_IN6, HIGH);
    analogWrite(Motor_ENC, VALL);
    // 右后轮向前运动
    digitalWrite(Motor_IN7, HIGH);
    digitalWrite(Motor_IN8, LOW);
    analogWrite(Motor_END, VALL);
}

// 小车停止
void STOP()
{
    digitalWrite(Motor_IN1, LOW);
    digitalWrite(Motor_IN2, LOW);
    digitalWrite(Motor_IN7, LOW);
    digitalWrite(Motor_IN8, LOW);
    digitalWrite(Motor_IN5, LOW);
    digitalWrite(Motor_IN6, LOW);
    digitalWrite(Motor_IN3, LOW);
    digitalWrite(Motor_IN4, LOW);
    analogWrite(Motor_ENA, 0);
    analogWrite(Motor_ENB, 0);
    analogWrite(Motor_ENC, 0);
    analogWrite(Motor_END, 0);
}

void demo()
{
    FRONTWARD(0);
    SPEED_SETTING(210, 255, 210, 210);
    delay(2000);
    STOP();
    delay(2000);

    BACKWARD(0);
    SPEED_SETTING(210, 255, 210, 210);
    delay(2000);
    STOP();
    delay(2000);

    LEFTWARD(0);
    SPEED_SETTING(210, 255, 210, 210);
    delay(2000);
    STOP();
    delay(2000);

    RIGHTWARD(0);
    SPEED_SETTING(210, 255, 210, 210);
    delay(2000);
    STOP();
    delay(2000);

    LEFT_FRONTWARD(0);
    SPEED_SETTING(210, 0, 0, 230);
    delay(3000);
    STOP();
    delay(2000);

    RIGHT_FRONTWARD(0);
    SPEED_SETTING(0, 255, 210, 0);
    delay(3000);
    STOP();
    delay(2000);

    RIGHT_BACKWARD(0);
    SPEED_SETTING(210, 0, 0, 230);
    delay(3000);
    STOP();
    delay(2000);

    LEFT_BACKWARD(0);
    SPEED_SETTING(0, 255, 210, 0);
    delay(3000);
    STOP();
    delay(2000);

    RIGHT_TURNAROUND(255);
    delay(3500);
    STOP();
    delay(2000);

    LEFT_TURNAROUND(255);
    delay(3500);
    STOP();
    delay(2000);
}

