#include "Collector.h"

Collector::Collector(int left, int right, int motor, UINT32 IONum1, UINT32 IONum2):
	collectorM(motor),
	deployed(IONum1),
	undeployed(IONum2),
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
void Collector::setState(collectorState newState){
	if(newState==COLLECTOR_DEPLOY && newState==COLLECTOR_DEPLOYED){
		return;
	}
	if(newState==COLLECTOR_UNDEPLOY && newState==COLLERTOR_UNDEPLOYED){
		return;
	}
	state = newState;
}
void Collector::deploy(){
	switch (state){
	case COLLECTOR_DEPLOY:
		collectorM.Set(Relay::kForward);
		break;
	case COLLECTOR_DEPLOYED:
		if(deployed.Get()){
			collectorM.Set(Relay::kOff);
		}
	case COLLECTOR_UNDEPLOY:
		collectorM.Set(Relay::kReverse);
		break;
	case COLLERTOR_UNDEPLOYED:
		if(undeployed.Get()){
			collectorM.Set(Relay::kOff);
		}
	}
}

