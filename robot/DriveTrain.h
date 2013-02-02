#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H
#include "WPILib.h"

class DriveTrain{
	public:
		DriveTrain(int topLeft, int backLeft, int topRight, int backRight);
		
		void drive(double x, double y, double r);
		void set();
		virtual ~DriveTrain(){}
	private:
		double speedX, speedY, rotation;
		RobotDrive driveTrain;
};
#endif
