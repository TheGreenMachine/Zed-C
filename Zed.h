#ifndef ZED_H
#define ZED_H
#include "WPILib.h"
class Zed : public SimpleRobot {

public:
	Zed();

	void Autonomous();

	void OperatorControl();
};
#endif
