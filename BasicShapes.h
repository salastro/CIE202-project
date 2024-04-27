//Header file for Basic shapes in the game
#pragma once
#include "shape.h"


// Rectangle
/*			wdth
	+-------------------+
	|					|
hght|		 x			|
	|					|
	+-------------------+
*/
class Rect :public shape
{
	int hght, wdth;
public:
	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);
	virtual void draw() const;
	virtual void rotate();
	virtual void resizeUp();
	virtual void resizeDown();
	virtual void flip();
};


// Circle
// Reference point of the circle is its center
class Circle :public shape
{
	int rad;
public:
	Circle(game* r_pGame, point ref, int r);
	virtual void draw() const;
	virtual void rotate();
	virtual void resizeUp();
	virtual void resizeDown();
	virtual void flip();
};

// Equilateral Triangle
/*
		 p1
		 ^
		/ \
	   /   \
	s /  x  \ s
	 /       \
	/_________\
	p2	 s	  p3
*/
class EquilateralTriangle :public shape
{
	int side;
	point p1, p2, p3;
public:
	EquilateralTriangle(game* r_pGame, point ref, int s);
	virtual void draw() const;
	virtual void rotate();
	virtual void resizeUp();
	virtual void resizeDown();
	virtual void flip();
};

// Right Triangle
/*
		 p1
		 ^
		/|
	   / |
	x /  | h
	 /   |
	/____|
	p2 b p3
*/
class RightTriangle :public shape
{
	int height, base;
	point p1, p2, p3;
public:
	RightTriangle(game* r_pGame, point ref, int h, int b);
	virtual void draw() const;
	virtual void rotate();
	virtual void resizeUp();
	virtual void resizeDown();
	virtual void flip();
};
