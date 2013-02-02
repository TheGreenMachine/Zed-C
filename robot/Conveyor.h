#ifndef CONVEYOR_CPP
#define CONVEYOR_CPP

#include "WPILib.h"

class Conveyor{
	public:
		Conveyor(int port)
			:conveyor(port){}

		set(double velocity){
			conveyor.Set(velocity);
		}

	static const double CONVEYOR_IN = 1;
	static const double CONVEYOR_OUT = -1;
	static const double CONVEYOR_STOP = 0;
	private:
		Victor conveyor;
};

#endif
