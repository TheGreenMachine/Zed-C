#ifndef NULL_PID_OUTPUT_H
#define NULL_PID_OUTPUT_H
#include "WPILib.h"

class NullPIDOutput :public PIDOutput{
	public:
		static NullPIDOutput* getPointer(){return new NullPIDOutput();}
		void PIDWrite(float){}
};

#endif
