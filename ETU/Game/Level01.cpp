#include "stdafx.h"
#include "Level01.h"
#include "game.h"
#include "CharacterType.h"
#include "Level01ContentManager.h"

const float Level01Scene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float Level01Scene::GAMEPAD_SPEEDRATIO = 1000.0f;
const float Level01Scene::KEYBOARD_SPEED = 0.1f;
const float Level01Scene::TIME_BETWEEN_FIRE = 0.5f;
const float Level01Scene::MAX_NB_ENEMIES = 15;
const float Level01Scene::MAX_NB_BULLETS = 15;
const float Level01Scene::ENEMY_SPAWN_TIME = 1;
const float Level01Scene::ENEMY_SPAWN_DISTANCE = 15;
const float Level01Scene::SPAWN_MARGIN = -50;

Level01Scene::Level01Scene()
    : Scene(SceneType::LEVEL01_SCENE)
    , enemySpawnTimer(0)
    , timeSinceLastFire(0)
{
}

Level01::~Level01()
{

}

SceneType Level01::update()
{
    static int cptScrollBackground = 0;
    backgroundSprite.setTextureRect(sf::IntRect((int)(0.5f * cptScrollBackground++), 0, Game::GAME_WIDTH, Game::GAME_HEIGHT));
    SceneType retval = getSceneType();
    player.update(TIME_PER_FRAME, inputs);
    for (StandardEnemy& e : standardEnemies) {
        if (e.update(1.0f / (float)Game::FRAME_RATE, inputs))
            e.deactivate();
        if (e.isFiring())
            fireEnemyBullet(e);
    }


    for (Bullet& b : standardBullets)
    {
        if (b.update(1.0f / (float)Game::FRAME_RATE))
            b.deactivate();
    }

    enemySpawnTimer += 1.0f / (float)Game::FRAME_RATE;

    if (enemySpawnTimer >= ENEMY_SPAWN_TIME) {
        spawnStandardEnemy();
        enemySpawnTimer = 0;
    }

    for (Bullet& e : standardBullets)
    {
        if (e.update(1.0f / (float)Game::FRAME_RATE))
            e.deactivate();
    }

    if (inputs.fireBullet && timeSinceLastFire >= TIME_BETWEEN_FIRE)
    {
        firePlayerBullet();
    }

    for (Bullet& b : standardBullets)
    {
        for (StandardEnemy& e : standardEnemies)
        {
            if (b.collidesWith(e))
            {
                b.deactivate();
                e.onHit();
            }
        }
    }
    standardBullets.remove_if([](const GameObject& b) {return !b.isActive();});
    standardEnemies.remove_if([](const GameObject& b) {return !b.isActive(); });
    timeSinceLastFire += 1.0f / (float)Game::FRAME_RATE;



    return retval;

}



#pragma region Enemy
StandardEnemy& Level01Scene::getAvailableStandardEnemy()
{
    for (StandardEnemy& e : standardEnemies)
    {
        if (!e.isActive())
        {
            return e;
        }
    }
    addNewStandardEnemies();
    return standardEnemies.back();
}

StandardEnemy& Level01Scene::getAvailableBossEnemy()
{
    for (StandardEnemy& e : bossEnemies)
    {
        if (!e.isActive())
        {
            return e;
        }
    }
    addNewBossEnemies();
    return bossEnemies.back();
}

void Level01Scene::addNewStandardEnemies() {
    for (size_t i = 0; i < MAX_NB_ENEMIES; i++)
    {
        StandardEnemy enemy;
        enemy.init(contentManager);
        standardEnemies.push_back(enemy);
    }
}

void Level01Scene::addNewBossEnemies() {
    for (size_t i = 0; i < MAX_NB_ENEMIES; i++)
    {
        StandardEnemy enemy;
        enemy.init(contentManager);
        bossEnemies.push_back(enemy);
    }
}

StandardEnemy Level01Scene::spawnStandardEnemy()
{
    return StandardEnemy();
}

StandardEnemy Level01Scene::spawnBossEnemy()
{
    return StandardEnemy();
}

#pragma endregion

#pragma region Bullet
void Level01Scene::fireEnemyBullet(StandardEnemy enemy)
{
    Bullet& b = getAvailableStandardBullet();
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
    addNewStandardBullets();
    return standardBullets.back();
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
    addNewBossBullets();
    return bossBullets.back();
}

void Level01Scene::addNewStandardBullets() {
    for (size_t i = 0; i < MAX_NB_BULLETS; i++)
    {
        Bullet newBullet;
        standardBullets.push_back(newBullet);
    }
}

void Level01Scene::addNewBossBullets() {
    for (size_t i = 0; i < MAX_NB_BULLETS; i++)
    {
        Bullet newBullet;
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

}

bool Level01::uninit()
{
    return true;
}

bool Level01::init()
{
    timeSinceLastFire = TIME_BETWEEN_FIRE * 3;
    inputs.reset();
    if (contentManager.loadContent() == false)
    {
        return false;
    }
    backgroundSprite.setTexture(contentManager.getBackgroundTexture());
    srand((unsigned)time(nullptr));

    addNewStandardEnemies();
    addNewBossEnemies();
    addNewStandardBullets();
    addNewBossBullets();

    //return player.init(contentManager);
}
bool Level01::handleEvents(sf::RenderWindow& window)
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
    inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ? -3.0f : 0.0f;
    inputs.moveFactorY -= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ? -3.0f : 0.0f;
    inputs.fireBullet = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    return retval;
}
