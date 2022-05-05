#pragma once
#include "Scene.h"
#include "MenuContentManager.h"
//#include "Hud.h"
class TitleScene :
    public Scene
{
public:
    // Héritées via Scene
    TitleScene();
    ~TitleScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
private:
    MenuContentManager contentManager;
    sf::Texture menuImageTexture;
    sf::Sprite menuImage;
    sf::Text menuStartText;
    sf::Music titleMusic;
    bool gameStarted;
};
