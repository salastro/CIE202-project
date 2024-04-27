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
	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};


// Circle
// Reference point of the circle is its center
class Circle :public shape
{
	int rad;
public:
	Circle(game* r_pGame, point ref, int r);
	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};

// Isosceles Triangle
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
class IsoscelesTriangle :public shape
{
	int width;
	int height;
	point p1, p2, p3;
public:
	IsoscelesTriangle(game* r_pGame, point ref, int r_hght, int r_wdth);
	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
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
	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
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
	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};
