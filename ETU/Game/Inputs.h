#pragma once

struct Inputs
{
	static const float CONTROLLER_DEAD_ZONE;

	Inputs();
	void reset();
	//Port�e analogue -100 � 100
	static float eliminateVibration(float analogInput);
	bool playFireSound;
	float moveFactorX;
	float moveFactorY;

};

