#include "Bullet.h"

extern float xBackgroundSize;
extern float yBackgroundSize;

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, float speed, float radius,
    sf::Color color, float naxLifeTime)
    : sf::CircleShape(radius)
{
    setSpeed(speed);
    setDirection(direction);
    setPosition(position);
    lifeTime.restart();
    setFillColor(color);
    setMaxLifeTime(maxLifeTime);
    setOrigin(sf::Vector2f(radius / 2, radius / 2));
}

Bullet::~Bullet()
{
}

const float& Bullet::getMaxLifeTime() const
{
    return maxLifeTime;
}

void Bullet::setMaxLifeTime(const float& newMaxLifeTime)
{
    if (newMaxLifeTime <= 0)
    {
        throw std::logic_error("maxLifeTime cannot be less or equal zero");
    }
    this->maxLifeTime = newMaxLifeTime;
}

const float& Bullet::getSpeed() const
{
    return speed;
}

void Bullet::setSpeed(const float& newSpeed)
{
    if (newSpeed <= 0)
    {
        throw std::logic_error("speed cannot be less or equal zero");
    }
    this->speed = newSpeed;
}

const sf::Vector2f& Bullet::getDirection() const
{
    return direction;
}

void Bullet::setDirection(const sf::Vector2f& newDirection)
{
    this->direction = newDirection;
}

void Bullet::updateBullet()
{
    move(sf::Vector2f(direction.x * speed, direction.y * speed));
}

bool Bullet::isEndBulletLife()
{
    if (lifeTime.getElapsedTime().asSeconds() >= maxLifeTime)
    {
        return true;
    }
    if (getPosition().x < getRadius() / 2)
    {
        return true;
    }
    if (getPosition().x > xBackgroundSize - getRadius() / 2)
    {
        return true;
    }
    if (getPosition().y < getRadius() / 2)
    {
        return true;
    }
    if (getPosition().y > yBackgroundSize - getRadius() / 2)
    {
        return true;
    }
    return false;
}
