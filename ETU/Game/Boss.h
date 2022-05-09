#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
class Boss :
	public AnimatedGameObject
{
public:
	//static const float BOSS_SPAWN_Y_POSITION;
	Boss();
	Boss(const Boss& src);
	virtual bool init(const Level01ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;
	bool isFiring();
	void onHit();
};

