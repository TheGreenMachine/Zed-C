#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "utils/utils.h"

class Components{
	public:
		static Components& getInstance(){static Components instance; return instance;}
		FilteredGamePad driver;
		FilteredGamePad shooter;
		RobotDrive driveTrain;
		Jaguar shooterMotor;
		
	private:
		//Warning these numbers are made up :)
		static const unsigned short FRONT_LEFT_WHEEL = 0;
		static const unsigned short BACK_LEFT_WHEEL = 1;
		static const unsigned short FRONT_RIGHT_WHEEL = 2;
		static const unsigned short BACK_RIGHT_WHEEL = 3;
		static const unsigned short DRIVER_PORT = 0;
		static const unsigned short SHOOTER_PORT = 1;
		static const unsigned short SHOOTER_MOTOR = 4;
		static const std::vector<smartptr<GamePadFilter> > FILTERS; 
		Components():
			driver(DRIVER_PORT),
			shooter(SHOOTER_PORT),
			driveTrain(FRONT_LEFT_WHEEL, BACK_LEFT_WHEEL, FRONT_RIGHT_WHEEL, BACK_RIGHT_WHEEL),
			shooterMotor(SHOOTER_MOTOR)
		{
			QuadraticFilter* q = new QuadraticFilter(); 
			driver.addFilter(smartptr<GamePadFilter>(q));
			q = new QuadraticFilter(); //Not sure if this second allocation is necessary
			shooter.addFilter(smartptr<GamePadFilter>(q));
		}
};
#endif
