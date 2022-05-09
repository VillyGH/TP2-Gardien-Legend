#include "stdafx.h"
#include "StandardEnemyIdleAnimation.h"
#include "Level01ContentManager.h"

const float StandardEnemyIdleAnimation::ANIMATION_LENGTH = 1.5f;

StandardEnemyIdleAnimation::StandardEnemyIdleAnimation(sf::Sprite& s)
	: CyclicAnimation(s, ANIMATION_LENGTH, true)
{

}


bool StandardEnemyIdleAnimation::init(const Level01ContentManager& contentManager)
{
	const sf::Texture& texture = contentManager.getEnemiesTexture();
	frames.push_back(AnimationFrame(texture, sf::IntRect(17, 913, 73, 110)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(22, 913, 73, 110)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(168, 913, 73, 110)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(238, 913, 73, 110)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(313, 913, 73, 110)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(388, 913, 73, 110)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(463, 913, 73, 110)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(538, 913, 73, 110)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(613, 913, 73, 110)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(18, 1032, 76, 112)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(93, 1032, 76, 112)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(236, 1032, 76, 112)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(313, 1032, 76, 112)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(388, 1032, 76, 112)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(463, 1032, 76, 112)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(538, 1032, 76, 112)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(613, 1032, 76, 112)));

	return true;
}