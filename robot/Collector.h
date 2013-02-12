#ifndef COLLECTOR_H
#define COLLECTOR_H
#include "WPILib.h"

class Collector{
	public:
		Collector(int right, int left, int motor, UINT32 IONum1, UINT32 IONum2);
		enum collectorState{
			COLLECTOR_DEPLOY,
			COLLECTOR_DEPLOYED,
			COLLECTOR_UNDEPLOY,
			COLLECTOR_UNDEPLOYED
		};
		
		//Takes a direction
		void setStar(int);
		void setState(collectorState);
		void doCollector();
		void setStarDirection(int dir);
	private:
		Relay collectorM;
		DigitalInput deployed;
		DigitalInput undeployed;
		Relay starR;
		Relay starL;
		collectorState state;
		int starDirection;
};
#endif
