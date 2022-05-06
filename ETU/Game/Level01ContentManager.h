#pragma once
#include "stdafx.h"
#include "ContentManager.h"
class Level01ContentManager : ContentManager
{
public:
	Level01ContentManager();
	virtual bool loadContent();

	const sf::Texture& getBackgroundTexture() const;
	const sf::Texture& getMainCharacterTexture() const;
	const sf::Texture& getMiscTexture() const;
	const sf::Texture& getEnemiesTexture() const;
	const sf::SoundBuffer& getPlayerGunSoundBuffer() const;
	const sf::SoundBuffer& getEnemyGunSoundBuffer() const;
	const sf::SoundBuffer& getHealthSoundBuffer() const;
	const sf::SoundBuffer& getGunBonusSoundBuffer() const;
	const sf::SoundBuffer& getEnemyKilledSoundBuffer() const;
private:
	sf::Texture mainCharacterTexture;
	sf::Texture backgroundTexture;
	sf::Texture miscTexture;
	sf::Texture enemiesTexture;
	sf::SoundBuffer playerGunSoundBuffer;
	sf::SoundBuffer enemyGunSoundBuffer;
	sf::SoundBuffer healthBonusSoundBuffer;
	sf::SoundBuffer gunBonusSoundBuffer;
	sf::SoundBuffer enemyKilledSoundBuffer;
};



