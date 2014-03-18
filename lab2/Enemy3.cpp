/* Ditu Alexandru 333 CA */
#include "Enemy3.h"
#include "GenericEnemy.h"


Enemy3::Enemy3(void)
{
	createObject2D();
}


Enemy3::~Enemy3(void)
{
}

void Enemy3::createObject2D() {
	Circle2D *circle;
	Polygon2D *triangle1, *triangle2, *triangle3, *triangle4;

	center = Point2D(0,0);
	radius = 5;
	float size = 20;

	circle = new Circle2D(center, (float)radius, Color(0,1,1), true);
	triangle1 = new Polygon2D(Color(0,1,1), false);
	triangle1->addPoint(Point2D(-size, size));
	triangle1->addPoint(Point2D(0, size));
	triangle1->addPoint(Point2D(0, 0));

	triangle2 = new Polygon2D(Color(0,1,1), false);
	triangle2->addPoint(Point2D(size, size));
	triangle2->addPoint(Point2D(size, 0));
	triangle2->addPoint(Point2D(0, 0));

	triangle3 = new Polygon2D(Color(0,1,1), false);
	triangle3->addPoint(Point2D(size, -size));
	triangle3->addPoint(Point2D(0, -size));
	triangle3->addPoint(Point2D(0, 0));

	triangle4 = new Polygon2D(Color(0,1,1), false);
	triangle4->addPoint(Point2D(-size, -size));
	triangle4->addPoint(Point2D(-size, 0));
	triangle4->addPoint(Point2D(0, 0));

	shapes.push_back(circle);
	shapes.push_back(triangle1);
	shapes.push_back(triangle2);
	shapes.push_back(triangle3);
	shapes.push_back(triangle4);

	speed = 2;
	angle = (float)rand() / 500;
	value = 30;

	setBorder();
	for (unsigned int i = 0; i < borderSegments.size(); i++) {
		shapes.push_back(borderSegments[i]);
	}

	setType(3);

}