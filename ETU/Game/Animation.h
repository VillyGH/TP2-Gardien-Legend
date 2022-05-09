#pragma once
#include "AnimationFrame.h"
struct Inputs;
class Level01ContentManager;
class Animation
{
public:
	void reset();
	virtual void update(float deltaT, const Inputs& inputs);
	virtual unsigned int getNextFrame() const = 0;
	virtual bool init(const Level01ContentManager& contentManager) = 0;
	float getTimeInCurrentState() const;
	virtual bool isOver() const;
	virtual float getPercentage() const = 0;
protected:

	Animation(sf::Sprite& s, float length);
	std::vector<AnimationFrame> frames;
	float lengthInSeconds;
	float timeInCurrentState;

private:
	sf::Sprite& sprite;
};

