//Implicitly import all necessary classes from header file
#include "FilteredGamePad.h"

float FilteredGamePad::GetLeftX(){
	float result = GamePadL::GetLeftX();
	for(std::vector::iterator i = filters.begin(); i != v.end(); ++i){
		result = i->LeftX(result);
	}
	return result;
}


float FilteredGamePad::GetLeftY(){
	float result = GamePadL::GetLeftY();
	for(std::vector::iterator i = filters.begin(); i != v.end(); ++i){
		result = i->LeftY(result);
	}
	return result;
}


float FilteredGamePad::GetRightX(){
	float result = GamePadL::GetRightX();
	for(std::vector::iterator i = filters.begin(); i != v.end(); ++i){
		result = i->RightX(result);
	}
	return result;
}

float FilteredGamePad::GetLeftY(){
	float result = GamePadL::GetLeftY();
	for(std::vector::iterator i = filters.begin(); i != v.end(); ++i){
		result = i->LeftY(result);
	}
	return result;
}
