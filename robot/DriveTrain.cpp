#include "DriveTrain.h"

DriveTrain::DriveTrain(int topLeft, int backLeft, int topRight, int backRight) :
    driveTrain(topLeft, backLeft, topRight, backRight)
{
    driveTrain.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
    driveTrain.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
}

void DriveTrain::drive(double x, double y, double r)
{
    speedX = x;
    speedY = y;
    rotation = r;
    set();
}
void DriveTrain::set()
{
    driveTrain.MecanumDrive_Cartesian(speedX, speedY, rotation);
}
