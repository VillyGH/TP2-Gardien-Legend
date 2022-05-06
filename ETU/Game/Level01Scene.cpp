#include "stdafx.h"
#include "Level01Scene.h"
#include "game.h"
#include "CharacterType.h"
#include "ContentManager.h"

const float Level01::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float Level01::GAMEPAD_SPEEDRATIO = 1000.0f;
const float Level01::KEYBOARD_SPEED = 0.1f;
const float Level01::TIME_BETWEEN_FIRE = 0.5f;
const float Level01::MAX_ENEMIES = 15;
const float Level01::ENEMY_SPAWN_TIME = 1;
const float Level01::ENEMY_SPAWN_DISTANCE = 15;
const float Level01::SPAWN_MARGIN = -50;

Level01Scene::Level01Scene()
    : Scene(SceneType::LEVEL01_SCENE)
{
}

Level01Scene::~Level01Scene()
{

}

SceneType Level01Scene::update()
{
    static int cptScrollBackground = 0;
    backgroundSprite.setTextureRect(sf::IntRect((int)0, (0.5 * cptScrollBackground--), Game::GAME_WIDTH, Game::GAME_HEIGHT));
    SceneType retval = getSceneType();
    player.update(TIME_PER_FRAME, inputs);
    /*for (LargeEnemy& e : enemies)
        if (e.update(1.0f / (float)Game::FRAME_RATE, inputs))
            e.deactivate();
        if (e.isFiring())
            fireEnemyBullet(e);
    }


    for (Bullet& e : enemyBullets)
    {
        if (e.update(1.0f / (float)Game::FRAME_RATE))
            e.deactivate();
    }

    enemySpawnTimer += 1.0f / (float)Game::FRAME_RATE;

    if (enemySpawnTimer >= ENEMY_SPAWN_TIME) {
        spawnEnemy();
        enemySpawnTimer = 0;
    }
    /*
    for (Bullet& e : bullets)
    {
        if (e.update(1.0f / (float)Game::FRAME_RATE))
            e.deactivate();
    }

    if (inputs.fireBullet && timeSinceLastFire >= TIME_BETWEEN_FIRE)
    {
        fireBullet(player.getPosition());
    }

    for (Bullet& b : bullets)
    {
        for (LargeEnemy& e : enemies)
        {
            if (b.collidesWith(e))
            {
                b.deactivate();
                e.onHit();
            }
        }
    }
    bullets.remove_if([](const GameObject& b) {return !b.isActive();});
    enemies.remove_if([](const GameObject& b) {return !b.isActive(); });
    timeSinceLastFire += 1.0f / (float)Game::FRAME_RATE;
    */


    return retval;

}


void Level01::fireEnemyBullet(EnemyType1 enemy)
{
    Bullet& b = getAvailableEnemyBullet();
    b.setPosition(enemy.getPosition());
}
void Level01Scene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundSprite);
    player.draw(window);
    /*
    for (const LargeEnemy& e : enemies)
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
    if (contentManager.loadContent() == false)
    {
        return false;
    }
    backgroundSprite.setTexture(contentManager.getBackgroundTexture());
    srand((unsigned)time(nullptr));

    if (!music.openFromFile("Assets\\Music\\Title\\SkyFire (Title Screen).ogg"))
        return false;
    music.setVolume(10);
    music.setLoop(true);
    music.play();


    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        EnemyType1 enemy;
        enemy.init(contentManager);
        enemies.push_back(enemy);
    }

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
