#ifndef AUGER_H
#define AUGER_H
#include "WPILib.h"

class Auger{
	public:
		Auger(int relayNum, UINT32 IONum);
		
		void set(Relay::Value);
		void feed();
		void goHome();
	private:
		Relay auger;
		DigitalInput homeInput;
		Counter home;
		
};



#endif
