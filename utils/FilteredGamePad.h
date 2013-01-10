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
class FilteredGamePad : public GamePadL {
	public:
		FilteredGamePad( const std::vector< smartptr<GamePadFilter> >& inputFilters):
			filters(inputFilters) {}

		virtual float GetLeftX();
		virtual float GetLeftY();
		virtual float GetRightX();
		virtual float GetRightY();
};

#endif
