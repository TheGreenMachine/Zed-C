#include "Zed.h"
#include "utils/utils.h"
#include "Components.h"
#include "WPILib.h"
#include "robot/Shooter.h"
#include "robot/Auger.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <sstream>

Zed::Zed(){}

void Zed::Autonomous(){

}

void Zed::OperatorControl(){
	Components& comps = Components::getInstance();
	ToggleHelper PIDToggle;
	while(IsEnabled() && IsOperatorControl()){
		//Get the strafing directions for the robot
		if(comps.driver.GetRawAxis(5) != 0 ||	comps.driver.GetRawAxis(6) != 0){
			speedX = comps.driver.GetRawAxis(5) * D_PAD_FACTOR;
			speedY = comps.driver.GetRawAxis(6) * D_PAD_FACTOR;
		}
		else {
			speedX = comps.driver.GetLeftX();
			speedY = comps.driver.GetLeftY();
		}
		//Handle Vision Tracking
		if(PIDToggle(comps.shooter.GetRawButton(5))){
			isTracking = !isTracking;
		}
		
		if(comps.shooter.GetDpadY()>0){
			isTracking=false;
			lift=Relay::kForward;
		}
		else if(comps.shooter.GetDpadY()<0){
			isTracking=false;
			lift=Relay::kReverse;
		}

		if(isTracking){
			autoTrack();
		}
		if(comps.shooter.GetRawButton(4)){
			isClosest = true;
		}
		if(comps.shooter.GetRawButton(4)){
			isHighGoal = true;
			isClosest = false;
		}
		if(comps.shooter.GetRawButton(2)){
			isHighGoal = false;
			isClosest = false;
		}
		if(isTracking){
			comps.anglePID.Enable();
			comps.rotationPID.Enable();
			angle = comps.anglePID.Get();
			rotation = comps.rotationPID.Get();
		}
		else {
			comps.anglePID.Disable();
			comps.rotationPID.Disable();
			rotation = comps.driver.GetRightX();
			if(rotation == 0){
				rotation = comps.shooter.GetRightX();
			}
		}

		//Handle collector and conveyor
		if(comps.driver.GetRawButton(8)){
			collectorDirection = 1;
		}
		else if (comps.driver.GetRawButton(6)){
			collectorDirection = -1;
		}
		else{
			collectorDirection = 0;
		}
		
		if(comps.driver.GetRawButton(2)){
			comps.collectorMotor.setState(Collector::COLLECTOR_DEPLOY);
		}
		else if(comps.driver.GetRawButton(4)){
			comps.collectorMotor.setState(Collector::COLLECTOR_UNDEPLOY);
		}
		
		if(comps.driver.GetRawButton(7)){
			conveyorVelocity = Relay::kForward;
		}
		else if (comps.driver.GetRawButton(5)){
			conveyorVelocity = Relay::kReverse;
		}
		else{
			conveyorVelocity = Relay::kOff;
		}
		
		//Handle auger
		if(comps.shooter.GetRawButton(10)){
			comps.augerMotor.setState(Auger::AUGER_FEEDING_START);
		}
		else if(comps.shooter.GetRawButton(9)){
			comps.augerMotor.setState(Auger::AUGER_LOADING_START);
		}
		
		mechanismSet();
		Wait(.005);
	}
}

void Zed::updateDriverStation(){
	DriverStationLCD* lcd = DriverStationLCD::GetInstance();
	lcd->Clear();
	lcd->PrintfLine(DriverStationLCD::kUser_Line1, 0,
			"Shooter Speed: %f", shooterSpeed);
	lcd->UpdateLCD();
}

bool isCenter(Packet p){
	return p.isCenter;
}

bool isNotCenter(Packet p){
	return !p.isCenter;
}
bool absDist(Packet p1,Packet p2){
	double dist1=p1.x*p1.x+p1.y*p1.y;
	double dist2=p2.x*p2.x+p2.y*p2.y;
	return dist1<=dist2;
}

typedef std::vector<Packet>::iterator iter;
void Zed::autoTrack(){
	std::vector<Packet> packets = parsePacket();
	if(!isClosest){
		iter sep = std::remove_if(packets.begin(), packets.end(), 
				isHighGoal? isNotCenter: isCenter);
		packets.erase(sep, packets.end());
	}
	iter min = std::min_element(packets.begin(), packets.end(), absDist);
	
	if(min == packets.end()) return;
	
	Components& comps = Components::getInstance();
	comps.angleInput->set(min->y);
	comps.rotationInput->set(min->x);
}

typedef std::string::iterator siter;
std::vector<std::string> tokenize(std::string str, char sep, bool endWithSep){
	std::vector<std::string> tokens;
	siter start = str.begin();
	siter end = str.end();

	while(start != end){
		siter pos = std::find(start, end, sep);
		if(pos == start){
			++start;
			continue;
		}
		else if(pos == end){
			if(endWithSep){
				start = pos;
			}
			else {
				tokens.push_back(std::string(start, pos));
				start = pos;
			}
		}
		else {
			tokens.push_back(std::string(start, pos));
			start = pos + 1;
		}
	}
	return tokens;
}


std::vector<Packet> parsePacket(std::string netPacket){
	using std::string;
	using std::vector;
	vector<Packet> packets;
	vector<string> tokens = tokenize(netPacket, ':', true);

	//Parse tokens
	for(std::vector<string>::iterator i = tokens.begin(); i != tokens.end(); ++i){
		vector<string> values = tokenize(*i, ',', false);
		if(values.size() != 4){
			continue;
		}
		double x, y, dist;
		bool isHigh;
		std::stringstream convert(std::stringstream::in | std::stringstream::out);

		convert << values[0];
		convert >> x;
	
		convert.clear();
		convert << values[1];
		convert >> y;

		convert.clear();
		convert << values[2];
		convert >> dist;

		convert.clear();
		convert << values[3];
		convert >> isHigh;

		Packet p = {x, y, dist, isHigh};
		packets.push_back(p);
	}
	return packets;
}



void Zed::mechanismSet(){
	updateDriverStation();

	Components& comps = Components::getInstance();

	//Drive
	comps.driveTrain.drive(speedX, speedY, rotation);
				
	//Shooter
	comps.shooterMotor.setVelocity(shooterSpeed);
	comps.shooterMotor.setAngle(angle);
				
	//Screw Lift
	comps.screwLiftMotor.set(lift);
	
	//Collector
	comps.collectorMotor.setStarDirection(collectorDirection);
	comps.collectorMotor.doCollector();
	
	//Conveyor
	comps.conveyorMotor.set(conveyorVelocity);
	
	//Auger
	comps.augerMotor.doAuger();
	}
START_ROBOT_CLASS(Zed);
