#pragma once
#include "Point2D.h"
#include <vector>

using namespace std;

//obiect generic 2D ajutator - ca sa pun toate obiectele (puncte, linii, dreptunghi, circle, polygon)
//in sistemul de coordonate, pentru a fi desenate
class Object2D
{
public:
	vector <Point2D*> points;
	vector <Point2D*> transf_points;
	int type; //1 = linie; 2 = dreptunghi; 3=cerc; 4=poligon
	Color color;
	bool fill;

public:
	Object2D() {}

	Object2D(vector <Point2D*> _points,int _type,Color _color,bool _fill)
	{
		for (unsigned int i = 0; i < _points.size(); i++)
		{
			points.push_back(new Point2D(_points[i]->x,_points[i]->y));
			transf_points.push_back(new Point2D(_points[i]->x,_points[i]->y));
		}
		type = _type;
		color = _color;
		fill = _fill;
	}


	~Object2D() {}

	Point2D* getMinPoint() {
		Point2D *min = new Point2D();

		min->x = transf_points[0]->x;
		min->y = transf_points[0]->y;

		for (unsigned int i = 0; i < transf_points.size(); i++) {
			if (min->x > transf_points[i]->x) {
				min->x = transf_points[i]->x;
			}
			if (min->y > transf_points[i]->y) {
				min->y = transf_points[i]->y;
			}
		}

		return min;
	}


	Point2D* getMaxPoint() {
		Point2D *max = new Point2D();

		max->x = transf_points[0]->x;
		max->y = transf_points[0]->y;

		for (unsigned int i = 0; i < transf_points.size(); i++) {
			if (max->x < transf_points[i]->x) {
				max->x = transf_points[i]->x;
			}
			if (max->y < transf_points[i]->y) {
				max->y = transf_points[i]->y;
			}
		}
		
		return max;
	}

		
};