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
	this->draw();
}

void Rect::resizeUp()
{
	hght *= 2;
	wdth *= 2;
	this->draw();
}

void Rect::resizeDown()
{
	hght *= 2;
	wdth *= 2;
	this->draw();
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

void Circle::rotate()
{
	// Circles are perfectly symetric, they don't rotate around their center.
	this->draw();
}

void Circle::resizeUp()
{
	rad *= 2;
	this->draw();
}

void Circle::resizeDown()
{
	rad /= 2;
	this->draw();
}

////////////////////////////////////////////////////  class equilateral triangle  ///////////////////////////////////////

EquilateralTriangle::EquilateralTriangle(game* r_pGame, point ref, int r_side) :shape(r_pGame, ref)
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

void EquilateralTriangle::draw() const
{
	window* pW = pGame->getWind();
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, FILLED);
}

void EquilateralTriangle::rotate()
{
	window* pW = pGame->getWind();

	// Save old points for future calculation
	point p1tmp = p1, p2tmp = p2, p3tmp = p3;

	// Rotation around point formula
	// x' = -(y-ry)+rx
	// y' =  (x-rx)+ry
	p1.x = -(p1tmp.y - RefPoint.y) + RefPoint.x;
	p1.y = p1tmp.x - RefPoint.x + RefPoint.y;
	p2.x = -(p2tmp.y - RefPoint.y) + RefPoint.x;
	p2.y = p2tmp.x - RefPoint.x + RefPoint.y;
	p3.x = -(p3tmp.y - RefPoint.y) + RefPoint.x;
	p3.y = p3tmp.x - RefPoint.x + RefPoint.y;

	this->draw();
}

void EquilateralTriangle::resizeUp()
{
	side *= 2;
	this->draw();
}

void EquilateralTriangle::resizeDown()
{
	side /= 2;
	this->draw();
}

////////////////////////////////////////////////////  class right angled triangle  ///////////////////////////////////////

RightTriangle::RightTriangle(game* r_pGame, point ref, int r_height, int r_base) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	height = r_height;
	base = r_base;
	p1.x = RefPoint.x - base / 2;
	p1.y = RefPoint.x - height / 2;
	p2.x = RefPoint.x - base / 2;
	p2.y = RefPoint.x + height / 2;
	p3.x = RefPoint.x + base / 2;
	p3.y = RefPoint.x + height / 2;
}

void RightTriangle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, FILLED);
}

void RightTriangle::rotate()
{
	window* pW = pGame->getWind();

	// Save old points for future calculation
	point p1tmp = p1, p2tmp = p2, p3tmp = p3;

	// Rotation around point formula
	// x' = -(y-ry)+rx
	// y' =  (x-rx)+ry
	p1.x = -(p1tmp.y - RefPoint.y) + RefPoint.x;
	p1.y = p1tmp.x - RefPoint.x + RefPoint.y;
	p2.x = -(p2tmp.y - RefPoint.y) + RefPoint.x;
	p2.y = p2tmp.x - RefPoint.x + RefPoint.y;
	p3.x = -(p3tmp.y - RefPoint.y) + RefPoint.x;
	p3.y = p3tmp.x - RefPoint.x + RefPoint.y;

	this->draw();
}

void RightTriangle::resizeUp()
{
	height *= 2;
	base *= 2;
	draw();
}

void RightTriangle::resizeDown()
{
	height /= 2;
	base /= 2;
	draw();
}
