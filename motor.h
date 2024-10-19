#ifndef MOTOR_H_
#define MOTOR_H_

class Motor
{
public:
    void SPEED_SETTING(char, char, char, char);
    void FRONTWARD(char );
    void BACKWARD(char );
    void LEFTWARD(char );
    void RIGHTWARD(char );
    void LEFT_FRONTWARD(char );
    void RIGHT_FRONTWARD(char );
    void LEFT_BACKWARD(char );
    void RIGHT_BACKWARD(char );
    void LEFT_TURNAROUND(char );
    void RIGHT_TURNAROUND(char );
    void STOP();
    void demo();

private:
};

#endif
