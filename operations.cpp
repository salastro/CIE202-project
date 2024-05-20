#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
/////////////////////////////////// class operation  //////////////////
operation::operation(game* r_pGame)
{
	pGame = r_pGame;
}


/////////////////////////////////// class operAddSign  //////////////////

operAddSign::operAddSign(game* r_pGame) :operation(r_pGame)
{
}

void operAddSign::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Sign(pGame, signShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

operRotate::operRotate(game* r_pGame) :operation(r_pGame)
{
}

void operRotate::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* psh = pGrid->getActiveShape();
	if (psh)
		psh->rotate();
}

operPlus::operPlus(game* r_pGame) :operation(r_pGame)
{
}

void operPlus::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* psh = pGrid->getActiveShape();
	if (psh)
		psh->resizeUp();
}

operMinus::operMinus(game* r_pGame) :operation(r_pGame)
{
}

void operMinus::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* psh = pGrid->getActiveShape();
	if (psh)
		psh->resizeDown();
}

operDelete::operDelete(game* r_pGame) :operation(r_pGame)
{

}

void operDelete::Act()
{
	grid* pGrid = pGame->getGrid();
	pGrid->deleteShape();
}

operHint::operHint(game* r_pGame) :operation(r_pGame)
{
}

void operHint::Act()
{
}

operGameLevel::operGameLevel(game* r_pGame) :operation(r_pGame)
{
}

void operGameLevel::Act()
{
}

operSave::operSave(game* r_pGame) :operation(r_pGame)
{
}

void operSave::Act()
{
}

operLoad::operLoad(game* r_pGame) :operation(r_pGame)
{
}

void operLoad::Act()
{
}

operRefresh::operRefresh(game* r_pGame) :operation(r_pGame)
{
}

void operRefresh::Act()
{
}

operCar::operCar(game* r_pGame) :operation(r_pGame)
{

}

void operCar::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point carShapeRef = { xGrid,yGrid };
	shape* psh = new Car(pGame, carShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

operHouse::operHouse(game* r_pGame) :operation(r_pGame)
{
}

void operHouse::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point houseShapeRef = { xGrid,yGrid };
	shape* psh = new House(pGame, houseShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}

operTree::operTree(game* r_pGame) :operation(r_pGame)
{
}

void operTree::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point treeShapeRef = { xGrid,yGrid };
	shape* psh = new Tree(pGame, treeShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}

operAirplane::operAirplane(game* r_pGame) :operation(r_pGame)
{
}

void operAirplane::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point planeShapeRef = { xGrid,yGrid };
	shape* psh = new Plane(pGame, planeShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}

operIcecream::operIcecream(game* r_pGame) :operation(r_pGame)
{
}

void operIcecream::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point IcecreamShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Icecream(pGame, IcecreamShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}

operCloud::operCloud(game* r_pGame) :operation(r_pGame)
{
}

void operCloud::Act()
{
	window* pw = pGame->getWind();
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;
	point cloudShapeRef = { xGrid,yGrid };
	shape* psh = new Cloud(pGame, cloudShapeRef);
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}
