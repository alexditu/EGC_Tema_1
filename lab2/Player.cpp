/* Ditu Alexandru 333 CA */
#include "Player.h"


Player::Player(void)
{
	createPlayer();
}


Player::~Player(void)
{
}

Player::Player(float radius) {
	Player::radius = radius;
	createPlayer();
}

void Player::createPlayer () {
	Object2D *circle, *circle2;
	Polygon2D *poly;
	Line2D *line;

	center = Point2D(0,0);
	circle = new Circle2D(center, Player::radius, Color(1,0,0), false);
	circle2 = new Circle2D(center, Player::radius - 3, Color(1,0,0), false);

	poly = new Polygon2D(Color(1,0,0), false);
	poly->addPoint(Point2D(0, 20));
	poly->addPoint(Point2D(-20, 0));
	poly->addPoint(Point2D(-10, -20));
	poly->addPoint(Point2D(-10, 0));
	poly->addPoint(Point2D(0, 10));
	poly->addPoint(Point2D(10, 0));
	poly->addPoint(Point2D(10, -20));
	poly->addPoint(Point2D(20, 0));

	weapon = new Polygon2D(Color(1,0,0), true);	
	weapon->addPoint(Point2D(-15,35));
	weaponPoints.push_back(Point2D(-15,35));

	weapon->addPoint(Point2D(15,35));
	weaponPoints.push_back(Point2D(15,35));

	weapon->addPoint(Point2D(0,100));
	weaponPoints.push_back(Point2D(0,100));

	line = new Line2D(Point2D(-15,35), Point2D(0, 100), Color(0,0,0));
	weaponSegments.push_back(line);
	line = new Line2D(Point2D(15,35), Point2D(0, 100), Color(0,0,0));
	weaponSegments.push_back(line);

	
	player.push_back(circle);
	player.push_back(circle2);
	player.push_back(poly);
	player.push_back(weapon);
	player.push_back(weaponSegments[0]);
	player.push_back(weaponSegments[1]);

	lives = 5;
	score = 0;
	

}

int Player::getSize() {
	return player.size();
}

Object2D* Player::getElement(int i) {
	return player[i];
}

Point2D Player::getCenter() {
	return center;
}

Polygon2D* Player::getWeapon() {
	return weapon;
}

// intoarce segmentele ce alcatuiesc arma, dar in pozitia in care sunt
// dupa ce sufera transformori (in pozitia curenta)
Line2D* Player::getWeaponSegment(int i) {
	return weaponSegments[i]->getLine();
}

float Player::getRadius() {
	return Player::radius;
}

Point2D Player::getWeaponPoint(int i) {
	return weaponPoints[i];
}

int Player::getWeaponPointsSize() {
	return weaponPoints.size();
}

int Player::getLives() {
	return lives;
}

void Player::setLives(int val) {
	lives = val;
}
	
long int Player::getScore() {
	return score;
}
	
void Player::setScore(long int val) {
	score = val;
}
	
void Player::incScore(long int incVal) {
	score += incVal;
}

void Player::takeOneLife() {
	lives --;
}

//void Player::setWeaponCoordinates(int x, int y) {
//	for (int i = 0; i < weaponSegments.size(); i++) {
//		weaponSegments[i]->
