#ifndef COLLECTOR
#define COLLECTOR
#include "WPILib.h"

class Collector{
	public:
		Collector(int right, int left, int rol);
		
		//Takes a direction
		void set(short); 
	private:
		Relay starR;
		Relay starL;
		Relay roller;
};
#endif
