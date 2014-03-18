/* Ditu Alexandru 333 CA */
#include "GenericEnemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"


GenericEnemy::GenericEnemy(void)
{
	alive = 0;
}


GenericEnemy::~GenericEnemy(void)
{
}

int GenericEnemy::getSize() {
	return shapes.size();
}

Object2D* GenericEnemy::getElement(int i) {
	return shapes[i];
}

Point2D GenericEnemy::getCenter() {
	return center;
}

void GenericEnemy::setBorder() {
	min = shapes[0]->getMinPoint();
	max = shapes[0]->getMaxPoint();

	// aflu min si max dintre toate formele acestui obiect
	for (int i = 0; i < shapes.size(); i++) {
		if (min->x > shapes[i]->getMinPoint()->x) {
			min->x = shapes[i]->getMinPoint()->x;
		}
		if (min->y > shapes[i]->getMinPoint()->y) {
			min->y = shapes[i]->getMinPoint()->y;
		}
		if (max->x < shapes[i]->getMaxPoint()->x) {
			max->x = shapes[i]->getMaxPoint()->x;
		}
		if (max->y < shapes[i]->getMaxPoint()->y) {
			min->y = shapes[i]->getMaxPoint()->y;
		}
	}


	// creez chenarul ce incadreaza obiectul (border);
	border = new Polygon2D(Color(1,0,0), false);
	border->addPoint(Point2D(min->x, min->y));
	border->addPoint(Point2D(max->x, min->y));
	border->addPoint(Point2D(max->x, max->y));
	border->addPoint(Point2D(min->x, max->y));

	Line2D* line;
	line = new Line2D(Point2D(min->x, min->y), Point2D(max->x, min->y), Color(0,0,0));
	borderSegments.push_back(line);
	line = new Line2D(Point2D(max->x, min->y), Point2D(max->x, max->y), Color(0,0,0));
	borderSegments.push_back(line);
	line = new Line2D(Point2D(max->x, max->y), Point2D(min->x, max->y), Color(0,0,0));
	borderSegments.push_back(line);
	line = new Line2D(Point2D(min->x, max->y), Point2D(min->x, min->y), Color(0,0,0));
	borderSegments.push_back(line);
}

// functie ce intoarce coordonatele fiecarui segment al chenarului,
// dar dupa ce au fost aplicate toate transformarile (rotatie, translatie)
// deci, pozitia curenta a chenarului
Line2D* GenericEnemy::getBorderSegment(int i) {
	return borderSegments[i]->getLine();
}

bool GenericEnemy::isAlive() {
	return alive;
}

void GenericEnemy::giveLife() {
	alive = 1;
}

void GenericEnemy::takeLife() {
	alive = 0;
}

void GenericEnemy::setNewPosition(Point2D newPos) {
	this->position = newPos;
}
	
Point2D GenericEnemy::getPosition() {
	return GenericEnemy::position;
}

void GenericEnemy::incSpeed() {
	GenericEnemy::speed += 0.1;
}

void GenericEnemy::incAngle() {
	GenericEnemy::angle += 0.1;
}

float GenericEnemy::getAngle() {
	return GenericEnemy::angle;
}

float GenericEnemy::getSpeed() {
	return GenericEnemy::speed;
}

int GenericEnemy::getValue() {
	return value;
}

void GenericEnemy::setAngle (float angle) {
	this->angle = angle;
}

void GenericEnemy::setType (int type) {
	this->type = type;
}

int GenericEnemy::getType () {
	return this->type;
}

Point2D* GenericEnemy::getMin() {
	Point2D *newMin;
	newMin = shapes[0]->getMinPoint();

	// aflu min dintre toate formele acestui obiect
	for (int i = 0; i < shapes.size(); i++) {
		if (newMin->x > shapes[i]->getMinPoint()->x) {
			newMin->x = shapes[i]->getMinPoint()->x;
		}
		if (newMin->y > shapes[i]->getMinPoint()->y) {
			newMin->y = shapes[i]->getMinPoint()->y;
		}
	}
	return newMin;
}

Point2D* GenericEnemy::getMax() {
	Point2D *newMax;
	newMax = shapes[0]->getMaxPoint();

	// aflu max dintre toate formele acestui obiect
	for (int i = 0; i < shapes.size(); i++) {
		if (newMax->x < shapes[i]->getMaxPoint()->x) {
			newMax->x = shapes[i]->getMaxPoint()->x;
		}
		if (newMax->y < shapes[i]->getMaxPoint()->y) {
			newMax->y = shapes[i]->getMaxPoint()->y;
		}
	}
	return newMax;
}
