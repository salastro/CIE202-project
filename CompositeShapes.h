#pragma once
#include "Basicshapes.h"


////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
//This class reprsents the composite shape "sign"
//The sign is composed of 2 Recatngles
/*

					 ------------------
					|				   |
					|		 x		   |     x is the reference point of the Sign shape
					|			       |
					 ------------------
						   |   |
						   |   |
						   | . |
						   |   |
						   |   |
							---
*/

//Note: sign reference point is the center point of the top rectangle
class Sign :public shape
{
	Rect* base;
	Rect* top;
public:
	Sign(game* r_pGame, point ref);
	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};


////////////////////////////////////////////////////  class Cloud  ///////////////////////////////////////
class Cloud : public shape
{
private:

	// Objects
	Circle* top;
	Circle* center;
	Circle* bottomLeft;
	Circle* bottomRight;

	// Points
	point topRef;
	point centerRef;
	point bottomLeftRef;
	point bottomRightRef;

	// Variables
	int rad;

public:
	Cloud(game* r_pGame, point ref);

	void updateCircles();
	void updateCirclesRef();

	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};


////////////////////////////////////////////////////  class House  ///////////////////////////////////////	
class House : public shape
{
private:
	// Objects
	Rect* base;
	IsoscelesTriangle* roof;

	// Points
	point baseRef;
	point roofRef;

	// Variables
	int baseWidth;
	int baseHeight;
	int roofWidth;
	int roofHeight;


public:
	House(game* r_pGame, point ref);

	void updateHouse();

	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};

////////////////////////////////////////////////////  class Tree  ///////////////////////////////////////

class Tree : public shape
{
private:
	// Objects
	Rect* trunk;
	Cloud* crown;
	// Reference points
	point trunkRef;
	point crownRef;
	// Variables
	int trunkHeight;
	int crownRad;

public:
	Tree(game* r_pGame, point ref);
	void draw() const override;
	void updateTree();
	void rotate() override;
	void updateTreeRefRotate();
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};
