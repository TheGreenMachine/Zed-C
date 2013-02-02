#include "Shooter.h"

void setupSpeedJag(CANJaguar& jag, int P, int I, int D, CANJaguar::SpeedReference mode){
	std::exception except;
	for(int i = 0; i<5;++i){
		try{
			jag.ConfigEncoderCodesPerRev(180);
			jag.SetPID(P, I, D);
			jag.SetSafetyEnabled(false);
			jag.SetSpeedReference(mode);
			jag.EnableControl(0.0);
			return;
		}
		catch(std::exception e){ except = e;
		}
	}
	throw except;
}

Shooter::Shooter(int port1, int port2, int port3, int port4): 
		shooter1(port1,CANJaguar::kSpeed),
		shooter2(port2, CANJaguar::kSpeed),
		lifter(port3,CANJaguar::kSpeed),
{
	
	setupSpeedJag(shooter1, P1, I1, D1, CANJaguar::kSpeedRef_InvEncoder);
	setupSpeedJag(shooter2, P2, I2, D2, CANJaguar::kSpeedRef_InvEncoder);
	/////////////////////////////////////////////////////////////////////
	std::exception except;
	for(int i = 0; i<5;++i){
		try, kPosRef_Potentiomete{
		try {
			lifter.SetPID(P3, I3, D3);
			lifter.SetSafetyEnabled(false);
			lifter.SetPositionReference(CANJaguar::kPosRef_Potentiometer);
			lifter.ConfigEncoderCodesPerRev(0.0);
			lifter.EnableControl(0.0);
			return;
		}
		catch(std::exception e){
			except = e;
		}
	}
	throw except;
	setupSpeedJag(lifter,	P3, I3, D3, CANJaguar::kSpeedRef_InvEncoder);

}

void Shooter::setVelocity(double velocity){
	shooter1.Set(velocity);
	shooter2.Set(velocity);
}

void Shooter::setAngle(double velocity){
	lifter.Set(velocity);
}

