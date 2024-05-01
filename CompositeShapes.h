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

	void update();
	void updateRef();

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

	void update();
	void updateRef();

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
	int trunkWidth;
	int crownRad;

public:
	Tree(game* r_pGame, point ref);
	void draw() const override;
	void update();
	void rotate() override;
	void updateRef();
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};

////////////////////////////////////////////////////  Class Icecream  ///////////////////////////////////////	
class Icecream : public shape
{
private:
	// Objects
	Circle* scoop;
	IsoscelesTriangle* cone;
	// Reference points
	point scoopRef;
	point coneRef;
	// Variables
	int scoopRad;
	int coneHeight;

public:
	Icecream(game* r_pGame, point ref);

	void update();

	void draw() const override;
	void rotate() override;
	void updateRef();
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};

////////////////////////////////////////////////////  Class Plane  ///////////////////////////////////////	
class Plane : public shape
{
private:
	// Objects
	Rect* body;
	EquilateralTriangle* head;
	RightTriangle* leftWing;
	RightTriangle* rightWing;
	RightTriangle* leftTail;
	RightTriangle* rightTail;
	// Reference points
	point bodyRef;
	point headRef;
	point leftWingRef;
	point rightWingRef;
	point leftTailRef;
	point rightTailRef;
	// Variables
	int bodyHeight, bodyWidth;
	int wingHeight, wingWidth;
	int tailHeight, tailWidth;

public:
	Plane(game* r_pGame, point ref);

	void update();
	void updateRef();

	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};

////////////////////////////////////////////////////  Class Car  ///////////////////////////////////////	
class Car : public shape
{
private:
	// Objects
	Rect* body;
	Rect* head;
	RightTriangle* topLeft;
	RightTriangle* topRight;
	Circle* leftWheel;
	Circle* rightWheel;
	// Reference points
	point bodyRef;
	point headRef;
	point topLeftRef;
	point topRightRef;
	point leftWheelRef;
	point rightWheelRef;
	// Variables
	int bodyHeight, bodyWidth;
	int headHeight, headWidth; // headWidth < bodyWidth
	int topWidth;
	int wheelRad;

public:
	Car(game* r_pGame, point ref);

	void update();
	void updateRef();

	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override;
};
