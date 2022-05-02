#include "stdafx.h"
#include "ContentManager.h"


ContentManager::ContentManager()
{
}

bool ContentManager::loadContent()
{

  if (!backgroundTexture.loadFromFile("Assets\\Sprites\\Level01\\SpaceBackground.png"))
    return false;
  else
    backgroundTexture.setRepeated(true);
  if(!mainCharacterTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - The Guardian Alyssa.bmp"))
    return false;
  if (!miscTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Miscellaneous.bmp"))
    return false;
  if (!enemiesTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Bosses.bmp"))
    return false;
  if (!mainFont.loadFromFile("Assets\\Fonts\\Level01\\emulogic.ttf"))
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
  if (!titleScreenTexture.loadFromFile("Assets\\Sprites\\Title\\Title.png"))
    return false;
  
  return true;
} 
const sf::Texture& ContentManager::getEnemiesTexture() const
{
  return enemiesTexture;
}

const sf::Texture& ContentManager::getBackgroundTexture() const
{
  return backgroundTexture;
}
const sf::Texture& ContentManager::getMiscTexture() const
{
  return miscTexture;
}

const sf::Texture& ContentManager::getMainCharacterTexture() const
{
  return mainCharacterTexture;
}

const sf::Font& ContentManager::getMainFont() const
{
  return mainFont;
}
const sf::SoundBuffer& ContentManager::getPlayerGunSoundBuffer() const
{
  return playerGunSoundBuffer;
}

const sf::SoundBuffer& ContentManager::getEnemyGunSoundBuffer() const
{
  return enemyGunSoundBuffer;
}

const sf::SoundBuffer& ContentManager::getHealthSoundBuffer() const
{
  return healthBonusSoundBuffer;
}

const sf::SoundBuffer& ContentManager::getGunBonusSoundBuffer() const
{
  return gunBonusSoundBuffer;
}
const sf::SoundBuffer& ContentManager::getEnemyKilledSoundBuffer() const
{
  return enemyKilledSoundBuffer;
}

const sf::Texture& ContentManager::getTitleScreenTexture() const
{
  return titleScreenTexture;
}