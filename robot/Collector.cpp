#include "Collector.h"

Collector::Collector(int left, int right):
	starR(right),
	starL(left){}

void Collector::set(short direction){
	switch(direction){
		case 1 :
			starL.Set(Relay::kForward);
			starR.Set(Relay::kReverse);
			break;
		case -1 :
			starL.Set(Relay::kReverse);
			starR.Set(Relay::kForward);
			break;
		case 0 :
			starL.Set(Relay::kOff);
			starR.Set(Relay::kOff);
			break;
	}

}
