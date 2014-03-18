/* Ditu Alexandru 333 CA */
#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Bullet.h"
#include "GenericEnemy.h"
#include "Collision.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>


#define PI 3.14159265358979323846
#define inf 1000000
using namespace std;

Visual2D *v2d1, *v2dScore;
Text *title, *score, *textLives, *gameOver, *textCrtLevel;
string livess = "Lives:   ";
string stringLevel = "Level:   ";


// Player and enemies:
Player player(30);
vector <GenericEnemy> enemies;


// buffer pentru memorat ce tasta e apasata
bool *keyStates = new bool[256];

// variabile pentru miscare (viteza, unghi etc.)
static float speed_inc = 6;
static float angle = 0;
static float angle_inc = 0.1;
static float rotAngle = 0;

static bool weapon_on = false;

// pozitia curenta a player-ului (a centrului player-ului)
static float posX = 0, posY = 0;

Collision collision(WINDOW_X_MIN, WINDOW_X_MAX, WINDOW_Y_MIN, WINDOW_Y_MAX);
Point2D spawnPosition[4];
int level = 0;
int numberOfEnemies[3];
bool gameEnded;

vector <Bullet> bullets;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	glutFullScreen();

	// context vizual pentru terenul de joc
	v2d1 = new Visual2D(WINDOW_X_MIN, WINDOW_Y_MIN, WINDOW_X_MAX, WINDOW_Y_MAX,
						0,DrawingWindow::height/8,DrawingWindow::width,DrawingWindow::height); 
	v2d1->tipTran(true);
	v2d1->cadruFereastra(Color(1,0,0));
	addVisual2D(v2d1);

	// context vizual pentru scor
	v2dScore = new Visual2D (0, 0, DrawingWindow::width, DrawingWindow::height/8, 0, 0, DrawingWindow::width, DrawingWindow::height/8);
	v2dScore->tipTran(true);
	addVisual2D(v2dScore);
	
	title = new Text("SCORE:", Point2D(650, 50), Color(0,1,1), BITMAP_TIMES_ROMAN_24);
	score = new Text("0", Point2D(685,5), Color(0,1,1), BITMAP_TIMES_ROMAN_24);
	textLives = new Text("Lives:   3", Point2D(1000,5), Color(0,1,1), BITMAP_TIMES_ROMAN_24);
	gameOver = new Text("GAME OVER!", Point2D(-100,0), Color(0,1,1), BITMAP_TIMES_ROMAN_24);
	textCrtLevel = new Text("Level: x", Point2D(300,5), Color(0,1,1), BITMAP_TIMES_ROMAN_24);

	textLives->setText(livess.append(to_string(player.getLives())));
	textCrtLevel->setText(stringLevel.append(to_string(level+1)));

	addText_to_Visual2D(title, v2dScore);
	addText_to_Visual2D(score, v2dScore);
	addText_to_Visual2D(textLives, v2dScore);
	addText_to_Visual2D(textCrtLevel, v2dScore);
	
	
	// Adaug formele ce reprezinta player-ul, mai putin arma si conturul armei, de asta am pus si -3
	for (int i = 0; i < player.getSize() - 3; i++) {
		addObject2D_to_Visual2D(player.getElement(i), v2d1);
	}


	// cele 4 locuri in care pot aparea inamicii
	spawnPosition[0] = Point2D(0, WINDOW_Y_MAX * 5 / 8);
	spawnPosition[1] = Point2D(WINDOW_Y_MAX * 5 / 8, 0);
	spawnPosition[2] = Point2D(0, WINDOW_Y_MIN * 5 / 8);
	spawnPosition[3] = Point2D(WINDOW_Y_MIN * 5 / 8, 0);

	// Initializez cu false keyStates (nicio tasta nu a fost apasata)
	keyStates[KEY_UP] = false;
	keyStates[KEY_LEFT] = false;
	keyStates[KEY_RIGHT] = false;
	keyStates[KEY_SPACE] = false;
	keyStates[KEY_DOWN] = false;
	keyStates['w'] = false;
	weapon_on = false;

	// folosesc mai tarziu rand()
	srand(time(NULL));

	level = -1;
	// proportiile de spwan-are a inamicilor
	numberOfEnemies[0] = 3;
	numberOfEnemies[1] = 2;
	numberOfEnemies[2] = 1;
	gameEnded = false;

}


//functia care permite animatia
void DrawingWindow::onIdle()
{

	Point2D playerCenter = player.getCenter();
	float newPosX, newPosY;

	int sx, sy; // semnul pt x si y

	if (keyStates[KEY_UP]) {

		// calculez noua pozitie a centrului player-ului
		newPosX = posX + speed_inc * cos(angle + PI/2);
		newPosY = posY + speed_inc * sin(angle + PI/2);
		
		sx = collision.sign(cos(angle + PI/2));
		sy = collision.sign(sin(angle + PI/2));
		
		// verific mai intai daca arma player-ului iese din teren:
		bool wIsInWindow = true;
		if (weapon_on) {
			for (int i = 0; i < 2; i++)  {
				if (!collision.isInWindow(player.getWeaponSegment(i)->getP1()->x,
										  player.getWeaponSegment(i)->getP1()->y)) {
					wIsInWindow = false;
				}
				if (!collision.isInWindow(player.getWeaponSegment(i)->getP2()->x,
										  player.getWeaponSegment(i)->getP2()->y)) {
					wIsInWindow = false;
				}
			}
		}
		
		// verific daca nu cumva player-ul iese din teren
		if ((collision.isInWindow(newPosX + playerCenter.x + player.getRadius() * sx,
								 newPosY + playerCenter.y + player.getRadius() * sy) == true) &&
								 (wIsInWindow == true)) {
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-playerCenter.x, -playerCenter.y);
			Transform2D::rotateMatrix(angle);
			Transform2D::translateMatrix(playerCenter.x, playerCenter.y);
			Transform2D::translateMatrix(posX, posY);
			Transform2D::translateMatrix(speed_inc * cos(angle + PI/2), speed_inc * sin(angle + PI/2));

			posX = posX + speed_inc*cos(angle + PI/2);
			posY = posY + speed_inc*sin(angle + PI/2);

			for (int i = 0; i < player.getSize(); i++) {
				Transform2D::applyTransform(player.getElement(i));
			}
		}

	}

	if (keyStates[KEY_DOWN]) {
		
		// calculez noua pozitie a centrului player-ului
		newPosX = posX - speed_inc * cos(angle + PI/2);
		newPosY = posY - speed_inc * sin(angle + PI/2);

		sx = collision.sign(cos(angle + PI/2));
		sy = collision.sign(sin(angle + PI/2));

		bool wIsInWindow = true;
		
		if (collision.isInWindow(newPosX + playerCenter.x - player.getRadius() * sx,
								 newPosY + playerCenter.y - player.getRadius() * sy) &&
								 (wIsInWindow == true)){
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-playerCenter.x, -playerCenter.y);
			Transform2D::rotateMatrix(angle);
			Transform2D::translateMatrix(playerCenter.x, playerCenter.y);
			Transform2D::translateMatrix(posX, posY);
			Transform2D::translateMatrix(-speed_inc * cos(angle + PI/2), -speed_inc * sin(angle + PI/2));

			posX = posX - speed_inc*cos(angle + PI/2);
			posY = posY - speed_inc*sin(angle + PI/2);

			for (int i = 0; i < player.getSize(); i++) {
				Transform2D::applyTransform(player.getElement(i));
			}
		}

	}

	if(keyStates[KEY_LEFT]) {
		
		bool wIsInWindow = true;
		if (weapon_on) {
			for (int i = 0; i < 2; i++)  {
				if (!collision.isInWindow(player.getWeaponSegment(i)->getP1()->x + cos(angle + PI/2),
										  player.getWeaponSegment(i)->getP1()->y + sin(angle + PI/2))) {
					wIsInWindow = false;
				}
				if (!collision.isInWindow(player.getWeaponSegment(i)->getP2()->x,
										  player.getWeaponSegment(i)->getP2()->y)) {
					wIsInWindow = false;
				}
			}
		}
		if (wIsInWindow) {
			angle += angle_inc;
			if (angle > 2*PI) {
				angle -= 2*PI;
			}
			if (angle < -2*PI) {
				angle += 2*PI;
			}
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-playerCenter.x, -playerCenter.y);
			Transform2D::rotateMatrix(angle);
			Transform2D::translateMatrix(playerCenter.x, playerCenter.y);
			Transform2D::translateMatrix(posX, posY);
			for (int i = 0; i < player.getSize(); i++) {
				Transform2D::applyTransform(player.getElement(i));
			}
		}
	}

	if(keyStates[KEY_RIGHT]) {
		
		bool wIsInWindow = true;
		if (weapon_on) {
			for (int i = 0; i < 2; i++)  {
				if (!collision.isInWindow(player.getWeaponSegment(i)->getP1()->x + cos(angle + PI/2),
										  player.getWeaponSegment(i)->getP1()->y + sin(angle + PI/2))) {
					wIsInWindow = false;
				}
				if (!collision.isInWindow(player.getWeaponSegment(i)->getP2()->x,
										  player.getWeaponSegment(i)->getP2()->y)) {
					wIsInWindow = false;
				}
			}
		}
		if (wIsInWindow) {
			angle -= angle_inc;
			if (angle > 2*PI) {
				angle -= 2*PI;
			}
			if (angle < -2*PI) {
				angle += 2*PI;
			}
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-playerCenter.x, -playerCenter.y);
			Transform2D::rotateMatrix(angle);
			Transform2D::translateMatrix(playerCenter.x, playerCenter.y);
			Transform2D::translateMatrix(posX, posY);
			for (int i = 0; i < player.getSize(); i++) {
				Transform2D::applyTransform(player.getElement(i));
			}
		}
	}

	// verific daca s-a tras cu arma; daca da, trebuie sa desenez gloantele
	if (keyStates['w']) {

		keyStates['w'] = false;
		if (weapon_on) {

			// poate sa traga cu maxim 5 gloante
			int no = 0;
			for (int i = 0; i < bullets.size(); i++) {
				if (bullets[i].isAlive()) {
					no ++;
				}
			}

			if (no < 5) {
				Bullet bullet;
				bullet.giveLife();
				bullet.setAngle(angle + PI / 2);
				// aflu pozitia glontului (in fata player-ului)
				float xPos, yPos;
				xPos = posX + (player.getRadius() + bullet.getDistance()) * cos(bullet.getAngle());
				yPos = posY + (player.getRadius() + bullet.getDistance()) * sin(bullet.getAngle());
				bullet.setNewPosition(Point2D(xPos, yPos));

				// pt ca vectorul de bullets sa nu devina prea mare, pun gloante noi in locurile libere
				// din vector
				bool foundFreeSpace = false;
				for (int i = 0; i < bullets.size(); i++) {
					if (!bullets[i].isAlive()) {
						bullets[i] = bullet;
						foundFreeSpace = true;
						break;
					}
				}
				if (!foundFreeSpace) {
					bullets.push_back(bullet);
				}
				// trebuie sa il afisez
				addObject2D_to_Visual2D(bullet.getElement(0), v2d1);
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(bullet.getPosition().x, bullet.getPosition().y);
				Transform2D::applyTransform(bullet.getElement(0));
			}
		}
	}

	// verific daca arma se intersecteaza cu vreun inamic
	if (weapon_on) {
		for (int i = 0; i < 2; i++) {
			Line2D *w = player.getWeaponSegment(i);
			for (unsigned int ii = 0; ii < enemies.size(); ii++) {
				if (enemies[ii].isAlive()) {
					for (int j = 0; j < 4; j++) {
						Line2D *e = enemies[ii].getBorderSegment(j);
						if (collision.segmentIntersection(w, e) == true) {
							player.incScore(enemies[ii].getValue());
							score->setText(to_string(player.getScore()));
							for (int k = 0; k < enemies[ii].getSize(); k++) {
								removeObject2D_from_Visual2D(enemies[ii].getElement(k), v2d1);
							}
							enemies[ii].takeLife();
							enemies.erase(enemies.begin() + ii);
							break;
						}
					}
				}
			}
		}
	}

	// verific daca vreun inamic se intersecteaza cu player-ul
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (enemies[i].isAlive()) {

			// Enemyborder vs player
			for (int j = 0; j < 4; j++) {
				Line2D *sgmt = enemies[i].getBorderSegment(j);
				Point2D *cen = new Point2D(posX, posY);
				if (collision.circleSegmentIntersection(cen, player.getRadius(), sgmt->getPoint1(), sgmt->getPoint2())) {
					player.takeOneLife();
					livess = "Lives:   ";
					textLives->setText(livess.append(to_string(player.getLives())));

					// sterg toti inamicii de pe ecran
					for (unsigned int k = 0; k < enemies.size(); k++) {
						if (enemies[k].isAlive()) {
							for (int l = 0; l < enemies[k].getSize(); l++) {
								removeObject2D_from_Visual2D(enemies[k].getElement(l), v2d1);
							}
							enemies[k].takeLife();
						}
					}
					
					level --; //ma asigur ca raman la acelasi nivel
					enemies.clear();

					// daca am ramas fara vieti => gameOver
					if (player.getLives() == 0) {
						gameEnded = true;
						addText_to_Visual2D(gameOver, v2d1);
						

						// sterg si player-ul de pe ecran
						for (int k = 0; k < player.getSize(); k++) {
							removeObject2D_from_Visual2D(player.getElement(k), v2d1);
						}

						// in cazul in care am ramas fara vieti, nu mai continui sa fac verificari,
						// asa ca ies fortat din for, facand i mai mare decat valoarea maxima acceptata :)
						i = enemies.size();
						break;
					}

					//resetez pozitia player-ului:
					Transform2D::loadIdentityMatrix();
					angle = 0;
					for (int k = 0; k < player.getSize(); k++) {
						Transform2D::applyTransform(player.getElement(k));
					}
					posX = posY = 0;
					break;
				}
			}

			// verific daca inamicul i se intersecteaza cu vreun glont
			// EnemyBorder vs gloante
			if (i < enemies.size() && enemies[i].isAlive()) {
				for (int j = 0; j < bullets.size(); j++) {
					if (bullets[j].isAlive()) {
						if (collision.isInBorder(enemies[i].getMin(), enemies[i].getMax(), bullets[j].getPosition())) {
							player.incScore(enemies[i].getValue());
							score->setText(to_string(player.getScore()));
							for (int k = 0; k < enemies[i].getSize(); k++) {
								removeObject2D_from_Visual2D(enemies[i].getElement(k), v2d1);
							}
							enemies[i].takeLife();
							enemies.erase(enemies.begin() + i);
							break;
						}
					}
				}
			}

		}
	}

	// animatie inamici:
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (enemies[i].isAlive()) {

			float rnd = rand() % 100;
			Point2D p;
			float nextX, nextY, difX, difY;

			// animatie diferita pentru inamicii de tipul 3 (cei care urmaresc player-ul)
			if (enemies[i].getType() != 3) {
				p = Point2D(enemies[i].getPosition().x + enemies[i].getSpeed() * cos(enemies[i].getAngle()),
							enemies[i].getPosition().y + enemies[i].getSpeed() * sin(enemies[i].getAngle()));
			} else {
					
				difX = (posX - enemies[i].getPosition().x);
				difY = (posY - enemies[i].getPosition().y);

				nextX = (1 / sqrt(difX * difX + difY * difY)) * difX;
				nextY = (1 / sqrt(difX * difX + difY * difY)) * difY;
				p = Point2D (enemies[i].getPosition().x + enemies[i].getSpeed() * nextX,
							enemies[i].getPosition().y + enemies[i].getSpeed() * nextY);
			}

			if (collision.isInWindow(p.x + collision.sign(p.x) * 30, p.y + collision.sign(p.y) * 30)) {
				
				if (enemies[i].getType() == 3) {
					Transform2D::loadIdentityMatrix();
					Transform2D::translateMatrix(-enemies[i].getCenter().x, -enemies[i].getCenter().y);
					Transform2D::rotateMatrix(rotAngle);
					rotAngle += 0.08;
						
					Transform2D::translateMatrix(enemies[i].getPosition().x, enemies[i].getPosition().y);
					Transform2D::translateMatrix(enemies[i].getSpeed() * nextX, 
													enemies[i].getSpeed() * nextY);
					enemies[i].setNewPosition(p);
	
					for (int j = 0; j < enemies[i].getSize(); j++) {
						Transform2D::applyTransform(enemies[i].getElement(j));
					}
						
				} else {
					Transform2D::loadIdentityMatrix();
					Transform2D::translateMatrix(-enemies[i].getCenter().x, -enemies[i].getCenter().y);
					Transform2D::translateMatrix(enemies[i].getPosition().x, enemies[i].getPosition().y);
					Transform2D::translateMatrix(enemies[i].getSpeed() * cos(enemies[i].getAngle()), 
													enemies[i].getSpeed() * sin(enemies[i].getAngle()));
	
					enemies[i].setNewPosition(p);
	
					for (int j = 0; j < enemies[i].getSize(); j++) {
						Transform2D::applyTransform(enemies[i].getElement(j));
					}
				}
			} else {
				enemies[i].setAngle ((float)rand() / 500);
			}
		}
	}


	// animatie gloante (daca exista vreun glont)
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isAlive()) {
			float xPos, yPos;
			xPos = bullets[i].getPosition().x + bullets[i].getSpeed() * cos(bullets[i].getAngle());
			yPos = bullets[i].getPosition().y + bullets[i].getSpeed() * sin(bullets[i].getAngle());

			if(collision.isInWindowOrOnBorder(xPos + bullets[i].getRadius() * cos(bullets[i].getAngle()),
											  yPos + bullets[i].getRadius() * sin(bullets[i].getAngle()))) {

				bullets[i].setNewPosition(Point2D(xPos, yPos));
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(xPos, yPos);
				Transform2D::applyTransform(bullets[i].getElement(0));

			} else {
				// daca glontul a iesit din teren, il sterg din vector ca sa nu-l mai animez degeaba
				removeObject2D_from_Visual2D(bullets[i].getElement(0), v2d1);
				bullets[i].takeLife();
			
			}
		}
	}

	// trec la level-ul urmator daca am distrus toti inamicii
	bool allEnemiesAreDead = true;
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].isAlive()) {
			allEnemiesAreDead = false;
			break;
		}
	}
	if (allEnemiesAreDead && !gameEnded) {
		level ++;
		stringLevel = "Level:  ";
		stringLevel.append(to_string(level+1));
		textCrtLevel->setText(stringLevel);
		goToNextLevel (level);
	}

}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	v2d1->poarta(0,height/8,width,height);
	v2dScore->poarta(0,0,width,height/8);

}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	
	keyStates[key] = true;

	// pe tasta space se activeaza arma burghiu
	if (key == KEY_SPACE && !gameEnded) {
		if (weapon_on == false) {
			// verific mai intai daca arma player-ului iese din teren:
			bool wIsInWindow = true;
			for (int i = 0; i < 2; i++)  {
				if (!collision.isInWindow(player.getWeaponSegment(i)->getP1()->x,
											player.getWeaponSegment(i)->getP1()->y)) {
					wIsInWindow = false;
				}
				if (!collision.isInWindow(player.getWeaponSegment(i)->getP2()->x,
											player.getWeaponSegment(i)->getP2()->y)) {
					wIsInWindow = false;
				}
			}
			// daca arma nu iese din teren, atunci pot sa o activez
			if (wIsInWindow) {
				addObject2D_to_Visual2D(player.getWeapon(), v2d1);
				weapon_on = true;
				speed_inc = speed_inc / 2;
			}
		} else {
			removeObject2D_from_Visual2D(player.getWeapon(), v2d1);
			weapon_on = false;
			speed_inc = 2 * speed_inc;
		}
	}

	switch(key)
	{
		case 27 : {
			exit(0);
			break;
		}
	}
}

void DrawingWindow::onKeyUp(unsigned char key) {
	keyStates[key] = false;
}

void DrawingWindow::onSpecialKeyUp(int key) {
	keyStates[key] = false;
}

void DrawingWindow::onSpecialKey(int key) {
	keyStates[key] = true;
}

void DrawingWindow::makeEnemies (int *number) {

	// create more enemies
	for (int k = 0; k < number[0]; k++) {
		enemies.push_back(Enemy1());
	}
	for (int k = 0; k < number[1]; k++) {
		enemies.push_back(Enemy2());
	}
	for (int k = 0; k < number[2]; k++) {
		enemies.push_back(Enemy3());
	}

	// Spawn Enemies
	for (unsigned int j = 0; j < enemies.size(); j++) {
		int rnd = rand() % 4;

		// verific daca pot sa spwn-ez in aceasta pozitie inamicii (sa nu se intersecteze cu player-ul)
		bool collisionWithPlayer = true;
		while (collisionWithPlayer) {
			Point2D *areaMin, *areaMax;
			int space = 80;
			areaMin = new Point2D(posX - space, posY - space);
			areaMax = new Point2D(posX + space, posY + space);
			if (!collision.isInBorder(areaMin, areaMax, spawnPosition[rnd])) {
				collisionWithPlayer = false;
			} else {
				rnd = (rnd + 1) % 4;
			}
		}


		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(-enemies[j].getCenter().x, -enemies[j].getCenter().y); 
		Transform2D::translateMatrix(spawnPosition[rnd].x, spawnPosition[rnd].y);
		Point2D p(spawnPosition[rnd].x, spawnPosition[rnd].y);
		enemies[j].setNewPosition(p);
		for (int i = 0; i < enemies[j].getSize(); i++) {
			Transform2D::applyTransform(enemies[j].getElement(i));
			addObject2D_to_Visual2D(enemies[j].getElement(i), v2d1);
		}
		enemies[j].giveLife();
	}
}

void DrawingWindow::goToNextLevel (int level) {
	cout << "Go to level: " << level << endl;
	static int  number[3];
	if (level == 0) {
		number[0] = 1;
		number[1] = 0;
		number[1] = 0;
	} else {
		for (int i = 0; i < 3; i++) {
			if (i == 2 && level > 4) {
				number[i] = numberOfEnemies[i] * 4;
			} else {
				number[i] = numberOfEnemies[i] * level;
			}
		}
	}
	// raman la level-ul 10 altfel se creeaza prea multi inamici
	if (level == 11) {
		level = 10;
	}
	makeEnemies(number);
}



//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1366, 768, 200, 50, "Laborator EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}