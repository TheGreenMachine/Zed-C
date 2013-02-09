#include "ScrewLift.h"

ScrewLift::ScrewLift(UINT32 elevationInput, UINT32 angleInput, 
					 UINT32 upperInput, UINT32 lowerInput):
	elevation(elevationInput),
	angle(angleInput),
	upperLimit(upperInput),
	lowerLimit(lowerInput){}

double ScrewLift::getAngle(){
	return angle.GetAcceleration();
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
