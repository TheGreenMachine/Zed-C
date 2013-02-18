#ifndef SCREWLIFT_H
#define SCREWLIFT_H
#include "WPILib.h"

class ScrewLift
{
public:
    ScrewLift(UINT32 elevationInput, UINT32 channel, UINT32 lowerInput, UINT32 upperInput);

    //Takes a direction
    void set(Relay::Value);
    float setAngle(float);
private:
    Relay elevation;
    AnalogChannel angle;
    DigitalInput lowerLimit;
    DigitalInput upperLimit;
};

#endif
