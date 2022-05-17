#include "stdafx.h"
#include "StandardEnemyExplosionAnimation.h"
#include "Level01ContentManager.h"
#include "ContentManager.h"

const float StandardEnemyExplosionAnimation::ANIMATION_LENGTH = 0.75f;

StandardEnemyExplosionAnimation::StandardEnemyExplosionAnimation(sf::Sprite& s)
	: LinearAnimation(s, ANIMATION_LENGTH)
{

}


bool StandardEnemyExplosionAnimation::init(const Level01ContentManager& contentManager)
{
	const sf::Texture& texture = contentManager.;

	frames.push_back(AnimationFrame(texture, sf::IntRect(10, 313, 50, 50)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(68, 332, 20, 20)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(91, 328, 30, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(119, 324, 35, 35)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(157, 324, 35, 35)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(195, 329, 25, 25)));
	return true;
}