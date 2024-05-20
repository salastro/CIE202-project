#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include <thread>
#include <chrono>
#include <iostream>
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
	// shape* psh = pGrid->getActiveShape();
	// psh->rotate();
	// pGrid->setActiveShape(psh);

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
	grid* pGrid = pGame->getGrid();
	pGrid->deleteShape();
}

void operDelete::Act()
{
}

operHint::operHint(game* r_pGame) :operation(r_pGame)
{
	

}

void operHint::Act()
{
	if (pGame->getToolbar()->get_level() < 3)
	{
		//std::cout << "Hint is Available from level 3: " << pGame->getToolbar()->get_level() << endl << endl << endl << endl;
		pGame->getWind()->SetPen(BLACK);
		pGame->getWind()->DrawString(50, 30, "Hint is available from level 3");
		return;
	};
	int CurrentScore = pGame->getToolbar()->get_score();
	pGame->getToolbar()->set_score(CurrentScore - 1);

	int randomIndex = rand() % (pGame->getGrid()->getShapeCount());
 
	shape* selectedShape = pGame->getGrid()->getShapeList()[randomIndex];
	if (selectedShape)
	{
		grid* pGrid = pGame->getGrid();
		pGrid->setActiveShape(selectedShape);
		color originalColor = selectedShape->getColor();
		selectedShape->setColor(BLACK);
		selectedShape->draw();
		std::this_thread::sleep_for(std::chrono::seconds(2));
		selectedShape->setColor(originalColor); 
		selectedShape->draw();
	}
}	


operGameLevel::operGameLevel(game * r_pGame) :operation(r_pGame){}


void operGameLevel::Act()
{

	int gameLevel = -1;

	while (gameLevel < 1 || gameLevel > 5)
	{
		pGame->getWind()->DrawString(config.windWidth / 2, config.windHeight / 3, "Enter Game level Between 1 - 5: "); // Prompt the user
		char key;
		keytype keyType = pGame->getWind()->GetKeyPress(key);

		if (keyType == ASCII && key >= '1' && key <= '5') // Check if the input is between 1 - 5 & Convert the ASCII character to an integer
		{gameLevel = key - '0';} 
		
	}

	if (pGame->getToolbar())
	{
		pGame->getToolbar()->set_level(gameLevel);
		//std::cout << "Game Level is set to: " <<pGame->getToolbar()->get_level() << endl << endl << endl << endl;

	}


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
	grid* pGrid = pGame->getGrid(); 
	toolbar* pToolbar = pGame->getToolbar(); 
	int currentLevel = pToolbar->get_level();  //started using variables to make it easier
	int numShapes = 2 * currentLevel + 1;

	for (int i = 0; i < numShapes; ++i)
	{	
		pGrid->setActiveShape(pGrid->getShapeList()[i]) ;
		pGrid->deleteShape();
	}
	// to be added: generate random shapes 
	
	for (int i = 0; i < numShapes; ++i)
	{
		shape* newShape = pGrid->getShapeList()[i];
		if (pGrid)
		{
			pGrid->addShape(newShape);
		}
	}
	pGrid->draw();
}

operExit::operExit(game* r_pGame) :operation(r_pGame)
{
}
void operExit::Act()
{
	// Ask the user if they want to save before exiting
	pGame->printMessage("Press 's' to save before exiting.");

	pGame->getWind()->FlushKeyQueue();

	char key;
	keytype keyType = pGame->getWind()->GetKeyPress(key);

	/*if (keyType == ASCII && key == 's')
		operSave(pGame).Act();
	}*/

	// Exit the game
	pGame->setExitFlag(true);
}
