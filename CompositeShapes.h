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
	void rotate() override = 0;
	void resizeUp() override = 0;
	void resizeDown() override = 0;
	void flip() override = 0;
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

	void initializeCircles(point ref);
	void updateCircles();

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
	Rect* base;
	EquilateralTriangle* roof;

public:
	House(game* r_pGame, point ref, int baseWidth, int baseHeight, int roofSide);

	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override = 0;
};

////////////////////////////////////////////////////  class Tree  ///////////////////////////////////////

class Tree : public shape
{
private:
	Rect* trunk;
	Circle* crown;

public:
	Tree(game* r_pGame, point trunkRef, int trunkWidth, int trunkHeight, point crownRef, int crownRadius);

	void draw() const override;
	void rotate() override;
	void resizeUp() override;
	void resizeDown() override;
	void flip() override = 0;
};
