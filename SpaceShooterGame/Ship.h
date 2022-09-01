#ifndef SHIPS_H
#define SHIPS_H

#include "Entity.h"
#include "Bullet.h"

class Ship : public Entity
{
protected:
	//variables
	float speed = 5.f;
	float acceleration = 2.f;
	float rotateAngle = 5.f;
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
		float speed = 5.f,
		float acceleration = 2.f,
		float rotateAngle = 5.f,
		int maxHP = 100,
		int maxEnergy = 100);
	Ship(const Ship& ship);
	virtual ~Ship();

	//getters and setters
	const float& getSpeed() const;
	void setSpeed(const float& newSpeed);

	const float& getAcceleration() const;
	void setAcceleration(const float& newAcceleration);

	const float& getRotateAngle() const;
	void setRotateAngle(const float& newRotateAngle);

	const float& getReloadingTime() const;
	void setReloadingTime(const float& newReloadingTime);

	const int& getMaxHP() const;
	void setMaxHP(const int& newMaxHP);

	const int& getMaxEnergy() const;
	void setMaxEnergy(const int& newMaxEnergy);

	const int& getCurrentHP() const;
	void setCurrentHP(const int& newCurrentHP);

	const int& getCurrentEnergy() const;
	void setCurrentEnergy(const int& newCurrentEnergy);

	const int& getScore() const;
	void setScore(const int& newScore);

	const sf::Color& getBulletColor() const;
	void setBulletColor(const sf::Color& newBulletColor);

	const float& getBulletRadius() const;
	void setBulletRadius(const float& newBulletRadius);

	//It's public due to we have to modify this conteiner
	std::vector<Bullet> bullets;

	//functions
	void shoot(const sf::Vector2f& direction);
	bool shipExplode(const int& damage);
	bool checkPosition();

	//pure virtual functions
	virtual void updateEntity() = 0;
};

#endif // !SHIPS_H
