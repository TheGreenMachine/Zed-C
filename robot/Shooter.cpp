#include "Shooter.h"

Shooter::Shooter(int port): shooter (port,CANJaguar::kSpeed){
	std::exception except;
	bool isExcept;
	for(int i = 0; i<5;++i){
		try{
			shooter.ConfigEncoderCodesPerRev(180);
			shooter.SetPID(0.345,0.503, 0.0);
			shooter.SetSafetyEnabled(false);
			shooter.SetSpeedReference(CANJaguar::kSpeedRef_InvEncoder);
			shooter.EnableControl(0.0);
			isExcept = false;
			break;
		}
		catch(std::exception e){
			except = e;
			isExcept = true;
		}
	}
	if(isExcept){
		throw except;
	}
}

void Shooter::setVelocity(double velocity){
	
	shooter.Set(velocity);
	
}
