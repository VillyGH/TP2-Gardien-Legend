#pragma once
#include "GameObject.h"
#include "AnimationState.h"

class Level01ContentManager;
class Animation;
struct Inputs;
class AnimatedGameObject :
    public GameObject
{
public:
  AnimatedGameObject();
  virtual ~AnimatedGameObject();
  AnimatedGameObject(const AnimatedGameObject& src);

  virtual bool update(float deltaT, const Inputs& inputs) ;
  virtual void draw(sf::RenderWindow& window) const override;
  virtual bool init(const Level01ContentManager& contentManager);

protected:
  State currentState;
  std::map<State, Animation*> animations;
  Level01ContentManager* contentManager;
private:
  AnimatedGameObject& operator=(const AnimatedGameObject&);

  
};

