#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public sf::CircleShape
{
private:
	//variables
	float maxLifeTime = 3.f;  //seconds
	sf::Clock lifeTime;
	float speed = 10.f;

	sf::Vector2f direction = sf::Vector2f(1, 1);

public:
	//constructors and destructor
	Bullet(sf::Vector2f position = sf::Vector2f(0, 0),
		sf::Vector2f direction = sf::Vector2f(1, 1),
		float speed = 10.f,
		float radius = 1,
		sf::Color color = sf::Color::Black,
		float naxLifeTime = 6.f);
	virtual ~Bullet();

	//getters and setters
	const float& getMaxLifeTime() const;
	void setMaxLifeTime(const float& newMaxLifeTime);

	const float& getSpeed() const;
	void setSpeed(const float& newSpeed);

	const sf::Vector2f& getDirection() const;
	void setDirection(const sf::Vector2f& newDirection);

	//functions
	void updateBullet();
	bool isEndBulletLife();
};

#endif BULLET_H
