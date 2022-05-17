#include "stdafx.h"
#include "ScoreBoardScene.h"
#include <iostream>

const float ScoreboardScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const std::string ScoreboardScene::PATH_TO_BIN_FILE = "stats.bin";
const int ScoreboardScene::MAX_NB_CHARS_INITIALS = 3;

ScoreboardScene::ScoreboardScene()
	: Scene(SceneType::SCOREBOARD_SCENE)
	, hasExited(false)
	, stats()
	, currentInitials(0)
	, canExit(false)
	, lockedInScore(false)
	, scoreIndex(0)
	, nameIndex(0)
{
}

ScoreboardScene::~ScoreboardScene()
{

}

SceneType ScoreboardScene::update()
{
	SceneType retval = getSceneType();

	if (hasExited)
		retval = SceneType::NONE;

	return retval;
}

void ScoreboardScene::draw(sf::RenderWindow& window) const
{
	window.draw(backgroundSprite);
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
	if (!readFromFile(stats))
		return false;
	setScoreText();
	setInitialsText();



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
	const std::string enterNameTextString = "PRESS ESC OR A TO QUIT";
	enterNameText.setString(enterNameTextString);
	canExit = true;
}

void ScoreboardScene::setInitialsText()
{
	bool nameWritten = false;
	int currentIndex = 0;
	initialsText.setFont(contentManager.getMainFont());
	initialsText.setCharacterSize(24);
	initialsText.setPosition(Game::GAME_WIDTH / 4.0f, Game::GAME_HEIGHT / 3.0f);
	initialsText.setOrigin(initialsText.getGlobalBounds().width / 2, initialsText.getGlobalBounds().width / 2);
	for (const PlayerStats& stat : stats)
	{
		if (stat.score != 0) {
			currentIndex++;
			if (stat.score == (int)std::round(result.level01SceneResult.score) && !nameWritten) {
				initialsText.setString(initialsText.getString() + "   " + "\n");
				nameWritten = true;
				nameIndex = currentIndex - 1;
			} else {
				initialsText.setString(initialsText.getString() + stat.name + "\n");
			}
		}
	}
}

void ScoreboardScene::addInitialsText(const char initial)
{
	if (currentInitials < MAX_NB_CHARS_INITIALS) {
		std::string text = initialsText.getString();
		if (nameIndex != scoreIndex) {
			text[(nameIndex) * 4 + newInitials.size()] = initial;
		}
		else {
			text += initial;
		}
		initialsText.setString(text);
		newInitials += initial;
		currentInitials++;
	}
}

void ScoreboardScene::removeInitialsText()
{
	std::string text = initialsText.getString();
	if (nameIndex != scoreIndex) {
		text[(nameIndex) * 4 + newInitials.size() - 1] = ' ';
		initialsText.setString(text);
	}
	else {
		initialsText.setString(text.substr(0, text.size() - 1));
	}
	newInitials = newInitials.substr(0, newInitials.size() - 1);
	currentInitials--;
}

bool operator<(const PlayerStats& playerStatA, const PlayerStats& playerStatB)
{
	if (playerStatA.score > playerStatB.score)
		return true;

	return false;
}


void ScoreboardScene::setScoreText()
{
	bool scoreWritten = false;
	scoresText.setFont(contentManager.getMainFont());
	scoresText.setCharacterSize(24);
	scoresText.setPosition(Game::GAME_WIDTH / 1.5f, Game::GAME_HEIGHT / 3.0f);
	scoresText.setOrigin(scoresText.getGlobalBounds().width / 2, scoresText.getGlobalBounds().width / 2);
	for (const PlayerStats& stat : stats)
	{
		if (stat.score != 0) {
			scoreIndex++;
			if (scoreIndex >= MAX_NB_PLAYERS_LEADERBOARD)
				scoreIndex--;
		}
	}
	stats[scoreIndex].score = std::round(result.level01SceneResult.score);
	std::sort(stats, stats + MAX_NB_PLAYERS_LEADERBOARD);
	for (const PlayerStats& stat : stats)
	{
		if (stat.score != 0) {
			scoresText.setString(scoresText.getString() + std::to_string((int)stat.score) + "\n");
		}
	}
}

void ScoreboardScene::saveStats()
{
	strcpy_s(stats[nameIndex].name, newInitials.c_str());
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
			if (event.text.unicode > 65 && event.text.unicode < 122) {
				addInitialsText((char)event.text.unicode);
			}
		}
		if (sf::Joystick::isConnected(0)) {
			if (event.type == sf::Event::JoystickButtonPressed) {
				if (sf::Joystick::isButtonPressed(0, sf::Joystick::Y))
				{
					if (currentInitials != 0 && !lockedInScore) {
						removeInitialsText();
					}
				}
				if (sf::Joystick::isButtonPressed(0, sf::Joystick::X))
				{
					if (currentInitials == 3 && !lockedInScore) {
						saveStats();
						writeToFile(stats);
						changeEnterNameText();
					}
				}
				if (sf::Joystick::isButtonPressed(0, sf::Joystick::X) && canExit)
				{
					hasExited = true;
				}
			}
		} else {
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape && canExit)
				{
					hasExited = true;
				}
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (currentInitials != 0 && !lockedInScore) {
						removeInitialsText();
					}
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (currentInitials == 3 && !lockedInScore) {
						saveStats();
						writeToFile(stats);
						changeEnterNameText();
						lockedInScore = true;
					}
				}
			}
		}
	}
	return retval;
}
