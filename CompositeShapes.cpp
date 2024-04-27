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

void Sign::rotate() {};
void Sign::resizeUp() {};
void Sign::resizeDown() {};
void Sign::flip() {};


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

	void Cloud::updateCirclesRef() {
		topRef = { RefPoint.x, RefPoint.y - rad / 2 };
		centerRef = { RefPoint.x, RefPoint.y };
		bottomLeftRef = { RefPoint.x - rad, RefPoint.y };
		bottomRightRef = { RefPoint.x + rad, RefPoint.y };
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
		updateCirclesRef();
		updateCircles();
		
	}

	void Cloud::resizeDown() {
		rad /= 2;
		updateCirclesRef();
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


Tree::Tree(game* r_pGame, point ref) : shape(r_pGame, ref), crownRad(config.treeShape.crownRad), trunkHeight(config.treeShape.trunkHeight)
{
	// Calculate positions for trunk and crown
	trunkRef = { ref.x, ref.y + crownRad};
	crownRef = { ref.x, ref.y };

	// Create trunk rectangle and crown circle
	trunk = new Rect(r_pGame, trunkRef, trunkHeight, trunkHeight / 5);
	crown = new Cloud(r_pGame, crownRef);
};

void Tree::updateTree() {
	trunkRef = { RefPoint.x, RefPoint.y + crownRad};
	crownRef = { RefPoint.x, RefPoint.y };
	delete trunk, crown;
	trunk = new Rect(pGame, trunkRef, trunkHeight, trunkHeight / 5);
	crown = new Cloud(pGame, crownRef);
}

void Tree::draw() const
{
	// Draw trunk and crown
	trunk->draw();
	crown->draw();
}
void Tree::updateTreeRefRotate() {
	trunkRef = { RefPoint.x, RefPoint.y + trunkHeight / 2 };
	crownRef = { RefPoint.x, RefPoint.y };
}
void Tree::rotate()
{
	
	// Rotate the crown
	crown->rotate();
	trunk->rotate();
	// Update the tree
	updateTreeRefRotate();
}

void Tree::resizeUp()
{
	updateTree();
	// Double the size of the trunk and crown
	trunk->resizeUp();
	crown->resizeUp();
}

void Tree::resizeDown()
{
	updateTree();
	// half the size of the trunk and crown
	trunk->resizeDown();
	crown->resizeDown();
}

void Tree::flip()
{
	updateTree();
	// Flip the crown
	crown->flip();
	trunk->flip();
}

//--------------------------------- class Icecream -----------------------------------//

