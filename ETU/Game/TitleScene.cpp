#include "stdafx.h"
#include "TitleScene.h"
#include "TitleSceneContentManager.h"
#include "game.h"

const unsigned int TitleScene::TEXT_SIZE = 25;

TitleScene::TitleScene()
  : Scene(SceneType::TITLE_SCENE),
    nextScene(SceneType::TITLE_SCENE)
{

}

TitleScene::~TitleScene()
{

}
SceneType TitleScene::update()
{
    if (nextScene != SceneType::TITLE_SCENE)
    {
        SceneType retval = nextScene;
        nextScene = SceneType::TITLE_SCENE;
        return retval;
    }
    return nextScene = getSceneType();
}

void TitleScene::draw(sf::RenderWindow& window) const
{
  window.draw(menuImage);
  window.draw(titleText);

}

bool TitleScene::init()
{
  if (TitleSceneContentManager::getInstance().loadContent() == false)
  {
    return false;
  }

  menuImage.setTexture(TitleSceneContentManager::getInstance().getTitleScreenTexture());
  menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
  menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);

  titleText.setFont(TitleSceneContentManager::getInstance().getMainFont());
  titleText.setCharacterSize(TEXT_SIZE);
  titleText.setString("Press any key to start game");
  titleText.setPosition((Game::GAME_WIDTH - titleText.getLocalBounds().width) / 2, (Game::GAME_HEIGHT - titleText.getLocalBounds().height) /1.25);

  if (!spaceGameMusic.openFromFile("Assets\\Music\\Title\\SkyFire.ogg"))
      return false;

  spaceGameMusic.setLoop(true);

  spaceGameMusic.play();

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
    if (event.type == sf::Event::KeyPressed) 
        nextScene = SceneType::LEVEL01;
   

  }
  return retval;

}
