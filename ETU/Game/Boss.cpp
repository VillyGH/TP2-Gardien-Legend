#include "stdafx.h"
#include "Boss.h"
#include "Inputs.h"
#include "game.h"
#include "BossIdleAnimation.h"
#include "Publisher.h"

const float Boss::BOSS_SPAWN_Y_POSITION = -15;
const float Boss::BOSS_Y_MAX_POSITION = 160;
const float Boss::BOSS_VERTICAL_SPEED = 4;
const float Boss::BOSS_HORIZONTAL_SPEED = 8;
const float Boss::BOSS_BULLET_DAMAGE = 25;
const float Boss::BOSS_SPAWN_KILL_COUNT = 15;
const sf::Vector2f Boss::BOSS_SCALING_SIZE(1.5, 1.5); 
const float Boss::MAX_BOSS_HEALTH = 100;
const float Boss::HEALTH_BAR_MAX_WIDTH = 100;
const float Boss::HEALTH_BAR_MAX_HEIGHT = 10;
const float Boss::MIN_FIRING_FRAME = 6;
const float Boss::MAX_FIRING_FRAME = 12;





Boss::Boss()
	 :moveAngle(0)
	, health(0)
{

}
Boss::Boss(const Boss& src)
	: AnimatedGameObject(src)
{
	init(*contentManager);
	setPosition(src.getPosition());
	if (src.isActive())
		activate();
	else
		deactivate();
}
bool Boss::init(const Level01ContentManager& contentManager)
{
	setPosition(sf::Vector2f(Game::GAME_WIDTH * 0.5f, BOSS_SPAWN_Y_POSITION));
	health = MAX_BOSS_HEALTH; 
	initHealthBar(contentManager);
	currentState = State::BOSS;
	Animation* idleAnimation = new BossIdleAnimation(*this);
	bool retval = idleAnimation->init(contentManager);
	if (retval)
		animations[State::BOSS] = idleAnimation;
	this->scale(BOSS_SCALING_SIZE);
	deathSoundBuffer = contentManager.getEnemyKilledSoundBuffer();
	firingSoundBuffer = contentManager.getEnemyGunSoundBuffer();

	sound.setMinDistance(10);
	sound.setVolume(10);
	return retval && AnimatedGameObject::init(contentManager);
}

bool Boss::initHealthBar(const Level01ContentManager& contentManager) {
	hpBarBack.setSize(sf::Vector2f(HEALTH_BAR_MAX_WIDTH + 10, HEALTH_BAR_MAX_HEIGHT + 5));
	hpBarBack.setFillColor(sf::Color::White);
	hpBarBack.setOrigin(hpBarBack.getSize().x / 2, hpBarBack.getSize().y / 2);

	hpBarInner.setSize(sf::Vector2f(HEALTH_BAR_MAX_WIDTH, HEALTH_BAR_MAX_HEIGHT));
	hpBarInner.setFillColor(sf::Color::Red);
	hpBarInner.setOrigin(hpBarInner.getSize().x / 2, hpBarInner.getSize().y / 2);


	return false;
}

void Boss::draw(sf::RenderWindow& window) const
{
	if (isActive()) {
		window.draw(hpBarBack);
		window.draw(*this);
		window.draw(hpBarInner);
	}



}

bool Boss::update(const float deltaT, const Inputs& inputs, const sf::Vector2f& dest)
{
	if(getPosition().y < BOSS_Y_MAX_POSITION)
		move(sf::Vector2f(0, BOSS_VERTICAL_SPEED));
	else 
	{
		setDestination(dest);
		move(cos(moveAngle) * BOSS_HORIZONTAL_SPEED, 0);
	}

	if (getGlobalBounds().height < -getGlobalBounds().height * 0.5f)
		setPosition(getPosition().x, 0);

	if (animations[currentState]->isOver())
		return true;

	updateHealthBar();


	return AnimatedGameObject::update(deltaT, inputs);
}

bool Boss::updateHealthBar() {
	float percent = health / MAX_BOSS_HEALTH;
	hpBarInner.setSize(
		sf::Vector2f(static_cast<float>(std::floor(HEALTH_BAR_MAX_WIDTH * percent)),
			hpBarInner.getSize().y
		)
	);

	hpBarBack.setPosition(getPosition().x, getGlobalBounds().top - 10);
	hpBarInner.setPosition(hpBarBack.getPosition());

	return false;
}

void Boss::playFireSound() {
	sound.setBuffer(firingSoundBuffer);
	sound.play();
}

bool Boss::isFiring() {
	if (animations[currentState]->getNextFrame() > MIN_FIRING_FRAME && animations[currentState]->getNextFrame() < MAX_FIRING_FRAME)
		return true;
	return false;
}

void Boss::setDestination(const sf::Vector2f& dest) 
{
	destination.x = dest.x;
	destination.y = dest.y;
	moveAngle = atan2f((destination.y - getPosition().y), (destination.x - getPosition().x));
}


void Boss::onHit()
 {
	health--;
	if (health <= 0) {
		sound.setBuffer(deathSoundBuffer);
		sound.play();
		Publisher::notifySubscribers(Event::BOSS_KILLED, this);
		deactivate();
	}
}