#include "stdafx.h"
#include "AnimationFrame.h"

AnimationFrame::AnimationFrame(const sf::Texture& text, sf::IntRect rect)
	: texture(text)
	, rectangle(rect)
{
}

const sf::Texture& AnimationFrame::getTexture() const
{
	return texture;
}

const sf::IntRect& AnimationFrame::getRectangle() const
{
	return rectangle;
}