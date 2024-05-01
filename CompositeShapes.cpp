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
	topRef = { ref.x, ref.y - rad / 2 };
	centerRef = { ref.x, ref.y };
	bottomLeftRef = { ref.x - rad, ref.y };
	bottomRightRef = { ref.x + rad, ref.y };

	top = new Circle(pGame, topRef, rad);
	center = new Circle(pGame, centerRef, rad);
	bottomLeft = new Circle(pGame, bottomLeftRef, rad);
	bottomRight = new Circle(pGame, bottomRightRef, rad);
}

void Cloud::update() {
	delete top, center, bottomLeft, bottomRight;
	top = new Circle(pGame, topRef, rad);
	center = new Circle(pGame, centerRef, rad);
	bottomLeft = new Circle(pGame, bottomLeftRef, rad);
	bottomRight = new Circle(pGame, bottomRightRef, rad);
}

void Cloud::updateRef() {
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
	update();
}

void Cloud::resizeUp() {
	rad *= 2;
	updateRef();
	update();

}

void Cloud::resizeDown() {
	rad /= 2;
	updateRef();
	update();
}

// Cloud is symmetric, no need to flip
void Cloud::flip() {}

//--------------------------------- class House -----------------------------------//

House::House(game* r_pGame, point ref) : shape(r_pGame, ref),
baseHeight(config.houseShape.baseHeight), baseWidth(config.houseShape.baseWidth),
roofHeight(config.houseShape.roofHeight), roofWidth(config.houseShape.roofWidth)
{

	// Calculate positions for base and roof
	baseRef = { ref.x, ref.y + baseHeight / 2 };
	roofRef = { ref.x, ref.y - roofHeight / 2 };

	// Create base rectangle and roof triangle
	base = new Rect(pGame, baseRef, baseHeight, baseWidth);
	roof = new IsoscelesTriangle(pGame, roofRef, roofHeight, roofWidth);
}

void House::update() {
	delete base, roof;
	base = new Rect(pGame, baseRef, baseHeight, baseWidth);
	roof = new IsoscelesTriangle(pGame, roofRef, roofHeight, roofWidth);
}

void House::updateRef() {
	baseRef = { RefPoint.x, RefPoint.y + baseHeight / 2 };
	roofRef = { RefPoint.x, RefPoint.y - roofHeight / 2 };
}

void House::draw() const
{
	// Draw base and roof
	base->draw();
	roof->draw();
}

void House::rotate()
{
	rotateAroundPoint(baseRef, RefPoint);
	rotateAroundPoint(roofRef, RefPoint);
	update();
	base->rotate();
	roof->rotate();
}

void House::resizeUp()
{
	baseHeight *= 2;
	baseWidth *= 2;
	roofHeight *= 2;
	roofWidth *= 2;
	updateRef();
	update();
}

void House::resizeDown()
{
	baseHeight /= 2;
	baseWidth /= 2;
	roofHeight /= 2;
	roofWidth /= 2;
	updateRef();
	update();
}

// House is symmetric, no need to flip
void House::flip() {};

//--------------------------------- class Tree -----------------------------------//


Tree::Tree(game* r_pGame, point ref) : shape(r_pGame, ref),
trunkWidth(config.treeShape.trunkWidth),
trunkHeight(config.treeShape.trunkHeight), crownRad(config.treeShape.crownRad)
{
	// Calculate positions for trunk and crown
	trunkRef = { RefPoint.x, RefPoint.y + trunkHeight / 2 };
	crownRef = { RefPoint.x, RefPoint.y - crownRad / 2 };

	// Create trunk rectangle and crown circle
	trunk = new Rect(pGame, trunkRef, trunkHeight, trunkWidth);
	crown = new Cloud(pGame, crownRef);
};

void Tree::update() {
	delete trunk, crown;
	trunk = new Rect(pGame, trunkRef, trunkHeight, trunkWidth);
	crown = new Cloud(pGame, crownRef);
}

void Tree::draw() const
{
	// Draw trunk and crown
	trunk->draw();
	crown->draw();
}
void Tree::updateRef() {
	trunkRef = { RefPoint.x, RefPoint.y + trunkHeight / 2 };
	crownRef = { RefPoint.x, RefPoint.y - crownRad / 2 };
}
void Tree::rotate()
{
	rotateAroundPoint(crownRef, RefPoint);
	rotateAroundPoint(trunkRef, RefPoint);
	update();
	trunk->rotate();
	crown->rotate();
}

void Tree::resizeUp()
{
	trunkHeight *= 2;
	trunkWidth *= 2;
	crownRad *= 2;
	updateRef();
	update();
}

void Tree::resizeDown()
{
	trunkHeight /= 2;
	trunkWidth /= 2;
	crownRad /= 2;
	updateRef();
	update();
}

// Tree is symmetric, no need to flip
void Tree::flip() {}

//--------------------------------- Class Icecream -----------------------------------//

Icecream::Icecream(game* r_pGame, point ref) : shape(r_pGame, ref),
scoopRad(config.icecreamShape.scoopRad),
coneHeight(config.icecreamShape.coneHeight)
{
	// Calculate positions for trunk and crown
	scoopRef = { RefPoint.x, RefPoint.y + scoopRad / 2 };
	coneRef = { RefPoint.x, RefPoint.y - coneHeight / 2 };

	// Create trunk rectangle and crown circle
	scoop = new Circle(pGame, scoopRef, scoopRad);
	cone = new IsoscelesTriangle(pGame, coneRef, coneHeight, 2 * scoopRad);
};

void Icecream::update() {
	delete scoop, cone;
	scoop = new Circle(pGame, scoopRef, scoopRad);
	cone = new IsoscelesTriangle(pGame, coneRef, coneHeight, 2 * scoopRad);
}

void Icecream::draw() const
{
	scoop->draw();
	cone->draw();
}

void Icecream::updateRef()
{
	scoopRef = { RefPoint.x, RefPoint.y + scoopRad / 2 };
	coneRef = { RefPoint.x, RefPoint.y - coneHeight / 2 };
}

void Icecream::rotate()
{
	rotateAroundPoint(scoopRef, RefPoint);
	rotateAroundPoint(coneRef, RefPoint);
	update();
}

void Icecream::resizeUp()
{
	scoopRad *= 2;
	coneHeight *= 2;
	updateRef();
	update();
}

void Icecream::resizeDown()
{
	scoopRad /= 2;
	coneHeight /= 2;
	updateRef();
	update();
}

// Icecream is symmetric, no need to flip
void Icecream::flip() {}

//--------------------------------- Class Plane -----------------------------------//

Plane::Plane(game* r_pGame, point ref) :shape(r_pGame, ref),
bodyHeight(config.planeShape.bodyHeight),
bodyWidth(config.planeShape.bodyWidth),
wingHeight(config.planeShape.wingHeight),
wingWidth(config.planeShape.wingWidth),
tailHeight(config.planeShape.tailHeight),
tailWidth(config.planeShape.tailWidth)
{
	// Ref Points
	bodyRef = RefPoint;
	headRef = { RefPoint.x, RefPoint.y - bodyHeight / 2 - bodyWidth / 2 };
	leftWingRef = { RefPoint.x - bodyWidth / 2 - wingWidth / 2, RefPoint.y - wingHeight / 2 };
	rightWingRef = { RefPoint.x + bodyWidth / 2 + wingWidth / 2, RefPoint.y - wingHeight / 2 };
	leftTailRef = { RefPoint.x - bodyWidth / 2 - tailWidth / 2, RefPoint.y + bodyHeight / 2 - tailHeight * 2 / 3 };
	rightTailRef = { RefPoint.x + bodyWidth / 2 + tailWidth / 2, RefPoint.y + bodyHeight / 2 - tailHeight * 2 / 3 };

	// Objects
	body = new Rect(pGame, bodyRef, bodyHeight, bodyWidth);
	head = new EquilateralTriangle(pGame, headRef, bodyWidth);
	leftWing = new RightTriangle(pGame, leftWingRef, wingHeight, -wingWidth);
	rightWing = new RightTriangle(pGame, rightWingRef, wingHeight, wingWidth);
	leftTail = new RightTriangle(pGame, leftTailRef, tailHeight, -tailWidth);
	rightTail = new RightTriangle(pGame, rightTailRef, tailHeight, tailWidth);
};

void Plane::update()
{
	delete body, head, leftWing, rightWing, leftTail, rightTail;
	body = new Rect(pGame, bodyRef, bodyHeight, bodyWidth);
	head = new EquilateralTriangle(pGame, headRef, bodyWidth);
	leftWing = new RightTriangle(pGame, leftWingRef, wingHeight, -wingWidth);
	rightWing = new RightTriangle(pGame, rightWingRef, wingHeight, wingWidth);
	leftTail = new RightTriangle(pGame, leftTailRef, tailHeight, -tailWidth);
	rightTail = new RightTriangle(pGame, rightTailRef, tailHeight, tailWidth);
}

void Plane::updateRef()
{
	bodyRef = RefPoint;
	headRef = { RefPoint.x, RefPoint.y - bodyHeight / 2 - bodyWidth / 2 };
	leftWingRef = { RefPoint.x - bodyWidth / 2 - wingWidth / 2, RefPoint.y - wingHeight / 2 };
	rightWingRef = { RefPoint.x + bodyWidth / 2 + wingWidth / 2, RefPoint.y - wingHeight / 2 };
	leftTailRef = { RefPoint.x - bodyWidth / 2 - tailWidth / 2, RefPoint.y + bodyHeight / 2 - tailHeight * 2 / 3 };
	rightTailRef = { RefPoint.x + bodyWidth / 2 + tailWidth / 2, RefPoint.y + bodyHeight / 2 - tailHeight * 2 / 3 };
}

void Plane::draw() const
{
	body->draw();
	head->draw();
	leftWing->draw();
	rightWing->draw();
	leftTail->draw();
	rightTail->draw();
}

void Plane::rotate()
{
	rotateAroundPoint(bodyRef, RefPoint);
	rotateAroundPoint(headRef, RefPoint);
	rotateAroundPoint(leftWingRef, RefPoint);
	rotateAroundPoint(rightWingRef, RefPoint);
	rotateAroundPoint(leftTailRef, RefPoint);
	rotateAroundPoint(rightTailRef, RefPoint);
	update();
	body->rotate();
	head->rotate();
	leftWing->rotate();
	rightWing->rotate();
	leftTail->rotate();
	rightTail->rotate();
}

void Plane::resizeUp()
{
	bodyHeight *= 2;
	bodyWidth *= 2;
	wingHeight *= 2;
	wingWidth *= 2;
	tailHeight *= 2;
	tailWidth *= 2;
	updateRef();
	update();
}

void Plane::resizeDown()
{
	bodyHeight /= 2;
	bodyWidth /= 2;
	wingHeight /= 2;
	wingWidth /= 2;
	tailHeight /= 2;
	tailWidth /= 2;
	updateRef();
	update();
}

// Plane is symmetric, no need to flip
void Plane::flip() {}
