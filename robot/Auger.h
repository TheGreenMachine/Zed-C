#ifndef AUGER_H
#define AUGER_H
#include "WPILib.h"

class Auger{
	public:
		Auger(int relayNum, UINT32 IONum);
		enum augerState{
			AUGER_IDLE,
			AUGER_MANUALFWD,
			AUGER_MANUALREV,
			AUGER_LOADING_START,
			AUGER_LOADING_WAITON,
			AUGER_LOADING_WAITOFF,
			AUGER_FEEDING_START,
			AUGER_FEEDING_WAITON,
			AUGER_FEEDING_WAITOFF
		};
		void doAuger();
		void setState(augerState);
	private:
		Relay auger;
		DigitalInput homeInput;
		Counter home;
		augerState state;
		
};



#endif
