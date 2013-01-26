#ifndef MUT_PID_INPUT_H
#define MUT_PID_INPUT_H
#include "WPILib.h"
class MutablePIDInput : public PIDSource{
	public:
		static MutablePIDInput* getPointer(){return new MutablePIDInput();}
		double PIDGet(){return value;}
		void set(double val){value = val;}
	private:
		double value;
};

#endif
