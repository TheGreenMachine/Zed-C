#include "ScrewLift.h"

ScrewLift::ScrewLift(UINT32 elevationInput, UINT32 channel, 
					 UINT32 upperInput, UINT32 lowerInput):
	elevation(elevationInput),
	angle(channel),
	upperLimit(upperInput),
	lowerLimit(lowerInput){}

float ScrewLift::setAngle(float ang){
	return (ang-27)*0.47;
}

void ScrewLift::set(Relay::Value val){
	if(val==Relay::kForward && upperLimit.Get()){
		elevation.Set(Relay::kOff);
	}
	else if(val==Relay::kReverse && lowerLimit.Get()){
		elevation.Set(Relay::kOff);
	}	
	else {
		elevation.Set(val);
	}
}
