#include "CompositeShapes.h"
#include "gameConfig.h"

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	point topRef = ref;	//top rect ref is the same as the sign
	point baseRef = { ref.x, ref.y + config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2 };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
}

void Sign::draw() const
{
	base->draw();
	top->draw();
}


//--------------------------------- class Cloud -----------------------------------//

Cloud::Cloud(game* r_pGame, point ref) : shape(r_pGame, ref), rad(config.cloudShape.radius) {
	pGame = r_pGame;
    initializeCircles(ref);
}

void Cloud::initializeCircles(point ref) {
    topRef = { ref.x, ref.y - rad / 2 };
    centerRef = { ref.x, ref.y };
    bottomLeftRef = { ref.x - rad, ref.y };
    bottomRightRef = { ref.x + rad, ref.y };

    top = new Circle(pGame, topRef, rad);
    center = new Circle(pGame, centerRef, rad);
    bottomLeft = new Circle(pGame, bottomLeftRef, rad);
    bottomRight = new Circle(pGame, bottomRightRef, rad);
}

void Cloud::updateCircles() {
    delete top, center, bottomLeft, bottomRight;

    top = new Circle(pGame, topRef, rad);
    center = new Circle(pGame, centerRef, rad);
    bottomLeft = new Circle(pGame, bottomLeftRef, rad);
    bottomRight = new Circle(pGame, bottomRightRef, rad);
}

void Cloud::draw() const {
    top->draw();
    center->draw();
    bottomLeft->draw();
    bottomRight->draw();
}

void Cloud::rotate() {
    rotateAroundPoint(topRef, RefPoint);
    rotateAroundPoint(centerRef, RefPoint);
    rotateAroundPoint(bottomLeftRef, RefPoint);
    rotateAroundPoint(bottomRightRef, RefPoint);

    updateCircles();
}

void Cloud::resizeUp() {
    rad *= 2;
    updateCircles();
}

void Cloud::resizeDown() {
    rad /= 2;
    updateCircles();
}

// Cloud is symmetric, no need to flip
void Cloud::flip() {}


//--------------------------------- class House -----------------------------------//


House::House(game* r_pGame, point ref, int baseWidth, int baseHeight, int roofSide) : shape(r_pGame, ref)
{
	// Calculate positions for base and roof
	point baseRef = { ref.x - baseWidth / 2, ref.y };
	point roofRef = { ref.x, ref.y - roofSide / 2 };

	// Create base rectangle and roof triangle
	base = new Rect(r_pGame, baseRef, baseHeight, baseWidth);
	roof = new EquilateralTriangle(r_pGame, roofRef, roofSide);
}

void House::draw() const
{
	// Draw base and roof
	base->draw();
	roof->draw();
}

void House::rotate()
{
	// Rotate the roof
	roof->rotate();
}

void House::resizeUp()
{
	// Double the size of the base and roof
	base->resizeUp();
	roof->resizeUp();
}

void House::resizeDown()
{
	// half the size of the base and roof
	base->resizeDown();
	roof->resizeDown();
}


//--------------------------------- class Tree -----------------------------------//


Tree::Tree(game* r_pGame, point trunkRef, int trunkWidth, int trunkHeight, point crownRef, int crownRadius)
	: shape(r_pGame, trunkRef)
{
	// Create trunk
	trunk = new Rect(r_pGame, trunkRef, trunkHeight, trunkWidth);

	// Create crown
	crown = new Circle(r_pGame, crownRef, crownRadius);
}

void Tree::draw() const
{
	// Draw trunk and crown
	trunk->draw();
	crown->draw();
}

void Tree::rotate()
{
	// Rotate trunk and crown together
	trunk->rotate();
	crown->rotate();
}

void Tree::resizeUp()
{
	// Double the dimensions of trunk and increase crown radius by 10%
	trunk->resizeUp();
	crown->resizeUp();
}

void Tree::resizeDown()
{
	// Halve the dimensions of trunk and decrease crown radius by 10%
	trunk->resizeDown();
	crown->resizeDown();
}