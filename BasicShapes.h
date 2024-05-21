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
	void save(libxl::Sheet* sheet, int row) override;
	void load(libxl::Sheet* sheet, int row) override;
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
	void save(libxl::Sheet* sheet, int row) override;
	void load(libxl::Sheet* sheet, int row) override;
};

class Triangle :public shape
{
protected:
	point p1, p2, p3;
public:
	Triangle(game* r_pGame, point ref);
	void draw() const override;
	void rotate() override;
	virtual void flip() override;
	void move(Direction direction) override;
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
class IsoscelesTriangle :public Triangle
{
	int width;
	int height;
public:
	IsoscelesTriangle(game* r_pGame, point ref, int r_hght, int r_wdth);
	void resizeUp() override;
	void resizeDown() override;
	void save(libxl::Sheet* sheet, int row) override;
	void load(libxl::Sheet* sheet, int row) override;
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
class EquilateralTriangle :public Triangle
{
	int side;
public:
	EquilateralTriangle(game* r_pGame, point ref, int s);
	void resizeUp() override;
	void resizeDown() override;
	void save(libxl::Sheet* sheet, int row) override;
	void load(libxl::Sheet* sheet, int row) override;
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
class RightTriangle :public Triangle
{
	int height, base;
public:
	RightTriangle(game* r_pGame, point ref, int h, int b);
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
	void save(libxl::Sheet* sheet, int row) override;
	void load(libxl::Sheet* sheet, int row) override;
};
