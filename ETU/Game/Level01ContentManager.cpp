#include "stdafx.h"
#include "Level01ContentManager.h"


Level01ContentManager::Level01ContentManager()
{

}

bool Level01ContentManager::loadContent()
{

	if (!backgroundTexture.loadFromFile("Assets\\Sprites\\Level01\\SpaceBackground.png"))
		return false;
	else
		backgroundTexture.setRepeated(true);
	if (!mainCharacterTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - The Guardian Alyssa.bmp"))
		return false;
	if (!miscTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Miscellaneous.bmp"))
		return false;
	if (!enemiesTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Bosses.bmp"))
		return false;
	if (!playerGunSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\playerGun.wav"))
		return false;
	if (!enemyGunSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\enemyGun.wav"))
		return false;
	if (!healthBonusSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\healthBonus.wav"))
		return false;
	if (!gunBonusSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\gunBonus.wav"))
		return false;
	if (!enemyKilledSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\enemyKilled.wav"))
		return false;
	ContentManager::loadContent();

	return true;
}

const sf::Texture& Level01ContentManager::getEnemiesTexture() const
{
	return enemiesTexture;
}

const sf::Texture& Level01ContentManager::getBackgroundTexture() const
{
	return backgroundTexture;
}
const sf::Texture& Level01ContentManager::getMiscTexture() const
{
	return miscTexture;
}

const sf::Texture& Level01ContentManager::getMainCharacterTexture() const
{
	return mainCharacterTexture;
}

const sf::SoundBuffer& Level01ContentManager::getPlayerGunSoundBuffer() const
{
	return playerGunSoundBuffer;
}

const sf::SoundBuffer& Level01ContentManager::getEnemyGunSoundBuffer() const
{
	return enemyGunSoundBuffer;
}

const sf::SoundBuffer& Level01ContentManager::getHealthSoundBuffer() const
{
	return healthBonusSoundBuffer;
}

const sf::SoundBuffer& Level01ContentManager::getGunBonusSoundBuffer() const
{
	return gunBonusSoundBuffer;
}
const sf::SoundBuffer& Level01ContentManager::getEnemyKilledSoundBuffer() const
{
	return enemyKilledSoundBuffer;
}
