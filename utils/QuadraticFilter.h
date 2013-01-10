#ifndef QUADRATIC_FILTER_H
#define QUADRATIC_FILTER_H
#include "GamePadFilter"

class QuadraticFilter : public GamePadFilter {
  public :
    double LeftX(double x){return x*x;}
    double LeftY(double x){return x*x;}
    double RightX(double x){return x*x;}
    double RightY(double x){return x*x;}

#endif
