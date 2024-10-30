# 1 "d:\\Codefields\\arduino-smart-car\\firmware\\SmartMKcar\\SmartMKcar.ino"
# 2 "d:\\Codefields\\arduino-smart-car\\firmware\\SmartMKcar\\SmartMKcar.ino" 2





//#define pressures   true


//#define rumble false

// pwm settings
u16 VA;
u16 VB;
u16 VC;
u16 VD;
u16 VALL = 255;
int count = 10;

PS2X ps2x; // create PS2 Controller Class
int error = 0;
byte type = 0;
byte vibrate = 0x00;
# 38 "d:\\Codefields\\arduino-smart-car\\firmware\\SmartMKcar\\SmartMKcar.ino"
void SPEED_SETTING(char A, char B, char C, char D); // 设置速度
void FRONTWARD(char VALL); // 小车向前运动
void BACKWARD(char VALL); // 小车向后运动
void LEFTWARD(char VALL); // 小车向左运动
void RIGHTWARD(char VALL); // 小车向右运动
void LEFT_FRONTWARD(char VALL); // 小车向左前运动
void LEFT_BACKWARD(char VALL); // 小车向左后运动
void RIGHT_FRONTWARD(char VALL); // 小车向右前运动
void RIGHT_BACKWARD(char VALL); // 小车向右后运动
void RIGHT_TURNAROUND(char VALL); // 小车原地向右转
void LEFT_TURNAROUND(char VALL); // 小车原地向左转

void STOP(); // 小车停止
void demo(); // 小车运动示例
void setup()
{
    pinMode(13, 0x1);
    pinMode(12, 0x1);
    pinMode(9, 0x1);
    pinMode(8, 0x1);
    pinMode(7, 0x1);
    pinMode(4, 0x1);
    pinMode(3, 0x1);
    pinMode(2, 0x1);
    pinMode(11, 0x1);
    pinMode(10, 0x1);
    pinMode(6, 0x1);
    pinMode(5, 0x1);
    Serial.begin(57600);
    delay(300);
    // setup pins and settings:
    // GamePad(clock, command, attention, data, Pressures?, Rumble?)
    /*error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);



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



    //  Serial.print(ps2x.Analog(1), HEX);*/
# 96 "d:\\Codefields\\arduino-smart-car\\firmware\\SmartMKcar\\SmartMKcar.ino"
    while (count > 0)
    {
        count--;
        error = ps2x.config_gamepad(12 /* connect to the clock pin of PS2 controller*/, 11 /* connect to the command pin of PS2 controller*/, 10 /* connect to the select pin of PS2 controller*/, 13 /* connect to the data pin of PS2 controller*/, false, true);
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

        if (ps2x.ButtonPressed(0x0010))
        {
            FRONTWARD(VALL);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x0020))
        {
            RIGHTWARD(0);
            SPEED_SETTING(255, 255, 255, 255);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x0080))
        {
            LEFTWARD(0);
            SPEED_SETTING(255, 255, 255, 255);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x0040))
        {
            BACKWARD(VALL);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x0100))
        {
            LEFT_FRONTWARD(VALL);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x0200))
        {
            RIGHT_FRONTWARD(VALL);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x0400))
        {
            LEFT_BACKWARD(VALL);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x0800))
        {
            RIGHT_BACKWARD(VALL);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x8000))
        {
            LEFT_TURNAROUND(VALL);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x2000))
        {
            RIGHT_TURNAROUND(VALL);
            vibrate = 0x10;
        }
        if (ps2x.ButtonPressed(0x0008))
        {
            demo();
        }

        if (ps2x.ButtonReleased(0x0010))
        {
            STOP();
            vibrate = 0x00;
        }
        if (ps2x.ButtonReleased(0x0020))
        {
            STOP();
            vibrate = 0x00;
        }
        if (ps2x.ButtonReleased(0x0080))
        {
            STOP();
            vibrate = 0x00;
        }
        if (ps2x.ButtonReleased(0x0040))
        {
            STOP();
            vibrate = 0x00;
        }
        if (ps2x.ButtonReleased(0x0100))
        {
            STOP();
            vibrate = 0x00;
        }
        if (ps2x.ButtonReleased(0x0200))
        {
            STOP();
            vibrate = 0x00;
        }
        if (ps2x.ButtonReleased(0x0400))
        {
            STOP();
            vibrate = 0x00;
        }
        if (ps2x.ButtonReleased(0x0800))
        {
            STOP();
            vibrate = 0x00;
        }
        if (ps2x.ButtonReleased(0x8000))
        {
            STOP();
            vibrate = 0x00;
        }
        if (ps2x.ButtonReleased(0x2000))
        {
            STOP();
            vibrate = 0x00;
        }
    }
    delay(50);
}

void SPEED_SETTING(char A, char B, char C, char D)
{
    analogWrite(9 /* Motor1 Speed*/, A);
    analogWrite(6 /* Motor2 Speed*/, B);
    analogWrite(5 /* Motor3 Speed*/, C);
    analogWrite(3 /* Motor4 Speed*/, D);
}

// 小车向前运动
void FRONTWARD(char VALL)
{
    // 右前轮向前运动
    digitalWrite(8 /* Motor1 Direction FR*/, 0x0);
    digitalWrite(7 /* Motor1 Direction*/, 0x1);
    analogWrite(9 /* Motor1 Speed*/, VALL);
    // 左前轮向前运动
    digitalWrite(2 /* Motor2 Direction FL*/, 0x0);
    digitalWrite(4 /* Motor2 Direction*/, 0x1);
    analogWrite(6 /* Motor2 Speed*/, VALL);
    // 右后轮向前运动
    digitalWrite(14 /* Motor3 Direction BR*/, 0x0);
    digitalWrite(15 /* Motor3 Direction*/, 0x1);
    analogWrite(5 /* Motor3 Speed*/, VALL);
    // 左后轮向前运动
    digitalWrite(17 /* Motor4 Direction BL*/, 0x0);
    digitalWrite(16 /* Motor4 Direction*/, 0x1);
    analogWrite(3 /* Motor4 Speed*/, VALL);
}

// 小车向后运动
void BACKWARD(char VALL)
{
    // 右前轮向后运动
    digitalWrite(8 /* Motor1 Direction FR*/, 0x1);
    digitalWrite(7 /* Motor1 Direction*/, 0x0);
    analogWrite(9 /* Motor1 Speed*/, VALL);
    // 左前轮向后运动
    digitalWrite(2 /* Motor2 Direction FL*/, 0x1);
    digitalWrite(4 /* Motor2 Direction*/, 0x0);
    analogWrite(6 /* Motor2 Speed*/, VALL);
    // 右后轮向后运动
    digitalWrite(14 /* Motor3 Direction BR*/, 0x1);
    digitalWrite(15 /* Motor3 Direction*/, 0x0);
    analogWrite(5 /* Motor3 Speed*/, VALL);
    // 左后轮向后运动
    digitalWrite(17 /* Motor4 Direction BL*/, 0x1);
    digitalWrite(16 /* Motor4 Direction*/, 0x0);
    analogWrite(3 /* Motor4 Speed*/, VALL);
}

// 小车向左运动
void LEFTWARD(char VALL)
{
    // 左前轮向后运动
    digitalWrite(2 /* Motor2 Direction FL*/, 0x1);
    digitalWrite(4 /* Motor2 Direction*/, 0x0);
    analogWrite(6 /* Motor2 Speed*/, VALL);
    // 左后轮向前运动
    digitalWrite(17 /* Motor4 Direction BL*/, 0x0);
    digitalWrite(16 /* Motor4 Direction*/, 0x1);
    analogWrite(3 /* Motor4 Speed*/, VALL);
    // 右前轮向前运动
    digitalWrite(8 /* Motor1 Direction FR*/, 0x0);
    digitalWrite(7 /* Motor1 Direction*/, 0x1);
    analogWrite(9 /* Motor1 Speed*/, VALL);
    // 右后轮向后运动
    digitalWrite(14 /* Motor3 Direction BR*/, 0x1);
    digitalWrite(15 /* Motor3 Direction*/, 0x0);
    analogWrite(5 /* Motor3 Speed*/, VALL);
}

// 小车向右运动
void RIGHTWARD(char VALL)
{
    // 右前轮向后运动
    digitalWrite(8 /* Motor1 Direction FR*/, 0x1);
    digitalWrite(7 /* Motor1 Direction*/, 0x0);
    analogWrite(9 /* Motor1 Speed*/, VALL);
    // 右后轮向前运动
    digitalWrite(14 /* Motor3 Direction BR*/, 0x0);
    digitalWrite(15 /* Motor3 Direction*/, 0x1);
    analogWrite(5 /* Motor3 Speed*/, VALL);
    // 左前轮向前运动
    digitalWrite(2 /* Motor2 Direction FL*/, 0x0);
    digitalWrite(4 /* Motor2 Direction*/, 0x1);
    analogWrite(6 /* Motor2 Speed*/, VALL);
    // 左后轮向后运动
    digitalWrite(17 /* Motor4 Direction BL*/, 0x1);
    digitalWrite(16 /* Motor4 Direction*/, 0x0);
    analogWrite(3 /* Motor4 Speed*/, VALL);
}

// 小车向左前运动
void LEFT_FRONTWARD(char VALL)
{
    // 右前轮向前运动
    digitalWrite(8 /* Motor1 Direction FR*/, 0x0);
    digitalWrite(7 /* Motor1 Direction*/, 0x1);
    analogWrite(9 /* Motor1 Speed*/, VALL);
    // 左后轮向前运动
    digitalWrite(17 /* Motor4 Direction BL*/, 0x0);
    digitalWrite(16 /* Motor4 Direction*/, 0x1);
    analogWrite(3 /* Motor4 Speed*/, VALL);
    // 右后轮静止
    digitalWrite(14 /* Motor3 Direction BR*/, 0x0);
    digitalWrite(15 /* Motor3 Direction*/, 0x0);
    analogWrite(5 /* Motor3 Speed*/, VALL);
    // 左前轮静止
    digitalWrite(2 /* Motor2 Direction FL*/, 0x0);
    digitalWrite(4 /* Motor2 Direction*/, 0x0);
    analogWrite(6 /* Motor2 Speed*/, VALL);
}

// 小车向左后运动
void LEFT_BACKWARD(char VALL)
{
    // 左前轮向后运动
    digitalWrite(2 /* Motor2 Direction FL*/, 0x1);
    digitalWrite(4 /* Motor2 Direction*/, 0x0);
    analogWrite(6 /* Motor2 Speed*/, VALL);
    // 右后轮向后运动
    digitalWrite(14 /* Motor3 Direction BR*/, 0x1);
    digitalWrite(15 /* Motor3 Direction*/, 0x0);
    analogWrite(5 /* Motor3 Speed*/, VALL);
    // 右前轮静止
    digitalWrite(8 /* Motor1 Direction FR*/, 0x0);
    digitalWrite(7 /* Motor1 Direction*/, 0x0);
    analogWrite(9 /* Motor1 Speed*/, VALL);
    // 左后轮精止
    digitalWrite(17 /* Motor4 Direction BL*/, 0x0);
    digitalWrite(16 /* Motor4 Direction*/, 0x0);
    analogWrite(3 /* Motor4 Speed*/, VALL);
}

// 小车向右前运动
void RIGHT_FRONTWARD(char VALL)
{
    // 左前轮向前运动
    digitalWrite(2 /* Motor2 Direction FL*/, 0x0);
    digitalWrite(4 /* Motor2 Direction*/, 0x1);
    analogWrite(6 /* Motor2 Speed*/, VALL);
    // 右后轮向前运动
    digitalWrite(14 /* Motor3 Direction BR*/, 0x0);
    digitalWrite(15 /* Motor3 Direction*/, 0x1);
    analogWrite(5 /* Motor3 Speed*/, VALL);
    // 左后轮静止
    digitalWrite(17 /* Motor4 Direction BL*/, 0x0);
    digitalWrite(16 /* Motor4 Direction*/, 0x0);
    analogWrite(3 /* Motor4 Speed*/, VALL);
    // 右前轮静止
    digitalWrite(8 /* Motor1 Direction FR*/, 0x0);
    digitalWrite(7 /* Motor1 Direction*/, 0x0);
    analogWrite(9 /* Motor1 Speed*/, VALL);
}

// 小车向右后运动
void RIGHT_BACKWARD(char VALL)
{
    // 右前轮向后运动
    digitalWrite(8 /* Motor1 Direction FR*/, 0x1);
    digitalWrite(7 /* Motor1 Direction*/, 0x0);
    analogWrite(9 /* Motor1 Speed*/, VALL);
    // 左后轮向后运动
    digitalWrite(17 /* Motor4 Direction BL*/, 0x1);
    digitalWrite(16 /* Motor4 Direction*/, 0x0);
    analogWrite(3 /* Motor4 Speed*/, VALL);
    // 右后轮静止
    digitalWrite(14 /* Motor3 Direction BR*/, 0x0);
    digitalWrite(15 /* Motor3 Direction*/, 0x0);
    analogWrite(5 /* Motor3 Speed*/, VALL);
    // 左前轮静止
    digitalWrite(2 /* Motor2 Direction FL*/, 0x0);
    digitalWrite(4 /* Motor2 Direction*/, 0x0);
    analogWrite(6 /* Motor2 Speed*/, VALL);
}

// 小车原地向右转
void RIGHT_TURNAROUND(char VALL)
{
    // 左前轮向前运动
    digitalWrite(2 /* Motor2 Direction FL*/, 0x0);
    digitalWrite(4 /* Motor2 Direction*/, 0x1);
    analogWrite(6 /* Motor2 Speed*/, VALL);
    // 右前轮向后运动
    digitalWrite(8 /* Motor1 Direction FR*/, 0x1);
    digitalWrite(7 /* Motor1 Direction*/, 0x0);
    analogWrite(9 /* Motor1 Speed*/, VALL);
    // 左后轮向前运动
    digitalWrite(14 /* Motor3 Direction BR*/, 0x1);
    digitalWrite(15 /* Motor3 Direction*/, 0x0);
    analogWrite(5 /* Motor3 Speed*/, VALL);
    // 右后轮向后运动
    digitalWrite(17 /* Motor4 Direction BL*/, 0x0);
    digitalWrite(16 /* Motor4 Direction*/, 0x1);
    analogWrite(3 /* Motor4 Speed*/, VALL);
}

// 小车原地向左转
void LEFT_TURNAROUND(char VALL)
{
    // 左前轮向后运动
    digitalWrite(2 /* Motor2 Direction FL*/, 0x1);
    digitalWrite(4 /* Motor2 Direction*/, 0x0);
    analogWrite(6 /* Motor2 Speed*/, VALL);
    // 右前轮向前运动
    digitalWrite(8 /* Motor1 Direction FR*/, 0x0);
    digitalWrite(7 /* Motor1 Direction*/, 0x1);
    analogWrite(9 /* Motor1 Speed*/, VALL);
    // 左后轮向后运动
    digitalWrite(14 /* Motor3 Direction BR*/, 0x0);
    digitalWrite(15 /* Motor3 Direction*/, 0x1);
    analogWrite(5 /* Motor3 Speed*/, VALL);
    // 右后轮向前运动
    digitalWrite(17 /* Motor4 Direction BL*/, 0x1);
    digitalWrite(16 /* Motor4 Direction*/, 0x0);
    analogWrite(3 /* Motor4 Speed*/, VALL);
}

// 小车停止
void STOP()
{
    digitalWrite(8 /* Motor1 Direction FR*/, 0x0);
    digitalWrite(7 /* Motor1 Direction*/, 0x0);
    digitalWrite(17 /* Motor4 Direction BL*/, 0x0);
    digitalWrite(16 /* Motor4 Direction*/, 0x0);
    digitalWrite(14 /* Motor3 Direction BR*/, 0x0);
    digitalWrite(15 /* Motor3 Direction*/, 0x0);
    digitalWrite(2 /* Motor2 Direction FL*/, 0x0);
    digitalWrite(4 /* Motor2 Direction*/, 0x0);
    analogWrite(9 /* Motor1 Speed*/, 0);
    analogWrite(6 /* Motor2 Speed*/, 0);
    analogWrite(5 /* Motor3 Speed*/, 0);
    analogWrite(3 /* Motor4 Speed*/, 0);
}

void demo()
{
    BACKWARD(128);
    delay(2000);
    STOP();
    delay(2000);
    FRONTWARD(128);
    delay(2000);
    STOP();
    delay(2000);
    LEFTWARD(128);
    delay(2000);
    STOP();
    delay(2000);
    RIGHTWARD(128);
    delay(2000);
    STOP();
    delay(2000);
    LEFT_FRONTWARD(128);
    delay(2000);
    STOP();
    delay(2000);
    LEFT_BACKWARD(128);
    delay(2000);
    STOP();
    delay(2000);
    RIGHT_FRONTWARD(128);
    delay(2000);
    STOP();
    delay(2000);
    RIGHT_BACKWARD(128);
    delay(2000);
    STOP();
    delay(2000);
    RIGHT_TURNAROUND(128);
    delay(2000);
    STOP();
    delay(2000);
    LEFT_TURNAROUND(128);
    delay(2000);
    STOP();
    delay(2000);
}
