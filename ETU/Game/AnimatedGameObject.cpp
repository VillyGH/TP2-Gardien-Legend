#include "stdafx.h"
#include "AnimatedGameObject.h"
#include "Animation.h"

AnimatedGameObject::AnimatedGameObject()
	: currentState(State::NONE)
	, contentManager(nullptr)
{

}
AnimatedGameObject::~AnimatedGameObject()
{
	for (auto const& anim : animations)
	{
		delete anim.second;
	}
	animations.clear();
}
AnimatedGameObject::AnimatedGameObject(const AnimatedGameObject& src)
	:GameObject(src)
	, contentManager(src.contentManager)
	, currentState(State::NONE)

{

}
void AnimatedGameObject::draw(sf::RenderWindow& window) const
{
	if (isActive())
		window.draw(*this);
}

bool AnimatedGameObject::update(float deltaT, const Inputs& inputs)
{
	bool retval = GameObject::update(deltaT);
	if (false == retval)
		animations[currentState]->update(deltaT, inputs);

	return retval;
}

bool AnimatedGameObject::init(const Level01ContentManager& contentManager)
{
	this->contentManager = const_cast<Level01ContentManager*>(&contentManager);
	return true;
}