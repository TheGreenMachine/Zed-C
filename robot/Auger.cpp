#include "Auger.h"

Auger::Auger(int relayNum, UINT32 IONum):
	auger(relayNum),
	homeInput(IONum),
	home(homeInput){}

void Auger::set(Relay::Value val){
	auger.Set(val);
}

void Auger::goHome(){
	home.Reset();
	home.Start();
	auger.Set(Relay::kForward);
	while(home.Get()==0){
		Wait(0.005);
	}
	auger.Set(Relay::kOff);
}

void Auger::feed(){
	auger.Set(Relay::kForward);
	while(homeInput.Get()){
		Wait(0.005);
	}
	home.Reset();
	home.Start();
	while(!home.Get()){
		Wait(0.005);
	}
	auger.Set(Relay::kOff);
}
