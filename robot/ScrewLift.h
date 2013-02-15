#ifndef SCREWLIFT_H
#define SCREWLIFT_H
#include "WPILib.h"

class ScrewLift{
	public:
		ScrewLift(UINT32 elevationInput, UINT32 channel, 
				  UINT32 upperInput, UINT32 lowerInput);
		
		//Takes a direction
		void set(Relay::Value); 
		void setAngle(float);
	private:
		Relay elevation;
		AnalogChannel angle;
		DigitalInput upperLimit;
		DigitalInput lowerLimit;
};


#endif
