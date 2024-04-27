#include "CompositeShapes.h"
#include "gameConfig.h"

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref):shape(r_pGame, ref)
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

Cloud::Cloud(game* r_pGame, point ref, int radius) : shape(r_pGame, ref)
{
    // Calculate positions for circles
    point baseRef = ref;
    point topLeftRef = { ref.x - radius * 1.5, ref.y - radius / 2 };
    point topRightRef = { ref.x + radius * 1.5, ref.y - radius / 2 };
    point bottomLeftRef = { ref.x - radius * 1.2, ref.y + radius / 2 };
    point bottomRightRef = { ref.x + radius * 1.2, ref.y + radius / 2 };

    // Create circles
    base = new Circle(r_pGame, baseRef, radius);
    topLeft = new Circle(r_pGame, topLeftRef, radius);
    topRight = new Circle(r_pGame, topRightRef, radius);
    bottomLeft = new Circle(r_pGame, bottomLeftRef, radius);
    bottomRight = new Circle(r_pGame, bottomRightRef, radius);
}

void Cloud::draw() const
{
    // Draw circles
    base->draw();
    topLeft->draw();
    topRight->draw();
    bottomLeft->draw();
    bottomRight->draw();
}

void Cloud::rotate()
{
    // Rotate each circle individually
    base->rotate();
    topLeft->rotate();
    topRight->rotate();
    bottomLeft->rotate();
    bottomRight->rotate();
}

void Cloud::resizeUp()
{
    // Double the radius of each circle
    base->resizeUp();
    topLeft->resizeUp();
    topRight->resizeUp();
    bottomLeft->resizeUp();
    bottomRight->resizeUp();
}

void Cloud::resizeDown()
{
    // Halve the radius of each circle
    base->resizeDown();
    topLeft->resizeDown();
    topRight->resizeDown();
    bottomLeft->resizeDown();
    bottomRight->resizeDown();
}


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