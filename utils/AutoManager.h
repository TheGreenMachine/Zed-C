#ifndef AUTO_MANAGER_H
#define AUTO_MANAGER_H
#include <vector>
#include "WPILib.h"

class AutoManager {
  public:
    AutoManager(SimpleRobot& base, 
          const std::vector<smartptr<AutoStep> >& inputSteps):
      robot(base),
      steps(inputSteps){}
    void run();
  private:
    std::vector<smartptr<AutoStep> > steps;
    SimpleRobot& robot;
    bool isRunning();
};
#endif
