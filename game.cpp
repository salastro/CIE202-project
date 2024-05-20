#include "game.h"
#include "gameConfig.h"

#include <iostream>


game::game()
{

	//Create the main window
	createWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//Create and draw the toolbar
	createToolBar();

	//Create and draw the grid
	createGrid();
	shapesGrid->draw();	//draw the grid and all shapes it contains.

	//Create and clear the status bar
	clearStatusBar();
}

game::~game()
{
	delete pWind;
	delete shapesGrid;
}


//////////////////////////////////////////////////////////////////////////////////////////
void game::createWind(int w, int h, int x, int y)
{
	pWind = new window(w, h, x, y);
	pWind->SetBrush(config.bkGrndColor);
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->DrawRectangle(0, 0, w, h);
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the mode
void game::createToolBar()
{
	gameToolbar = new toolbar(this);
}

void game::createGrid()
{
	//calc some grid parameters
	point gridUpperLeftPoint = { 0, config.toolBarHeight };
	int gridHeight = config.windHeight - config.toolBarHeight - config.statusBarHeight;
	//create the grid
	shapesGrid = new grid(gridUpperLeftPoint, config.windWidth, gridHeight, this);
}

operation* game::createRequiredOperation(toolbarItem clickedItem)
{
	operation* op = nullptr;
	switch (clickedItem)
	{
		/*case ITM_SIGN:
			op = new operAddSign(this);
			break;*/
	case ITM_CAR:
		printMessage("YOU PRESSED CAR");
		op = new operCar(this);
		break;
	case ITM_HOUSE:
		printMessage("YOU PRESSED HOUSE");
		op = new operHouse(this);
		break;
	case ITM_TREE:
		printMessage("YOU PRESSED TREE");
		op = new operTree(this);
		break;
	case ITM_PLANE:
		printMessage("YOU PRESSED AIRPLANE");
		op = new operAirplane(this);
		break;
	case ITM_ICECREAM:
		printMessage("YOU PRESSED Icecream");
		op = new operIcecream(this);
		break;
	case ITM_CLOUD:
		printMessage("YOU PRESSED Cloud ");
		op = new operCloud(this);
		break;
	case ITM_Rotate:
		printMessage("YOU PRESSED ROTATE ");
		op = new operRotate(this);
		break;
	case ITM_Plus:
		printMessage("YOU PRESSED PLUS");
		op = new operPlus(this);
		break;
	case ITM_Minus:
		printMessage("YOU PRESSED MINUS");
		op = new operMinus(this);
		break;
	case ITM_Refresh:
		printMessage("YOU PRESSED REFRESH");
		op = new operRefresh(this);
		break;
	case ITM_Hint:
		printMessage("YOU PRESSED HINT");
		op = new operHint(this);
		break;
	case ITM_Delete:
		printMessage("YOU PRESSED DELETE");
		op = new operDelete(this);
		break;
	case ITM_GameLevel:
		printMessage("YOU PRESSED Level");
		op = new operGameLevel(this);
		break;
	case ITM_Save:
		printMessage("YOU PRESSED SAVE");
		op = new operSave(this);
		break;
	case ITM_Load:
		printMessage("YOU PRESSED Load");
		op = new operLoad(this);
		break;
	}
	return op;
}

//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}



window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}



string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return shapesGrid;
}



////////////////////////////////////////////////////////////////////////
void game::run()
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;
	keytype keyboardInput;
	char key;

	// Flush Queue
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - SHAPE HUNT (CIE 101 / CIE202 - project) - - - - - - - - - -");
	toolbarItem clickedItem = ITM_CNT;
	do
	{
		//printMessage("Ready...");
		//1- Get user click
		pWind->GetMouseClick(x, y);

		keyboardInput = pWind->GetKeyPress(key);

		if (keyboardInput == ARROW)
		{
			shape* activeShape = getGrid()->getActiveShape();
			if (activeShape) {
				switch (key)
				{
				case 8:
					activeShape->move(UP);
					break;
				case 2:
					activeShape->move(DOWN);
					break;
				case 6:
					activeShape->move(RIGHT);
					break;
				case 4:
					activeShape->move(LEFT);
					break;
				default:
					break;
				}
				shapesGrid->draw();
			}
		}

		//2-Explain the user click
		//If user clicks on the Toolbar, ask toolbar which item is clicked
		if (y >= 0 && y < config.toolBarHeight)
		{
			clickedItem = gameToolbar->getItemClicked(x);

			//3-create the approp operation accordin to item clicked by the user
			operation* op = createRequiredOperation(clickedItem);
			if (op)
				op->Act();

			//4-Redraw the grid after each action
			shapesGrid->draw();

		}

	} while (clickedItem != ITM_EXIT);
}

void game::test()
{
	while (true) {

		//////////////////////// Basic Shapes ///////////////////////////

		// // Circle
		// Circle* C = new Circle(this, { 600, 300 }, 100);
		// C->draw();

		// // Rectangle
		// Rect* R = new Rect(this, { 500, 300 }, 100, 50);
		// R->draw();
		// for (size_t i = 0; i < 10; i++)
		// {
		// R->move(UP);
		// R->move(RIGHT);
		// }
		// R->draw();

		// // Eq Tri
		// EquilateralTriangle* EqTri = new EquilateralTriangle(this, { 600, 300 }, 50);
		// EqTri->draw();
		// EqTri->rotate();
		// EqTri->draw();

		// // Ri Tri
		// RightTriangle* RiTri = new RightTriangle(this, { 200, 200 }, 100, 100);
		// RiTri->rotate();
		// RiTri->draw();

		//////////////////////// Composite Shapes ////////////////////////

		// // Cloud
		// Cloud* Cl = new Cloud(this, { 1050, 400 });
		// Cl->draw();

		// // House
		// House* H = new House(this, { 200, 300 });
		// H->draw();

		// // Tree
		// Tree* T = new Tree(this, { 900, 300 });
		// T->draw();

		// // Icecream
		// Icecream* I = new Icecream(this, { 750, 300 });
		// I->draw();

		// // Plane
		// Plane* P = new Plane(this, { 400, 300 });
		// P->draw();

		// // Car
		// Car* Ca = new Car(this, { 600,300 });
		// Ca->draw();
	}
}

void game::setStartClock(time_t duration)
{
	startClock = clock();
	countdownDuration = duration; // Set the countdown duration

}

time_t game::getStartClock()
{
	return startClock;

}

void game::updateTime()
{
	// Calculate elapsed time
	time_t elapsedTime = (clock() - getStartClock()) / CLOCKS_PER_SEC;
	time_t remainingTime = countdownDuration - elapsedTime;

	// Calculate minutes and seconds from remainingTime
	time_t min = remainingTime / 60;
	time_t sec = remainingTime % 60;

	// If time is up, set remainingTime to 0
	if (remainingTime <= 0) {
		min = 0;
		sec = 0;

	}

	// Update the display
	pWind->SetPen(LAVENDER);
	pWind->SetBrush(LAVENDER);
	pWind->DrawRectangle(780, 0, 780 + 65, 35);

	pWind->SetPen(BLACK);
	pWind->SetFont(15, BOLD, BY_NAME, "Arial");
	pWind->DrawString(780, 5, "Timer: " + std::to_string(min) + ":" + std::to_string(sec));
}

