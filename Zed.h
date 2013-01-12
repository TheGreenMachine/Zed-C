#ifndef ZED_H
#define ZED_H
#include "WPILib.h"
class Zed : public SimpleRobot {
	public:
		Zed();
		void Autonomous();
		void OperatorControl();
		void mechanismSet();
	private:
		float speedX;
		float speedY;
		float rotation;
		float shooterPower;
};
#endif
