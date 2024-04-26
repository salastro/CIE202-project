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
	draw();
}

////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
Circle::Circle(game* r_pGame, point ref, int r) :shape(r_pGame, ref)
{
	rad = r;
}

void Circle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawCircle(RefPoint.x, RefPoint.y, rad, FILLED);
}

void Circle::rotate()
{
}



////////////////////////////////////////////////////  class equilateral triangle  ///////////////////////////////////////
EquilateralTriangle::EquilateralTriangle(game* r_pGame, point ref, int s) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	side = s;
	p1.x = RefPoint.x;
	p1.y = RefPoint.y - side / 2;
	p2.x = RefPoint.x - side / 2;
	p2.y = RefPoint.y + side / 2;
	p3.x = RefPoint.x + side / 2;
	p3.y = RefPoint.y + side / 2;
}

void EquilateralTriangle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, FILLED);
}

void EquilateralTriangle::rotate()
{
	point p1tmp = p1, p2tmp = p2, p3tmp = p3;
	// p -> p'
	// p'.x = p.y-r.y+r.x
	// p'.y = -p.x+r.x+r.y
	// https://www.khanacademy.org/math/geometry/hs-geo-transformations/hs-geo-rotations/a/rotating-shapes
	p1.x = p1tmp.y - RefPoint.y + RefPoint.x;
	p1.y = -p1tmp.x + RefPoint.x + RefPoint.y;
	p2.x = p2tmp.y - RefPoint.y + RefPoint.x;
	p2.y = -p2tmp.x + RefPoint.x + RefPoint.y;
	p3.x = p3tmp.y - RefPoint.y + RefPoint.x;
	p3.y = -p3tmp.x + RefPoint.x + RefPoint.y;
	draw();
}

////////////////////////////////////////////////////  class right angled triangle  ///////////////////////////////////////

RightTriangle::RightTriangle(game* r_pGame, point ref, int h, int b) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	height = h;
	base = b;
	p1.x = RefPoint.x + base / 2;
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
	point p1tmp = p1, p2tmp = p2, p3tmp = p3;
	// p -> p'
	// p'.x = p.y-r.y+r.x
	// p'.y = -p.x+r.x+r.y
	// https://www.khanacademy.org/math/geometry/hs-geo-transformations/hs-geo-rotations/a/rotating-shapes
	p1.x = p1tmp.y - RefPoint.y + RefPoint.x;
	p1.y = -p1tmp.x + RefPoint.x + RefPoint.y;
	p2.x = p2tmp.y - RefPoint.y + RefPoint.x;
	p2.y = -p2tmp.x + RefPoint.x + RefPoint.y;
	p3.x = p3tmp.y - RefPoint.y + RefPoint.x;
	p3.y = -p3tmp.x + RefPoint.x + RefPoint.y;
	draw();
}
