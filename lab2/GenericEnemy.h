/* Ditu Alexandru 333 CA */
#pragma once
#include "Framework/Object2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
using namespace std;

class GenericEnemy
{
protected:
	vector <Object2D*> shapes;
	Point2D center;
	Polygon2D *border;
	vector <Line2D*> borderSegments;
	bool alive;
	int value;
	Point2D position;
	float angle, speed;
	int type;
	Point2D *min, *max;
	

public:
	
	GenericEnemy(void);
	~GenericEnemy(void);

	//void createObject2D();
	int getSize();
	Object2D* getElement(int i);
	Point2D getCenter();
	void setBorder();
	Line2D *getBorderSegment(int i);
	bool isAlive();
	void giveLife();
	void takeLife();
	void setNewPosition(Point2D newPos);
	Point2D getPosition();
	void incSpeed();
	void incAngle();
	float getAngle();
	float getSpeed();
	int getValue();
	void setAngle (float angle);
	void setType (int type);
	int getType ();
	Point2D* getMin();
	Point2D* getMax();
};

