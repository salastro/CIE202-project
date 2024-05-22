#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "libxl/include_cpp/libxl.h"
	
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

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();

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
	if (pGame->getToolbar()->getLevel() < 3)
	{
		pGame->getWind()->SetPen(BLACK);
		pGame->getWind()->DrawString(50, 50, "Hint is available from level 3");
		return;
	}

	int CurrentScore = pGame->getToolbar()->getScore();
	pGame->getToolbar()->setScore(CurrentScore - 1);

	grid* pGrid = pGame->getGrid();

	if (pGrid->getShapeCount() > 0) {
		// Seed the random number generator
		srand((time(0)));

		int randomIndex = rand() % pGrid->getShapeCount();
		shape* selectedShape = pGrid->getShapeList()[randomIndex];
		
		if (selectedShape)
		{
			pGrid->setActiveShape(selectedShape);
			pGrid->deleteShape();

			color originalColor = selectedShape->getColor();
			selectedShape->setColor(YELLOW);
			selectedShape->draw();

			// Introduce a delay if needed for visualization
			// pGame->getWind()->Delay(500); // Example delay function

			// Restore the original color
			selectedShape->setColor(originalColor);
			selectedShape->draw();
		}
	}
	else {
		pGame->getWind()->SetPen(BLACK);
		pGame->getWind()->DrawString(50, 50, "No shapes available for hint.");
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
	

	//////////////////////////////////////////// Used Clear Grid Function Again ////////////////////////////////////////////	

	pGame->getGrid()->clearGrid();

	if (pGame->getToolbar())
	{
		pGame->getToolbar()->setLevel(gameLevel);
		//std::cout << "Game Level is set to: " <<pGame->getToolbar()->getLevel() << endl << endl << endl << endl;

	}




	///////////////////////////////////////////////// SAVE ///////////////////////////////////////
}

operSave::operSave(game* r_pGame) :operation(r_pGame)
{
}

void operSave::Act()
{
	// Access the shapesList from the grid
	grid* pGrid = pGame->getGrid();
	if (!pGrid) {
		// Handle error: grid not found
		return;
	}
	shape** shapes = pGrid->getShapeList();
	

	////// For testing//////
	/*Car* car1 = new Car(pGame, { 299, 399 });
	Car* car2 = new Car(pGame, { 299, 399 });
	Car* car3 = new Car(pGame, { 299, 399 });
	shape* shapes[] = { car1, car2, car3 };
	int numShapes = 3;
	*/

	// Create a new Excel book
	libxl::Book* book = xlCreateXMLBook();
	if (!book) {
		// Handle error: unable to create book
		return;
	}

	// Add a sheet to the book
	libxl::Sheet* sheet = book->addSheet("Shapes");
	if (!sheet) {
		book->release();
		return;
	}

	// Header Raw for Game
	sheet->writeStr(1, 0, "level");
	sheet->writeStr(1, 1, "score");
	sheet->writeStr(1, 2, "lives");
	sheet->writeStr(1, 3, "time");
	sheet->writeStr(1, 4, "ShapeCount");

	// Save the game data
	toolbar* pToolbar = pGame->getToolbar();
	sheet->writeNum(2, 0, pToolbar->getLevel());
	sheet->writeNum(2, 1, pToolbar->getScore());
	sheet->writeNum(2, 2, pToolbar->getLives());
	sheet->writeNum(2, 3, pToolbar->getTime());
	sheet->writeNum(2, 4, pGrid->getShapeCount());


	// Header Raw for Shapes
	sheet->writeStr(3, 0, "Type");
	sheet->writeStr(3, 1, "Ref x");
	sheet->writeStr(3, 2, "Ref y");
	sheet->writeStr(3, 3, "Width");
	sheet->writeStr(3, 4, "Height");
	sheet->writeStr(3, 5, "par 3");
	sheet->writeStr(3, 6, "par 4");
	sheet->writeStr(3, 7, "par 5");
	sheet->writeStr(3, 8, "par 6");
	sheet->writeStr(3, 9, "par 7");
	sheet->writeStr(3, 10, "Shape Cout");


	//Cloud* cloud = new Cloud(pGame, { 299, 399 });
	//cloud->save(sheet, 4);

	int row = 4; 

	/*int numShapes = pGrid->getShapeCount();*/      //////////////Shape count return garbage Value This is not my function nor my fault///////
	int numShapes = pGrid->getShapeCount();


	for (int i = 0; i < numShapes; ++i) {
		if(shapes[i])
		shapes[i]->save(sheet, row++);
	}

	if (!book->save("shapes.xlsx")) {
		// Handle error: unable to save book
		book->release();
		return;
	}

	// Release resources
	book->release();
}



/////////////////////////////////////////////////LOAD///////////////////////////////////////////


operLoad::operLoad(game* r_pGame) :operation(r_pGame)
{
}
void operLoad::Act()
{

	// Open the Excel book
	libxl::Book* book = xlCreateXMLBook();
	if (!book) {
		return;
	}

	if (!book->load("shapes.xlsx")) {
		book->release();
		return;
	}

	grid* pGrid = pGame->getGrid();
	if (!pGrid) {
		book->release();
		return;
	}
	
	/////////////////////////////////// Had to wait for someone to create clearGrid() function to be used here /////////////////////////////

	pGrid->clearGrid();
	/*pGrid->clearGridArea();*/


	// Get the sheet named "Shapes" from the book
	libxl::Sheet* sheet = book->getSheet(0);
	if (!sheet) {
		book->release();
		return;
	}

	// Get the number of rows in the sheet

	//////////////////////////////// Just One line added to get the number of rows in the sheet and saved the number of shapes in the sheet  ////////////////////////////

	int numRows =  (sheet->readNum(2,4))+3;
	pGame->getToolbar()->setLevel(sheet->readNum(2, 0));
	pGame->getToolbar()->setScore(sheet->readNum(2, 1));
	pGame->getToolbar()->setLives(sheet->readNum(2, 2));
	pGame->getToolbar()->setTime(sheet->readNum(2, 3));


	for (int row = 4; row <= numRows; ++row) {
		
		std::string type = sheet->readStr(row, 0);

		// Create objects of the corresponding shape classes based on the type
		if (type == "Rectangle") {
			Rect* rect = new Rect(pGame, { 1,2 }, 1, 1);
			rect->load(sheet, row);
			pGrid->addShape(rect);
		}
		else if (type == "Circle") {
			Circle* circle = new Circle(pGame, { 2,3 }, 1);
			circle->load(sheet, row);
			pGrid->addShape(circle);
		}
		else if (type == "IsoscelesTriangle") {
			IsoscelesTriangle* triangle = new IsoscelesTriangle(pGame, { 3,4 }, 1, 1);
			triangle->load(sheet, row);
			pGrid->addShape(triangle);
		}
		else if (type == "EquilateralTriangle") {
			EquilateralTriangle* triangle = new EquilateralTriangle(pGame, { 4,5 }, 1);
			triangle->load(sheet, row);
			pGrid->addShape(triangle);
		}
		else if (type == "RightTriangle") {
			RightTriangle* triangle = new RightTriangle(pGame, { 4,5 }, 1, 1);
			triangle->load(sheet, row);
			pGrid->addShape(triangle);
		}
		else if (type == "Car") {
			Car* car = new Car(pGame, { 4,5 });
			car->load(sheet, row);
			pGrid->addShape(car);
		}
		else if (type == "House") {
			House* house = new House(pGame, { 4,5 });
			house->load(sheet, row);
			pGrid->addShape(house);
		}
		else if (type == "Tree") {
			Tree* tree = new Tree(pGame, { 4,5 });
			tree->load(sheet, row);
			pGrid->addShape(tree);
		}
		else if (type == "Cloud") {
			Cloud* cloud = new Cloud(pGame, { 4,5 });
			cloud->load(sheet, row);
			pGrid->addShape(cloud);
		}
		else if (type == "Plane") {
			Plane* plane = new Plane(pGame, { 4,5 });
			plane->load(sheet, row);
			pGrid->addShape(plane);
		}
		else if (type == "Icecream") {
			Icecream* iceCream = new Icecream(pGame, { 4,5 });
			iceCream->load(sheet, row);
			pGrid->addShape(iceCream);
		}
		
	}
	pGrid->draw();

	// Release resources
	book->release();

}


operRefresh::operRefresh(game* r_pGame) :operation(r_pGame)
{
}

void operRefresh::Act()
{
	grid* pGrid = pGame->getGrid(); 
	toolbar* pToolbar = pGame->getToolbar(); 
	int currentLevel = pToolbar->getLevel();  //started using variables to make it easier
	int numShapes = 2 * currentLevel + 1;
	int currentLives = pToolbar->getLives();
	pToolbar->setLives(currentLives - 1); //decrement lives by 1


	/////////////////////////////////////////////// Used The Newly Created clearGrid() Function ////////////////////////////////////////////

	pGrid->clearGrid();

	/*for (int i = 0; i < numShapes; ++i)
	{	
		pGrid->setActiveShape(pGrid->getShapeList()[i]) ;
		pGrid->deleteShape();
	}*/


	/////////////////////////////////////// I left a comment here to mention that i wanted to add generaterandomshapes() function to the grid class after beeen finished //////////////////////////////


	// to be added: generate random shapes 
	
	pGame->generateRandomShapes();

	///////////////////////////////////////////// Deleted as it was a Replacement for testing generateRandomShapes() function ////////////////////////////////////////////

	/*for (int i = 0; i < numShapes; ++i)
	{
		shape* newShape = pGrid->getShapeList()[i];
		if (pGrid)
		{
			pGrid->addShape(newShape);
		}
	}*/
	/*pGrid->draw();*/  //GenerateRandomShapes() /////////////////function Already has draw() function///////////////////////////
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
