#ifndef COLLECTOR
#define COLLECTOR
#include "WPILib.h"

class Collector{
	public:
		Collector(int right, int left);
		
		//Takes a direction
		void set(short); 
	private:
		Relay starR;
		Relay starL;
};
#endif
