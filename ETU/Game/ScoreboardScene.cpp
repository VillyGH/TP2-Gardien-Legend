#include "stdafx.h"
#include "ScoreBoardScene.h"
#include <iostream>

const float ScoreboardScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const std::string ScoreboardScene::PATH_TO_BIN_FILE = "stats.bin";

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

	setGameOverText();
	setLeaderboardText();
	setInitialsText();
	setScoreText();

	PlayerStats outStats[MAX_NB_PLAYERS_LEADERBOARD];

	PlayerStats inStats[MAX_NB_PLAYERS_LEADERBOARD];
	if (readFromFile(inStats))
	{
		if (0 == ::memcmp(outStats, inStats, MAX_NB_PLAYERS_LEADERBOARD * sizeof(PlayerStats)))
		{
			std::cout << "La désérialisation est similaire à la sérialisation" << std::endl;
		}
		else
		{
			std::cout << "Il y a eu un problème" << std::endl;
		}

	}

	return true;
}

void ScoreboardScene::setGameOverText()
{
	const std::string gameOverTextString = "GAME OVER";
	gameOverText.setFont(contentManager.getMainFont());
	gameOverText.setCharacterSize(64);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString(gameOverTextString);
	gameOverText.setPosition(Game::GAME_WIDTH / 2, Game::GAME_HEIGHT / 4.0f - gameOverText.getLocalBounds().height);
	gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
}

void ScoreboardScene::setLeaderboardText()
{
	const std::string leaderboardTextString = "LEADERBOARD";
	leaderboardText.setFont(contentManager.getMainFont());
	leaderboardText.setCharacterSize(48);
	leaderboardText.setString(leaderboardTextString);
	leaderboardText.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 3.0f - 5);
	leaderboardText.setOrigin(leaderboardText.getGlobalBounds().width / 2, leaderboardText.getGlobalBounds().width / 2);
}

void ScoreboardScene::setInitialsText()
{
	const std::string intialsTextString = "";
	initialsText.setFont(contentManager.getMainFont());
	initialsText.setCharacterSize(36);
	initialsText.setString("");
	initialsText.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 4.0f - 5);
}

void ScoreboardScene::addInitialsText(std::string intial)
{
	if (initialsText.getString().getSize() < NAME_LENGTH) {
		initialsText.setString(initialsText.getString() + intial);
	}
	initialsText.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 4.0f - 5);
}

void ScoreboardScene::removeInitialsText()
{
	if (initialsText.getString().getSize() > 0) {
		std::string text = initialsText.getString();
		initialsText.setString(text.substr(0, text.size() - 1));
	}
	initialsText.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 4.0f - 5);
}

void ScoreboardScene::setScoreText()
{

	const std::string scoresTextString = "";
	scoresText.setFont(contentManager.getMainFont());
	scoresText.setCharacterSize(36);
	scoresText.setString("");
	scoresText.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 4.0f - 5);
}

void ScoreboardScene::saveStats(std::string initials)
{
	sprintf_s(stats[0].name, initials.c_str());
	stats[0].score = score;
}


bool ScoreboardScene::writeToFile(const PlayerStats stats[MAX_NB_PLAYERS_LEADERBOARD])
{
	std::ofstream ofs(PATH_TO_BIN_FILE, std::ios::binary);
	if (!ofs)
		return false;
	ofs.write((char*)stats, sizeof(PlayerStats) * MAX_NB_PLAYERS_LEADERBOARD);
	ofs.close();
	return true;
}

bool ScoreboardScene::readFromFile(PlayerStats stats[MAX_NB_PLAYERS_LEADERBOARD])
{
	std::ifstream ifs(PATH_TO_BIN_FILE, std::ios::binary);
	if (!ifs)
		return false;
	ifs.read((char*)stats, sizeof(PlayerStats) * MAX_NB_PLAYERS_LEADERBOARD);
	ifs.close();
	return true;
}


bool ScoreboardScene::handleEvents(sf::RenderWindow& window)
{
	bool retval = false;
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			retval = true;
		}
		if (event.key.code == sf::Event::TextEntered) {
			if (event.text.unicode < 128)
				addInitialsText(std::to_string(event.text.unicode));
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				gameEnded = true;
			}
			if (event.key.code == sf::Keyboard::BackSpace)
			{
				removeInitialsText();
			}
			if (event.key.code == sf::Keyboard::Enter)
			{
				std::string initials = initialsText.getString();
				saveStats(initials);
			}
		}
		
	}

	return retval;
}
