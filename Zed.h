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
		//All of these default init correctly
		float speedX;
		float speedY;
		float rotation;
		float shooterSpeed;
		float angle;
        bool collect;
        bool isTracking;
        bool isHighGoal;
        //constants
        static const double SHOOTER_LARGE_STEP = 50;
        static const double SHOOTER_MEDIUM_STEP = 30;
        static const double SHOOTER_SMALL_STEP = 10;
        
        static const double SHOOTER_HIGH_SPEED = 4000;
        static const double SHOOTER_MEDIUM_SPEED = 2000;
        static const double SHOOTER_LOW_SPEED = 0;
};
#endif
