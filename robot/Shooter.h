#ifndef SHOOTER_H
#define SHOOTER_H
#include "WPILib.h"
class Shooter{
	public:
		Shooter(int);
		void setVelocity(double);
	private:
		CANJaguar shooter;
};
#endif

