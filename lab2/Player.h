/* Ditu Alexandru 333 CA */
#pragma once
#include "Framework/Object2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
using namespace std;

class Player
{

protected:
	vector <Object2D*> player;
	Point2D center;
	Polygon2D *weapon;
	vector <Line2D*> weaponSegments;
	vector <Point2D> weaponPoints;
	float radius;
	long int score;
	int lives;

public:
	Player(void);
	~Player(void);
	Player(float radius);

	void createPlayer();
	int getSize();

	// intoarce obiectele ce alcatuiesc player-ul (cerc, poligon etc)
	// folosita pentru afisarea pe ecran
	Object2D* getElement(int i);

	Point2D getCenter();
	Polygon2D* getWeapon();
	Line2D* getWeaponSegment(int i);
	void setWeaponCoordinates(int x, int y);
	float getRadius();
	Point2D getWeaponPoint(int i); // punctul din varful armei
	int getWeaponPointsSize();
	int getLives();
	void setLives(int val);
	long int getScore();
	void setScore(long int val);
	void incScore(long int incVal);
	void takeOneLife();
};

