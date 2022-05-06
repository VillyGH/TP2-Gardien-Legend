#include "stdafx.h"
#include "ScoreBoardScene.h"
#include "game.h"
#include "ScoreBoardContentManager.h"

const float ScoreboardScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;

ScoreboardScene::ScoreboardScene()
    : Scene(SceneType::SCOREBOARD_SCENE)
    , gameEnded(false)
{
}

ScoreboardScene::~ScoreboardScene()
{

}

SceneType ScoreboardScene::update()
{
    SceneType retval = getSceneType();

    if (gameEnded)
        retval = SceneType::NONE;

    return retval;
}

void ScoreboardScene::pause()
{

}

void ScoreboardScene::unPause()
{

}

void ScoreboardScene::draw(sf::RenderWindow& window) const
{
    window.draw(endGameImage);
    window.draw(gameOverText);
    window.draw(leaderboardText);
}

bool ScoreboardScene::uninit()
{
    return true;
}

bool ScoreboardScene::init()
{
    if (contentManager.loadContent() == false)
    {
        return false;
    }

    if (!scoreboardMusic.openFromFile("Assets\\Music\\GameTheme.ogg"))
        return false;

    scoreboardMusic.setVolume(10);
    scoreboardMusic.setLoop(true);
    scoreboardMusic.play();

    const std::string gameOverTextString = "GAME OVER";
    gameOverText.setFont(contentManager.getMainFont());
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString(gameOverTextString);
    gameOverText.setPosition(Game::GAME_WIDTH / 2, Game::GAME_HEIGHT / 4.0f - gameOverText.getLocalBounds().height);
    gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);

    const std::string leaderboardTextString = "LEADERBOARD";
    leaderboardText.setFont(contentManager.getMainFont());
    leaderboardText.setCharacterSize(48);
    leaderboardText.setString(leaderboardTextString);
    leaderboardText.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 3.0f - leaderboardText.getLocalBounds().height);
    leaderboardText.setOrigin(leaderboardText.getLocalBounds().width / 2, leaderboardText.getLocalBounds().height / 2);

    return true;
}

bool ScoreboardScene::handleEvents(sf::RenderWindow& window)
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
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                gameEnded = true;
                scoreboardMusic.play();
            }
        }
    }

    return retval;
}
