#include "stdafx.h"
#include "TitleScene.h"
#include "game.h"

TitleScene::TitleScene()
  : Scene(SceneType::TITLE_SCENE)
{

}

TitleScene::~TitleScene()
{

}
SceneType TitleScene::update()
{
  return getSceneType();
}

void TitleScene::draw(sf::RenderWindow& window) const
{
  window.draw(menuImage);
}

bool TitleScene::init()
{
  if(contentManager.loadContent())
    return false;
  menuImage.setTexture(contentManager.getTitleScreenTexture());
  menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
  menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);

  hud.initialize(contentManager);
  hud.addMenuStartText();

  return true;
}

bool TitleScene::uninit()
{
  return true;
}

bool TitleScene::handleEvents(sf::RenderWindow& window)
{
  bool retval = false;
  sf::Event event;
  while (window.pollEvent(event))
  {
    //x sur la fenêtre
    if (event.type == sf::Event::Closed)
    {
      window.close();
      retval = true;
    }
  }
  return retval;

}
