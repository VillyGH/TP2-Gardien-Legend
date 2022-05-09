#include "stdafx.h"
#include "BossIdleAnimation.h"
#include "Level01ContentManager.h"

const float BossIdleAnimation::ANIMATION_LENGTH = 1.5f;

BossIdleAnimation::BossIdleAnimation(sf::Sprite& s)
	: CyclicAnimation(s, ANIMATION_LENGTH, true)
{

}


bool BossIdleAnimation::init(const Level01ContentManager& contentManager)
{
	const sf::Texture& texture = contentManager.getEnemiesTexture();
	frames.push_back(AnimationFrame(texture, sf::IntRect(30, 1904, 91, 134)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(130, 1904, 91, 134)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(227, 1904, 91, 146)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(323, 1904, 91, 146)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(420, 1904, 91, 146)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(520, 1904, 91, 146)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(30, 2068, 91, 146)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(135, 2068, 77, 159)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(235, 2068, 77, 160)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(331, 2068, 77, 174)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(430, 2068, 77, 185)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(525, 2068, 77, 185)));

	return true;
}