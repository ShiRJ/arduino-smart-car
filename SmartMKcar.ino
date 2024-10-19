#include "PS2X_lib.h" //for v1.6
//#include "motor.h"

#define PS2_DAT 13      // connect to the data pin of PS2 controller
#define PS2_CMD 11      // connect to the command pin of PS2 controller
#define PS2_SEL 10      // connect to the select pin of PS2 controller
#define PS2_CLK 12      // connect to the clock pin of PS2 controller
#define Motor_FR_IN1 8  // Motor1 Direction FR为右前
#define Motor_FR_IN2 7  // Motor1 Direction
#define Motor_FL_IN3 2  // Motor2 Direction FL为左前
#define Motor_FL_IN4 4  // Motor2 Direction
#define Motor_BR_IN5 14 // Motor3 Direction BR为右后
#define Motor_BR_IN6 15 // Motor3 Direction
#define Motor_BL_IN7 17 // Motor4 Direction BL为左后
#define Motor_BL_IN8 16 // Motor4 Direction
#define Motor_FR_ENA 9  // M1 SPREED
#define Motor_FL_ENB 6  // M2 SPREED
#define Motor_BR_ENC 5  // M3 SPREED
#define Motor_BL_END 3  // M4 SPREED
//#define pressures   true
#define pressures false
//#define rumble true
#define rumble false

// pwm settings
int VA;
int VB;
int VC;
int VD;
const int VALL = 255;

PS2X ps2x; // create PS2 Controller Class
//Motor mt;
int error = 0;
byte type = 0;
byte vibrate = 0x00;

void setup()
{
    Serial.begin(57600);
    delay(300);
    // setup pins and settings: 
    //GamePad(clock, command, attention, data, Pressures?, Rumble?)
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

    if (error == 0)
    {
        Serial.print("Found Controller, configured successful ");
        Serial.print("pressures = ");
        if (pressures)
            Serial.println("true");
        else
            Serial.println("false");
        Serial.print("rumble = ");
        if (rumble)
            Serial.println("true");
        else
            Serial.println("false");
    }
    else if (error == 1)
        Serial.println("No controller found.");

    else if (error == 2)
        Serial.println("Controller found but not accepting commands.");

    else if (error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

    //  Serial.print(ps2x.Analog(1), HEX);

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
    {// DualShock Controller
        ps2x.read_gamepad(false, vibrate);
        /*if (ps2x.ButtonPressed())
        {
            if (ps2x.Button(PSB_PAD_UP))
            {
                mt.FRONTWARD (VALL);
            }
            if (ps2x.Button(PSB_PAD_RIGHT))
            {
                mt.RIGHTWARD(VALL);
            }
            if (ps2x.Button(PSB_PAD_LEFT))
            {
                mt.LEFTWARD(0);
                mt.SPEED_SETTING(0, 0, 0, 0);
            }
            if (ps2x.Button(PSB_PAD_DOWN))
            {
                mt.BACKWARD(0);
                mt.SPEED_SETTING(0, 0, 0, 0);
            }
            if (ps2x.Button(PSB_L2))
            {
                mt.LEFT_FRONTWARD(VALL);
            }
            if (ps2x.Button(PSB_R2))
            {
                mt.RIGHT_FRONTWARD(VALL);
            }
            if (ps2x.Button(PSB_L1))
            {
                mt.LEFT_BACKWARD(VALL);
            }
            if (ps2x.Button(PSB_R1))
            {
                mt.RIGHT_BACKWARD(VALL);
            }
            if (ps2x.Button(PSB_SQUARE))
            {
                mt.LEFT_TURNAROUND(64);
            }
            if (ps2x.Button(PSB_R1))
            {
                mt.RIGHT_TURNAROUND(64);
            }
            if (ps2x.Button(PSB_START))
            {
                mt.demo();
            }
        }
        if (ps2x.ButtonReleased())
        {
            if (ps2x.Button(PSB_PAD_UP))
            {
                mt.STOP();
            }
            if (ps2x.Button(PSB_PAD_RIGHT))
            {
                mt.STOP();
            }
            if (ps2x.Button(PSB_PAD_LEFT))
            {
                mt.STOP();
            }
            if (ps2x.Button(PSB_PAD_DOWN))
            {
                mt.STOP();
            }
            if (ps2x.Button(PSB_L2))
            {
                mt.STOP();
            }
            if (ps2x.Button(PSB_R2))
            {
                mt.STOP();
            }
            if (ps2x.Button(PSB_L1))
            {
                mt.STOP();
            }
            if (ps2x.Button(PSB_R1))
            {
                mt.STOP();
            }
            if (ps2x.Button(PSB_SQUARE))
            {
                mt.STOP();
            }
            if (ps2x.Button(PSB_R1))
            {
                mt.STOP();
            }
        }*/
    }
    delay(50);
}
