#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
#include "stdafx.h"
class Boss :
	public AnimatedGameObject
{
public:
	static const float BOSS_SPAWN_Y_POSITION;
	static const float BOSS_Y_MAX_POSITION;
	static const float BOSS_VERTICAL_SPEED;
	static const float BOSS_HORIZONTAL_SPEED;
	static const sf::Vector2f BOSS_SCALING_SIZE;
	static const float MAX_BOSS_HEALTH;


	Boss();
	Boss(const Boss& src);
	virtual bool init(const Level01ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs, sf::Vector2f destination);
	bool isFiring();
	void setDestination(const sf::Vector2f& destination);
	void onHit();

private:	
	sf::Vector2f destination;
	float moveAngle;
	float health;
};

