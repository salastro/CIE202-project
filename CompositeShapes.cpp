#include "CompositeShapes.h"
#include <iostream>
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
void Sign::move(Direction direction) {};

//--------------------------------- class Cloud -----------------------------------//

Cloud::Cloud(game* r_pGame, point ref) : shape(r_pGame, ref), rad(config.cloudShape.radius) {
	type = CLOUD;

	topRef = { ref.x, ref.y - rad / 2 };
	centerRef = { ref.x, ref.y };
	bottomLeftRef = { ref.x - rad, ref.y };
	bottomRightRef = { ref.x + rad, ref.y };

	top = new Circle(pGame, topRef, rad);
	center = new Circle(pGame, centerRef, rad);
	bottomLeft = new Circle(pGame, bottomLeftRef, rad);
	bottomRight = new Circle(pGame, bottomRightRef, rad);
}

Cloud::~Cloud() {
	delete top, center, bottomLeft, bottomRight;
}

void Cloud::update() {
	delete top, center, bottomLeft, bottomRight;
	top = new Circle(pGame, topRef, rad);
	center = new Circle(pGame, centerRef, rad);
	bottomLeft = new Circle(pGame, bottomLeftRef, rad);
	bottomRight = new Circle(pGame, bottomRightRef, rad);
}

void Cloud::updateRef() {
	orientation = 0;
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
	orientation += 1;
	update();
}

void Cloud::resizeUp() {
	size += 1;
	rad *= 2;
	updateRef();
	update();
}

void Cloud::resizeDown() {
	size -= 1;
	rad /= 2;
	updateRef();
	update();
}

// Cloud is symmetric, no need to flip
void Cloud::flip() {}

void Cloud::save(libxl::Sheet* sheet, int row)
{
	sheet->writeStr(row, 0, "Cloud");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, rad);
	sheet->writeNum(row, 4, orientation);
}

void Cloud::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	rad = sheet->readNum(row, 3);
	orientation = sheet->readNum(row, 4);
	updateRef();
	update();
}


void Cloud::move(Direction direction) {
	top->move(direction);
	center->move(direction);
	bottomLeft->move(direction);
	bottomRight->move(direction);
	movePoint(direction, RefPoint);
	updateRef();
}

//--------------------------------- class House -----------------------------------//

House::House(game* r_pGame, point ref) : shape(r_pGame, ref),
baseHeight(config.houseShape.baseHeight), baseWidth(config.houseShape.baseWidth),
roofHeight(config.houseShape.roofHeight), roofWidth(config.houseShape.roofWidth)
{
	type = HOUSE;

	// Calculate positions for base and roof
	baseRef = { ref.x, ref.y + baseHeight / 2 };
	roofRef = { ref.x, ref.y - roofHeight / 2 };

	// Create base rectangle and roof triangle
	base = new Rect(pGame, baseRef, baseHeight, baseWidth);
	roof = new IsoscelesTriangle(pGame, roofRef, roofHeight, roofWidth);
}

House::~House() {
	delete base, roof;
}

void House::update() {
	delete base, roof;
	base = new Rect(pGame, baseRef, baseHeight, baseWidth);
	roof = new IsoscelesTriangle(pGame, roofRef, roofHeight, roofWidth);
}

void House::updateRef() {
	orientation = 0;
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
	orientation += 1;
	rotateAroundPoint(baseRef, RefPoint);
	rotateAroundPoint(roofRef, RefPoint);
	update();
	for (int i = 0; i < orientation; i++)
	{
		base->rotate();
		roof->rotate();
	}
}

void House::resizeUp()
{
	size += 1;
	baseHeight *= 2;
	baseWidth *= 2;
	roofHeight *= 2;
	roofWidth *= 2;
	updateRef();
	update();
}

void House::resizeDown()
{
	size -= 1;
	baseHeight /= 2;
	baseWidth /= 2;
	roofHeight /= 2;
	roofWidth /= 2;
	updateRef();
	update();
}

// House is symmetric, no need to flip
void House::flip() {};

void House::save(libxl::Sheet* sheet, int row)
{
	sheet->writeStr(row, 0, "House");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, baseWidth);
	sheet->writeNum(row, 4, baseHeight);
	sheet->writeNum(row, 5, roofWidth);
	sheet->writeNum(row, 6, roofHeight);
	sheet->writeNum(row, 7, orientation);	
}

void House::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	baseWidth = sheet->readNum(row, 3);
	baseHeight = sheet->readNum(row, 4);
	roofWidth = sheet->readNum(row, 5);
	roofHeight = sheet->readNum(row, 6);
	orientation = sheet->readNum(row, 7);
	updateRef();
	update();
}

void House::move(Direction direction) {
	base->move(direction);
	roof->move(direction);
	movePoint(direction, RefPoint);
	updateRef();
}

//--------------------------------- class Tree -----------------------------------//


Tree::Tree(game* r_pGame, point ref) : shape(r_pGame, ref),
trunkWidth(config.treeShape.trunkWidth),
trunkHeight(config.treeShape.trunkHeight), crownRad(config.treeShape.crownRad)
{
	type = TREE;

	// Calculate positions for trunk and crown
	trunkRef = { RefPoint.x, RefPoint.y + trunkHeight / 2 };
	crownTopRef = { RefPoint.x, RefPoint.y - crownRad };
	crownLeftRef = { RefPoint.x - crownRad, RefPoint.y - crownRad / 2 };
	crownRightRef = { RefPoint.x + crownRad, RefPoint.y - crownRad / 2 };

	// Create trunk rectangle and crown circle
	trunk = new Rect(pGame, trunkRef, trunkHeight, trunkWidth);
	crownTop = new Circle(pGame, crownTopRef, crownRad);
	crownLeft = new Circle(pGame, crownLeftRef, crownRad);
	crownRight = new Circle(pGame, crownRightRef, crownRad);
};

Tree::~Tree() {
	delete trunk, crownTop, crownLeft, crownRight;
}

void Tree::update() {
	delete trunk, crownTop, crownLeft, crownRight;
	trunk = new Rect(pGame, trunkRef, trunkHeight, trunkWidth);
	crownTop = new Circle(pGame, crownTopRef, crownRad);
	crownLeft = new Circle(pGame, crownLeftRef, crownRad);
	crownRight = new Circle(pGame, crownRightRef, crownRad);
}

void Tree::updateRef() {
	orientation = 0;
	trunkRef = { RefPoint.x, RefPoint.y + trunkHeight / 2 };
	crownTopRef = { RefPoint.x, RefPoint.y - crownRad };
	crownLeftRef = { RefPoint.x - crownRad, RefPoint.y - crownRad / 2 };
	crownRightRef = { RefPoint.x + crownRad, RefPoint.y - crownRad / 2 };
	crownTop = new Circle(pGame, crownTopRef, crownRad);
	crownLeft = new Circle(pGame, crownLeftRef, crownRad);
	crownRight = new Circle(pGame, crownRightRef, crownRad);
}

void Tree::draw() const
{
	// Draw trunk and crown
	trunk->draw();
	crownTop->draw();
	crownLeft->draw();
	crownRight->draw();
}

void Tree::rotate()
{
	orientation += 1;
	rotateAroundPoint(crownTopRef, RefPoint);
	rotateAroundPoint(crownLeftRef, RefPoint);
	rotateAroundPoint(crownRightRef, RefPoint);
	rotateAroundPoint(trunkRef, RefPoint);
	update();
	for (int i = 0; i < orientation; i++)
	{
		trunk->rotate();
	}
}

void Tree::resizeUp()
{
	size += 1;
	trunkHeight *= 2;
	trunkWidth *= 2;
	crownRad *= 2;
	updateRef();
	update();
}

void Tree::resizeDown()
{
	size -= 1;
	trunkHeight /= 2;
	trunkWidth /= 2;
	crownRad /= 2;
	updateRef();
	update();
}

// Tree is symmetric, no need to flip
void Tree::flip() {}

void Tree::save(libxl::Sheet* sheet, int row) 
{
	sheet->writeStr(row, 0, "Tree");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, trunkWidth);
	sheet->writeNum(row, 4, trunkHeight);
	sheet->writeNum(row, 5, crownRad);
	sheet->writeNum(row, 6, orientation);

}

void Tree::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	trunkWidth = sheet->readNum(row, 3);
	trunkHeight = sheet->readNum(row, 4);
	crownRad = sheet->readNum(row, 5);
	orientation = sheet->readNum(row, 6);
	updateRef();
	update();
}

void Tree::move(Direction direction) {
	trunk->move(direction);
	crownTop->move(direction);
	crownLeft->move(direction);
	crownRight->move(direction);
	movePoint(direction, RefPoint);
	updateRef();
}

//--------------------------------- Class Icecream -----------------------------------//

Icecream::Icecream(game* r_pGame, point ref) : shape(r_pGame, ref),
scoopRad(config.icecreamShape.scoopRad),
coneHeight(config.icecreamShape.coneHeight)
{
	type = ICECREAM;

	// Calculate positions for trunk and crown
	scoopRef = { RefPoint.x, RefPoint.y - scoopRad / 2 };
	coneRef = { RefPoint.x, RefPoint.y + coneHeight / 2 };

	// Create trunk rectangle and crown circle
	scoop = new Circle(pGame, scoopRef, scoopRad);
	cone = new IsoscelesTriangle(pGame, coneRef, -coneHeight, 2 * scoopRad);
};

Icecream::~Icecream() {
	delete scoop, cone;
}

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
	orientation = 0;
	scoopRef = { RefPoint.x, RefPoint.y + scoopRad / 2 };
	coneRef = { RefPoint.x, RefPoint.y - coneHeight / 2 };
}

void Icecream::rotate()
{
	rotateAroundPoint(scoopRef, RefPoint);
	rotateAroundPoint(coneRef, RefPoint);
	update();
	orientation += 1;
	for (int i = 0; i < orientation; i++)
	{
		cone->rotate();
		cone->rotate();
		cone->rotate();
	}
}

void Icecream::resizeUp()
{
	size += 1;
	scoopRad *= 2;
	coneHeight *= 2;
	updateRef();
	update();
}

void Icecream::resizeDown()
{
	size -= 1;
	scoopRad /= 2;
	coneHeight /= 2;
	updateRef();
	update();
}

// Icecream is symmetric, no need to flip
void Icecream::flip() {}

void Icecream::save(libxl::Sheet* sheet, int row) 
{
	sheet->writeStr(row, 0, "Icecream");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, scoopRad);
	sheet->writeNum(row, 4, coneHeight);
	sheet->writeNum(row, 5, orientation);

}

void Icecream::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	scoopRad = sheet->readNum(row, 3);
	coneHeight = sheet->readNum(row, 4);
	orientation = sheet->readNum(row, 5);
	updateRef();
	update();
}

void Icecream::move(Direction direction) {
	scoop->move(direction);
	cone->move(direction);
	movePoint(direction, RefPoint);
	updateRef();
}

//--------------------------------- Class Plane -----------------------------------//

Plane::Plane(game* r_pGame, point ref) :shape(r_pGame, ref),
bodyHeight(config.planeShape.bodyHeight),
bodyWidth(config.planeShape.bodyWidth),
wingHeight(config.planeShape.wingHeight),
wingWidth(config.planeShape.wingWidth),
tailHeight(config.planeShape.tailHeight),
tailWidth(config.planeShape.tailWidth)
{
	type = PLANE;

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

Plane::~Plane() {
	delete body, head, leftWing, rightWing, leftTail, rightTail;
}

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
	orientation = 0;
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
	orientation += 1;
	for (int i = 0; i < orientation; i++)
	{
		body->rotate();
		head->rotate();
		leftWing->rotate();
		rightWing->rotate();
		leftTail->rotate();
		rightTail->rotate();
	}
}

void Plane::resizeUp()
{
	size += 1;
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
	size -= 1;
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

void Plane::save(libxl::Sheet* sheet, int row) 
{
	sheet->writeStr(row, 0, "Plane");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, bodyWidth);
	sheet->writeNum(row, 4, bodyHeight);
	sheet->writeNum(row, 5, wingWidth);
	sheet->writeNum(row, 6, wingHeight);
	sheet->writeNum(row, 7, tailWidth);
	sheet->writeNum(row, 8, tailHeight);
	sheet->writeNum(row, 9, orientation);
}

void Plane::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	bodyWidth = sheet->readNum(row, 3);
	bodyHeight = sheet->readNum(row, 4);
	wingWidth = sheet->readNum(row, 5);
	wingHeight = sheet->readNum(row, 6);
	tailWidth = sheet->readNum(row, 7);
	tailHeight = sheet->readNum(row, 8);
	orientation = sheet->readNum(row, 9);
	updateRef();
	update();
}

//--------------------------------- Class Car -----------------------------------//
void Plane::move(Direction direction) {
	body->move(direction);
	head->move(direction);
	leftWing->move(direction);
	rightWing->move(direction);
	leftTail->move(direction);
	rightTail->move(direction);
	movePoint(direction, RefPoint);
	updateRef();
}

//--------------------------------- Class Car -----------------------------------//

Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref),
bodyHeight(config.carShape.bodyHeight), bodyWidth(config.carShape.bodyWidth),
headHeight(config.carShape.headHeight), headWidth(config.carShape.headWidth),
wheelRad(config.carShape.wheelRad)
{
	type = CAR;

	// Variables
	topWidth = (bodyWidth - headWidth) / 2;

	// Ref points
	bodyRef = RefPoint;
	headRef = { RefPoint.x, RefPoint.y - bodyHeight / 2 - headHeight / 2 };
	topLeftRef = { RefPoint.x - bodyWidth / 2 + topWidth / 2, RefPoint.y - bodyHeight / 2 - headHeight / 2 };
	topRightRef = { RefPoint.x + bodyWidth / 2 - topWidth / 2, RefPoint.y - bodyHeight / 2 - headHeight / 2 };
	leftWheelRef = { RefPoint.x - bodyWidth / 2, RefPoint.y + bodyHeight / 2 };
	rightWheelRef = { RefPoint.x + bodyWidth / 2, RefPoint.y + bodyHeight / 2 };

	// Objects
	body = new Rect(pGame, bodyRef, bodyHeight, bodyWidth);
	head = new Rect(pGame, headRef, headHeight, headWidth);
	topLeft = new RightTriangle(pGame, topLeftRef, headHeight, -topWidth);
	topRight = new RightTriangle(pGame, topRightRef, headHeight, topWidth);
	leftWheel = new Circle(pGame, leftWheelRef, wheelRad);
	rightWheel = new Circle(pGame, rightWheelRef, wheelRad);
};

Car::~Car() {
	delete body, head, topLeft, topRight, leftWheel, rightWheel;
}

void Car::update()
{
	delete body, head, topLeft, topRight, leftWheel, rightWheel;
	body = new Rect(pGame, bodyRef, bodyHeight, bodyWidth);
	head = new Rect(pGame, headRef, headHeight, headWidth);
	topLeft = new RightTriangle(pGame, topLeftRef, headHeight, -topWidth);
	topRight = new RightTriangle(pGame, topRightRef, headHeight, topWidth);
	leftWheel = new Circle(pGame, leftWheelRef, wheelRad);
	rightWheel = new Circle(pGame, rightWheelRef, wheelRad);
}

void Car::updateRef()
{
	orientation = 0;
	topWidth = (bodyWidth - headWidth) / 2;
	bodyRef = RefPoint;
	headRef = { RefPoint.x, RefPoint.y - bodyHeight / 2 - headHeight / 2 };
	topLeftRef = { RefPoint.x - bodyWidth / 2 + topWidth / 2, RefPoint.y - bodyHeight / 2 - headHeight / 2 };
	topRightRef = { RefPoint.x + bodyWidth / 2 - topWidth / 2, RefPoint.y - bodyHeight / 2 - headHeight / 2 };
	leftWheelRef = { RefPoint.x - bodyWidth / 2, RefPoint.y + bodyHeight / 2 };
	rightWheelRef = { RefPoint.x + bodyWidth / 2, RefPoint.y + bodyHeight / 2 };
}

void Car::draw() const
{
	body->draw();
	head->draw();
	topLeft->draw();
	topRight->draw();
	leftWheel->draw();
	rightWheel->draw();
}

void Car::rotate()
{
	rotateAroundPoint(bodyRef, RefPoint);
	rotateAroundPoint(headRef, RefPoint);
	rotateAroundPoint(topLeftRef, RefPoint);
	rotateAroundPoint(topRightRef, RefPoint);
	rotateAroundPoint(leftWheelRef, RefPoint);
	rotateAroundPoint(rightWheelRef, RefPoint);
	update();
	orientation += 1;
	for (int i = 0; i < orientation; i++)
	{
		body->rotate();
		head->rotate();
		topLeft->rotate();
		topRight->rotate();
		leftWheel->rotate();
		rightWheel->rotate();
	}
}

void Car::resizeUp()
{
	size += 1;
	bodyHeight *= 2;
	bodyWidth *= 2;
	headHeight *= 2;
	headWidth *= 2;
	topWidth *= 2;
	wheelRad *= 2;
	updateRef();
	update();
}

void Car::resizeDown()
{
	size -= 1;
	bodyHeight /= 2;
	bodyWidth /= 2;
	headHeight /= 2;
	headWidth /= 2;
	topWidth /= 2;
	wheelRad /= 2;
	updateRef();
	update();
}

// Car is symmetric, no need to flip
void Car::flip() {}

void Car::save(libxl::Sheet* sheet, int row) 
{
	sheet->writeStr(row, 0, "Car");
	sheet->writeNum(row, 1, RefPoint.x);
	sheet->writeNum(row, 2, RefPoint.y);
	sheet->writeNum(row, 3, bodyWidth);
	sheet->writeNum(row, 4, bodyHeight);
	sheet->writeNum(row, 5, headWidth);
	sheet->writeNum(row, 6, headHeight);
	sheet->writeNum(row, 7, wheelRad);
	sheet->writeNum(row, 8, orientation);
	std::cout << "car is saved" << std::endl;
}

void Car::load(libxl::Sheet* sheet, int row)
{
	RefPoint.x = sheet->readNum(row, 1);
	RefPoint.y = sheet->readNum(row, 2);
	bodyWidth = sheet->readNum(row, 3);
	bodyHeight = sheet->readNum(row, 4);
	headWidth = sheet->readNum(row, 5);
	headHeight = sheet->readNum(row, 6);
	wheelRad = sheet->readNum(row, 7);
	orientation = sheet->readNum(row, 8);
	updateRef();
	update();
}

void Car::move(Direction direction) {
	body->move(direction);
	head->move(direction);
	topLeft->move(direction);
	topRight->move(direction);
	leftWheel->move(direction);
	rightWheel->move(direction);
	movePoint(direction, RefPoint);
	updateRef();
}
