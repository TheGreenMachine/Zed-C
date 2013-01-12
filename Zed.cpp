#include "Zed.h"
#include "utils/utils.h"
#include "Components.h"
#include "WPILib.h"

Zed::Zed(){}

void Zed::Autonomous(){}

void Zed::OperatorControl(){
	Components& comps = Components::getInstance();
	while(IsEnabled() && IsOperatorControl()){
		speedX = comps.driver.GetLeftX();
		speedY = comps.driver.GetLeftY();
		rotation = comps.driver.GetRightX();
		if(comps.shooter.GetRawButton(6)){
			shooterPower+=0.01;
		}
		else if(comps.shooter.GetRawButton(8)){
			shooterPower-=0.01;
		}
	}
}

void Zed::mechanismSet(){
	Components& comps = Components::getInstance();
	comps.driveTrain.MecanumDrive_Cartesian(speedX, speedY, rotation);
	comps.shooterMotor.SetSpeed(shooterPower);
}
START_ROBOT_CLASS(Zed);
