#include "AutoManager.h"

typedef std::vector<smartptr<AutoStep> >::iterator iter; //For readability

void AutoManager::run(){
	for(iter i = steps.begin(); i != steps.end() && isRunning(); ++i){
		(*i)->init();
		while(isRunning() && !((*i)->isDone() )){
			(*i)->run();
		}
		(*i)->finish();
	}
}

bool AutoManager::isRunning(){
	return robot.IsEnabled() && robot.IsAutonomous();
}
