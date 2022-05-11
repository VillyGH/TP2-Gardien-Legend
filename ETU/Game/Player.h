#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
#include "Subscriber.h"
struct Inputs;
class Player :
	public AnimatedGameObject, public Subscriber
{
public: 
	virtual void notify(Event event, const void* data) override;
public:
	static const float PLAYER_MOVE_SPEED;
	static const float INITIAL_LIFE_COUNT;
	Player();
	virtual bool init(const Level01ContentManager& contentManager);

	bool update(float deltaT, const Inputs& inputs) override;
	void handleOutOfBoundsPosition();

	bool isGunBonusActive();

	float gunBonusTimer;
	bool gunBonusIsActive; 
};

