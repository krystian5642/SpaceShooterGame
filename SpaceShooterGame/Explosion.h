#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "entity.h"
#include "Player.h"
#include "Enemy.h"

class Explosion : public Entity
{
protected:
	//virtual functions
	virtual void loadEntityTexture();

public:
	//constructors and virtual destructor
	Explosion(sf::Vector2f position = sf::Vector2f(0, 0),
		sf::Vector2f size = sf::Vector2f(0, 0),
		std::string objectName = "Explode",
		size_t textureNumber = 1);
	Explosion(const Explosion& explosion);
	virtual ~Explosion();

	//virtual functions
	virtual void updateEntity();
};

#endif // !EXPLOSION_H
