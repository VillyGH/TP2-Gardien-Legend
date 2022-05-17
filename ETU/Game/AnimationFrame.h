#pragma once
class AnimationFrame
{

public:
	AnimationFrame(const sf::Texture& text, sf::IntRect rect = sf::IntRect());
	const sf::Texture& getTexture() const;
	const sf::IntRect& getRectangle() const;
private:
	const sf::Texture& texture;
	sf::IntRect rectangle;
};

