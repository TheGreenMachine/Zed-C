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
	}
}

void Zed::mechanismSet(){
	Components& comps = Components::getInstance();
	comps.driveTrain.MecanumDrive_Cartesian(speedX, speedY, rotation);
}
START_ROBOT_CLASS(Zed);
