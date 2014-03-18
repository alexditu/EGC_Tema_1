EGC - Tema 1
	Geometry Wars
	Ditu Alexandru 333 CA
	
1. Cerinta
	Utilizand framework-ul de la laborator trebuie sa implementam un joc de tip
	Geometry Wars.
	
2. Utilizare
	Tastele folosite pentru joc sunt:
		- Sagetile (UP, DOWN, LEFT, RIGHT)
		- Tasta SPACE (activeaza/dezactiveaza arma)
		- Tasta 'w' face player-ul sa traga cu gloante in cazul in care arma burghiu
		  este activata; se trag maxim 5 gloante (dupa ce ies din teren, mai pot fi
		  trase altele etc.)
		- Tasta ESCAPE pentru a iesi din joc (dupa ce se termina jocul trebuie apasat
		  Escape)
		  
3. Implementare
	
	IDE:	Visual Studio 2012
	SO:		Windows 7 Professional, 64bit
	Framework-ul folosit este cel din lab3.
	
	Clase folosite:
		Am adaugat mai multe clase noi:
		- Player.h/Player.cpp
			- e o clasa folosita pentru a desena/anima/interactiona cu player-ul
			- detine toate informatiile necesare pentru utilizarea player-ului
			  (obiectele de tipul Object2D din care este alcatuit, arma burghiu,
			  vietile ramase, scorul, pozitia etc)
		- GenericEnemy.h/GenericEnemy.cpp
			- descrie inamicii in  general (contine informatiile comune despre
			  fiecare inamic
			- este clasa parinte pentru fiecare inamic in parte
		- Enemy1.h/Enemy1.cpp si Enemy2.h/Enemy2.cpp si Enemy3.h/Enemy3.cpp
			- descriu cele 3 tipuri de inamici in parte
			- diferentele intre ele este modul in care sunt desenati inamicii
			  (adica obiectele de tipul Object2D din care sunt facuti).
		- Bullet.h/Bullet.cpp
			- folosita pentru crearea si animatia gloantelor
		- Collision.h/Collision.cpp
			- clasa in care am implementat coliziunile
			- am folosit 2 tipuri de coliziuni: segment-segment si segment-cerc
			- segment-segment:
				- folosit intre inamci si arma player-ului
				- incadrez fiecare inamic intr-un chenar/dreptunghi (acesta nu
				  se vede pe ecran, insa sufera aceleasi transformari cu inamicul
				  pentru a avea mereu actualizata pozitia sa; in plus am adaugat
				  o noua functie in Line2D si anume getLine() care imi intoarce
				  linia formata din transf_points, pentru a avea pozitia curenta 
				  a fiecarei linii ce formeaza chenarul)
				- testez pentru fiecare inamic, pentru fiecare linie a chenarului,
				  daca se intersecteaza cu 2 segmente ale burghiului (am folosit doar
				  2 deoarece nu mai era necesar sa testez si cu baza burghiului)
			- segment-cerc:
				- folosit intre inamici si player
				- verific pentru fiecare inamic, pentru fiecare segement al
				  chenrului, daca se intersecteaza cu cercul player-ului.
			- de asemenea aceasta clasa mai are niste functii de testare
			  daca un obiect este in terenul de joc (isInBorder(...)) sau daca
			  un punct este in terenul de joc (isInWindow(..));
			  
		- Mentionez ca am modificat putin Line2D.h, am adaugat niste functii noi necesare
		  pentru coliziuni:
			- Point2D* getP1() / Point2D* getP2() -> intorc capetele segmentului dar din 
			  transf_points, deci pozitia curenta a capetelor unui segemnt
			- Point2D* getPoint1() / Point2D* getPoint2() -> intorc capetele segmentului
			  din points (deci nemodificate de Transform2D)
			- Line2D* getLine() -> intoarce o linie noua, alcatuita din transf_points, deci
			  linia in pozitia curenta (dupa modificarile din Transform2D)
		
		- Mentionez ca am modificat si DrawingWindow() (am adaugat urmatoarele functii):
			glutKeyboardFunc(keyboardFunction); //functia apelata la apasarea unei taste
			glutKeyboardUpFunc(keyboardUpFunction); // functie apelata la eliberarea unei taste
			glutSpecialFunc(specialFunction); //functia apelata la apasarea unei taste speciale
			glutSpecialUpFunc(specialKeyUp); //functie apelata la eliberarea unei taste speciale
			(stiu ca unele erau deja)
			
	- Toata "actiunea" se petrece in main() (sunt destul de multe comentarii in cod);
	  in linii mari:
	  - am folosit mai multe variabile globale pentru a descrie jocul in general
	  - in init() fac toate intializarile necesare iar in onIdle() toata animatia
	    (atat a player-ului cat si a inamicilor si a gloantelor), testez coliziunile,
		trec la level-ul urmator etc.
			
4. Testare
	...

5. Probleme aparute
	Desi am crezut ca sunt putine operatii de comparatie, am observat ca de la
	un numar putin mai mare de inamici (sa zicem vreo 30~40) incepe sa se miste
	mai greu (din cauza testelor de coliziune); in plus daca mai si trag cu arma
	(arma trage cu niste cercuri mici, iar pentru acestea verific daca sunt in
	interiorul fieacarui inamic - neglijez raza cercului, verific doar pentru
	centrul cercului-) se misca mult mai greu. Asa ca am limitat arma: poate trage
	cu maxim 5 gloante. Probabil nici nu este suficient de optimizat (poate pot limita
	numarul de for-uri).
	
6. Continutul Arhivei
	- tot framework-ul de la laboratorul 3
	- Bullet.h/.cpp
	- Collision.h/.cpp
	- Enemy1.h/.cpp
	- Enemy2.h/.cpp
	- Enemy3.h/.cpp
	- GenericEnemy.h/.cpp
	- Player.h/.cpp
	
7. Functionalitati
	- Player-ul se misca pe sageti, arma se activeaza cu space si eventual poate
	  trage cu gloante pe tasta 'w' (am ales w deoarece mereu cand ma joc tin
	  mana stanga pe wasd :) )
	- exista 3 tipuri de inamici: 2 dintre ei se misca random (sunt initializati
	  cu un unghi random si urmaresc acea traiectorie pana cand se izbesc de
	  marginea terenului de joc, dupa care aces unghi iar este initializat random
	  - nu am facut refractie, ceea ce putin mai "tricky" pentru player deoarece
	  nu poate anticipa unde va fi inamicul dupa ce se izbeste de perete-)
	- inamicul de tipul 3 urmareste player-ul (iar ca animatie se si invarte in
	  jurul centrului sau)
	- player-ul/inamicii nu au voie sa iasa din teren; nici player-ul nu are voie
	  sa isi activeze arma daca aceasta iese din teren
	- Fiecare inamic are asociata o anumita valoare, daca este distrus de catre
	  player atunci scorul jucatorului creste cu acea valoare (valorile fiecarui
	  inamic depind de nivelul de dificultate):
		- inamic1.val = 10 (e cel mai slab)
		- inamic2.val = 20 (e putin mai rapid)
		- inamic3.val = 30 (vine spre jucator)
	- Player-ul are initial scorul 0 si incepe de la level 1
	- Dupa ce omoara toti inamcii se trece la nivelul urmator
	- Daca un inamic este atins de arma player-ului moare
	- Daca un inamic se atinge de player, acesta moare si ii scade o viata (din cele
	  5 cate sunt initial)
	- Mentionez ca jocul este rulat in FullScreen (eu l-am folosit numai la
	  1366 x 768) si nu l-am rulat niciodata pe alt pc (nu stiu cum se comporta)

	Bonus:
		- exista inamici inteligenti (cei de tipul 3 vin spre player)
		- player-ul poate sa traga cu gloante
		- exista mai multe nivele de dificultate (se incepe de la level 1, in care
		  este un singru inamic, iar apoi apar din ce in ce mai multi in diferite
		  proportii)
		- inamcii au 4 locuri in care pot sa apara (se alege random in care din
		  cele 4 sa fie desenati si se verifica sa nu fie prea aproape de player)
		  
8. Altceva
	- in rezolvarea temei am citit si folosit informatii in urmatoarele site-uri
		[1] https://sites.google.com/site/t3hprogrammer/research/line-circle-collision/tutorial#TOC-The-Closest-Point-on-a-Line-to-a-Point-Algorithm
		[2] http://www.ahristov.com/tutorial/geometry-games/intersection-segments.html
		[3] http://www.swiftless.com/tutorials/opengl/keyboard.html
	
		[1] - despre intersectiile intre cerc si segment
		[2] - despre intersectii de segmente
		[3] - despre apasarea tastelor (in special sa pot inainta cu player-ul in timp ce ma rotesc)
			
			