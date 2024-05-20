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
