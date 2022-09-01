#ifndef  ENEMY_H
#define  ENEMY_H

#include "Ship.h"

class Enemy : public Ship
{
public:
	//constructors and virtual destructor
	Enemy(std::string objectName = "",
		float xScale = 1.f,
		float yScale = 1.f,
		size_t textureNumber = 1,
		float speed = 5.f,
		float acceleration = 2.f,
		float rotateAngle = 5.f,
		int maxHP = 100,
		int maxEnergy = 100);
	Enemy(const Enemy& enemy);
	virtual ~Enemy();

	//virtual functions
	virtual void updateEntity();
};

#endif // ! ENEMY_H
