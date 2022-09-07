#ifndef  ENTITY_H
#define  ENTITY_H

#include "Libraries.h"

class Entity : public sf::RectangleShape
{
protected:
	//varaibles
	std::shared_ptr<std::shared_ptr<sf::Texture>[]> entityTextures;
	std::string entityName = "";

	size_t textureNumber = 1;
	size_t textureIndex = 0;

	sf::Vector2f scale = sf::Vector2f(1, 1);

	std::vector <std::string> texturePaths;

	//pure virtual functions
	virtual void loadEntityTexture() = 0;

public:
	//constructors and virtual destructor
	Entity(std::string entityName = "",
		float xScale = 1,
		float yScale = 1,
		size_t textureNumber = 1);
	Entity(const Entity& entity);
	virtual ~Entity();

	//getters and setters
	std::string getEntityName() const;
	void setEntityName(std::string newEntityName);

	size_t getTextureNumber() const;
	void setTextureNumber(const size_t newTextureNumber);

	const sf::Vector2f& getScale() const;
	void setScale(const sf::Vector2f& newScale);

    size_t getTextureIndex() const;

	//pure virtual functions
	virtual void updateEntity(long double dt) = 0;
};

#endif // !ENTITY_H