#include "stdafx.h"
#include "Level01Scene.h"
#include "game.h"

#include "ContentManager.h"

const float Level01Scene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float Level01Scene::GAMEPAD_SPEEDRATIO = 1000.0f;
const float Level01Scene::KEYBOARD_SPEED = 0.1f;
const float Level01Scene::TIME_BETWEEN_FIRE = 0.5f;
const float Level01Scene::MAX_ENEMIES = 15; 

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
    backgroundSprite.setTextureRect(sf::IntRect((int)(0.5f * cptScrollBackground++), 0, Game::GAME_WIDTH, Game::GAME_HEIGHT));
    SceneType retval = getSceneType();
    //player.update(1.0f / (float)Game::FRAME_RATE, inputs);
    /*for (LargeEnemy& e : enemies)
        if (e.update(1.0f / (float)Game::FRAME_RATE, inputs))
            e.deactivate();

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



void Level01Scene::fireBullet(const sf::Vector2f& position)
{
    /*
    Bullet newBullet;
    newBullet.init(contentManager);
    newBullet.setPosition(position);
    newBullet.activate();
    bullets.push_back(newBullet);
    timeSinceLastFire = 0;
    */
}
void Level01Scene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundSprite);
    /*
    player.draw(window);
    for (const LargeEnemy& e : enemies)
        e.draw(window);
    for (const Bullet& e : bullets)
        e.draw(window);
    */
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

    for (int i = 0; i < 10; i++)
    {
        //EnemyType1 enemy;
        //enemy.init(contentManager);
        //enemy.setPosition(sf::Vector2f((i * (float)Game::GAME_WIDTH / 10.0f), (float)Game::GAME_HEIGHT + 50.0f * (float)(rand() % 100)));
       // enemy.activate();
        //enemies.push_back(enemy);
    }

    //return player.init(contentManager);
    return true;
}
bool Level01Scene::handleEvents(sf::RenderWindow& window)
{
    bool retval = false;
    inputs.reset();
    sf::Event event;
    while (window.pollEvent(event))
    {
        //x sur la fenêtre
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
