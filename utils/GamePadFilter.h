#ifndef GAMEPAD_FILTER_H
#define GAMEPAD_FILTER_H

/*
 * An abstract base class for designing gamepad filters
 */
class GamePadFilter {
	public:
		virtual double LeftX(double) = 0;
		virtual double RightX(double) = 0;
		virtual double LeftY(double) = 0;
		virtual double RightY(double) = 0;
};
#endif
