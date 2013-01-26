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
	while(IsEnabled() && IsOperatorControl()){
		speedX = comps.driver.GetLeftX();
		speedY = -comps.driver.GetLeftY();
		if(comps.shooter.GetRawButton(5)){
			//rotation = PID;
		}
		else {
			rotation = comps.driver.GetRightX();
		}

		if(comps.shooter.GetRawButton(6)){
			shooterSpeed+=SHOOTER_MEDIUM_STEP;
		}
		else if(comps.shooter.GetRawButton(8)){
			shooterSpeed-=SHOOTER_MEDIUM_STEP;
		}
		else if(comps.shooter.GetRawButton(1)){
			shooterSpeed= SHOOTER_LOW_SPEED;
		}
		else if(comps.shooter.GetRawButton(2)){
			shooterSpeed= SHOOTER_MEDIUM_SPEED;
		}
		else if(comps.shooter.GetRawButton(3)){
			shooterSpeed= SHOOTER_HIGH_SPEED;
		}
		else {
			shooterSpeed+= comps.shooter.GetRawAxis(5)*SHOOTER_LARGE_STEP;
			shooterSpeed+= comps.shooter.GetRawAxis(6)*SHOOTER_SMALL_STEP;
		}
		collect = comps.driver.GetRawButton(6);
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

bool isntCenter(Packet p){
	return !p.isCenter;
}
bool absDist(Packet p1,Packet p2){
	double dist1=p1.x*p1.x+p1.y*p1.y;
	double dist2=p2.x*p2.x+p2.y*p2.y;
	return dist1<=dist2;
}

typedef std::vector<Packet>::iterator iter;
void Zed::autoTrack(bool highGoal){
	std::vector<Packet> packets = parsePacket();
	packets.erase(
			std::remove_if(packets.begin(), packets.end(), highGoal?isntCenter:isCenter),
			packets.end());
	iter pos =std::min_element(packets.begin(),packets.end(),absDist);
	if(pos == packets.end()) return;
	Components& comps = Components::getInstance();
	comps.angleInput->set(pos->y);
	comps.rotationInput->set(pos->x);
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
        
        //Collector
      //  comps.collectorMotor.SetSpeed(
        //    collect? 0.75 : 0
        //);
}
START_ROBOT_CLASS(Zed);
