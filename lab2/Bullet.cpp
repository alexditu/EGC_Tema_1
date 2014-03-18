/* Ditu Alexandru 333 CA */
#include "Bullet.h"


Bullet::Bullet(void)
{
	createObject2D();
}


Bullet::~Bullet(void)
{
}

void Bullet::createObject2D() {

	center = Point2D(0,0);
	radius = RADIUS;
	Circle2D *circle = new Circle2D(center, radius, Color(1,0,0), true);
	shapes.push_back(circle);
	speed = SPEED;
	position = center;
	distanceFromPlayer = DISTANCE_FROM_PLAYER;

}

float Bullet::getDistance() {
	return distanceFromPlayer;
}

int Bullet::getRadius() {
	return radius;
}