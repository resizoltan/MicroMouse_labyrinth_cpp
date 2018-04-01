#pragma once


class position {
private:
	int x;
	int y;
public:
	position();
	position(int x, int y);
	~position();
	int Getx();
	int Gety();
	void Setx(int);
	void Sety(int);
	void Incx(int);
	void Incy(int);

	bool operator==(position &pos);
	bool operator!=(position &pos);
};
