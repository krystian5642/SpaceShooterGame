#ifndef PLAYER_H
#define PLATER_H

#include "Ship.h"

class Player : public Ship
{
public:
	//constructors and virtual destructor
	Player(std::string objectName = "",
		float xScale = 1.f,
		float yScale = 1.f,
		size_t textureNumber = 1,
		float speed = 300.f,
		float acceleration = 2.f,
		float rotateAngle = 200.f,
		int maxHP = 100,
		int maxEnergy = 100);
	Player(const Player& player);
	virtual ~Player();

	//virtual functions
	virtual void updateEntity(long double dt);
};

#endif PLAYER_H