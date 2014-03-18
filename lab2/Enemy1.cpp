/* Ditu Alexandru 333 CA */
#include "Enemy1.h"


Enemy1::Enemy1(void)
{
	createObject2D();
}


Enemy1::~Enemy1(void)
{
}

void Enemy1::createObject2D() {
	/*
		square1: 40 x 40
	*/
	Rectangle2D *square1;
	Polygon2D *square2;

	square1 = new Rectangle2D(Point2D(-100, 70), 40, 40, Color(0,1,0), false);
	square2 = new Polygon2D(Color(0,1,0), false);
	square2->addPoint(Point2D(-100, 90));
	square2->addPoint(Point2D(-80, 70));
	square2->addPoint(Point2D(-60, 90));
	square2->addPoint(Point2D(-80, 110));

	shapes.push_back(square1);
	shapes.push_back(square2);

	setBorder();
	for (int i = 0; i < borderSegments.size(); i++) {
		shapes.push_back(borderSegments[i]);
	}

	center = Point2D(-80, 90);
	position = center;
	speed = 2;
	angle = (float)rand() / 500;
	value = 10;
	setType(1);


}