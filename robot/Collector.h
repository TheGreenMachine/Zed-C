#ifndef COLLECTOR_H
#define COLLECTOR_H
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
