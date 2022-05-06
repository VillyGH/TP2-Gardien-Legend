#include "stdafx.h"
#include "PlayerShip.h"
#include "game.h"
#include "Inputs.h"
#include <iostream>


const float PlayerShip::PLAYER_MOVE_SPEED = 100.0f;

PlayerShip::PlayerShip()
{
	activate();
	
}


bool PlayerShip::update(const Inputs& inputs, float elapsedTime)
{
	
	return false;
}



