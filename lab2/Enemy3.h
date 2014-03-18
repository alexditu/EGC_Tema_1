/* Ditu Alexandru 333 CA */
#pragma once
#include "GenericEnemy.h"

class Enemy3 : public GenericEnemy
{
protected:
	int radius;

public:
	Enemy3(void);
	~Enemy3(void);

	void createObject2D();
};

