#include "ScrewLift.h"

ScrewLift::ScrewLift(UINT32 elevationInput, UINT32 channel, UINT32 lowerInput, UINT32 upperInput) :
    elevation(elevationInput), angle(channel), lowerLimit(lowerInput), upperLimit(upperInput)
{
}

float ScrewLift::setAngle(float ang)
{
    return (ang * (0.47 / 10)) + 27;
}

void ScrewLift::set(Relay::Value val)
{
    if (val == Relay::kReverse && !lowerLimit.Get())
    {
        elevation.Set(Relay::kOff);
    }
    else if(val == Relay::kForward && !upperLimit.Get())
    {
        elevation.Set(Relay::kOff);
    }
    else
    {
        elevation.Set(val);
    }
}
