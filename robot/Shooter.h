#ifndef SHOOTER_H
#define SHOOTER_H
#include "WPILib.h"
class Shooter
{
public:
    Shooter(int, int, int, int);
    void setVelocity(double);

private:
    CANJaguar shooter1;
    CANJaguar shooter2;

    ///////////////////
    static const int P1 = 1;
    static const int I1 = 0;
    static const int D1 = 0;

    static const int P2 = 1;
    static const int I2 = 0;
    static const int D2 = 0;

};
#endif

