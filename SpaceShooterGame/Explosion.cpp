#include "Explosion.h"

void Explosion::loadEntityTexture()
{
    entityTextures = std::make_shared<std::shared_ptr<sf::Texture>[]>(textureNumber);
    for (int i = 1; i <= textureNumber; i++)
    {
        texturePaths.push_back("Pictures\\Explosions\\explode (" + std::to_string(i) + ").png");
    }
    for (size_t i = 0; i < textureNumber; i++)
    {
        entityTextures[i] = std::make_shared<sf::Texture>();
        if (!entityTextures[i]->loadFromFile(texturePaths[i]))
        {
            throw std::logic_error("Could not load player texture");
        }
    }
    texturePaths.clear();
}

Explosion::Explosion(sf::Vector2f position, sf::Vector2f size, std::string objectName,
    size_t textureNumber) : Entity(objectName, size.x / 240, size.y / 240, textureNumber)
{
    setPosition(position);
    setSize(sf::Vector2f(size.x, size.x));
    loadEntityTexture();
    setOrigin(getSize().x / 2, getSize().y / 2);
}

Explosion::Explosion(const Explosion& explosion) : Entity(explosion)
{
    setPosition(explosion.getPosition());
}

Explosion::~Explosion()
{
}

void Explosion::updateEntity(long double dt)
{
    setTexture(entityTextures[textureIndex].get(), true);
    textureIndex++;
}
