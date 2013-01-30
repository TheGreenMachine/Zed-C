#ifndef COLLECTOR
#define COLLECTOR
#include "WPILib.h"

class Collector{
	public:
		Collector(int, int, int);
		void Set(bool);
		
	private:
		Victor starR;
		Victor starL;
		Victor belt;
};
#endif
