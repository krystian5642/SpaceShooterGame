#ifndef SHIPS_H
#define SHIPS_H

#include "Entity.h"
#include "Bullet.h"

class Ship : public Entity
{
protected:
	//variables
	float speed = 300.f;
	float acceleration = 2.f;
	float rotateAngle = 200.f;
	float reloadingTime = 1.f;

	int maxHP = 100;
	int maxEnergy = 100;
	int currentHP = 100;
	int currentEnergy = 100;
	int score = 0;

	sf::Clock shipClockReloading;
	sf::Clock shipClockMove;

	sf::Color bulletColor = sf::Color::Green;
	float bulletRadius = 5.f;

	//virtual functions
	virtual void loadEntityTexture();

public:
	//constructors and virtual destructor
	Ship(std::string objectName = "",
		float xScale = 1.f,
		float yScale = 1.f,
		size_t textureNumber = 1,
		float speed = 300.f,
		float acceleration = 2.f,
		float rotateAngle = 200.f,
		int maxHP = 100,
		int maxEnergy = 100);
	Ship(const Ship& ship);
	virtual ~Ship();

	//getters and setters
	float getSpeed() const;
	void setSpeed(float newSpeed);

	float getAcceleration() const;
	void setAcceleration(float newAcceleration);

	float getRotateAngle() const;
	void setRotateAngle(float newRotateAngle);

	float getReloadingTime() const;
	void setReloadingTime(float newReloadingTime);

	int getMaxHP() const;
	void setMaxHP(const int newMaxHP);

	int getMaxEnergy() const;
	void setMaxEnergy(const int newMaxEnergy);

	int getCurrentHP() const;
	void setCurrentHP(int newCurrentHP);

	int getCurrentEnergy() const;
	void setCurrentEnergy(int newCurrentEnergy);

	int getScore() const;
	void setScore(int newScore);

	const sf::Color& getBulletColor() const;
	void setBulletColor(const sf::Color& newBulletColor);

	float getBulletRadius() const;
	void setBulletRadius(float newBulletRadius);

	//It's public due to we have to modify this conteiner
	std::vector<Bullet> bullets;

	//functions
	void shoot(const sf::Vector2f& direction);
	bool shipExplode(int damage);
	bool checkPosition();

	//pure virtual functions
	virtual void updateEntity(long double dt) = 0;
};

#endif // !SHIPS_H
