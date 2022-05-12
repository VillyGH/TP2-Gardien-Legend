#pragma once
#include "Level01ContentManager.h"
#include "GameObject.h"


class LifeBonus :

    public GameObject
{
public:
    static const sf::Vector2f SCALING_SIZE;
    static const float BONUS_LIFE;
    static const float BONUS_POINTS;

    LifeBonus();
    virtual bool init(const Level01ContentManager& contentManager) override;
    void onPickUp();
    virtual bool update(float deltaT, const Inputs& inputs) override;
    void checkOutOfBounds();
private:
    float bonusTimer;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    float life;
};

