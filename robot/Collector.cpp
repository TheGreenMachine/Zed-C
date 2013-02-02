#include "Collector.h"

Collector::Collector(int left, int right, int rol):
	starR(right),
	starL(left),
	roller(rol){}

void Collector::set(short direction){
	Relay::Value val;
	switch(direction){
		case 1 :
			val = Relay::kForward;
			break;
		case -1 :
			val = Relay::kReverse;
			break;
		case 0 :
			val = Relay::kOff;
			break;
	}

	starL.Set(val);
	starR.Set(val);
	roller.Set(val);
}
