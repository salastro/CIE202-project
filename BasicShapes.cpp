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


void Rect::rotate(){
	// Swap width and height
	int temp = wdth;
	wdth = hght;
	hght = temp;

	// Adjust the reference point to keep the rectangle in the same position
	RefPoint.x += (wdth - hght) / 2;
	RefPoint.y += (hght - wdth) / 2;

	// Redraw the rotated rectangle
	draw();
}

void Rect::resizeUp() {
	// Double the height and width
	hght *= 2;
	wdth *= 2;
	// Redraw the resizedUp rectangle
	draw();
}


void Rect::resizeDown() {
	// Half the height and width
	hght *= 2;
	wdth *= 2;
	// Redraw the resizedDown rectangle 
	draw();

}

//---------------------------------------------------------------------------------------------------------------------





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

void Circle::rotate() {
		draw();
}

void Circle::resizeUp() {
	rad *= 2;
	draw();
}

void Circle::resizeDown() {
	rad /= 2;
	draw();
}

//---------------------------------------------------------------------------------------------------------------------




////////////////////////////////////////////////////  class equilateral triangle  ///////////////////////////////////////


EquilateralTriangle::EquilateralTriangle(game* r_pGame, point ref, int s) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	side = s;
}

void EquilateralTriangle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	point p1, p2, p3;
	p1.x = RefPoint.x;
	p1.y = RefPoint.y - side / 2;
	p2.x = RefPoint.x - side / 2;
	p2.y = RefPoint.y + side / 2;
	p3.x = RefPoint.x + side / 2;
	p3.y = RefPoint.y + side / 2;
	// Redraw the shape

	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, FILLED);
}

/*
		 p1
		 ^
		/ \
	   /   \
	s /  x  \ s
	 /       \
	/_________\
	p3	 s	  p2
*/

void EquilateralTriangle::rotate() {
	window* pW = pGame->getWind();	//get interface window

	point rotatedP1, rotatedP2, rotatedP3;
	rotatedP1.x = RefPoint.x + side / 2;  
	rotatedP1.y = RefPoint.y - side / 2; 

	rotatedP2.x = RefPoint.x - side / 2;  
	rotatedP2.y = RefPoint.y - side / 2;  

	rotatedP3.x = RefPoint.x;             
	rotatedP3.y = RefPoint.y + side;      
	// Redraw the shape
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawTriangle(rotatedP1.x, rotatedP1.y, rotatedP2.x, rotatedP2.y, rotatedP3.x, rotatedP3.y, FILLED);

	/////// ============ TODO: Use the draw function to redraw the shape with the updated coordinates ============ ///////

}
	


void EquilateralTriangle::resizeUp() {
	// Double the side length
    side *= 2;

    // Adjust the reference point to keep the triangle in the same position
    RefPoint.x -= side / 4; 
	RefPoint.y -= side / 4; 

    // Redraw the resized triangle
    draw();

}

void EquilateralTriangle::resizeDown() {
	// Double the side length
	side /= 2;

	// Adjust the reference point to keep the triangle in the same position
	RefPoint.x += side / 4;
	RefPoint.y += side / 4;

	// Redraw the resized triangle
	draw();

}

//---------------------------------------------------------------------------------------------------------------------





////////////////////////////////////////////////////  class right angled triangle  ///////////////////////////////////////

RightTriangle::RightTriangle(game* r_pGame, point ref, int h, int b) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	height = h;
	base = b;
}

void RightTriangle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	point p1, p2, p3;
	p1.x = RefPoint.x + base / 2;
	p1.y = RefPoint.x - height / 2;
	p2.x = RefPoint.x - base / 2;
	p2.y = RefPoint.x + height / 2;
	p3.x = RefPoint.x + base / 2;
	p3.y = RefPoint.x + height / 2;
	pW->DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, FILLED);
}



void RightTriangle::rotate() {
	int newX1 = RefPoint.x + (height / 2);
	int newY1 = RefPoint.y + (base / 2);

	int newX2 = RefPoint.x - (height / 2);
	int newY2 = RefPoint.y + (base / 2);

	int newX3 = RefPoint.x - (height / 2);
	int newY3 = RefPoint.y - (base / 2);

	// Redraw the shape with the updated coordinates
	window* pW = pGame->getWind();    // Get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawTriangle(newX1, newY1, newX2, newY2, newX3, newY3, FILLED);


	/////// ============ TODO: Use the draw function to redraw the shape with the updated coordinates ============ ///////


}

void RightTriangle::resizeUp() {
	// Double the height and base
	height *= 2;
	base *= 2;

	// Redraw the resized triangle
	draw();
}

void RightTriangle::resizeDown() {
	height /= 2;
	base /= 2;

	// Redraw the resized triangle
	draw();
}
