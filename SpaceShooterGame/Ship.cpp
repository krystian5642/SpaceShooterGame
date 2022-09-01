#include "Ship.h"

extern float xBackgroundSize;
extern float yBackgroundSize;

void Ship::loadEntityTexture()
{
    entityTextures = std::make_shared<std::shared_ptr<sf::Texture>[]>(textureNumber);
    entityTextures[0] = std::make_shared<sf::Texture>();
    if (!entityTextures[0]->loadFromFile(texturePaths[0]))
    {
        throw std::logic_error("Could not load ship texture");
    }
    setTexture(entityTextures[0].get());
}

Ship::Ship(std::string entityName, float xScale, float yScale, size_t textureNumber,
    float speed, float acceleration, float rotateAngle, int maxHP, int maxEnergy)
    : Entity(entityName, xScale, yScale, textureNumber)
{
    shipClockMove.restart();
    shipClockReloading.restart();
    setReloadingTime(0.3f);
    setSpeed(speed);
    setAcceleration(acceleration);
    setRotateAngle(rotateAngle);
    setMaxHP(maxHP);
    setMaxEnergy(maxEnergy);
    setBulletRadius(5.f);
}

Ship::Ship(const Ship& ship) : Entity(ship)
{
    shipClockMove.restart();
    shipClockReloading.restart();
    setSpeed(ship.speed);
    setReloadingTime(ship.reloadingTime);
    setAcceleration(ship.acceleration);
    setRotateAngle(ship.rotateAngle);
    setMaxHP(ship.maxHP);
    setMaxEnergy(ship.maxEnergy);
    setBulletRadius(ship.bulletRadius);
    setBulletColor(ship.bulletColor);
    setPosition(rand() % (int)xBackgroundSize, rand() % (int)yBackgroundSize);
}

Ship::~Ship()
{
}

const float& Ship::getSpeed() const
{
    return speed;
}

void Ship::setSpeed(const float& newSpeed)
{
    if (newSpeed < 0)
    {
        throw std::logic_error("speed could not be less than zero");
    }
    this->speed = newSpeed;
}

const float& Ship::getAcceleration() const
{
    return acceleration;
}

void Ship::setAcceleration(const float& newAcceleration)
{
    if (newAcceleration < 0)
    {
        throw std::logic_error("acceleration could not be less than zero");
    }
    this->acceleration = newAcceleration;
}

const float& Ship::getRotateAngle() const
{
    return rotateAngle;
}

void Ship::setRotateAngle(const float& newRotateAngle)
{
    if (newRotateAngle < 0)
    {
        throw std::logic_error("rotateAngle could not be less than zero");
    }
    this->rotateAngle = newRotateAngle;
}

const float& Ship::getReloadingTime() const
{
    return reloadingTime;
}

void Ship::setReloadingTime(const float& newReloadingTime)
{
    if (newReloadingTime <= 0)
    {
        throw std::logic_error("reloadingTime could not be less or equal zero");
    }
    this->reloadingTime = newReloadingTime;
}

const int& Ship::getMaxHP() const
{
    return maxHP;
}

void Ship::setMaxHP(const int& newMaxHP)
{
    if (newMaxHP <= 0)
    {
        throw std::logic_error("maxHP could not be less than zero");
    }
    this->maxHP = newMaxHP;
}

const int& Ship::getMaxEnergy() const
{
    return maxEnergy;
}

void Ship::setMaxEnergy(const int& newMaxEnergy)
{
    if (newMaxEnergy < 0)
    {
        throw std::logic_error("maxEnergy could not be less than zero");
    }
    this->maxEnergy = newMaxEnergy;
}

const int& Ship::getCurrentHP() const
{
    return currentHP;
}

void Ship::setCurrentHP(const int& newCurrentHP)
{
    if (newCurrentHP < 0)
    {
        throw std::logic_error("currentHP could not be less than zero");
    }
    this->currentHP = newCurrentHP;
}

const int& Ship::getCurrentEnergy() const
{
    return currentEnergy;
}

void Ship::setCurrentEnergy(const int& newCurrentEnergy)
{
    if (newCurrentEnergy < 0)
    {
        throw std::logic_error("currentEnergy could not be less than zero");
    }
    this->currentEnergy = newCurrentEnergy;
}

const sf::Color& Ship::getBulletColor() const
{
    return bulletColor;
}

void Ship::setBulletColor(const sf::Color& newBulletColor)
{
    this->bulletColor = newBulletColor;
}

const float& Ship::getBulletRadius() const
{
    return bulletRadius;
}

void Ship::setBulletRadius(const float& newBulletRadius)
{
    if (newBulletRadius <= 0)
    {
        throw std::logic_error("bulletRadius could not be less or equal zero");
    }
    this->bulletRadius = bulletRadius;
}

const int& Ship::getScore() const
{
    return score;
}

void Ship::setScore(const int& newScore)
{
    if (newScore < 0)
    {
        throw std::logic_error("score could not be less or equal zero");
    }
    this->score = newScore;
}

void Ship::shoot(const sf::Vector2f& direction)
{
    if (shipClockReloading.getElapsedTime().asSeconds() > reloadingTime)
    {
        Bullet bullet(getPosition(), direction, speed * 3, bulletRadius, bulletColor);
        bullets.push_back(bullet);
        shipClockReloading.restart();
    }
}

bool Ship::shipExplode(const int& damage)
{
    currentHP -= damage;
    if (currentHP <= 0) return true;
    else return false;
}

bool Ship::checkPosition()
{
    //Ship cannot escape beyond the background texture
    if (getPosition().x < getSize().x / 2)
    {
        setPosition(getSize().x / 2, getPosition().y);
    }
    if (getPosition().x > xBackgroundSize - getSize().x / 2)
    {
        setPosition(xBackgroundSize - getSize().x / 2, getPosition().y);
    }
    if (getPosition().y < getSize().x / 2)
    {
        setPosition(getPosition().x, getSize().x / 2);
    }
    if (getPosition().y > yBackgroundSize - getSize().x / 2)
    {
        setPosition(getPosition().x, yBackgroundSize - getSize().x / 2);
    }
    return true;
}
