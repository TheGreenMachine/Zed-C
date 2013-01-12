#ifndef AUTO_STEP_H
#define AUTO_STEP_H

class AutoStep {
	public:
		virtual void init() = 0;
		virtual void run() = 0;
		virtual bool isDone() = 0;
		virtual void finish() = 0;
};

#endif
