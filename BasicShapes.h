//Header file for Basic shapes in the game
#pragma once
#include "shape.h"

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////
//Rectanle class
/*							wdth
					---------------------
					|					|
			hght    |		 x			|     x is the reference point of the rectangle
					|					|
					--------------------
*/


class Rect :public shape
{
	int hght, wdth;	//height and width of the recangle
public:
	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);
	virtual void draw() const;
	virtual void rotate();

};


////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//Reference point of the circle is its center
class Circle :public shape
{
	//Add data memebrs for class circle
	int rad;
public:
	Circle(game* r_pGame, point ref, int r);
	virtual void draw() const;
	virtual void rotate();
};


////////////////////////////////////////////////////  class equilateral triangle  ///////////////////////////////////////
// Reference point of the triangle is its top point
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
	//Add data memebrs for class triangle
	int side;
public:
	EquilateralTriangle(game* r_pGame, point ref, int s);
	virtual void draw() const;
	virtual void rotate();
};

////////////////////////////////////////////////////  class right angled triangle  ///////////////////////////////////////
/*
Right angled triangle
		x is the reference point of the triangle
		/|
	   / |
	s /  | h
	 /   |
	/____|
		s
*/
class RightTriangle :public shape
{
	//Add data memebrs for class triangle
	int height, base;
public:
	RightTriangle(game* r_pGame, point ref, int h, int b);
	virtual void draw() const;
	virtual void rotate();
};
