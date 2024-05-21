#include "BasicShapes.h"
#include "gameConfig.h"
#include "game.h"

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////

Rect::Rect(game* r_pGame, point ref, int r_hght, int r_wdth) :shape(r_pGame, ref)
{
	hght = r_hght;
	wdth = r_wdth;
}

void Rect::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(config.penColor, config.penWidth);
	pW->SetBrush(config.fillColor);
	point upperLeft, lowerBottom;
	upperLeft.x = RefPoint.x - wdth / 2;
	upperLeft.y = RefPoint.y - hght / 2;
	lowerBottom.x = RefPoint.x + wdth / 2;
	lowerBottom.y = RefPoint.y + hght / 2;

	pW->DrawRectangle(upperLeft.x, upperLeft.y, lowerBottom.x, lowerBottom.y, FILLED);
}

void Rect::rotate()
{
	int tmp = wdth;
	wdth = hght;
	hght = tmp;
	orientation += 1;
}

void Rect::resizeUp()
{
	hght *= 2;
	wdth *= 2;
}

void Rect::resizeDown()
{
	hght /= 2;
	wdth /= 2;
}

// Rectangle symmetric, no need to flip
void Rect::flip() {}

void Rect::save(libxl::Sheet* sheet, int row) 
{
	sheet->writeStr(row, 0, "Rectangle");
	sheet->writeNum(row, 1, RefPoint.x); // Save x-coordinate to column 1
	sheet->writeNum(row, 2, RefPoint.y); // Save y-coordinate to column 2
	sheet->writeNum(row, 3, wdth);       // Save width to column 3
	sheet->writeNum(row, 4, hght);
	sheet->writeNum(row, 5, orientation);
}

void Rect::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	wdth = sheet->readNum(row, 3);
	hght = sheet->readNum(row, 4);
	orientation = sheet->readNum(row, 5);
}

////////////////////////////////////////////////////  class circle  ///////////////////////////////////////

Circle::Circle(game* r_pGame, point ref, int r) :shape(r_pGame, ref)
{
	rad = r;
}

void Circle::draw() const
{
	window* pW = pGame->getWind();
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawCircle(RefPoint.x, RefPoint.y, rad, FILLED);
}

// Circles are perfectly symetric, they don't rotate around their center.
void Circle::rotate() {}

void Circle::resizeUp()
{
	rad *= 2;
}

void Circle::resizeDown()
{
	rad /= 2;
}

// Circle symmetric, no need to flip
void Circle::flip() {}

void Circle::save(libxl::Sheet* sheet, int row) 
{
	sheet->writeStr(row, 0, "Circle");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, rad);
}

void Circle::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	rad = sheet->readNum(row, 3);
}


////////////////////////////////////////////////////  class isoceles triangle  ///////////////////////////////////////
////////////////////////////////////////////////////  abstract class triangle  ///////////////////////////////////////

Triangle::Triangle(game* r_pGame, point ref) : shape(r_pGame, ref) {}

void Triangle::draw() const
{
	window* pW = pGame->getWind();
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, FILLED);
}

void Triangle::rotate()
{
	rotateAroundPoint(p1, RefPoint);
	rotateAroundPoint(p2, RefPoint);
	rotateAroundPoint(p3, RefPoint);
}

void Triangle::flip() {}

void Triangle::move(Direction direction) {
	movePoint(direction, RefPoint);
	movePoint(direction, p1);
	movePoint(direction, p2);
	movePoint(direction, p3);
}

////////////////////////////////////////////////////  class isoceles triangle  ///////////////////////////////////////

IsoscelesTriangle::IsoscelesTriangle(game* r_pGame, point ref, int r_hght, int r_wdth) : Triangle(r_pGame, ref), height(r_hght), width(r_wdth)
{
	p1.x = RefPoint.x;
	p1.y = RefPoint.y - height / 2;
	p2.x = RefPoint.x - width / 2;
	p2.y = RefPoint.y + height / 2;
	p3.x = RefPoint.x + width / 2;
	p3.y = RefPoint.y + height / 2;
}

void IsoscelesTriangle::resizeUp()
{
	height *= 2;
	width *= 2;
}

void IsoscelesTriangle::resizeDown()
{
	height /= 2;
	width /= 2;
}

void IsoscelesTriangle::save(libxl::Sheet* sheet, int row)
{
	sheet->writeStr(row, 0, "EquilateralTriangle");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, height);
	sheet->writeNum(row, 4, width);
	sheet->writeNum(row, 5, orientation);
}

void IsoscelesTriangle::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	height = sheet->readNum(row, 3);
	width = sheet->readNum(row, 4);
	orientation = sheet->readNum(row, 5);
}


////////////////////////////////////////////////////  class equilateral triangle  ///////////////////////////////////////

EquilateralTriangle::EquilateralTriangle(game* r_pGame, point ref, int r_side) :Triangle(r_pGame, ref)
{
	pGame = r_pGame;
	side = r_side;
	p1.x = RefPoint.x;
	p1.y = RefPoint.y - side / 2;
	p2.x = RefPoint.x - side / 2;
	p2.y = RefPoint.y + side / 2;
	p3.x = RefPoint.x + side / 2;
	p3.y = RefPoint.y + side / 2;
}

void EquilateralTriangle::resizeUp()
{
	side *= 2;
}

void EquilateralTriangle::resizeDown()
{
	side /= 2;
}

void EquilateralTriangle::save(libxl::Sheet* sheet, int row)
{
	sheet->writeStr(row, 0, "EquilateralTriangle");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, side);
	sheet->writeNum(row, 5, orientation);
}

void EquilateralTriangle::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	side = sheet->readNum(row, 3);
	orientation = sheet->readNum(row, 5);
}

////////////////////////////////////////////////////  class right angled triangle  ///////////////////////////////////////

RightTriangle::RightTriangle(game* r_pGame, point ref, int r_height, int r_base) : Triangle(r_pGame, ref)
{
	height = r_height;
	base = r_base;
	p1.x = RefPoint.x - base / 2;
	p1.y = RefPoint.y - height / 2;
	p2.x = RefPoint.x + base / 2;
	p2.y = RefPoint.y + height / 2;
	p3.x = RefPoint.x - base / 2;
	p3.y = RefPoint.y + height / 2;
}

void RightTriangle::resizeUp()
{
	height *= 2;
	base *= 2;
}

void RightTriangle::resizeDown()
{
	height /= 2;
	base /= 2;
}

void RightTriangle::flip()
{
	base *= -1;
}

void RightTriangle::save(libxl::Sheet* sheet, int row)
{
	sheet->writeStr(row, 0, "RightTriangle");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, height);
	sheet->writeNum(row, 4, base);
	sheet->writeNum(row, 5, orientation);
}

void RightTriangle::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	height = sheet->readNum(row, 3);
	base = sheet->readNum(row, 4);
	orientation = sheet->readNum(row, 5);
}
