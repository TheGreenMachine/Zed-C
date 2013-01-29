#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H
#include "WPILib.h"
class DriveTrain{
	public:
		DriveTrain(int topLeft, int backLeft, int topRight, int backRight):
			driveTrain(topLeft, backLeft, topRight, backRight){
				driveTrain.SetInvertedMotor(RobotDrive::kFrontRightMotor,true);
				driveTrain.SetInvertedMotor(RobotDrive::kRearRightMotor,true);
		}
		
		void drive(double x, double y, double r){
			speedX = x;
			speedY = y;
			rotation = r;
			set();
		}
		void set(){
			driveTrain.MecanumDrive_Cartesian(speedX, speedY, rotation);
		}
		virtual ~DriveTrain(){}
	private:
		
		double speedX, speedY, rotation;
		RobotDrive driveTrain;
};

#endif
