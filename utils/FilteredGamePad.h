#ifndef FILTERED_GAMEPAD_H
#define FILTERED_GAMEPAD_H

#include "GamePadL.h"
#include "GamePadFilter.h"
#include "smartptr.h"
#include <vector>


/*
 * Currently provides filtering for only 4 functions
 *	GetLeftX
 *	GetRightX
 *	getLeftY
 *	getRightY
 */
class FilteredGamePad : public GamepadL {
	public:
		FilteredGamePad(unsigned int port, const std::vector< smartptr<GamePadFilter> >& inputFilters):
			GamepadL(port),
			filters(inputFilters){}

		virtual float GetLeftX();
		virtual float GetLeftY();
		virtual float GetRightX();
		virtual float GetRightY();
	private:
		std::vector<smartptr<GamePadFilter> > filters;
};

#endif
