#ifndef SCREWLIFT_H
#define SCREWLIFT_H
#include "WPILib.h"

class ScrewLift{
	public:
		ScrewLift(UINT32 elevationInput, UINT32 angleInput);
		
		//Takes a direction
		void set(Relay::Value); 
	private:
		Relay elevation;
		Accelerometer angle;
		
};


#endif
