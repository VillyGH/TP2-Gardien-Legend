#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
struct Inputs;
class Player :
    public AnimatedGameObject
{
	static const float PLAYER_MOVE_SPEED;
 public:
  Player();
   virtual bool init(const Level01ContentManager& contentManager);
   
   bool update(float deltaT, const Inputs& inputs) override;
   void handleOutOfBoundsPosition();
};

