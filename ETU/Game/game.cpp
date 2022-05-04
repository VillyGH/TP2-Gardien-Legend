#include "stdafx.h"
#include "game.h"
#include "ContentManager.h"
#include "TitleScene.h"
#include "Level01Scene.h"
#include "ScoreboardScene.h"
#include "scenetype.h"

const unsigned int Game::FRAME_RATE = 60;
const unsigned int Game::GAME_WIDTH = 720;
const unsigned int Game::GAME_HEIGHT = 1080;

Game::Game(std::string windowName)
  : gameName(windowName)
{
}

void Game::run()
{
  if (!init())
  {
    return;
  }

  while (window.isOpen())
  {
    bool windowIsClosed = handleEvents();
    if (windowIsClosed || true == update())
    {
      // On termine "normalement" l'application
      break;
    }
    else
    {
      window.clear();
      draw(window);
      window.display();
    }
  }

  uninit();
}

bool Game::handleEvents()
{
  bool retval = true;
  if (!scenes.empty())
    retval = scenes.top()->handleEvents(window);
  return retval;
}

bool Game::update()
{
  bool gameMustEnd = scenes.empty();
  if (!gameMustEnd)
  {
    SceneType nextSceneType = scenes.top()->update();
    // Si la nouvelle scène attendue est différente de l'ancienne...
    if (nextSceneType != scenes.top()->getSceneType())
    {
      Scene* nextScene = nullptr;
      // ... soit on veut retirer la scène courant de la pile
      if (SceneType::NONE== nextSceneType)
      {
        popScene(false);
      }
      else
      {
        // ... soit on veut en ajouter une nouvelle
        nextScene = getNextScene(nextSceneType);
      }
      if (nextScene != nullptr)
        pushScene(nextScene);
    }
  }
  return gameMustEnd;

}

bool Game::popScene(bool initNextScene)
{
  if (!scenes.empty())
  {
    Scene* top = scenes.top();
    top->uninit();
    delete top;
    scenes.pop();

    if (!scenes.empty())
    {
      if (initNextScene)
        scenes.top()->init();
      else
        scenes.top()->unPause();
    }
  }

  return scenes.empty();
}

bool Game::pushScene(Scene* newScene)
{
     bool retval = newScene->init();
  if (retval)
  {
    if (!scenes.empty())
      scenes.top()->pause();
    scenes.push(newScene);
  }

  return retval;
}

void Game::draw(sf::RenderWindow& window)  const
{
  if (!scenes.empty())
  {
    scenes.top()->draw(window);
  }
}

bool Game::init()
{
  window.create(sf::VideoMode(Game::GAME_WIDTH, Game::GAME_HEIGHT, 32), gameName);
  window.setFramerateLimit(FRAME_RATE);
  
  return pushScene(new InitialScene());
}

bool Game::uninit()
{
  while (!scenes.empty())
  {
    popScene(false);
  }
  return true;
}


Scene* Game::getNextScene(SceneType type) const
{
    Scene* scene = nullptr;
    switch (type)
    {
    case SceneType::TITLE_SCENE:
    {
        scene = new TitleScene();
        break;
    }
    case SceneType::LEVEL01_SCENE:
    {
        scene = new Level01Scene();
        break;
    }

    case SceneType::END_GAME_SCENE:
    {
        scene = new ScoreboardScene();
        break;
    }
    default:
    {
        scene = nullptr;
        break;
    }
    }
    return scene;
}

