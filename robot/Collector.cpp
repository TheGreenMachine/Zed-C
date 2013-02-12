#include "Collector.h"

Collector::Collector(int left, int right, int motor, UINT32 IONum1, UINT32 IONum2):
	collectorM(motor),
	deployed(IONum1),
	undeployed(IONum2),
	starR(right),
	starL(left),
	state(COLLECTOR_UNDEPLOYED),
	starDirection(1){}

void Collector::setStarDirection(int dir){
	starDirection = dir!=1 ? -1 : 1;
}

void Collector::setStar(int direction){
	switch(direction*starDirection){
		case 1 :
			starL.Set(Relay::kForward);
			starR.Set(Relay::kReverse);
			break;
		case -1 :
			starL.Set(Relay::kReverse);
			starR.Set(Relay::kForward);
			break;
		case 0 :
		default:
			starL.Set(Relay::kOff);
			starR.Set(Relay::kOff);
			break;
	}
}
void Collector::setState(collectorState newState){
	if(newState==COLLECTOR_DEPLOY && state==COLLECTOR_DEPLOYED){
		return;
	}
	if(newState==COLLECTOR_UNDEPLOY && state==COLLECTOR_UNDEPLOYED){
		return;
	}
	state = newState;
}
void Collector::doCollector(){
	switch (state){
	case COLLECTOR_DEPLOY:
		collectorM.Set(Relay::kForward);
		setStar(0);
		starDirection=1;
		break;
	case COLLECTOR_DEPLOYED:
		if(deployed.Get()){
			collectorM.Set(Relay::kOff);
		}
		setStar(1);
		break;
	case COLLECTOR_UNDEPLOY:
		collectorM.Set(Relay::kReverse);
		setStar(0);
		break;
	case COLLECTOR_UNDEPLOYED:
		if(undeployed.Get()){
			collectorM.Set(Relay::kOff);
		}
		setStar(0);
		break;
	default:
		collectorM.Set(Relay::kOff);
		setStar(0);
		state=COLLECTOR_UNDEPLOYED;
	}
}

