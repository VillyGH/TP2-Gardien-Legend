#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
class EnemyType1 :
	public AnimatedGameObject
{
public:
	EnemyType1();
	EnemyType1(const EnemyType1& src);
	virtual bool init(const Level01ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;
	bool isFiring();
	void onHit();
};

