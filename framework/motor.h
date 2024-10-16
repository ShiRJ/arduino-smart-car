#ifndef MOTOR_H_
#define MOTOR_H_
#include <Arduino.h>
class Motor
{
public:
    void SPEED_SETTING(char A, char B, char C, char D);
    void FRONTWARD(char VALL);
    void BACKWARD(char VALL);
    void LEFTWARD(char VALL);
    void RIGHTWARD(char VALL);
    void LEFT_FRONTWARD(char VALL);
    void RIGHT_FRONTWARD(char VALL);
    void LEFT_BACKWARD(char VALL);
    void RIGHT_BACKWARD(char VALL);
    void LEFT_TURNAROUND(char VALL);
    void RIGHT_TURNAROUND(char VALL);
    void STOP();
    void demo();
private:
};

#endif
