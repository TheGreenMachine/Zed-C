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

                collect = comps.driver.GetRawButton(6);
	}
}

void Zed::mechanismSet(){
	Components& comps = Components::getInstance();

        //Drive
	comps.driveTrain.MecanumDrive_Cartesian(speedX, speedY, rotation);
        
        //Shooter
	comps.shooterMotor.SetSpeed(shooterPower);
        
        //Collector
        comps.collectorMotor.SetSpeed(
            collect? 75 : 0
        );
}
START_ROBOT_CLASS(Zed);
