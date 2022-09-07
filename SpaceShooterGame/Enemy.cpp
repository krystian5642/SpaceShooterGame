#include "Enemy.h"

extern float xBackgroundSize;
extern float yBackgroundSize;

Enemy::Enemy(std::string objectName, float xScale, float yScale, size_t textureNumber,
    float speed, float acceleration, float rotateAngle, int maxHP, int maxEnergy)
    : Ship(objectName, xScale, yScale, textureNumber, speed,
        acceleration, rotateAngle, maxHP, maxEnergy)
{
    setReloadingTime(0.5f);
    setBulletColor(sf::Color::Red);
    texturePaths.push_back("Pictures\\Ships\\EnemyShips\\enemy1.png");
    setPosition(rand() % (int)xBackgroundSize, rand() % (int)yBackgroundSize);
    loadEntityTexture();
    setSize(sf::Vector2f(getTexture()->getSize().x * getScale().x,
        getTexture()->getSize().y * getScale().y));
    setOrigin(getSize().x / 2, getSize().y / 2);
}

Enemy::Enemy(const Enemy& enemy) : Ship(enemy)
{
    setRotateAngle(rand() % (int)150+100);
    setSpeed(rand() % (int)250 +200);
    setReloadingTime(enemy.reloadingTime);
}

Enemy::~Enemy()
{
}

void Enemy::updateEntity(long double dt)
{
    double PI = 3.141592653589;
    double angle = getRotation();
    double angleInRad = angle * PI / 180;
    sf::Vector2f direction(cos(angleInRad), sin(angleInRad));

    if (shipClockMove.getElapsedTime().asSeconds() < 0.5f)
    {
        rotate(rotateAngle * dt);
    }
    else if (shipClockMove.getElapsedTime().asSeconds() < 3)
    {
        move(sf::Vector2f(speed * direction.x * dt, speed * direction.y*dt));
        if (shipClockReloading.getElapsedTime().asSeconds() > reloadingTime)
        {
            shoot(direction);
        }
    }
    else
    {
        setRotateAngle(rand() % (int)150 + 100);
        setSpeed(rand() % (int)250 + 200);
        shipClockMove.restart();
    }
    checkPosition();
}
