#include "ScrewLift.h"

ScrewLift::ScrewLift(UINT32 elevationInput, UINT32 angleInput):
	elevation(elevationInput),
	angle(angleInput){}

void ScrewLift::set(Relay::Value val){
	elevation.Set(val);
}
