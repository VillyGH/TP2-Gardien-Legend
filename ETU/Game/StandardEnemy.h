#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
class StandardEnemy :
	public AnimatedGameObject
{
public:
	static const float MAX_ENEMY_HEALTH;
	StandardEnemy();
	StandardEnemy(const StandardEnemy& src);
	virtual bool init(const Level01ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;
	bool isFiring();
	void onHit(float damage);
	void checkOutOfBounds();

private:
	float health;
	sf::Sound sound;
	sf::SoundBuffer soundBuffer;
};

