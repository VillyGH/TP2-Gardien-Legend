#include "stdafx.h"
#include "Level01Scene.h"
#include "game.h"
#include "CharacterType.h"
#include "Level01ContentManager.h"
#include "Event.h"
#include <iostream>

const float Level01Scene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float Level01Scene::GAMEPAD_SPEEDRATIO = 1000.0f;
const float Level01Scene::KEYBOARD_SPEED = 0.1f;
const float Level01Scene::TIME_BETWEEN_FIRE = 0.2f;
const float Level01Scene::MAX_NB_STANDARD_ENEMIES = 15;
const float Level01Scene::MAX_NB_BOSS_ENEMIES = 3;
const float Level01Scene::MAX_NB_BULLETS = 30;
const float Level01Scene::STANDARD_ENEMY_SPAWN_TIME = 1;
const float Level01Scene::BOSS_ENEMY_SPAWN_TIME = 60;
const float Level01Scene::ENEMY_SPAWN_DISTANCE = 15;
const float Level01Scene::SPAWN_MARGIN = -50;
const float Level01Scene::PLAYER_BULLET_DAMAGE = 1;

Level01Scene::Level01Scene()
    : Scene(SceneType::LEVEL01_SCENE)
    , enemySpawnTimer(0)
    , timeSinceLastFire(0)
{
}

Level01Scene::~Level01Scene()
{

}

SceneType Level01Scene::update()
{
    static int cptScrollBackground = 0;
    backgroundSprite.setTextureRect(sf::IntRect(0, (int)(0.5f * cptScrollBackground--), Game::GAME_WIDTH, Game::GAME_HEIGHT));
    SceneType retval = getSceneType();
    player.update(TIME_PER_FRAME, inputs);
    for (StandardEnemy& e : standardEnemies) {
        if (e.update(1.0f / (float)Game::FRAME_RATE, inputs))
            e.deactivate();
        if (e.isFiring() && e.isActive())
            fireEnemyBullet(e);
    }

    enemySpawnTimer += 1.0f / (float)Game::FRAME_RATE;

    if (enemySpawnTimer >= STANDARD_ENEMY_SPAWN_TIME && !allEnemiesKilled) {
        
        spawnStandardEnemy();
        enemySpawnTimer = 0;
    }

    if (allEnemiesKilled) //À changer pour un compteur de Enemies Killed
        spawnBoss();

    if (boss.isActive())
        boss.update(1.0f / (float)Game::FRAME_RATE, inputs);

    for (Bullet& e : enemyBullets)
    {
        if (e.update(1.0f / (float)Game::FRAME_RATE, CharacterType::ENEMY_TYPE_1))
            e.deactivate();
    }

    for (Bullet& e : standardBullets)
    {
        if (e.update(1.0f / (float)Game::FRAME_RATE, CharacterType::PLAYER))
            e.deactivate();
    }

    if (inputs.fireBullet && timeSinceLastFire >= TIME_BETWEEN_FIRE)
    {
        firePlayerBullet();
        timeSinceLastFire = 0; 
    }

    for (Bullet& b : standardBullets)
    {
        for (StandardEnemy& e : standardEnemies)
        {
            if (b.collidesWith(e))
            {
                b.deactivate();
                e.onHit(1);
            }
        }
    }
   /* standardBullets.remove_if([](const GameObject& b) {return !b.isActive(); });
    standardEnemies.remove_if([](const GameObject& b) {return !b.isActive(); });*/
    timeSinceLastFire += 1.0f / (float)Game::FRAME_RATE;

    return retval;
}


#pragma region Enemy
void Level01Scene::addNewStandardEnemies() {
    for (size_t i = 0; i < MAX_NB_STANDARD_ENEMIES; i++)
    {
        StandardEnemy enemy;
        enemy.init(contentManager);
        standardEnemies.push_back(enemy);
    }
}

bool Level01Scene::spawnStandardEnemy()
{
    for (StandardEnemy& enemy : standardEnemies) {
        if (!enemy.isActive()) {
            enemy.activate();
            enemy.setPosition((rand() % Game::GAME_WIDTH - SPAWN_MARGIN), ENEMY_SPAWN_DISTANCE);
            return false;
        }
    }
    allEnemiesKilled = true; //À CHANGER
    return true;
}

bool Level01Scene::spawnBoss()
{
    boss.activate();
    boss.setPosition(Game::GAME_WIDTH * 0.5, 50);
    return true;
}


#pragma endregion

#pragma region Bullet
void Level01Scene::fireEnemyBullet(StandardEnemy enemy)
{
    Bullet& b = getAvailableEnemyBullet();
    b.setPosition(enemy.getPosition());
}

void Level01Scene::firePlayerBullet()
{
    Bullet& b = getAvailableStandardBullet();
    b.setPosition(player.getPosition());
}

Bullet& Level01Scene::getAvailableStandardBullet()
{
    for (Bullet& b : standardBullets)
    {
        if (!b.isActive())
        {
            b.activate();
            return b;
        }
    }
    Bullet newBullet;
    newBullet.init(contentManager, CharacterType::PLAYER);
    standardBullets.push_back(newBullet);

    return standardBullets.back();
}

Bullet& Level01Scene::getAvailableEnemyBullet()
{
    for (Bullet& b : enemyBullets)
    {
        if (!b.isActive())
        {
            b.activate();
            return b;
        }
    }
    Bullet newBullet;
    newBullet.init(contentManager, CharacterType::ENEMY_TYPE_1);
    enemyBullets.push_back(newBullet);
    return enemyBullets.back();
}

Bullet& Level01Scene::getAvailableBossBullet()
{
    for (Bullet& b : bossBullets)
    {
        if (!b.isActive())
        {
            b.activate();
            return b;
        }
    }
    Bullet newBullet;
    newBullet.init(contentManager, CharacterType::ENEMY_TYPE_1);
    bossBullets.push_back(newBullet);
    return bossBullets.back();
}

void Level01Scene::addNewStandardBullets() {
    for (size_t i = 0; i < MAX_NB_BULLETS; i++)
    {
        Bullet newBullet;
        newBullet.init(contentManager, CharacterType::PLAYER);
        standardBullets.push_back(newBullet);
    }
}

void Level01Scene::addNewEnemyBullets() {
    for (size_t i = 0; i < MAX_NB_BULLETS; i++)
    {
        Bullet newBullet;
        newBullet.init(contentManager, CharacterType::ENEMY_TYPE_1);
        enemyBullets.push_back(newBullet);
    }
}


void Level01Scene::addNewBossBullets() {
    for (size_t i = 0; i < MAX_NB_BULLETS; i++)
    {
        Bullet newBullet;
        newBullet.init(contentManager, CharacterType::BOSS);
        bossBullets.push_back(newBullet);
    }
}

#pragma endregion

void Level01Scene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundSprite);
    player.draw(window);

    for (const StandardEnemy& e : standardEnemies) 
        e.draw(window);       

    for (const Bullet& e : standardBullets)
        e.draw(window);

    for (const Bullet& e : enemyBullets)
        e.draw(window);

    if (boss.isActive())
        boss.draw(window);

    for (const Bullet& e : bossBullets)
        e.draw(window);

}

bool Level01Scene::uninit()
{
    return true;
}

bool Level01Scene::init()
{
    timeSinceLastFire = TIME_BETWEEN_FIRE * 3;
    inputs.reset();
    allEnemiesKilled = false;
    if (contentManager.loadContent() == false)
    {
        return false;
    }
    backgroundSprite.setTexture(contentManager.getBackgroundTexture());
    srand((unsigned)time(nullptr));

    addNewStandardEnemies();
    addNewStandardBullets();
    addNewEnemyBullets();

    boss.init(contentManager);
    addNewBossBullets();

    return player.init(contentManager);
}


bool Level01Scene::handleEvents(sf::RenderWindow& window)
{
    bool retval = false;
    inputs.reset();
    sf::Event event;
    while (window.pollEvent(event))
    {
        //x sur la fen�tre
        if (event.type == sf::Event::Closed)
        {
            window.close();
            retval = true;
        }
    }
    inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ? 3.0f : 0.0f;
    inputs.moveFactorX -= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ? 3.0f : 0.0f;
    inputs.moveFactorY -= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ? -3.0f : 0.0f;
    inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ? -3.0f : 0.0f;
    inputs.fireBullet = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    return retval;
}
