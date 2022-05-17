#pragma once
#include "GameObject.h"
struct Inputs;

class PlayerShip : public GameObject
{
	static const float PLAYER_MOVE_SPEED;
public:
	PlayerShip();	
	bool update(const Inputs& inputs, float elapsedTime);
private:
	void handleOutOfBoundsPosition();
};


