#pragma once
#include "AnimatedGameObject.h"
struct Inputs;
class Player :
    public AnimatedGameObject
{
	static const float PLAYER_MOVE_SPEED;
 public:
  Player();
   virtual bool init(const ContentManager& contentManager) override;
   
   bool update(float deltaT, const Inputs& inputs) override;
   void handleOutOfBoundsPosition();
};

