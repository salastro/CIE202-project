#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
/////////////////////////////////// class operation  //////////////////
operation::operation(game* r_pGame)
{
	pGame = r_pGame;
}


/////////////////////////////////// class operAddSign  //////////////////

operAddSign::operAddSign(game* r_pGame):operation(r_pGame)
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
	 psh->rotate();
	 pGrid->setActiveShape(psh);

}

operPlus::operPlus(game* r_pGame) :operation(r_pGame)
{
}

void operPlus::Act()
{
}

operMinus::operMinus(game* r_pGame) :operation(r_pGame)
{
}

void operMinus::Act()
{
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
