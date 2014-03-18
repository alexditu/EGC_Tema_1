/* Ditu Alexandru 333 CA */
#include "Enemy2.h"
using namespace std;


Enemy2::Enemy2(void)
{
	createObject2D();
}


Enemy2::~Enemy2(void)
{
}

void Enemy2::createObject2D() {
	Rectangle2D *square1, *square2;

	square1 = new Rectangle2D(Point2D(-100,20), 30, 30, Color(1,0,1), false);
	square2 = new Rectangle2D(Point2D(-88,8), 30, 30, Color(1,0,1), false);
	shapes.push_back(square1);
	shapes.push_back(square2);

	setBorder();
	for (int i = 0; i < borderSegments.size(); i++) {
		shapes.push_back(borderSegments[i]);
	}

	center = Point2D(-89, 29);
	position = Point2D(-89, 29);
	speed = 3;
	angle = (float)rand() / 500;
	value = 20;
	setType(2);
}
