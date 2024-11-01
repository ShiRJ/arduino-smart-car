# Arduino-smart-car

## 项目简介

基于Arduino的麦克纳姆轮智能遥控小车，采用双Arduino控制，其中Arduino UNO R3（ATMEGA328P）作为主控，负责四路电机PWM控制、PS2手柄通信以及麦克纳姆轮逆运动学分析解算。Arduino Pro Micro（ATMEGA32U4）作为从控，负责四路红外测速，并通过软串口将数据发送至主控。

$$
u ( t )=K_{p} \times e ( t )+K_{i} \times\int_{0}^{t} e ( \tau) d \tau+K_{d} \times\frac{d e ( t )} {d t}
$$

## 1. 开发板接口定义

### 主控板（Arduino UNO R3）引脚连接

| 引脚号 | 功能         | 连接说明                 |
| ------ | ------------ | ------------------------ |
| 2      | Motor_IN3    | 左前轮电机方向控制引脚   |
| 3      | Motor_END    | 左后轮电机PWM速度控制引脚 |
| 4      | Motor_IN4    | 左前轮电机方向控制引脚   |
| 5      | Motor_ENC    | 右后轮电机PWM速度控制引脚 |
| 6      | Motor_ENB    | 左前轮电机PWM速度控制引脚 |
| 7      | Motor_IN2    | 右前轮电机方向控制引脚   |
| 8      | Motor_IN1    | 右前轮电机方向控制引脚   |
| 9      | Motor_ENA    | 右前轮电机PWM速度控制引脚 |
| 10     | PS2_SEL      | PS2手柄选择引脚          |
| 11     | PS2_CMD      | PS2手柄命令引脚          |
| 12     | PS2_CLK      | PS2手柄时钟引脚          |
| 13     | PS2_DAT      | PS2手柄数据引脚          |
| A0     | Motor_IN5    | 右后轮电机方向控制引脚   |
| A1     | Motor_IN6    | 右后轮电机方向控制引脚   |
| A2     | Motor_IN8    | 左后轮电机方向控制引脚   |
| A3     | Motor_IN7    | 左后轮电机方向控制引脚   |

### 从控板（Arduino Pro Micro）引脚连接

// ...根据实际连接补充从控板引脚定义...

## 2. 使用方法

1. 按照上述引脚定义连接电机驱动、电机、PS2手柄接收器和两块Arduino开发板。
2. 将主控程序上传至Arduino UNO R3，将从控程序上传至Arduino Pro Micro。
3. 接通电源，确保PS2手柄正常连接。
4. 使用PS2手柄控制小车，实现全方位移动。

## 3. 项目说明

本项目通过双Arduino协作，实现了麦克纳姆轮小车的全向移动。主控板负责处理PS2手柄的指令和电机的PWM控制，以及麦克纳姆轮的逆运动学计算。从控板负责红外测速，并将速度数据通过软串口发送给主控板。通过调整PID参数，实现对小车运动的精确控制。
