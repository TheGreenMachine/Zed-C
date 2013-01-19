#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "utils/utils.h"
#include "WPILib.h"
#include "robot/Shooter.h"

class Components{
	public:
		static Components& getInstance(){static Components instance; return instance;}
		FilteredGamePad driver;
		FilteredGamePad shooter;
		RobotDrive driveTrain;
		Shooter shooterMotor;
		Jaguar collectorMotor;
		
	private:
		//Warning these numbers are made up :)
		static const unsigned short FRONT_LEFT_WHEEL = 0;
		static const unsigned short BACK_LEFT_WHEEL = 1;
		static const unsigned short FRONT_RIGHT_WHEEL = 2;
		static const unsigned short BACK_RIGHT_WHEEL = 3;
		static const unsigned short DRIVER_PORT = 0;
		static const unsigned short SHOOTER_PORT = 1;
		static const unsigned short SHOOTER_MOTOR = 4;
		static const unsigned short COLLECTOR_MOTOR = 5;
		static const std::vector<smartptr<GamePadFilter> > FILTERS; 
		Components():
			driver(DRIVER_PORT),
			shooter(SHOOTER_PORT),
			driveTrain(FRONT_LEFT_WHEEL, BACK_LEFT_WHEEL, FRONT_RIGHT_WHEEL, BACK_RIGHT_WHEEL),
			shooterMotor(SHOOTER_MOTOR),
			collectorMotor(COLLECTOR_MOTOR)
		{
			QuadraticFilter* q = new QuadraticFilter(); 
			DeadZoneFilter* d = new DeadZoneFilter(); 
			driver.addFilter(smartptr<GamePadFilter>(q));
			driver.addFilter(smartptr<GamePadFilter>(d));
			q = new QuadraticFilter(); //Not sure if this second allocation is necessary
			d = new DeadZoneFilter(); //Not sure if this second allocation is necessary
			shooter.addFilter(smartptr<GamePadFilter>(q));
			shooter.addFilter(smartptr<GamePadFilter>(d));
		}
};
#endif
