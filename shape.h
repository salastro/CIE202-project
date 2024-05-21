#pragma once
#include <string>
using namespace std;
#include "libxl/include_cpp/libxl.h"
#include "CMUgraphicsLib\CMUgraphics.h"


class game;     //forward declaration

struct point
{
	int x, y;
};

enum ShapeType
{
	//Basic shapes
	RCT, //rectangle
	CRC, //circle
	EQTRI, //equilateral triangle
	RITRI, //right angle triangle
	ISTRI, //isoceles triangle

	//Composite shapes
	CAR,
	CLOUD,
	HOUSE,
	ICECREAM,
	PLANE,
	TREE,
};

enum Direction {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
};

//Base class for all shapes including Basic shapes, Composite shapes
class shape
{
protected:
	point RefPoint; //Each shape must have a reference point
	game* pGame;        //pointer to game object
	color fillColor; //shape fill color
	color borderColor; //shape border color
	int orientation = 0;
	int size = 0;
	ShapeType type;
public:
	shape(game* r_pGame, point ref);
	virtual void draw() const = 0;//for a shape to draw itself on the screen
	void setRefPoint(point p);
	point getRefPoint() const;
	int getOrientation() const;
	ShapeType getType() const;
	int getSize() const;

	color getColor() const;
	void setColor(color col); 

	//-- The following functions should be supported by the shape class
	//-- It should be overridden by each inherited shape
	//-- Decide the parameters that you should pass to each function

	virtual void rotate() = 0; //Rotate the shape
	virtual void resizeUp() = 0; //Resize the shape
	virtual void resizeDown() = 0; //Resize the shape
	virtual void flip() = 0; //Flip the shape
	virtual void move(Direction direction); //Move the shape
	virtual void save(libxl::Sheet* sheet, int row) = 0; //Save the shape
	virtual void load(libxl::Sheet* sheet, int row) = 0; //Load the shape


	//virtual void save(ofstream &OutFile) = 0; //Save the shape parameters to the file
	//virtual void load(ifstream &Infile) = 0; //Load the shape parameters to the file

};

// Rotate by 90 degree
void rotateAroundPoint(point& p, const point& pivot);

// Move point in a direction
void movePoint(Direction direction, point& RefPoint);