#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

void gotoxy(int x, int y) { //gotoxy function
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class CPesawat {
protected:
	double _x, _y, _dx, _dy;
public:
	CPesawat(double x = 1, double y = 1, double dx = 1, double dy = 1) {
		_x = x; _y = y; _dx = dx; _dy = dy;
	}
	void set(double x, double y, double dx, double dy) {
		_x = x; _y = y; _dx = dx; _dy = dy;
	}
	double getX() { return _x; }
	double getY() { return _y; }
	double getDX() { return _dx; }
	double getDY() { return _dy; }
	void update() {
		_x += _dx;
		_y += _dy;
		if (_x <= 1) { _dx *= -1; }
		if (_x >= 168) { _dx *= -1; }
		if (_y <= 1) { _dy *= -1; }
		if (_y >= 35) { _dy *= -1; }
	}
};

class CPlayer :public CPesawat {

public:
	CPlayer(double x = 1, double y = 1, double dx = 0, double dy = 0) :
		CPesawat(x, y, dx, dy)
	{}
	void draw() {
		double x = _x, y = _y;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				gotoxy(_x, _y);
				if (i >= 1 && i <= 3)
					if (j == 0)
						cout << "-";
				if (j == 1)
					cout << "|";
				if (j == 2 && i == 0 || j == 3 && i == 1)
					cout << "\\";
				if (j == 2 && i == 4 || j == 3 && i == 3)
					cout << "/";
				if (j >= 3 && i == 0 || j >= 3 && i == 4)
					cout << "=";
				if (j == 4 && i == 2)
					cout << ")";
				_x++;
			}
			_x = x;
			_y++;
		}
		_y = y;
		_x = x;
	}
	void update() {
		CPesawat::update();
		_dx = 0;
		_dy = 0;
	}
	void Move(char direction) {
		if (direction == 'a' && _x >= 2) {//kiri
			_dx = -1.5;
			_dy = 0;
		}
		if (direction == 'w' && _y >= 2) {//atas
			_dx = 0;
			_dy = -1.5;
		}
		if (direction == 'd' && _x <= 165) {//kanan
			_dx = 1.5;
			_dy = 0;
		}
		if (direction == 's' && _y <= 35) {//bawah
			_dx = 0;
			_dy = 1.5;
		}
	}
	void ProcessInput() {
		if (_kbhit()) {
			char dir = _getch();
			Move(dir); //gerak
		}
	}
};

class CPeluru : public CPesawat {
	char _chr;
public:
	CPeluru(double x = 1, double y = 1, double dx = 0, double dy = 1, char chr = '-') :
		CPesawat(x, y, dx, dy)
	{
		_chr = chr;
	}
	void set(double x, double y, double dx, double dy, char chr) {
		_x = x; _y = y; _dx = dx; _dy = dy; _chr = chr;
	}
	void setChar(char chr = '-') { _chr = chr; }
	char getChar() { return _chr; }
	void draw() {
		gotoxy(_x, _y);
		cout << _chr;
	}
};

class CBiasa : public CPesawat {
protected:
	int _health;
public:
	CBiasa(double x = 10, double y = 10, double dx = -1, double dy = 0, int health = 1) : CPesawat(x, y, dx, dy) {
		_health = health;
	}
	void setHealth(int health) { _health = health; }
	int getHealth() { return _health; }
	virtual void healthMinus(int y) { _health--; }
	virtual void draw() {
		double x = _x, y = _y;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				gotoxy(_x, _y);
				if (i == 0 && j != 0 || j == 4 || i == 4 && j != 0 || j == 0 && i >= 1 && i <= 3)
					cout << "o";
				if (j == 0 && i == 0 || j == 0 && i == 4)
					cout << "-";
				if (j == 2 && i == 2)
					cout << _health;
				_x++;
			}
			_x = x;
			_y++;
		}
		_y = y;
		_x = x;
	}
	virtual void setY(double Y) {}
	virtual void shield() {}
	virtual void unshield(double dx, double dy) {}
};

class CZigZag : public CBiasa {
protected:

public:
	CZigZag(double x = 10, double y = 10, double dx = -1, double dy = 1, int health = 1) :
		CBiasa(x, y, dx, dy, health) {}
	void draw() {
		double x = _x, y = _y;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				gotoxy(_x, _y);
				if (i == 0 && j != 4 || i == 4 && j != 4)
					cout << "=";
				if (i == 2 && j == 0 || i == 2 && j == 4 || i == 1 && j == 1 || i == 1 && j == 3 || i == 3 && j == 1 || i == 3 && j == 3)
					cout << "*";
				if (j == 2 && i == 2)
					cout << _health;
				_x++;
			}
			_x = x;
			_y++;
		}
		_y = y;
		_x = x;
	}
};

class CSeeker : public CBiasa {
protected:

public:
	CSeeker(double x = 10, double y = 10, double dx = -1, double dy = -1, int health = 1) :
		CBiasa(x, y, dx, dy, health) {}
	void draw() {
		double x = _x, y = _y;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				gotoxy(_x, _y);
				if (i == 0 || i == 4)
					cout << "-";
				if (j == 4 && i >= 1 && i <= 3)
					cout << "|";
				if (j == 1 && i == 1)
					cout << "/";
				if (j == 1 && i == 3)
					cout << "\\";
				if (j == 0 && i == 2)
					cout << "(";
				if (j == 2 && i == 2)
					cout << _health;
				_x++;
			}
			_x = x;
			_y++;
		}
		_y = y;
		_x = x;
	}
	void setY(double y) {
		if (_y == y) { _dy = 0; }
		else if (y > _y) { _dy = 0.5; }
		else if (y < _y) { _dy = -0.5; }
	}
};

class CShield : public CBiasa {
protected:

public:
	CShield(double x = 10, double y = 10, double dx = 1, double dy = 0, int health = 1) :
		CBiasa(x, y, dx, dy, health) {}
	void shield() {
		double x = _x, y = _y;
		_dx = 0, _dy = 0;
		_health = getHealth();
		draw();
		for (int i = 0; i < 5; i++) {
			gotoxy(_x - 1, _y);
			cout << "#";
			_y++;
		}
		_x = x; _y = y;
	}
	void unshield(double dx, double dy) {
		_dx = dx;
		_dy = dy;
	}
	void draw() {
		double x = _x, y = _y;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				gotoxy(_x, _y);
				if (i == 0 && j >= 1 && j <= 3 || i == 4 && j >= 1 && j <= 3)
					cout << "=";
				if (j == 0 && i >= 1 && i <= 3 || j == 4 && i >= 1 && i <= 3)
					cout << "|";
				if (i == 0 && j == 0 || i == 4 && j == 4)
					cout << "/";
				if (i == 0 && j == 4 || i == 4 && j == 0)
					cout << "\\";
				if (j == 2 && i == 2)
					cout << _health;
				_x++;
			}
			_x = x;
			_y++;
		}
		_y = y;
		_x = x;
	}
	void healthMinus(int y) {
		if (y == 1) { _health--; }
	}
};

class CPlay {
	double keluar = 1;
	CBiasa* biasa[100];
	CPlayer p;
	CPeluru* peluru;
	bool games = true;
	int pel = 0, a = 0, gtc, timer = 0, banyak, s = 20, y = 1, kalah = 0;
public:
	void Initialize() {
		gtc = GetTickCount() % 10000 / 1000 - 1; //ambil second pertama
		banyak = 80;
		for (int i = 0; i < banyak; ) {
			biasa[i] = new CBiasa(); biasa[i]->set(165, rand() % 34 + 1, -0.75, 0);
			i++;
			biasa[i] = new CZigZag(); biasa[i]->set(165, rand() % 34 + 1, -0.75, 0.5);
			i++;
			biasa[i] = new CSeeker(); biasa[i]->set(165, rand() % 34 + 1, -1, 0);
			i++;
			biasa[i] = new CShield(); biasa[i]->set(165, rand() % 34 + 1, -0.5, 0);
			i++;
		}
		for (int i = 0; i < banyak; i++) {
			biasa[i]->setHealth(rand() % 6 + 3);
		}
	}
	void Run() {
		while (games) {
			system("cls");
			Draw();
			ProcessInput();
			Sleep(100);
			Updates();
		}
	}
	void Draw() {
		p.draw();
		for (int i = 0; i < keluar; i++) {
			biasa[i]->draw();
		}
		for (int i = 0; i < pel; i++) {
			peluru[i].draw();
		}
		gotoxy(0, 0); //untuk cek
		cout << "Duration  : " << timer << "     " << " Rest Enemy   : " << banyak;
		cout << "      " << "Enemy Pass (MAX 5)   : " << kalah << "      " << "Loading Enemy : " << keluar << endl;
	}
	void Updates() {
		if (gtc != GetTickCount() % 10000 / 1000 - 1) {
			timer++;
		}
		gtc = GetTickCount() % 10000 / 1000 - 1;
		if (timer % 30 == 0 && timer != 0 && keluar <= banyak) { keluar += 0.5; }
		if (keluar >= banyak) { keluar = banyak; }
		if (keluar >= 10) { keluar = 10; }
		p.update();
		for (int i = 0; i < keluar; i++) {
			biasa[i]->update();
			biasa[i]->setY(p.getY());
			if (timer >= s && timer <= s + 10) {
				biasa[i]->shield();
				y = 0;
			}
			else if (timer >= s + 10) {
				s += 20;
				y = 1;
			}
			else {
				biasa[i]->unshield(-0.25, 0);
				y = 1;
			}
		}
		if (a != 0) {
			CPeluru* temp;
			temp = new CPeluru[pel];
			for (int i = 0; i < pel - 1; i++) {
				temp[i] = peluru[i];
			}
			temp[pel - 1].set(p.getX() + 4, p.getY() + 2, 2, 0, '-');
			delete[]peluru;
			peluru = new CPeluru[pel];
			peluru = temp;
			temp = NULL;
			a = 0;
		}
		for (int i = 0; i < pel; i++) {
			peluru[i].update();
		}
		for (int j = 0; j < keluar; j++) {
			for (int i = 0; i < pel; i++) {
				if (peluru[i].getX() >= biasa[j]->getX() && peluru[i].getX() <= biasa[j]->getX() + 6 && peluru[i].getY() >= biasa[j]->getY() && peluru[i].getY() <= biasa[j]->getY() + 5) {
					CPeluru* temp;
					temp = new CPeluru[pel - 1];
					for (int x = 0; x < i; x++) {
						temp[x] = peluru[x];
					}
					for (int x = i; x < pel - 1; x++) {
						temp[x] = peluru[x + 1];
					}
					delete[]peluru;
					pel = pel - 1;
					peluru = new CPeluru[pel];
					peluru = temp;
					temp = NULL;
					biasa[j]->healthMinus(y);
				}
				else if (peluru[i].getX() >= 165) {
					CPeluru* temp;
					temp = new CPeluru[pel - 1];
					for (int x = 0; x < i; x++) {
						temp[x] = peluru[x];
					}
					for (int x = i; x < pel - 1; x++) {
						temp[x] = peluru[x + 1];
					}
					delete[]peluru;
					pel = pel - 1;
					peluru = new CPeluru[pel];
					peluru = temp;
					temp = NULL;
				}
			}
			if (biasa[j]->getX() - 5 <= p.getX() && biasa[j]->getX() + 5 >= p.getX() && biasa[j]->getY() - 6 <= p.getY() && biasa[j]->getY() + 6 >= p.getY()) {
				system("CLS");
				cout << "-------------------------YOU LOSE!---------------------------";
				games = false;
			}
			if (biasa[j]->getX() <= 2) {
				kalah++;
			}
		}
		for (int i = 0; i < keluar; i++) {
			if (biasa[i]->getHealth() <= 0 || biasa[i]->getX() <= 2) {
				for (int j = i; j < banyak - 1; j++) {
					biasa[j] = biasa[j + 1];
				}
				banyak--;
			}
		}
		if (keluar <= 0) {
			system("CLS");
			cout << "-------------------------YOU WIN!---------------------------";
			games = false;
		}
		if (kalah >= 5) {
			system("CLS");
			cout << "-------------------------YOU LOSE!---------------------------";
			games = false;
		}
	}
	void ProcessInput() {
		if (_kbhit()) {
			char dir = _getch();
			if (dir == 27) { games = false; }
			else if (dir == ' ') { pel++; a++; }
			else { p.Move(dir); } //gerak
		}
	}
};

void main() {
	CPlay play;
	play.Initialize();
	play.Run();
}