#ifndef CONVEYOR_H
#define CONVEYOR_H
#include "WPILib.h"

class Conveyor{
	public:
		Conveyor(int port)
			:conveyor(port){}

		void set(Relay::Value velocity);

	private:
		Victor conveyor;
};

#endif
