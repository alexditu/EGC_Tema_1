/* Ditu Alexandru 333 CA */
#pragma once
#include "GenericEnemy.h"

#define RADIUS 2.5
#define SPEED 8
#define DISTANCE_FROM_PLAYER 10


class Bullet : public GenericEnemy
{
protected:
	float distanceFromPlayer; // distanta de lansare a glontului fata de cercul player-ului 
	int radius; // raza glontului
public:
	Bullet(void);
	~Bullet(void);

	void createObject2D();
	float getDistance();
	int getRadius();
};

