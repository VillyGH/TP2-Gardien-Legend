#pragma once

struct Inputs
{
	static const float CONTROLLER_DEAD_ZONE;

	Inputs();
	void reset();
	//Portée analogue -100 à 100
	static float eliminateVibration(float analogInput);
	bool playFireSound;
	float moveFactorX;
	float moveFactorY;

};

