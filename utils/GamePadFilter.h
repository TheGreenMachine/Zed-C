#ifndef GAMEPAD_FILTER_H
#define GAMEPAD_FILTER_H

/*
 * An abstract base class for designing gamepad filters
 */
class GamePadFilter
{
public:
    virtual float LeftX(float) = 0;
    virtual float RightX(float) = 0;
    virtual float LeftY(float) = 0;
    virtual float RightY(float) = 0;
};
#endif
