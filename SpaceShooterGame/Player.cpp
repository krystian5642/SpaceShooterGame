#include "Player.h"

extern float xBackgroundSize;
extern float yBackgroundSize;

Player::Player(std::string objectName, float xScale, float yScale, size_t textureNumber,
    float speed, float acceleration, float rotateAngle, int maxHP, int maxEnergy)
    : Ship(objectName, xScale, yScale, textureNumber,
        speed, acceleration, rotateAngle, maxHP, maxEnergy)
{
    setScore(0);
    setBulletColor(sf::Color::Green);
    texturePaths.push_back("Pictures\\Ships\\PlayerShips\\ship1.png");
    setPosition(rand() % (int)xBackgroundSize, rand() % (int)yBackgroundSize);
    loadEntityTexture();
    setSize(sf::Vector2f(getTexture()->getSize().x * getScale().x, getTexture()->getSize().y * getScale().y));
    setOrigin(getSize().x / 2, getSize().y / 2);
}

Player::Player(const Player& player) : Ship(player)
{
    setScore(player.score);
}

Player::~Player()
{
}

void Player::updateEntity(long double dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        double PI = 3.141592653589;
        double angle = getRotation();
        double angleInRad = angle * PI / 180;
        sf::Vector2f currentSpeedVector;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && currentEnergy > 0)
        {
            currentEnergy--;
            currentSpeedVector = sf::Vector2f(acceleration * speed * cos(angleInRad) * dt, acceleration * speed * sin(angleInRad) * dt);
        }
        else
        {
            currentSpeedVector = sf::Vector2f(speed * cos(angleInRad) * dt, speed * sin(angleInRad) * dt);
        }
        move(currentSpeedVector);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        rotate(-rotateAngle * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        rotate(rotateAngle*dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        double PI = 3.141592653589;
        double angle = getRotation();
        double angleInRad = angle * PI / 180;
        sf::Vector2f direction(cos(angleInRad), sin(angleInRad));
        shoot(direction);
    }
    if (currentEnergy < maxEnergy && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        currentEnergy++;
    }
    checkPosition();
}
