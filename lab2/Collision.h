/* Ditu Alexandru 333 CA */
#pragma once
#include "Framework/Object2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"

class Collision
{
protected:
	float xMin, xMax, yMin, yMax;
public:
	Collision(float xMin, float xMax, float yMin, float yMax);
	Collision(void);
	~Collision(void);

	bool segmentIntersection (Point2D p1, Point2D p2, Point2D p3, Point2D p4);
	bool segmentIntersection(Line2D *line1, Line2D *line2);
	float min (float x, float y); // min dintre 2 valori
	float max (float x, float y); // max dintre 2 valori
	bool isInWindow(float x, float y); // verifica daca un punct este in interiorul terenului de joc
	bool isInWindowOrOnBorder(float x, float y); // verifica daca un punct este in interiorul terenului de joc sau pe margine
	int sign(float expr); // semnul unei expresii
	bool circleSegmentIntersection (Point2D *c, float radius, Point2D *p1, Point2D *p2);
	bool isInBorder(Point2D *min, Point2D *max, Point2D p); // verifica daca un obiect, anume un dreptunghi (dat prin min si max)
															// este in terenul de joc
};

