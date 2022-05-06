#include "stdafx.h"
#include "TitleScene.h"
#include "game.h"

TitleScene::TitleScene()
  : Scene(SceneType::TITLE_SCENE),
    gameStarted(false)
{

}

TitleScene::~TitleScene()
{

}
SceneType TitleScene::update()
{
    SceneType retval = getSceneType();

    if (gameStarted)
        retval = SceneType::LEVEL01_SCENE;

    return retval;
}

void TitleScene::draw(sf::RenderWindow& window) const
{
    window.draw(menuImage);
    window.draw(menuStartText);
}

bool TitleScene::init()
{
    if (!contentManager.loadContent())
        return false;

    if (!titleMusic.openFromFile("Assets\\Music\\Title\\SkyFire (Title Screen).ogg"))
        return false;
    titleMusic.setVolume(10);
    titleMusic.setLoop(true);
    titleMusic.play();

    menuImage.setTexture(contentManager.getTitleScreenTexture());
    menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
    menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);

    const std::string menuStartString = "Press any key to start";
    menuStartText.setFont(contentManager.getMainFont());
    menuStartText.setCharacterSize(16);
    menuStartText.setFillColor(sf::Color::White);
    menuStartText.setPosition(Game::GAME_WIDTH / 2.0f - menuStartText.getLocalBounds().width / 2.0f, Game::GAME_HEIGHT / 1.2f - menuStartText.getLocalBounds().height / 2.0f);
    menuStartText.setString(menuStartString);
    menuStartText.setOrigin(menuStartText.getLocalBounds().width / 2.0f, menuStartText.getLocalBounds().height / 2.0f);

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
        //x sur la fen�tre
        if (event.type == sf::Event::Closed)
        {
            window.close();
            retval = true;
        }
        if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed)
        {
            gameStarted = true;
        }
    }
    if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed)
    {
        gameStarted = true;
    }
  }
  return retval;

}