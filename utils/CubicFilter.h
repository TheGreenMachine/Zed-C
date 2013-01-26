#ifndef CUBIC_FILTER_H
#define CUBIC_FILTER_H
#include "GamePadFilter.h"

class CubicFilter : public GamePadFilter {
	public :
		float LeftX(float x){return x*x*x;}
		float LeftY(float x){return x*x*x;}
		float RightX(float x){return x*x*x;}
		float RightY(float x){return x*x*x;}
};
#endif
