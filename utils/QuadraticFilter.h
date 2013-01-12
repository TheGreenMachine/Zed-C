#ifndef QUADRATIC_FILTER_H
#define QUADRATIC_FILTER_H
#include "GamePadFilter.h"

class QuadraticFilter : public GamePadFilter {
  public :
    float LeftX(float x){return x*x;}
    float LeftY(float x){return x*x;}
    float RightX(float x){return x*x;}
    float RightY(float x){return x*x;}
};
#endif
