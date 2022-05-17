#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
#include "stdafx.h"
class Player;
class Boss :
	public AnimatedGameObject
{
public:
	static const float BOSS_SPAWN_Y_POSITION;
	static const float BOSS_Y_MAX_POSITION;
	static const float BOSS_VERTICAL_SPEED;
	static const float BOSS_SPAWN_KILL_COUNT;
	static const float BOSS_HORIZONTAL_SPEED;
	static const float MAX_BOSS_HEALTH;
	static const float HEALTH_BAR_MAX_WIDTH;
	static const float HEALTH_BAR_MAX_HEIGHT;
	static const float BOSS_BULLET_DAMAGE;
	static const float MIN_FIRING_FRAME;
	static const float MAX_FIRING_FRAME;

	static const sf::Vector2f BOSS_SCALING_SIZE;

	Boss();
	Boss(const Boss& src);
	virtual bool init(const Level01ContentManager& contentManager) override;
	bool initHealthBar(const Level01ContentManager& contentManager);
	bool update(float deltaT, const Inputs& inputs, const sf::Vector2f& dest);
	bool updateHealthBar();
	bool isFiring();
	void playFireSound();
	void setDestination(const sf::Vector2f& destination);
	void onHit();
	virtual void draw(sf::RenderWindow& window) const override;

private:	
	sf::Vector2f destination;
	float moveAngle;
	float health;
	sf::Sound sound;
	sf::SoundBuffer firingSoundBuffer;
	sf::SoundBuffer deathSoundBuffer;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner; 
};

