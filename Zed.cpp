#include "Zed.h"
#include "utils/utils.h"
#include "Components.h"
#include "WPILib.h"
#include "robot/Shooter.h"
#include <vector>
#include <algorithm>

Zed::Zed(){}

void Zed::Autonomous(){}

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

std::vector<Packet> Zed::parsePacket(){
	double x;
	double y;
	double dist;
	int isCenter;
	char packetStr[1024];
	char *save1;
	char *save2;
	std::vector<Packet> packets;
	NetworkTable* packetTable = NetworkTable::GetTable ("vision");
	std::string netPacket = packetTable->GetString("vtdata");
	strncpy(packetStr, netPacket.c_str(),1023);
	packetStr[1023] = '\0';
	char* packet = strtok_r(packetStr,":",&save1);
	while(packet != NULL){
		sscanf(packet, "%lg,%lg,%lg,%d", &x,&y,&dist,&isCenter);
		Packet p = {x,y,dist,isCenter};
		packets.push_back(p);
		packet=strtok(NULL,":");
		strtok_r(packet,NULL,&save2);
	}
	return packets;
}



void Zed::mechanismSet(){
	updateDriverStation();

	Components& comps = Components::getInstance();

	//Drive
	comps.driveTrain.drive(speedX, speedY, rotation);
				
	//Shooter
	//comps.shooterMotor.setVelocity(shooterSpeed);
	//comps.shooterMotor.setAngle(angle);
				
	//Collector
	comps.collectorMotor.set(collectorDirection);
	
	//Conveyor
	comps.conveyorMotor.set(conveyorVelocity);
	
}
START_ROBOT_CLASS(Zed);
