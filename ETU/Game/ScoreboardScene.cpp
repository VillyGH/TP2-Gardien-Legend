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
	, lockedInScore(false)
	, scoreIndex(0)
	, nbAlreadySavedInitials(0)
{
}

ScoreboardScene::~ScoreboardScene()
{

}

//void ScoreboardScene::fillPlayerStatsWithRandomValues(PlayerStats stats[MAX_NB_PLAYERS_LEADERBOARD])
//{
//	srand((unsigned)time(nullptr));
//	std::string names[] = { "SSD", "MAD", "SKT" };
//	for (int i = 0; i < NB_INITIAL_PLAYERS; i++)
//	{
//		sprintf_s(stats[i].name, "%s", names[rand() % (sizeof(names) / sizeof(names[0]))].c_str());
//		stats[i].score = 10000.f + rand() % 1000;
//	}
//}

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

	scoreIndex = 0;
	backgroundSprite.setTexture(contentManager.getBackgroundTexture());

	scoreIndex = 0;
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
				std::cout << "La d�s�rialisation est similaire � la s�rialisation" << std::endl;
			}
			else
			{
				std::cout << "Il y a eu un probl�me" << std::endl;
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
	const std::string enterNameTextString = "PRESS ESC OR A TO QUIT";
	enterNameText.setString(enterNameTextString);
	canExit = true;
}

void ScoreboardScene::setInitialsText()
{
	bool nameWritten = false;
	initialsText.setFont(contentManager.getMainFont());
	initialsText.setCharacterSize(24);
	initialsText.setPosition(Game::GAME_WIDTH / 4.0f, Game::GAME_HEIGHT / 3.0f);
	initialsText.setOrigin(initialsText.getGlobalBounds().width / 2, initialsText.getGlobalBounds().width / 2);
	for (const PlayerStats& stat : stats)
	{
		if (!strlen(stat.name) == 0) {
			if (stat.score == (int)std::round(result.level01SceneResult.score && !nameWritten)) {
				initialsText.setString(initialsText.getString() + "\n");
				nameWritten = true;
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
		initialsText.setString(initialsText.getString() + initial);
		newInitials += initial;
		currentInitials++;
	}
}

void ScoreboardScene::removeInitialsText()
{
	if (currentInitials > 0) {
		std::string text = initialsText.getString();
		initialsText.setString(text.substr(0, text.size() - 1));
		newInitials = newInitials.substr(0, newInitials.size() - 1);
		currentInitials--;
	}
}

int compare(const PlayerStats& playerStatA, const PlayerStats& playerStatB) {
	if (playerStatA.score > playerStatB.score)
		return 1;
	if (playerStatA.score < playerStatB.score)
		return -1;
	return 0;
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
	scoresText.setPosition(Game::GAME_WIDTH / 1.5f, initialsText.getPosition().y);
	scoresText.setOrigin(scoresText.getGlobalBounds().width / 2, scoresText.getGlobalBounds().width / 2);
	for (const PlayerStats& stat : stats)
	{
		if (stat.score != 0) {
			scoreIndex++;
		}
	}
	stats[scoreIndex].score = result.level01SceneResult.score;
	std::sort(stats, stats + 5);
	for (const PlayerStats& stat : stats)
	{
		if (stat.score != 0) {
			scoresText.setString(scoresText.getString() + std::to_string((int)stat.score) + "\n");
		}
	}
}

template <typename T, std::size_t N>
std::size_t array_size(T(&)[N])
{
	return N;
}

void ScoreboardScene::saveStats()
{
	strcpy_s(stats[scoreIndex - 1].name, newInitials.c_str());
	stats[scoreIndex - 1].score = (int)result.level01SceneResult.score;
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
