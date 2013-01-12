#ifndef AUTO_MANAGER_H
#define AUTO_MANAGER_H
#include <vector>
#include "smartptr.h"
#include "WPILib.h"
#include "AutoStep.h"
class AutoManager {
	public:
		AutoManager(SimpleRobot& base, 
					const std::vector<smartptr<AutoStep> >& inputSteps):
			robot(base),
			steps(inputSteps){}
		void run();
	protected:
		SimpleRobot& robot;
		std::vector<smartptr<AutoStep> > steps;
		bool isRunning();
};
#endif
