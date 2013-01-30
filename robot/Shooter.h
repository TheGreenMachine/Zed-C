#ifndef SHOOTER_H
#define SHOOTER_H
#include "WPILib.h"
class Shooter{
	public:
		Shooter(int, int, int, int);
		void setAngle(double);
		void setVelocity(double);

	private:
		CANJaguar shooter1;
		CANJaguar shooter2;
		CANJaguar lifter1;
		CANJaguar lifter2;
		
		///////////////////
		static const int P1 = 1;
		static const int I1 = 0;
		static const int D1 = 0;
		
		static const int P2 = 1;
		static const int I2 = 0;
		static const int D2 = 0;
		
		static const int P3 = 1;
		static const int I3 = 0;
		static const int D3 = 0;

		static const int P4 = 1;
		static const int I4 = 0;
		static const int D4 = 0;
};
#endif

