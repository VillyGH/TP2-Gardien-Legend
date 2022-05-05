#include "stdafx.h"
#include "EnemyType1IdleAnimation.h"
#include "Level01ContentManager.h"

const float EnemyType1IdleAnimation::ANIMATION_LENGTH = 1.5f;

EnemyType1IdleAnimation::EnemyType1IdleAnimation(sf::Sprite& s)
	: CyclicAnimation(s, ANIMATION_LENGTH, true)
{

}


bool EnemyType1IdleAnimation::init(const Level01ContentManager& contentManager)
{
	const sf::Texture& texture = contentManager.getEnemiesTexture();
	frames.push_back(AnimationFrame(texture, sf::IntRect(17, 913, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(22, 913, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(168, 913, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(238, 913, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(313, 913, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(388, 913, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(463, 913, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(538, 913, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(613, 913, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(18, 1030, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(93, 1030, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(238, 1030, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(313, 1030, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(388, 1030, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(463, 1030, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(536, 1030, 70, 118)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(611, 1030, 70, 118)));

	return true;
}