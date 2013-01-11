#include "AutoManager.h"

typedef std::vector::iterator iter; //For readability

void AutoManager::run(){
	for(iter i = steps.begin(); steps != steps.end() && isRunning(); ++i){
		i->start();
		while(isRunning() && !i->isDone()){
			i->run();
		}
		i->finish();
	}
}

bool AutoManager::isRunning(){
	return robot.IsEnabled() && robot.IsAutonomous();
}
