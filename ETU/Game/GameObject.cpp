#include "stdafx.h"
#include "GameObject.h"
#define RADIANS_TO_DEGREE 57.295779513f

GameObject::GameObject()
  : Sprite()
{
  active = false;
}

GameObject::GameObject(const GameObject& src)
  : Sprite(src)
  , active(src.active)
{
  if (nullptr != src.getTexture())
  {
    setTextureRect(src.getTextureRect());
    initialize(*src.getTexture(), src.getPosition());
  }
}

float GameObject::getAngleWith(const GameObject& other) const
{
  return atan2f(other.getPosition().y - getPosition().y, other.getPosition().x - getPosition().x);
}

void GameObject::draw(sf::RenderWindow& window) const
{
  if (isActive())
    window.draw(*this, sf::RenderStates(sf::BlendAlpha));
}

void GameObject::activate()
{
  active = true;
}

void GameObject::deactivate()
{
  active = false;
}

bool GameObject::isActive() const
{
  return active;
}

bool GameObject::collidesWith(const GameObject& other) const
{
  return isActive() && other.isActive() && getGlobalBounds().intersects(other.getGlobalBounds());
}

float GameObject::getRotationAngleInRadians() const
{
  return getRotation() / RADIANS_TO_DEGREE;
}


void GameObject::setRotationAngleRadians(const float angle)
{
  setRotation(angle * RADIANS_TO_DEGREE);
}

void GameObject::rotateInRadians(const float angle)
{
  rotate(angle * RADIANS_TO_DEGREE);
}

void GameObject::initialize(const sf::Texture& texture, const sf::Vector2f& initialPoistion)
{
  setTexture(texture);
  const sf::IntRect& rect = getTextureRect();
  setOrigin(sf::Vector2f(rect.width / 2.0f, rect.height / 2.0f));
  setPosition(initialPoistion);
}
bool GameObject::init(const Level01ContentManager& contentManager)
{
  return true;
}

bool GameObject::update(float deltaT)
{
  return false;
}
bool GameObject::update(float deltaT, const Inputs& inputs)
{
  return false;
}