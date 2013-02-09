#ifndef SCREWLIFT_H
#define SCREWLIFT_H
#include "WPILib.h"

class ScrewLift{
	public:
		ScrewLift(UINT32 elevationInput, UINT32 angleInput, 
				  UINT32 upperInput, UINT32 lowerInput);
		
		//Takes a direction
		void set(Relay::Value); 
		double getAngle();
	private:
		Relay elevation;
		Accelerometer angle;
		DigitalInput upperLimit;
		DigitalInput lowerLimit;
};


#endif
