//Implicitly import all necessary classes from header file
#include "FilteredGamePad.h"

typedef std::vector<smartptr<GamePadFilter> >::iterator iter;

float FilteredGamePad::GetLeftX(){
	float result = GamepadL::GetLeftX();
	for(iter i = filters.begin(); i != filters.end(); ++i){
		result = (*i)->LeftX(result);
	}
	return result;
}


float FilteredGamePad::GetLeftY(){
	float result = GamepadL::GetLeftY();
	for(iter i = filters.begin(); i != filters.end(); ++i){
		result = (*i)->LeftY(result);
	}
	return result;
}


float FilteredGamePad::GetRightX(){
	float result = GamepadL::GetRightX();
	for(iter i = filters.begin(); i != filters.end(); ++i){
		result = (*i)->RightX(result);
	}
	return result;
}

float FilteredGamePad::GetRightY(){
	float result = GamepadL::GetLeftY();
	for(iter i = filters.begin(); i != filters.end(); ++i){
		result = (*i)->LeftY(result);
	}
	return result;
}
