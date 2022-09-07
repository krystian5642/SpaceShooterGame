#include "Entity.h"

extern float xBackgroundSize;
extern float yBackgroundSize;

Entity::Entity(std::string entityName, float xScale, float yScale, size_t textureNumber)
{
	setEntityName(entityName);
	setScale(sf::Vector2f(xScale, yScale));
	setTextureNumber(textureNumber);
}

Entity::Entity(const Entity& entity)
{
	setEntityName(entity.entityName);
	setScale(entity.getScale());
	setTextureNumber(entity.textureNumber);
	entityTextures = entity.entityTextures;
	setTexture(entityTextures[0].get());
	setSize(entity.getSize());
	setOrigin(entity.getOrigin());
}

Entity::~Entity()
{
}

std::string Entity::getEntityName() const
{
	return entityName;
}

void Entity::setEntityName(std::string newEntityName)
{
	entityName = newEntityName;
}

size_t Entity::getTextureNumber() const
{
	return textureNumber;
}

void Entity::setTextureNumber(size_t newTextureNumber)
{
	if (newTextureNumber <= 0)
	{
		throw std::logic_error("textureNumber cannot be less or equal zero");
	}
	textureNumber = newTextureNumber;
}

const sf::Vector2f& Entity::getScale() const
{
	return scale;
}

void Entity::setScale(const sf::Vector2f& newScale)
{
	if (scale.x <= 0 && scale.y <= 0)
	{
		throw std::logic_error("scale cannot be less or equal zero");
	}
	scale = newScale;
}

size_t Entity::getTextureIndex() const
{
	return textureIndex;
}
