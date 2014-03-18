/* Ditu Alexandru 333 CA */
#include "Collision.h"


Collision::Collision(void)
{
}


Collision::~Collision(void)
{
}

Collision::Collision(float xMin, float xMax, float yMin, float yMax) {
	Collision::xMin = xMin;
	Collision::yMin = yMin;
	Collision::xMax = xMax;
	Collision::yMax = yMax;
}

float Collision::min (float x, float y) {
	if (x < y)
		return x;
	else
		return y;
}

float Collision::max (float x, float y) {
	if (x > y)
		return x;
	else
		return y;
}

bool Collision::segmentIntersection(Line2D *line1, Line2D *line2) {
	return segmentIntersection(*line1->getPoint1(), *line1->getPoint2(), *line2->getPoint1(), *line2->getPoint2() ); 
}

bool Collision::segmentIntersection(Point2D p1, Point2D p2, Point2D p3, Point2D p4) {
	
	float m;
	float xi, yi; // coordonatele punctului de intersectie
	float aux1, aux2;

	m = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	
	if (m == 0) {
		return false;
	}
	aux1 = p1.x * p2.y - p1.y * p2.x;
	aux2 = p3.x * p4.y - p3.y * p4.x;
	xi = ((p3.x - p4.x) * aux1 - (p1.x - p2.x) * aux2) / m;
	yi = ((p3.y - p4.y) * aux1 - (p1.y - p2.y) * aux2) / m;

	if (xi < min(p1.x, p2.x) || xi > max(p1.x, p2.x) || yi < min(p1.y, p2.y) || yi > max(p1.y, p2.y)) {
		return false;
	}
	if (xi < min(p3.x, p4.x) || xi > max(p3.x, p4.x) || yi < min(p3.y, p4.y) || yi > max(p3.y, p4.y)) {
		return false;
	}
	return true;
}

bool Collision::isInWindow(float x, float y) {

	if (x < xMin || x > xMax || y < yMin || y > yMax) {
		return false;
	} else {
		return true;
	}
}

bool Collision::isInWindowOrOnBorder(float x, float y) {

	if (x <= xMin || x >= xMax || y <= yMin || y >= yMax) {
		return false;
	} else {
		return true;
	}
}

int Collision::sign(float expr) {
	if (expr < 0) {
		return -1;
	} else {
		return 1;
	}
}

// intoarce false daca nu se intersecteaza, true daca se intersecteaza in cel putin un punct
bool Collision::circleSegmentIntersection (Point2D *c, float radius, Point2D *p1, Point2D *p2) {

    float A1 = p2->y - p1->y; 
    float B1 = p1->x - p2->x; 
    double C1 = (p2->y - p1->y)*p1->x + (p1->x - p2->x)*p1->y; 
    double C2 = -B1*c->x + A1*c->y; 
    double det = A1*A1 - -B1*B1; 
    double cx = 0; 
    double cy = 0; 
    if(det != 0){ 
		cx = (float)((A1*C1 - B1*C2)/det); 
		cy = (float)((A1*C2 - -B1*C1)/det); 
    }else{ 
		cx = c->x; 
		cy = c->y; 
    }

	float dist = sqrt((cx - c->x) * (cx - c->x) + (cy - c->y) * (cy - c->y));
	if (dist <= radius) {
		if (cx >= min(p1->x, p2->x) && cx <= max(p1->x, p2->x) && cy >= min(p1->y, p2->y) && cy <= max(p1->y, p2->y)) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Collision::isInBorder(Point2D *min, Point2D *max, Point2D p) {
	if (p.x > min->x && p.x < max->x && p.y > min->y && p.y < max->y) {
		return true;
	} else {
		return false;
	}
}
