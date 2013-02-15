#ifndef ZED_H
#define ZED_H
#include "WPILib.h"
#include <vector>
struct Packet{
	double x, y, dist;
	bool isCenter;
};
class Zed : public SimpleRobot {
	public:
		Zed();
		void Autonomous();
		void OperatorControl();
		void mechanismSet();
		std::vector<Packet> parsePacket();
		void autoTrack();
	private:
		void updateDriverStation();
		float speedX; //Strafing speed horizontal
		float speedY; //Strafing speed vertiacal
		float rotation; //Rotation speed 
		float shooterSpeed; //Shooter speed
		Relay::Value lift; //Screw lift movement
		float angle; //The angle of the shooter
		float lastSpeed; //Last manually set speed
		bool isTracking; //Is vision tracking enabled
		bool isHighGoal; //Targeting the high goal?
		bool isClosest; //Targeting the closest goal?
		int collectorDirection;//Direction of collector
		Relay::Value conveyorVelocity; //Velocity for the conveyor
		//constants
		static const double SHOOTER_LARGE_STEP = 50;
		static const double SHOOTER_MEDIUM_STEP = 30;
		static const double SHOOTER_SMALL_STEP = 10;
		
		static const double SHOOTER_HIGH_SPEED = 4000;
		static const double SHOOTER_MEDIUM_SPEED = 2000;
		static const double SHOOTER_LOW_SPEED = 0;
		
		static const double D_PAD_FACTOR = .60;
};
#endif
