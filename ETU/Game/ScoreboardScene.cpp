#include "stdafx.h"
#include "ScoreBoardScene.h"
#include <iostream>

const float ScoreboardScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const std::string ScoreboardScene::PATH_TO_BIN_FILE = "stats.bin";
const int ScoreboardScene::NB_INITIAL_PLAYERS = 3;
const int ScoreboardScene::MAX_NB_CHARS_INITIALS = 3;

ScoreboardScene::ScoreboardScene()
	: Scene(SceneType::SCOREBOARD_SCENE)
	, hasExited(false)
	, stats()
	, currentInitials(0)
	, canExit(false)
	, currentIndex(0)
	, nbAlreadySavedInitials(0)
{
}

ScoreboardScene::~ScoreboardScene()
{

}

void ScoreboardScene::fillPlayerStatsWithRandomValues(PlayerStats stats[MAX_NB_PLAYERS_LEADERBOARD])
{
	srand((unsigned)time(nullptr));
	std::string names[] = { "SSD", "MAD", "SKT" };
	for (int i = 0; i < NB_INITIAL_PLAYERS; i++)
	{
		sprintf_s(stats[i].name, "%s", names[rand() % (sizeof(names) / sizeof(names[0]))].c_str());
		stats[i].score = 10000.f + rand() % 1000;
	}
}

SceneType ScoreboardScene::update()
{
	SceneType retval = getSceneType();

	if (hasExited)
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
	window.draw(backgroundSprite);
	window.draw(endGameImage);
	window.draw(gameOverText);
	window.draw(leaderboardText);
	window.draw(enterNameText);
	window.draw(initialsText);
	window.draw(scoresText);
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

	backgroundSprite.setTexture(contentManager.getBackgroundTexture());

	setGameOverText();
	setLeaderboardText();
	setEnterNameText();

	//PlayerStats outStats[MAX_NB_PLAYERS_LEADERBOARD];
	//fillPlayerStatsWithRandomValues(outStats);

	/*if (writeToFile(outStats))
	{
		if (readFromFile(stats))
		{
			if (0 == ::memcmp(outStats, stats, MAX_NB_PLAYERS_LEADERBOARD * sizeof(PlayerStats)))
			{
				std::cout << "La désérialisation est similaire à la sérialisation" << std::endl;
			}
			else
			{
				std::cout << "Il y a eu un problème" << std::endl;
			}

		}
	}*/
	if (!readFromFile(stats))
		return false;

	setInitialsText();
	setScoreText();

	return true;
}

void ScoreboardScene::setGameOverText()
{
	const std::string gameOverTextString = "GAME OVER";
	gameOverText.setFont(contentManager.getMainFont());
	gameOverText.setCharacterSize(64);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString(gameOverTextString);
	gameOverText.setPosition(Game::GAME_WIDTH / 2.f, Game::GAME_HEIGHT / 7.0f - gameOverText.getLocalBounds().height);
	gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2.f, gameOverText.getLocalBounds().height / 2.f);
}

void ScoreboardScene::setLeaderboardText()
{
	const std::string leaderboardTextString = "LEADERBOARD";
	leaderboardText.setFont(contentManager.getMainFont());
	leaderboardText.setCharacterSize(44);
	leaderboardText.setString(leaderboardTextString);
	leaderboardText.setPosition(Game::GAME_WIDTH / 2.0f, gameOverText.getPosition().y + 125);
	leaderboardText.setOrigin(leaderboardText.getGlobalBounds().width / 2, leaderboardText.getGlobalBounds().height / 2);
}

void ScoreboardScene::setEnterNameText()
{
	const std::string enterNameTextString = "PLEASE ENTER YOUR NAME";
	enterNameText.setFont(contentManager.getMainFont());
	enterNameText.setCharacterSize(24);
	enterNameText.setString(enterNameTextString);
	enterNameText.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT - 100.f);
	enterNameText.setOrigin(enterNameText.getGlobalBounds().width / 2, enterNameText.getGlobalBounds().height / 2);
}

void ScoreboardScene::changeEnterNameText()
{
	const std::string enterNameTextString = "PRESS ESC TO QUIT";
	enterNameText.setString(enterNameTextString);
	canExit = true;
}

void ScoreboardScene::setInitialsText()
{
	initialsText.setFont(contentManager.getMainFont());
	initialsText.setCharacterSize(24);
	initialsText.setPosition(Game::GAME_WIDTH / 4.0f, Game::GAME_HEIGHT / 3.0f);
	initialsText.setOrigin(initialsText.getGlobalBounds().width / 2, initialsText.getGlobalBounds().width / 2);
	for (const PlayerStats& stat : stats)
	{
		if (!strlen(stat.name) == 0) {
			std::string text = initialsText.getString() + stat.name + "\n";
			initialsText.setString(text);
		}
			
	}
	initialsText.setString(initialsText.getString() + "\n");
}

void ScoreboardScene::addInitialsText(const char initial)
{
	if (currentInitials < MAX_NB_CHARS_INITIALS) {
		std::string text = initialsText.getString();
		if (currentIndex == currentInitials) {
			initialsText.setString(initialsText.getString() + initial);
		}
		else {
			text[nbAlreadySavedInitials + currentIndex] = initial;
			initialsText.setString(text);
		}
		currentInitials++;
		currentIndex++;
	}
}

void ScoreboardScene::removeInitialsText()
{
	if (currentInitials > 0) {
		std::string text = initialsText.getString();
		//initialsText.setString(text.substr(0, text.size() - 1));
		text.erase(currentIndex - 1, 1);
		initialsText.setString(text);
		std::cout << text;
		currentInitials--;
		currentIndex--;
	}
}

void ScoreboardScene::setScoreText()
{
	scoresText.setFont(contentManager.getMainFont());
	scoresText.setCharacterSize(24);
	scoresText.setPosition(Game::GAME_WIDTH / 1.5f, initialsText.getPosition().y);
	scoresText.setOrigin(scoresText.getGlobalBounds().width / 2, scoresText.getGlobalBounds().width / 2);
	for (const PlayerStats& stat : stats)
	{
		if(stat.score != 0)
			scoresText.setString(scoresText.getString() + std::to_string(stat.score) + "\n");
	}
	scoresText.setString(scoresText.getString() + std::to_string((int)result.level01SceneResult.score));
}

void ScoreboardScene::saveStats(std::string initials)
{
	if (initials.size() == 3) {
		sprintf_s(stats[0].name, initials.c_str());
		stats[0].score = result.level01SceneResult.score;
	}
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

bool ScoreboardScene::readFromFile(const PlayerStats stats[MAX_NB_PLAYERS_LEADERBOARD])
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
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode > 97 && event.text.unicode < 122) {
				addInitialsText((char)event.text.unicode);
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape && canExit)
			{
				hasExited = true;
			}
			if (event.key.code == sf::Keyboard::BackSpace)
			{
				if (currentIndex != 0) {
					removeInitialsText();
				}
			}
			if (event.key.code == sf::Keyboard::Enter)
			{
				std::string initials = initialsText.getString();
				saveStats(initials);
				writeToFile(stats);
				changeEnterNameText();
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				if (currentIndex < MAX_NB_CHARS_INITIALS && currentInitials > currentIndex) {
					currentIndex++;
					
				}
				//std::cout << currentInitials;
				std::cout << currentIndex;
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				if (currentIndex > 0) {
					currentIndex--;
				}
				std::cout << currentIndex;
			}
		}
		
	}
	return retval;
}
